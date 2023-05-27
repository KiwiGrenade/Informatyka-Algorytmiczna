/* GORC.C
   Goldberg - Radzik algorithm
   with detecting negative cycles
*/

node *spc (long n, node *node_first, node *source )

{

node   *i,          /* scanning node */
       *j,          /* node on the head of the arc */
       *k,          /* node on negative cycle */
       *node_stop;  /* fiction: node after the last in the network */

arc    *arc_ij,     /* current arc */
       *arc_stop;   /* the next arc after the last arc going from current node */

long long   dist_new,    /* distance to node_to via node_from */
       dist_i,      /* distance of node_from */
       r_cost;      /* arc reduced cost */

stack  new_pass,    /* stack for new pass */
       top_sort,    /* stack for topologocal sorting */
       pass;        /* stack for Bellmann-Ford pass */

int scanZero;

/* status of a node */ 
#define OUT_OF_STACKS  0
#define IN_NEW_PASS    1
#define IN_TOP_SORT    2
#define IN_PASS        3

//long   num_scans = 0;

/* initialization */

 INIT_STACK ( new_pass );
 INIT_STACK ( top_sort );
 INIT_STACK ( pass );

FOR_ALL_NODES ( i )
   { 
      i -> parent   = NNULL;
      i -> dist     = VERY_FAR;
      i -> status   = OUT_OF_STACKS;
      i -> scanZero   = 0;
   }

source -> parent = source;
source -> dist   = 0;

 PUSH ( new_pass, source );

source -> status = IN_NEW_PASS;

/* main loop */

while ( NONEMPTY_STACK ( new_pass ) ) {
  /* topological sorting */
  while ( NONEMPTY_STACK ( new_pass ) ) {
    POP ( new_pass, i );

    if (  i -> status == IN_NEW_PASS ) {
      /* looking for any arc with negative reduced cost outgoing from i
	 if any - start depth first search from i */
      
      dist_i   = i -> dist;
      
      FOR_ALL_ARCS_FROM_NODE ( i, arc_ij ) {
	if ( dist_i + arc_ij -> len
	     <
	     ( arc_ij -> head ) -> dist
	     )
	  break;
      }
      
      if ( arc_ij != arc_stop ) {
	i -> status  = IN_TOP_SORT;
	i -> current = i -> first;
	i -> negs    = 0;
	i -> scanZero = 0;
      }
      else
	i -> status = OUT_OF_STACKS;
    }

    if ( i -> status == IN_TOP_SORT ) {
      /* depth first search */

      while ( 1 ) {
	dist_i   = i -> dist;
	scanZero = i -> scanZero;
	
	FOR_ALL_ARCS_FROM_NODE_DFS ( i, arc_ij, i -> current ) {
	  j = arc_ij -> head;
	  r_cost = dist_i + arc_ij -> len - j -> dist;
	  
	  if ((r_cost < 0) ||
	      (scanZero && (r_cost == 0))) {
	    if ( j -> status < IN_TOP_SORT ) {
	      /* next node in DFS */
	      i -> current = arc_ij + 1;
	      PUSH ( top_sort, i );
		
	      j -> status  = IN_TOP_SORT;
	      j -> current = j -> first;
	      j -> negs    = i -> negs;
	      j -> scanZero = 0;
	      if ( r_cost < 0 ) j -> negs ++;
	      i = j;
	      
	      break;
	    }

	    if ( j -> status == IN_TOP_SORT ) {
	      /* negative or zero cycle is detected */
	      if ( r_cost < 0 || i -> negs > j -> negs ) {
		/* negative cycle is detected */
		j -> parent = i;
		/* marking negative cycle */
		while ( i != j ) {
		  POP ( top_sort, k );
		  i -> parent = k;
		  i = k;
		}
		// n_scans = n_scans;
		return i;
	      }
	    }
	    
	  }
	}
	
	if ( arc_ij == arc_stop ) {
	  if (i -> scanZero) {
	    /* done scanning i */
	    i -> status = IN_PASS;
	    PUSH ( pass, i );
	    n_scans ++;
	    
	    if ( NONEMPTY_STACK ( top_sort ) ) {
	      POP ( top_sort, i );
	    }
	    else
	      break;
	  }
	  else {
	    i -> scanZero = 1;
	    i -> current = i -> first;
	  }
	}
      }
    }
  } /* end of topological sorting */
  
  /* Bellman - Ford pass */

  while ( NONEMPTY_STACK (pass)) {
    n_scans ++;

    POP ( pass, i );
    i -> status = OUT_OF_STACKS;
    
    dist_i   = i -> dist;
    
    FOR_ALL_ARCS_FROM_NODE ( i, arc_ij ) {
      /* scanning arcs outgoing from  i  */
      
      j  = arc_ij -> head;
      dist_new = dist_i + ( arc_ij -> len );

      if ( dist_new <  j -> dist ) {
	j -> dist   = dist_new;
	j -> parent = i;
	
	if (  j -> status == OUT_OF_STACKS  ) {
	  PUSH ( new_pass, j );
	  j -> status = IN_NEW_PASS;
	}
      }
      
    } /* end of scanning  i  */
  } /* end of one pass */
 } /* end of the main loop */

//  n_scans = n_scans;
 return NNULL;
}
