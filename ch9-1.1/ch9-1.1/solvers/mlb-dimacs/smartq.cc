/* smartq.cc by Andrew Goldberg
 */

#include <stdlib.h>
#include <stdio.h>                // has stderr, etc.
#include <string.h>               // has memset
#include "stack.h"
#include "sp.h"
#include "assert.h"

#define NEXT(pNode)          ( (pNode)->sBckInfo.next )
#define PREV(pNode)          ( (pNode)->sBckInfo.prev )
#define BUCKET(pNode)        ((Bucket *)((pNode)->sBckInfo.bucket))
#ifndef MLB
#define CALIBER(pNode)       ( (pNode)->sBckInfo.caliber )
#endif

#ifdef ALLSTATS                        // expensive stats to calculate
#define EMPTY_BUCKET              statEmpty++
#define EXPANDED_NODE             statExpandedNodes++
#define EXPANDED_BUCKET           statExpandedBuckets++
#define INSERT_TO_BUCKET          statInsert++
#define POS_EVAL                  statPosEval++
#else
#define EMPTY_BUCKET              
#define EXPANDED_NODE             
#define EXPANDED_BUCKET           
#define INSERT_TO_BUCKET
#define POS_EVAL
#endif

#define LOW_LEVEL_BUCKET_SIZE(minArcLen) ( (minArcLen) > 0 ? (minArcLen) : 1 )

//------------------------------------------------------------
// SmartQ::Init()
// SmartQ::SmartQ()
// SmartQ::~SmartQ()
//     Initialization involves mostly allocating space for the
//     buckets.  The number of buckets we need is determined by
//     the maximum arc length (which is how many buckets ahead
//     we must be able to go in one step) and the number of
//     bucket levels.  We thus figure out the number of buckets
//     at each level as well.
//        Deinitialization merely deleted the buckets.  We crash
//     if there's not enough memory.
//        Init() resets indices.  It must be done each time we
//     want to use the buckets, as opposed to Bucket(), which
//     allocates memory and need only be done once.
//------------------------------------------------------------

void SmartQ::Init()
{
   Level *pLevel;
   ulong iBucket;

#ifndef MLB
   F->Clear();
#endif
   for ( pLevel = rgLevels; pLevel <= topLevel; pLevel++ ) {
     pLevel->cNodes = 0;
     pLevel->pBucket = pLevel->rgBin;              // curr bucket is leftmost
     if (pLevel != topLevel)
       for (iBucket = 0; iBucket < delta; iBucket++)
	 pLevel->rgBin[iBucket].pNode = NULL;
     else
       for (iBucket = 0; iBucket < topDelta; iBucket++)
	 pLevel->rgBin[iBucket].pNode = NULL;
   }
   minLevel = topLevel;

   statEmpty = 0;
   statExpandedNodes = 0;
   statExpandedBuckets = 0;
   statInsert = 0;
   statPosEval = 0;
}

//reInit is same as Init but does not clear statistics
void SmartQ::reInit()
{
   Level *pLevel;
   ulong iBucket;

#ifndef MLB
   F->Clear();
#endif
   for ( pLevel = rgLevels; pLevel <= topLevel; pLevel++ ) {
     pLevel->cNodes = 0;
     pLevel->pBucket = pLevel->rgBin;              // curr bucket is leftmost
     if (pLevel != topLevel)
       for (iBucket = 0; iBucket < delta; iBucket++)
	 pLevel->rgBin[iBucket].pNode = NULL;
     else
       for (iBucket = 0; iBucket < topDelta; iBucket++)
	 pLevel->rgBin[iBucket].pNode = NULL;
   }
   minLevel = topLevel;

}

SmartQ::SmartQ(long long *pMinArcLen, long long *pMaxArcLen, 
	       ulong cLevels, ulong logD, long n, Node *nodes)
{
  ulong i;
  Level *pLevel;
#ifndef MLB
  Arc *lastArc, *arc;
  Node *currentNode;
#endif
  long long maxArcLen, minArcLen;
  ulong logMax;

  maxArcLen = *pMaxArcLen;
  minArcLen = *pMinArcLen;
  logDelta = logD;

  F = new Stack(n);
#ifndef MLB  
  // compute calibers
  for (currentNode = nodes; currentNode < nodes + n; currentNode++)
    CALIBER(currentNode) = VERY_FAR;
  
  for (currentNode = nodes; currentNode < nodes + n; currentNode++) {
    lastArc = (currentNode + 1)->first - 1;
    for (arc = currentNode->first; arc <= lastArc; arc++) 
      if (CALIBER(arc->head) > arc->len)
	CALIBER(arc->head) = arc->len;
  }
#endif
  
  // compute logBottom = floor(log_2(minArcLen))

  logBottom = 0;
  while ((long long) 1 << logBottom < minArcLen)
    logBottom++;

  // exactly one of #levels, logDelta is specified; compute the other
  // first compute logMax such that 2^logMax > maxArcLen

  logMax = 0;
  do
    logMax++;
  while (((long long) 1 << logMax) <= maxArcLen);

  if (cLevels > 0) {
    // compute delta and logDelta
    // delta is the smallest power of 2 such that if
    // k is the number of levels, 
    // then delta^k * minArcLen >= 2^logMax > maxArcLen

    logDelta = 1;
    while (logDelta * cLevels + logBottom < logMax)
      logDelta++;
  }
  else 
    if (logDelta > 0) { // logDelta specified
      // compute the smallest number of levels, k such that
      // delta^k * minArcLen >= 2^logMax > maxArcLen

      while (logDelta * cLevels + logBottom < logMax)
	cLevels++;

    }
    else {
      // optimize cLevels and delta for the worst case
      // roughly we want RHO*cLevels = delta
      // let rho = log(RHO)
      ulong rho = 4; // adjust to your taste

      if (logMax - logBottom <= rho) {
	cLevels = 1;
	logDelta = logMax - logBottom;
	assert(logDelta > 0);
      }
      else {
	logDelta = rho;
	cLevels = 1 << (logDelta - rho); // = delta/RHO
	while (logDelta * cLevels + logBottom < logMax) {
	  logDelta++;
	  cLevels = 1 << (logDelta - rho); // = delta/RHO
	}
	// but cLevels and logDelta may be too big
	while (logDelta * cLevels + logBottom >= logMax) {
	  cLevels--;
	}
	cLevels++;

	while (logDelta * cLevels + logBottom >= logMax) {
	  logDelta--;
	}
	logDelta++;
      }
    }

#ifndef MLB
  logTopDelta = logDelta + 2;
#else
  logTopDelta = logDelta + 1;
#endif

  relBitMask = 0;
  for (i = 1; i <= (cLevels-1) * logDelta + logTopDelta; i++)
    relBitMask = 1 + (relBitMask << 1);

  delta = 1 << logDelta;
  topDelta = 1 << logTopDelta;

  // initialize levels
  rgLevels = new Level[cLevels+1]; // a pointer may run one over topLevel
  assert(rgLevels);
  topLevel = rgLevels + cLevels-1;

  for (pLevel = rgLevels; pLevel < topLevel; pLevel++) {
    pLevel->rgBin = new Bucket[delta];
    for (i = 0; i < delta; i++)
      pLevel->rgBin[i].pLevel = pLevel;   // store level info
    // do shifts and masks
     pLevel->digShift = logBottom + logDelta * (pLevel - rgLevels);
     // set relevant bit mask
     pLevel->digMask = 0;
     for (i = 0; i < logDelta; i++)
       pLevel->digMask = 1 + ((pLevel->digMask) << 1);
     
  }
  // now the top level
  topLevel->rgBin = new Bucket[topDelta];
  for (i = 0; i < topDelta; i++)
    topLevel->rgBin[i].pLevel = topLevel;   // store level info
  topLevel->digShift = logBottom + logDelta * (topLevel - rgLevels);
  topLevel->digMask = 0;
  for (i = 0; i < logTopDelta; i++)
    topLevel->digMask = 1 + ((topLevel->digMask) << 1);
  
  Init();
}

SmartQ::~SmartQ()
{
   Level *pLevel;

   for ( pLevel = rgLevels; pLevel <= topLevel; pLevel++ )
      delete pLevel->rgBin;
   delete rgLevels;
   F->~Stack();
}

//------------------------------------------------------------
// SmartQ::DistToLevel()
//   use node's distance and mu to find node's level
//------------------------------------------------------------

Level *SmartQ::DistToLevel(long long *pDist)
{
  Level *lev;
  long long tDist, tMu;

  assert(mu <= *pDist);
  tDist = (*pDist >> logBottom) & relBitMask;
  tMu = (mu >> logBottom) & relBitMask;

  lev = rgLevels;
  while (lev < topLevel) {
    tDist = tDist >> logDelta;    
    tMu = tMu >> logDelta;    
    if (tDist != tMu)
      lev++;
    else
      break;
  }
  return(lev);
}


//------------------------------------------------------------
// SmartQ::DistToBucket()
//   use node's distance and level to find node's bucket
//------------------------------------------------------------

Bucket *SmartQ::DistToBucket(long long *pDist, Level *lev)

{

  POS_EVAL;
  return (lev->rgBin + 
	  (((ulong) ((*pDist) >> (lev->digShift)))
	   & (lev->digMask)));
}

//------------------------------------------------------------
// SmartQ::Insert()
// SmartQ::Delete()
//     This takes a node and removes it from a bucket or
//     adds it to a bucket.  We update level statistics.
//     Both insert and delete RETURN the node passed to them.
//------------------------------------------------------------

Node *SmartQ::Insert(Node *node, Bucket *bckNew)
{
  INSERT_TO_BUCKET;
  //   printf(">>>Inserting d %lld lev %d buck %d\n",
  //   	 node->dist, bckNew->pLevel - rgLevels, bckNew - bckNew->pLevel->rgBin);
  node->sBckInfo.bucket = bckNew; // where we live, now
  //  BUCKET(node) = bckNew;          // where we live, now
  if ( bckNew->pNode == NULL )    // we're the first one in the bucket
    {
      bckNew->pNode = NEXT(node) = PREV(node) = node;    // a cycle of length 1
    }
  else                            // insert us in cycle, before first
    {
      PREV(node) = PREV(bckNew->pNode);
      NEXT(node) = bckNew->pNode;
      NEXT(PREV(bckNew->pNode)) = node;
      PREV(bckNew->pNode) = node;
    }
  
  node->where = IN_BUCKETS;
  bckNew->pLevel->cNodes++;      // another node at this level
  if (bckNew->pLevel->cNodes == 1) { // set pBucket
    bckNew->pLevel->pBucket = DistToBucket(&mu, bckNew->pLevel);
  }

  if (minLevel > bckNew->pLevel) {
    minLevel = bckNew->pLevel;
  }

  return node;
}

Node *SmartQ::Delete(Node *node, Bucket *bckOld)
{
  assert( BUCKET(node) == bckOld );
  if ( NEXT(node) == node )    // we're the last one in the bucket
    {
      bckOld->pNode = NULL;     // (nodes loop around to form a cycle)
    }
  else                         // update people around us
    {
      NEXT(PREV(node)) = NEXT(node);
      PREV(NEXT(node)) = PREV(node);
      bckOld->pNode = NEXT(node);    // in case node was = pNode.  Can't hurt.
    }
  assert(bckOld->pLevel->cNodes > 0);
  bckOld->pLevel->cNodes--;
  node->where = IN_NONE;       // no longer in buckets
  return node;
}

//------------------------------------------------------------
// SmartQ::SortBucket()
//  First examine all nodes in the bucket and find the minimum
//  The minimum distance node will be returned and mu set to its dist
//  Other nodes in the bucket will be either
//    inserted into F if possible
//    or inserted into B w.r.t. the new mu
//------------------------------------------------------------

Node *SmartQ::SortBucket(Level *pLevel)
{
  Node *pNode, *nextNode, *ans;
  Bucket *bckNew = NULL;      // the bucket we insert pNode into
  long long dMin;

  assert(pLevel != rgLevels);
  EXPANDED_BUCKET;
  pNode = pLevel->pBucket->pNode;         // the bucket we're sorting
  assert(pNode != NULL);
  NEXT(PREV(pNode)) = NULL;               // turn our ring into a list

  // find minimum
  ans = pNode;
  dMin = pNode->dist;
  for (pNode = NEXT(pNode); pNode; pNode = nextNode ) { 
    // go through our list of nodes
    nextNode = NEXT(pNode);
    if (pNode->dist < dMin) {
      dMin = pNode->dist;
      ans = pNode;
    }
  }

  //   update mu
  assert(mu <= ans->dist);
  // if logBottom > 0, need to erase last bits
  mu = (ans->dist >> logBottom) << logBottom;
  
  
  // sort
  pNode = pLevel->pBucket->pNode;
  pLevel->pBucket->pNode = NULL;          // remember to bookkeep now
  for (;
       pNode;
       pNode = nextNode) {
    nextNode = NEXT(pNode);

    pLevel->cNodes--;
    EXPANDED_NODE;               // we've moved another node
    if (pNode == ans) continue;  // do not insert answer
#ifndef MLB    
    if (pNode->dist <= mu + CALIBER(pNode)) {
      pNode->where = IN_F;
      F->Push(pNode);
    }
    else {
#endif
      assert(pLevel > rgLevels);
      bckNew = DistToBucket(&(pNode->dist),
			    DistToLevel(&(pNode->dist)));
      assert(bckNew->pLevel < pLevel);
      Insert(pNode, bckNew);     // Insert increases cNodes
#ifndef MLB
    }
#endif
  }

  assert(ans != NULL);
  return ans;
}

//------------------------------------------------------------
// SmartQ::RemoveMin()
//   Find the lowest nonempty level and the fist nonempty bucket at
//   this level.
//   If the level is zero remove a node from the bucket 
//   and update mu
//   Otherwise sort nodes in the bucket, also updating mu 
//   and removing min
//------------------------------------------------------------

Node *SmartQ::RemoveMin()
{
  //   Bucket *pBucket;            // bucket holding the min node
  Level *pLevel;
  Node *ans;

  while ((!minLevel->cNodes) && (minLevel <= topLevel))
    minLevel++;

  if (minLevel > topLevel) {
    minLevel = topLevel;
    return NULL;
  }

  pLevel = minLevel;
  assert(pLevel->cNodes);

  // find first nonempty bucket
  if (pLevel->pBucket->pNode == NULL) {
    if (pLevel < topLevel) {
      assert(DistToBucket(&mu,  pLevel) == pLevel->pBucket);
      do {
	EMPTY_BUCKET;
	(pLevel->pBucket)++;
      } while (pLevel->pBucket->pNode == NULL);
      assert(pLevel->pBucket - pLevel->rgBin < (long) delta);
    }
    else
      do {
	EMPTY_BUCKET;
	if (pLevel->pBucket - pLevel->rgBin < (long) topDelta - 1)
	  (pLevel->pBucket)++;
	else
	  pLevel->pBucket = pLevel->rgBin;
      } while (pLevel->pBucket->pNode == NULL);
  }
  
  assert(pLevel->pBucket != NULL);
  // do bottom level specially
  if (pLevel == rgLevels) {
    ans = Delete(pLevel->pBucket->pNode, pLevel->pBucket);
    //   update mu
    assert(mu <= ans->dist);
    // if logBottom > 0, need to erase last bits
    mu = (ans->dist >> logBottom) << logBottom;
  }
  else { 
    // do other levels all the same.
    ans = SortBucket(pLevel); // this updates mu
  }
  return(ans);
}

//------------------------------------------------------------
// SmartQ::PrintStats()
//     Prints stats specific to bucket implementation: how many
//     empty buckets we scan over, how many nodes we move from
//     one level to another, how many buckets we expand,
//     how many nodes, when put into a bucket, are the first
//     in the bucket, and how many nodes, when removed from
//     a bucket, are the last in a bucket.  We only print
//     these things when ALLSTATS is true.
//------------------------------------------------------------

void SmartQ::PrintStats(long tries)
{
#ifdef ALLSTATS
   printf("c Empty Buckets (ave): %10lld     \n", statEmpty);
   printf("c Expanded Nodes(ave): %12.1f     Expanded Buckets (ave): %8.1f\n",
	  (float) statExpandedNodes/ (float) tries, 
	  (float) statExpandedBuckets/ (float) tries);
   printf("c Bucket inserts (ave): %11.1f     Position evals (ave): %10.1f\n",
	  (float) statInsert/ (float) tries, 
	  (float) statPosEval/ (float) tries);
#endif
}

/* Smart dijsksta uses node calibers to put nodes
   into the set F of nodes with exact distances instead of the buckets.
   Nodes in F have priority when the next node to be scanned is chosen.

   Multi-level buckets do not use F.

   For single-pair, dijkstra returns false if the sink is not NULL and 
   is not reached
 */

#ifdef SINGLE_PAIR
bool SmartQ::dijkstra(Node *source, Node *sink, SP *sp)
#else
void SmartQ::dijkstra(Node *source, SP *sp)
#endif
{
   Node *currentNode, *newNode;   // newNode is beyond our current range
   Arc *arc, *lastArc;            // last arc of the current node
   Bucket *bckOld, *bckNew;
#ifdef SINGLE_PAIR
   bool reached;
#endif

   reInit();                        // reset indices
   mu = 0;
   sp->curTime++;
   source->tStamp = sp->curTime;

#ifdef SINGLE_PAIR
   if (source == sink) return(true);
   if (sink == NULL)
     reached = true;
   else
     reached = false;
#endif

#ifndef MLB
   source->where = IN_F;
   F->Push(source);
#else
   bckNew = DistToBucket(&(source->dist), DistToLevel(&(source->dist)));
   Insert(source, bckNew);
#endif

   do
   {
     if (F->IsEmpty()) {
       currentNode = RemoveMin();
       if (currentNode == NULL) {
	 assert(F->IsEmpty());
	 break;
       }
#ifdef SINGLE_PAIR
       // check if done
       if (currentNode == sink) {
	 reached = true;
	 break;
       }
#endif
     }
     else {
       currentNode = (Node *) F->Pop();
#ifdef SINGLE_PAIR
       // check if done
       if (currentNode == sink) {
	 reached = true;
	 break;
       }
       // do not need to search past sink distance
       if ((sink != NULL) && (sink->tStamp == sp->curTime) &&
	   (currentNode->dist >= sink->dist))
	 continue;
#endif
     }
     
     //     printf(">>>scanning d %lld (mu %lld)\n", currentNode->dist, mu);
     sp->cScans++;
     assert(currentNode->tStamp == sp->curTime);
     currentNode->where = IN_SCANNED;
     // scan node
     lastArc = (currentNode + 1)->first - 1;
     for ( arc = currentNode->first; arc <= lastArc; arc++ )
      {
	 newNode = arc->head;                      // where our arc ends up
	 if (newNode->tStamp != sp->curTime)
	   sp->initNode(newNode);
	 if ( currentNode->dist + arc->len < newNode->dist )
	 {
	   assert(newNode->where != IN_F);
	   assert(newNode->where != IN_SCANNED);
	   bckOld = BUCKET(newNode);       // NULL if node not in a bucket
	   newNode->dist = currentNode->dist + arc->len; // we're shorter
	   newNode->parent = currentNode;                // update sp tree

#ifndef MLB
	   if (newNode->dist <= mu + CALIBER(newNode)) {
	     // the node must go to F
	     if ( InBucket(newNode) ) {

	       Delete(newNode, bckOld);
	     }
#ifdef SINGLE_PAIR
	     if (newNode == sink) {
	       reached = true;
	       break;
	     }
	     // do not need to search past sink distance
	     if ((sink != NULL) && (sink->tStamp == sp->curTime) &&
		 (newNode->dist >= sink->dist))
	       continue;
#endif
	     // note that newNode cannot be in F
	     newNode->where = IN_F;
	     F->Push(newNode);
	   }
	   else {
#endif
	     // relocate the node in B if needed
	     bckNew = DistToBucket(&(newNode->dist),
				   DistToLevel(&(newNode->dist)));
	     if ( bckOld != bckNew ) {           // we need to move the node
	       if ( InBucket(newNode) ) {        // a move, not an insert
		 Delete(newNode, bckOld);
	       }
	       Insert(newNode, bckNew);
	       sp->cUpdates++;
	     }
#ifndef MLB
	   }
#endif
	 }
      }
   } while (1);

#ifdef SINGLE_PAIR
   return(reached);
#endif
}

