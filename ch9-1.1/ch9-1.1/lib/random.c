#include "ll-core/include/LRandSource.h"

LRandSource *LRS;

void init_rand(long iSeed)

{
  LRS = LRandSource_New ((i4) iSeed);
}

long nrand (long n)

{
  return ((long) LRandSource_GetRandUI4(LRS, (ui4) 0, (ui4) (n-1)));
}


long long myRandom(long long lo, long long hi)

{
  
  return((long long) LRandSource_GetRandUI8(LRS, (ui8) lo, (ui8) hi));

}




