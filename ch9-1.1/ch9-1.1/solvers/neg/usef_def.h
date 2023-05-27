/* -----  useful definitions for shortest paths ----- */

/* Total agreements:
   In all code of this library
long   n          - the number of node in the network;
long   m          - the number of arcs;
long   nmin       - the number of minimal node;
node*  node_first - pointer to the first node in the network;
node*  node_stop  - fiction: node after the last in the network;
arc*   arc_first  - pointer to the first arc;
arc*   arc_stop   - the next arc after the last arc going from current node
*/

#define NNULL             (node*)NULL

//#define VERY_FAR          1073741823
#define VERY_FAR          4611686018427387904LL

#define NODE_NUMBER(node) (long)( ( (node) - node_first ) + nmin )

#define ARC_NUMBER(arc)   (long)( (arc) - arc_first )

#define FOR_ALL_NODES( node )\
        node_stop = node_first + n ;\
        for ( node = node_first; node != node_stop; node++ )

#define FOR_ALL_ARCS_FROM_NODE( node, arc )\
        arc_stop = ( ( node ) + 1 ) -> first;\
        for ( arc = ( node ) -> first; arc != arc_stop; arc++ )

#define FOR_ALL_ARCS_FROM_NODE_DFS( node, arc, start )\
        arc_stop = ( ( node ) + 1 ) -> first;\
        for ( arc = start; arc != arc_stop; arc++ )
