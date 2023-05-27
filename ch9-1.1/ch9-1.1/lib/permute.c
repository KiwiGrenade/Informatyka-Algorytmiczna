#ifdef PERMUTE_NODES
#define ID(nd) (nodeArr[nd])
#else
#define ID(nd) nd
#endif

// generate random permutation of nodes
void randomPerm(long n, long *nodeIds, long *source)

{
  long i;
#ifdef PERMUTE_NODES
  long j, hold;
#endif
  
  for (i = 1; i <= n; i++) {
    nodeIds[i] = i;
  }
#ifdef PERMUTE_NODES
  for (i = 1; i <= n; i++) {
    j = nrand(n) + 1;

    hold = nodeIds[i];
    nodeIds[i] = nodeIds[j];
    nodeIds[j] = hold;
  }
#endif
  *source = nodeIds[*source];
  /*
  for (i = 1; i <= n; i++) {
    printf("c %ld -> %ld\n", i, nodeIds[i]);
  }
  */
}

