// by Andrew Goldberg, january 12, 2006

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"random.c"

#define MAXLINE 100

/*

Takes two arguments, pMag, the magnitude of the perturbation, and
a seed.

Reads the graph from stdin and writes to stdout

For each node, generates a random number in [0, pMag).
For each arc (v,w), subtracts from the length the number for v
and ads the number of w.

*/
int main (int argc, char *argv[] )

{
  long pMag;
  long n, m;
  long long len;
  long seed;
  long v, w;
  long *pertArr;
  char inLine[MAXLINE];
  char prType[4];

  if (argc != 3) {
    fprintf(stderr, "ERROR: wrong number of arguments. See README\n");
    exit(1);
  }

  pMag = atol(argv[1]);
  seed = atol(argv[2]);

  init_rand(seed);


  do {
    if (gets(inLine) == NULL) {
      fprintf(stderr, "ERROR: no problem line\n");
      exit(1);
    }
  } while(inLine[0] != 'p');

  sscanf(inLine, "%*c %2s %ld %ld\n", prType, &n, &m);
  printf("%s\n", inLine);

  pertArr = (long *) calloc(n+1, sizeof(long));
  for (int i = 0; i < n; i++) {
    pertArr[i] = nrand(pMag);
  }

  for (int i = 0; i < m;) {
    if (gets(inLine) == NULL) {
      fprintf(stderr, "ERROR: not enough arc lines\n");
      exit(1);
    }
    if (inLine[0] != 'a') {
      printf("%s\n", inLine);
      continue;
    }
    i++;
    sscanf(inLine, "%*c %ld %ld %lld\n", &v, &w, &len);
    printf("a %ld %ld %lld\n", v, w, len - pertArr[v] + pertArr[w]);
  }

  free(pertArr);
  exit (0);
}



