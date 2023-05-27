/* -----   stacks definitions ----- */

typedef struct str_stack
           {
	     long     top;
             node   **arr;
	   }
             stack;

#define INIT_STACK( stack )\
{\
\
  stack.arr = (node**) calloc ( n, sizeof (node*) );\
  stack.top = -1;\
\
  if ( stack.arr == (node**) NULL )\
    exit ( 1 );\
}

#define NONEMPTY_STACK( stack )     ( stack.top >= 0 )

#define POP( stack, node )\
{\
node = stack.arr [ stack.top ];\
stack.top -- ;\
}

#define PUSH( stack, node )\
{\
  stack.top ++ ;\
  stack.arr [ stack.top ] = node;\
}\

