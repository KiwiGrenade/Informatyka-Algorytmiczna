/* -----   queues definitions ----- */
/* needs standard type "node" to be properly defined */

node *q_head,                    /* head of the queue */
     *q_tail,                    /* tail of the queue */
     *q_entry;                   /* entry to the middle of queue */

/* status of node regarding to queue */ 
#define OUT_OF_QUEUE   0
#define INACTIVE       1
#define IN_QUEUE       2
#define ACTIVE         2
#define NOT_ACTIVE     3
#define SCANNED_OUT    4
#define IN_QUEUE_AGAIN 5
#define SCANNED        6

#define INIT_QUEUE(source)\
{\
q_head = q_tail = source;\
source -> next   = NNULL;\
source -> status = IN_QUEUE;\
}

#define INIT_DQUEUE(source)\
{\
q_head = q_tail = source;\
q_entry = NNULL;\
source -> next   = NNULL;\
source -> status = IN_QUEUE_AGAIN;\
}

#define NONEMPTY_QUEUE           ( q_head != NNULL )

#define NODE_OUT_OF_QUEUE(node)  ( node -> status == OUT_OF_QUEUE )
#define NOT_IN_QUEUE(node)  ( node -> status < IN_QUEUE )

#define EXTRACT_FIRST(node)\
{\
node = q_head;\
node -> status = OUT_OF_QUEUE;\
q_head = q_head -> next;\
}

#define DEXTRACT_FIRST(node)\
{\
node = q_head;\
if ( q_head == q_entry ) q_entry = NNULL;\
q_head = q_head -> next;\
}

#define EXTRACT_FIRST_WITH_STATUS( node )\
{\
node = q_head;\
q_head = q_head -> next;\
}

#define INSERT_TO_QUEUE(node)\
{\
 if ( q_head == NNULL )\
   q_head = node;\
 else\
   q_tail -> next = node;\
\
 q_tail = node;\
 q_tail -> next = NNULL;\
 node -> status = IN_QUEUE;\
}

#define INSERT_TO_ENTRY(node)\
{\
  if ( q_entry != NNULL )\
    {\
      node  -> next = q_entry -> next;\
      q_entry -> next = node;\
      if ( q_entry == q_tail ) q_tail = node;\
    }\
  else\
    {\
       if ( q_head == NNULL ) q_tail = node;\
       node -> next = q_head;\
       q_head = node;\
    }\
   q_entry        = node;\
}\

#define MAKE_ACTIVE( v )\
{\
   if ( NODE_OUT_OF_QUEUE ( v ) )\
     INSERT_TO_QUEUE ( v )\
   else\
     v -> status = ACTIVE;\
}
