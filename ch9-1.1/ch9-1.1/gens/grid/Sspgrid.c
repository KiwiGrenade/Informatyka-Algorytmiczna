#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "values.h"

#include "random.c"
#include "permute.c"


/* generator of random networks for the shortest paths problem;
   extended DIMACS format for output */

int main (int argc, char *argv[] )

{
  long x, y;          // grid length and width
  long n, m;          // no. nodes and arcs
  long long lX, hX;   // arc length bounds in x dimention
  long long lY, hY;   // arc length bounds in y dimention  
  long seed;
  long i, j;
  long *nodeArr;
  long source;

  x = atol(argv[1]);
  lX = atol(argv[2]);
  hX = atoll(argv[3]);
  y = atol(argv[4]);
  lY = atoll(argv[5]);
  hY = atoll(argv[6]);
  seed = atol(argv[7]);

  init_rand(seed);
  
  printf("c grid graph x=%ld lX=%lld lY=%lld y=%ld lY=%lld hY=%lld seed=%ld\n",
	 x, lX, hX, y, lY, hY, seed);

  n = x * y;
  // source is handled differently, it does not participate in permutation
  source = n+1;
  nodeArr = (long *) calloc(n+2, sizeof(long));
  randomPerm(n, nodeArr, &source);

  m = 4*n - 2*(x+y) + y;
  printf("p sp %ld %ld\n", n+1, m);

  for (i = 1; i <= x; i++) {
    for (j = 1; j <= y; j++) {
      // go down
      if (j > 1)
	printf("a %ld %ld %lld\n", 
	       ID(y*(i-1) + j), ID(y*(i-1) + j - 1), myRandom(lY, hY));
      // go up
      if (j < y)
	printf("a %ld %ld %lld\n", 
	       ID(y*(i-1) + j), ID(y*(i-1) + j + 1), myRandom(lY, hY));
      //go left
      if (i > 1)
	printf("a %ld %ld %lld\n", 
	       ID(y*(i-1) + j), ID(y*(i-2) + j), myRandom(lX, hX));
      //go right
      if (i < x)
	printf("a %ld %ld %lld\n", 
	       ID(y*(i-1) + j), ID(y*(i) + j), myRandom(lX, hX));
    }
  }

  // source arcs
  for (j = 1; j <= y; j++)
    printf("a %ld %ld %d\n", 
	   n+1, ID(j), 0);

  exit (0);
}



