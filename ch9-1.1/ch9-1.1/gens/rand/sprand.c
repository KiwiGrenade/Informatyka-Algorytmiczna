#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "values.h"
#include "random.c"
#include "permute.c"

/* generator of random networks for the shortest paths problem;
   extended DIMACS format for output */


// arguments: <nodes> <arcs> <low len> <high len> <seed>
int main (int argc, char *argv[] )

{
  long n, m;
  long long lL, hL;
  long seed;
  long i;
  long v, w;
  long *nodeArr;
  long source;

  n = atol(argv[1]);
  m = atol(argv[2]);
  lL = atoll(argv[3]);
  hL = atoll(argv[4]);
  seed = atol(argv[5]);

  init_rand(seed);

  source = 1;
  nodeArr = (long *) calloc(n+1, sizeof(long));
  randomPerm(n, nodeArr, &source);
  
  printf("c random graph n=%ld m=%ld lo=%lld hi=%lld seed=%ld\n",
	 n, m, lL, hL, seed);
  printf("p sp %ld %ld\n", n, m);

  // print cycle
  for (i = 1; i < n; i++)
    printf("a %ld %ld %lld\n", ID(i), ID(i+1), myRandom(lL, hL));
  printf("a %ld %ld %lld\n", ID(n), ID(1), myRandom(lL, hL));

  for (i = n+1; i <= m; i++) {
    do {
      v = 1 + nrand(n);
      w = 1 + nrand(n);
    } while (v == w);
    printf("a %ld %ld %lld\n", ID(v), ID(w), myRandom(lL, hL));
  }

  exit (0);
}



