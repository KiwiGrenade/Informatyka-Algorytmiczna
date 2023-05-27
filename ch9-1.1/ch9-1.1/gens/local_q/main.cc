/* main.cc  by Andrew Goldberg
 *     Driver for all the sp algorithms.
 *
 */

#include <stdlib.h>       // for atoi
#include <stdio.h>        // for printf
#include <string.h>
#include <math.h>
#include "../../lib/random.c"
#include "sp.h"           // shortest-path class

extern int parse_gr( long *n_ad, long *m_ad, Node **nodes_ad, Arc **arcs_ad, 
		  long *node_min_ad, char *problem_name );
#define SZ_DIK_SMARTQ   "Dijkstra with Smart Queues"
#define SZ_DIK_MLB      "Dijkstra with Multi-Level Buckets"
#define SZ_BFS          "Breadth-First Search"

int main(int argc, char **argv)
{
   Arc *arcs;
   Node *nodes, *source = NULL;
#ifdef SINGLE_PAIR
   Node *sink = NULL;
#endif
   long n, m, nmin, nS, iT, nT, seed;
   char *szAlgorithm, gName[100], aName[100];
   FILE *aFile;
   double dist;
   long long maxArcLen, minArcLen;
   SP *sp;
   ulong cLevels;
   ulong logDelta;
   bool doBFS = false;
   long *s_array, *t_array;
   long range, sampleR;

#if (defined CHECKSUM) && (!defined SINGLE_PAIR)
   Node *node;
#endif

   if (argc != 5) {
     fprintf(stderr, 
	     "Usage: \"%s <file> <num. s> <log init. t rank> <seed>\"\n", argv[0]);
     exit(0);
   }

   strcpy(gName, argv[1]);
   strcat(gName, ".gr");

   fprintf(stderr, "Parsing...\n");
   parse_gr(&n, &m, &nodes, &arcs, &nmin, gName ); 
   fprintf(stderr, "          ...done\n");

   ArcLen(n, nodes, &minArcLen, &maxArcLen);      // other useful stats

   nS = atoi(argv[2]);
   iT = atoi(argv[3]); // log of initial t rank
   nT = (long) (log(n)/log(2)) - iT;

   s_array = (long*) calloc(nS+1, sizeof(long));
   if (s_array == NULL) {
     fprintf(stderr, "ERROR: can't allocate s_array\n");
     exit(1);
   }

   t_array = (long*) calloc(nS*nT+1, sizeof(long));
   if (t_array == NULL) {
     fprintf(stderr, "ERROR: can't allocate t_array\n");
     exit(1);
   }

   seed = atoi(argv[4]);
   init_rand(seed);

   // sanity check
   dist = (double) maxArcLen * (double) (n-1);
   if (dist > VERY_FAR) {
     fprintf(stderr, "Warning: distances may overflow\n");
     fprintf(stderr, "         proceed at your own risk!\n");
   }

   // figure out what algorithm to use
   cLevels = 0;
   logDelta = 0;
   szAlgorithm = SZ_DIK_SMARTQ;
#ifdef MLB
   szAlgorithm = SZ_DIK_MLB;
#endif

   sp = new SP(n, nodes, cLevels, logDelta, doBFS);

   if (doBFS) {  // get baseline timing
     dist = sp->BFS(source);

     ArcLen(n, nodes, &minArcLen, &maxArcLen);      // other useful stats
   
   }
   else {
     sp->init();

     dist = 0.0;

     // generate s's and t's
     for (int i = 0; i < nS; i++) {
       s_array[i] = nrand(n);
     }
     for (int j = 0; j < nT; j++) {
       range = 1 << (j+iT);
       for (int i = 0; i < nS; i++) {
	 sampleR = range + nrand(range);
	 if (sampleR > n) sampleR = n;
	 t_array[j + i*nT] = sampleR;
       }
     }
     
     for (int i = 0; i < nS; i++) {
       source = nodes + s_array[i];
       sp->initS(source);
       sp->sp(source, nT, t_array, i);
     }

     // output aux files
     for (int j = 0; j < nT; j++) {
       sprintf(aName, "%s.%ld.p2p", argv[1], j+iT);
       aFile = fopen(aName, "w");
       fprintf(aFile, "p aux sp p2p %ld\n", nS);
       for (int i = 0; i < nS; i++) {
	 fprintf(aFile, "q %ld %ld\n", s_array[i] + 1, t_array[j + i*nT] + 1);
       }
       fclose(aFile);
     }

   }

   sp->~SP();
   return 0;
}
