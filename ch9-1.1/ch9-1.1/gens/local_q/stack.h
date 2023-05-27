// stack.h  by craig silverstein.  started 11 february 1995.
//     Implements a stack with a fixed size.  Since this is so
//     trivial, everything is done inlined.  We separate this
//     mainly so we can have a stack class.  The data of the
//     stack are void * pointers; they must be explicitly
//     casted when popped.
//        We also let you (horrors!) iterate through a stack.  ITERATE
//     holds a static counter, it returns a new void * on each call
//     until it's done, when it returns a NULL and resets the static
//     counter to 0 for the next call to ITERATE.


#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <assert.h>      // make sure we don't overflow the stack.

#define NOT_IN_STACK    0
#define IN_STACK        1

#define STK_MIN(a,b)    ( (a) < (b) ? (a) : (b) )

class Stack {
private:
  void **data;
  long maxSize;
  long top;              // data[top-1] holds the top element
  long curr;             // used for iterate

public:
  Stack(long size)        { top = 0;  curr = 0; maxSize = size;
			    data = new void * [maxSize]; assert(data); }
  ~Stack()                { delete data; }
  void *Push(void *elt)   { assert(top+1<=maxSize); return (data[top++]=elt); }
  void *Pop()             { assert(top > 0);        return (data[--top]); }
  void Clear()            { top = 0; }
  int IsEmpty()           { return top == 0; }
  void *Iterate()         { if ( curr == top ) { curr = 0; return NULL; }
			    return data[curr++]; }
};

#endif
