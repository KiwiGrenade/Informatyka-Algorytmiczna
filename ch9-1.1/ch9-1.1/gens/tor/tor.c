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
  long long M;        // arc length bound
  long long L;
  long seed;
  long C;             // number of cycles
  long i, j;
  long long K;
  long *nodeArr;
  long source;
  int *cycleX;        // 0 if no cycle at this coordinate, 1 if cycle
  long *negY;         // in i-th position, Y coordinate of negative arc
                      // on i-th cycle
  long curCyc;

  if (argc != 6) {
    fprintf(stderr, "Usage: tor.exe x y M C seed\n");
    exit(1);
  }

  x = atol(argv[1]);
  y = atol(argv[2]);
  M = atoll(argv[3]);
  C = atol(argv[4]);
  seed = atol(argv[5]);

  init_rand(seed);
  
  printf("c tor graph x=%ld y=%ld M=%lld C=%ld seed=%ld\n",
	 x, y, M, C, seed);

  n = x * y;
  source = 1;
  nodeArr = (long *) calloc(n+1, sizeof(long));
  randomPerm(n, nodeArr, &source);
  
  cycleX =  (int *) calloc(x+1, sizeof(int));
  negY = (long *) calloc(C+1, sizeof(long));

  // determine where cycles go
  if (C <= n/2) {
    for (i = 1; i <= x; i++) {
      cycleX[i] =  0;
    }
    for (i = 1; i <= C; ) {
      K = myRandom(1, x);
      if (cycleX[K] !=  1) {
	cycleX[K] =  1;
	i++;
      }
    }
  }
  else {
    for (i = 1; i <= x; i++) {
      cycleX[i] =  1;
    }
    for (i = 1; i <= x-C; ) {
      K = myRandom(1, x);
      if (cycleX[K] !=  0) {
	cycleX[K] = 0;
	i++;
      }
    }
  }

  // generate negY's
  for (i = 1; i <= C; i++) {
    negY[i] = (long) myRandom(1, y);
  }

  m = 4*n;
  printf("p sp %ld %ld\n", n, m);

  curCyc = 0;
  for (i = 1; i <= x; i++) {
    if (cycleX[i] == 1) 
      curCyc++;

    for (j = 1; j <= y; j++) {
      // go down
      if (cycleX[i] == 0) {
	L = myRandom(0, M);
      }
      else {
	if (negY[curCyc] == j)
	  L = -(1 + M/2);
	else
	  L = 0;
      }
      if (j > 1) {
	printf("a %ld %ld %lld\n", 
	       ID(y*(i-1) + j), ID(y*(i-1) + j - 1), L);
      }
      else
	printf("a %ld %ld %lld\n", 
	       ID(y*(i-1) + j), ID(y*(i-1) + y), L);
      
      // go up
      if (j < y)
	printf("a %ld %ld %lld\n",
	       ID(y*(i-1) + j), ID(y*(i-1) + j + 1), myRandom(0,M));
      else
	  printf("a %ld %ld %lld\n",
		 ID(y*(i-1) + j), ID(y*(i-1) + 1), myRandom(0,M));

      //go left
      if ((cycleX[i] == 1) && (L <= 0))
	L = (1 + M/2);
      else
      L = myRandom(0, M);

      if (i > 1)
	printf("a %ld %ld %lld\n", 
	       ID(y*(i-1) + j), ID(y*(i-2) + j), L);
	else
	  printf("a %ld %ld %lld\n", 
		 ID(y*(i-1) + j), ID(y*(x-1) + j), L);
      
      //go right
      if ((cycleX[i] == 1) && (L <= 0))
	L = (1 + M/2);
      else
      L = myRandom(0, M);

      if (i < x)
	  printf("a %ld %ld %lld\n", 
		 ID(y*(i-1) + j), ID(y*(i) + j), L);
      else
	printf("a %ld %ld %lld\n", 
	       ID(y*(i-1) + j), ID(y*(0) + j), L);
    }
  }

  exit (0);
}



