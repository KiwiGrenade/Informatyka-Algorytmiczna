#include <stdio.h>
#include <stdlib.h>
#include "LFile.h"
#include "LException.h"

int main (int argc, char** argv)
{
	LFile *infile;
	FILE *outfile;
	ui4 insize, i;
	ui4 source, target;

	/*command line help...*/
	if (argc < 3) 
	{
        	printf("Usage: inFile outFile\n");
        	return 0;
	} 

	/*opens input file...*/
	Try
		infile=LFile_Open (argv[1], LFile_READ);
	CatchAny
	{
		printf ("Could not open input file!\n");
		return 0;
	}

	/*opens output file...*/
	outfile=fopen (argv[2], "w");
	if (outfile==NULL)
	{
		printf ("Could not open output file!\n");
		LFile_Close (&infile);
		return 0;
	}

	/*gets input file size...*/
	insize=LFile_GetSize (infile);

	for (i=0; i<insize; i=i+8)
	{
		/*reads endpoints...*/
		LFile_ReadN4 (infile, &source);
		LFile_ReadN4 (infile, &target);
		/*writes string...*/
		fprintf (outfile, "%d %d\n", source, target);
	}

	/*closes files...*/
	LFile_Close (&infile);
	fclose (outfile);

	return 0;
}
