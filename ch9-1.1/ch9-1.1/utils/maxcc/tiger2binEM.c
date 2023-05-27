#include <stdio.h>
#include <stdlib.h>
#include "LFile.h"
#include "LString.h"

#define BUF_SIZE 16384

int main (int argc, char** argv)
{
	LFile *outfile;
	i1* theToken;
	ui4 endpoint;
	
	FILE *f;
	char buffer[BUF_SIZE];
	int i, j;

	if (argc < 3) {
        printf("Usage: inFile outFile\n");
        exit(1);
	}
	
	//opens source file...
	f=fopen (argv[1], "r");
	if (f!=NULL)
		printf ("%s successfully opened\n", argv[1]);
	else
	{
		printf("failed to open %s\n", argv[1]);
		exit(1);
	}

	//opens destination file...
	outfile=LFile_Open (argv[2], LFile_WRITE);

	//writes 'c'...
	LFile_WriteString (outfile, "c\n");

	//gets number of nodes...
	fgets (buffer, BUF_SIZE, f);
	j=atoi (buffer);
	printf ("Number of nodes: %d\n", j);

	//writes number of nodes...
	LFile_WriteString (outfile, buffer);
	
	//skips nodes...
	for (i=0; i<j; i++)
		fgets (buffer, BUF_SIZE, f);
	
	//gets number of arcs...	
	fgets (buffer, BUF_SIZE, f);
	j=atoi (buffer);
	printf ("Number of arcs: %d\n", j);
	
	//writes number of arcs...
	LFile_WriteString (outfile, buffer);
	
	for (i=0; i<j; i++)
	{
		//reads arc endpoints and writes them to disk...
		fgets (buffer, BUF_SIZE, f);
		theToken=LString_Tokenizer (buffer, " ");
		endpoint=LString_ToUI4 (theToken);
		LFile_Write (outfile, &endpoint, 4);
		theToken = LString_Tokenizer(NULL, " ");
		endpoint=LString_ToUI4 (theToken);
		LFile_Write (outfile, &endpoint, 4);
	
		//drops extra line...
		fgets (buffer, BUF_SIZE, f);
	}
	
	//closes files...
	LFile_Close (&outfile);
	fclose (f);
	
	return 0;
} 

