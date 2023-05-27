/* smartq.h  by Andrew Goldberg
   started 5/25/01
 */

#ifndef SMARTQ_H
#define SMARTQ_H

#include "nodearc.h"         // dfn of node and arc

#ifndef ulong
typedef unsigned long ulong; // to get that extra bit
#endif

class SP;                // defined in sp.h
class Stack;             // defined in stack.h
struct Level;            // defined below; defined here for Bucket

typedef struct Bucket {
   Node *pNode;          // pointer the the list of nodes at this level
   Level *pLevel;        // what level this bucket is on
} Bucket;

typedef struct Level {
  ulong cNodes;         // number of nodes currently stored at this level
  Bucket *rgBin;        // points to the cBuckets buckets at our level
  Bucket *pBucket;      // the current bucket at level i
  ulong digShift;       // shifting distance and the applying 
  ulong digMask;        // digMask gives the digit
} Level;

class SmartQ {
 private:
   Level *rgLevels;          // pointer to the first level
   Level *topLevel;          // pointer to the last levels
   Level *minLevel;          // levels below are empty
   ulong delta;              // number of buckets at each level
                             // except top level has 2 delta buckets
                             // must be a power of two
   ulong logDelta;           // base 2
   ulong topDelta;           // number of top level buckets
   ulong logTopDelta;        // base 2
   ulong logBottom;          // log of bottom level bucket width
                             // equal to floor of log_2(minArcLen)
   unsigned long long relBitMask;  // bits determining node position

   long long statEmpty;      // statistic: how many empty buckets we scanned
   long statExpandedNodes;   // statistic: how many nodes we expand out
   long statExpandedBuckets; // statistic: how many buckets we expand out of
   long statInsert;          // statistic: how many Insert operations
   long statPosEval;         // statistic: how many distToBucket operations
   
   Level *DistToLevel(long long *pDist);
   Bucket *DistToBucket(long long *pDist, Level *lev);

   Node *SortBucket(Level *pLevel);

   Stack *F;
   long long mu;

 public:
   SmartQ(long long *pMinArcLen, long long *pMaxArcLen, ulong cLevels, 
	  ulong logD, long n, Node *nodes);
   ~SmartQ();
   void Init();              // resets bucket indices.  Assumes buckets are OK
   void reInit();
#ifdef SINGLE_PAIR
   bool dijkstra(Node *source, Node *sink, SP *sp); // run dijkstra's algorithm
#else
   void dijkstra(Node *source, SP *sp);            // run dijkstra's algorithm
#endif
   void PrintStats(long tries);

   Node *Insert(Node *node, Bucket *bckNew);
   Node *Delete(Node *node, Bucket *bckOld);
   Node *RemoveMin();
   int InBucket(Node *node)        { return node->where == IN_BUCKETS; }
};

#endif
