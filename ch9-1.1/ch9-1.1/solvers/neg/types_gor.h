/* definitions for GOR */

typedef  /* arc */
   struct arc_st
{
   long              len;            /* length of the arc */
   struct node_st   *head;           /* head node */
}
  arc;

typedef  /* node */
   struct node_st
{
   arc              *first;           /* first outgoing arc */
   arc              *current;         /* current arc in DFS */
   long long         dist;	      /* tentative shortest path length */
   struct node_st   *parent;          /* parent pointer */
   long              negs;            /* number of negative arcs on the way to
                                         the node */
   int               status;          /* status of node */
   int               scanZero;        /* should we look at zero reduced cost 
					 arcs? */
} node;
