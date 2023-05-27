
#include <stxxl>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/param.h>
#include <sys/times.h>

typedef unsigned char byte;

using stxxl::syscall_file;
using stxxl::file;

int main (int argc, char *argv[])
{
	unsigned int theBlockSize, theNumBlocks;
	unsigned int i, j;
	int theCheckSum;
	unsigned int theIndex;
	float theRandom;

	/*time structs...*/
	struct tms theTMS_begin, theTMS_end;
	
	//command line help...
	if (argc<3)
	{
		printf ("Usage: blockpass.exe filename blocksize\n");
		return 0;
	}

	//block size...
	theBlockSize=atoi (argv[2]);
	theBlockSize=theBlockSize*1024;
	printf ("Block size: %d bytes\n", theBlockSize);

	//generates random seed...
	srand ((unsigned)time (NULL));

	//opens file...
	syscall_file theFile (argv[1], file::RDONLY);

	//maps vector...
	stxxl::vector<byte> theVector (&theFile);
	//creates constant reference in order to avoid writes!!!
	const stxxl::vector<byte> & theCVector=theVector;

	//computes number of blocks...
	theNumBlocks=theCVector.size ()/theBlockSize;
	printf ("Number of blocks: %d\n", theNumBlocks);

	/*fetches initial times...*/
	times (&theTMS_begin);

	//scans vector...
	for (i=0; i<theNumBlocks; i++)
	{
		//generates random number in [0..1[
		theRandom=rand ()/(RAND_MAX+1.0);
		//converts it to an index...
		theIndex=(unsigned int)(theRandom*theNumBlocks);
		//accesses selected block through constant reference...
		for (j=theIndex*theBlockSize; j<(theIndex*theBlockSize)+theBlockSize; j++)
			theCheckSum=theCheckSum+theCVector[j];

		if (i%100==0)
		{
			printf ("%d ", i);
			fflush (stdout);
		}
	}

	/*fetches final times...*/
	times (&theTMS_end);

	//prints results...
	printf ("Block scan completed.\n");
	printf ("User time: %f seconds\n", (float)((theTMS_end.tms_utime)-(theTMS_begin.tms_utime))/HZ);
	printf ("System time: %f seconds\n", (float)((theTMS_end.tms_stime)-(theTMS_begin.tms_stime))/HZ);
	
	return 0;
} 
