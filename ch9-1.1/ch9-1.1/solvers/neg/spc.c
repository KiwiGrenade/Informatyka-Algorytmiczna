/* Driver for general shortest path/negative cycle algorithms */
/* by Andrew Goldberg */

/* Functions for constructing shortest path tree:
   bfct.c   - Bellmann-Ford algorithm + traversing the upper brunch (Tarjan)
   gorc.c   - topological sorting algorithm (Goldberg-Radzik)
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* statistics */
long n_scans;

/* types_### -  node & arc structures */
/* queue.h   - operation with queues  *
/* stack.h   - operations with stacks */

/* some useful definitions to simlify text */
#include "usef_def.h"

#ifdef bfct
#include "types_simp.h"
#include "queue.h"
#include "bfct.c"
#endif

#ifdef gorc
#include "types_gor.h"
#include "stack.h"
#include "gorc.c"
#endif

/* parser for reading extended DIMACS format input and transforming the
   data to the internal representation */
#include "parser_gr.cc"
#include "parser_ss.cc"

/* function 'timer()' for mesuring processor time */
#include "timer.c"

// one argument means find a negative cycle
// two arguments means take sources in auxilary file
main (int argc, char **argv)

{

  float   tm;                     /* running time */
  char gName[100], aName[100], oName[100];

  arc     *arc_first,            /* first arc */
    *arc_stop,             /* stop arc for scans */
    *ta;                   /* current arc */

  node    *node_first,           /* first node */
    *node_stop,            /* after the last node */
    *source,               /* root of the tree */
    *k,                    /* current node */
    *i,                    /* current node */
    *point;                /* NULL if no negative cycle detected
			      or a node on the negative cycle */
  
  long    n,                     /* number of nodes */
    m,                     /* number of arcs  */
    l_cycle = 0;           /* number of arcs in negative cycle */

  int cycleDetection;      /* 1 for cycle detection problem, 0 ow. */

#ifdef CHECKSUM  
  long long int  sum_d = 0;   /* control sum for solution */
#endif

  long long int len_c = 0,    /* length of negative cycle */
    l_min;
  
  node    *dummyNode;         /* for sentinel uses */

  FILE *oFile;

  long minLen, maxLen;

   long nmin, nQ;
   long *source_array=NULL;

  
   fprintf(stderr, "c SPC DIMACS Challenge vestion\nc\n");

  if ((argc < 3) || (argc > 4)) {
    fprintf(stderr, 
	    "Usage: \"%s <graph file> [<aux file>] <out file>\"\n",
	    argv[0]);
    exit(0);
  }

  /* if no auxilary file, cycle detection problem */
  cycleDetection = (argc == 3);
  
  strcpy(gName, argv[1]);
  if (!cycleDetection) {
    strcpy(aName, argv[2]);
    strcpy(oName, argv[3]);
  }
  else
    strcpy(oName, argv[2]);

  oFile = fopen(oName, "a");

  dummyNode = (node *) calloc(1, sizeof(node));

  printf("c Parsing...\n");

  if (!cycleDetection) {
    parse_gr(&n, &m, &node_first, &arc_first, &nmin, gName, 0); 
    parse_ss(&nQ, &source_array, aName);
  }
  else {
    parse_gr(&n, &m, &node_first, &arc_first, &nmin, gName, 1); 
    nQ = 1;
  }

  printf("c           done parsing\n");

  if (!cycleDetection)
    fprintf(oFile, "f %s %s\n", gName, aName);
  else
    fprintf(oFile, "f %s\n", gName);

  minLen = node_first->first->len;
  maxLen = minLen;

  FOR_ALL_NODES(k) {
    FOR_ALL_ARCS_FROM_NODE(k,ta) {
      if (ta->len > maxLen)
	maxLen = ta->len;
      if (ta->len < minLen)
	minLen = ta->len;
    }
  }

  fprintf(oFile, "g %ld %ld %ld %ld\n", n, m, minLen, maxLen);

  tm = timer(); // start timing

  for (int i = 0; i < nQ; i++) {

    if (!cycleDetection)
      source = node_first + source_array[i] - 1;
    else
      source = node_first + n - 1;

    point = spc ( n, node_first, source );
    
#ifdef CHECKSUM
    if ( point == NNULL ) {
      FOR_ALL_NODES ( k ) {
	if ( k -> parent != NNULL )
	  sum_d += (k -> dist);
      }
      fprintf(stderr, "d %lld\n", sum_d);
      fprintf(oFile, "D %d\n", 0);  /* no negative cycle */
      fprintf(oFile, "d %d %lld\n", (source - node_first) + 1, sum_d);
    }
    else {
      k = point;
      fprintf(oFile, "D %d\n", 1);  /* negative cycle */
      do {
	node *node_i;
	l_cycle ++ ;
	node_i = k -> parent;

	l_min = VERY_FAR;
	FOR_ALL_ARCS_FROM_NODE ( node_i, ta ) {
	  if ( ( ta -> head ) == k && ( ta -> len ) < l_min )
	    l_min = ta -> len;
	}
	len_c += l_min;
	
	k = node_i;
      } while ( k != point );
      sum_d = len_c;
      printf("c Negative cycle detected\n");
      printf ("c Negative cycle arcs:   %10ld\n", l_cycle );
      printf ("c Negative cycle length: %10.0d\n", len_c );
#ifdef PRINT_CYCLE
      printf ("c Negative cycle:\n");
      k = point;
      do {
	printf ("c %7ld\n", NODE_NUMBER ( k ) );
	k = k -> parent;	      
      } while ( k != point );
#endif
    }
#endif
  }

  tm = timer() - tm;

#ifndef CHECKSUM  
  fprintf(stderr,"c Nodes: %24ld       Arcs: %22ld\n",  n, m);
  if (!cycleDetection) {
    fprintf(stderr,"c Trials: %23ld\n", nQ);
  }
    fprintf(stderr,"c Scans (ave):    %18.2f\n",
	    (float) n_scans / (float) nQ);
    fprintf(stderr,"c Time (ave, ms): %18.2f\n", 
	    1000.0 * tm/(float) nQ);

    fprintf(oFile,"v %f\n",
	    (float) n_scans / (float) nQ);
    fprintf(stderr,"t %f\n", 1000.0 * tm/(float) nQ);

#endif

    fclose(oFile);
}
