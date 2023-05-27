/* ============================================================================
 *  subgraph.c
 * ============================================================================

 *  Author:         (C) 2006 Camil Demetrescu, Andrea Ribichini
 *  License:        See the end of this file for license information
 *  Created:        Jan 18, 2006
 *  Module:         stream
 *  Notes:          extract subgraph induced by a list of nodes
                    from a TIGER/Line graph. List of nodes is given
                    as binary file containing node ids of type ui4

 *  Last changed:   $Date: 2006/10/30 08:09:39 $  
 *  Changed by:     $Author: demetres $
 *  Revision:       $Revision: 1.3 $
*/

#include <stdio.h>
#include <stdlib.h>

#include "LException.h"
#include "LMemory.h"
#include "LFile.h"
#include "LString.h"
#include "LArray.h"
#include "LHash.h"
#include "LHashStatic.h"

/* constants */
#define Buf_Size        4096
#define BYTES_PER_ARC   160
#define BYTES_PER_NODE  100


int main (int argc, char *argv[])
{
	ui4 ApproxMemSize;

	i1 tmpFilename1[LFile_MAX_PATHNAME_LEN], 
	   tmpFilename2[LFile_MAX_PATHNAME_LEN];

	FILE *inputFile  = NULL, 
	     *outputFile = NULL, 
	     *validNodes = NULL, 
	     *validArcs  = NULL;

	LFile *nodeIds   = NULL;

	i1 numNodesString[Buf_Size];
	i4 numNodes;

	int i;

	i1 nodeString[Buf_Size];
	i1 nodeString2[Buf_Size];
	i1* theToken;
	ui4 nodeId;
	i4 nodeLatitude, nodeLongitude;
	
	ui4 NumValidNodes=0;
	ui4 NumValidArcs=0;
	
	i4 numArcs;
	i1 numArcsString[Buf_Size];
	
	typedef struct tagArcSlot
	{
		ui4 sourceId;
		ui4 targetId;
		f8 travelTime;
		f8 spatialDistance;
		ui4 roadCategory;
	
		Bool sourceNode;
		Bool targetNode;
	} ArcSlot;

	LHash *sources, *targets;
	LArray *ArcTable;
	
	i1 endPoints[Buf_Size];
	i1 otherData[Buf_Size];
	
	ui4 readArcs;
    ui4 totalReadValidNodes = 0;
	ui4 totalReadArcs = 0;

	ArcSlot tmpArcSlot;
	
	i1 tmpBuffer[Buf_Size];
	ui4 source, target;
	ui4 arcIndex;

	LArray* theList;
	
	ui4 j;
	ui4 theIndex;
	ArcSlot *tableItem;
	ui4 theListLength;
	
	ui4 numPasses=0;
	
	LArray *theListOfLists;
	ui4 theListOfListsLength; 
	
	/* PROCESSES COMMAND LINE */

    /* print header */
    LSystem_Print("\n* 9th DIMACS Implementation Challenge: Shortest Paths\n");
    LSystem_Print(  "* http://www.dis.uniroma1.it/~challenge9\n");
    LSystem_Print(  "* extracts induced subgraphs from TIGER/Line files\n\n");

	if (argc!=5)
	{
		printf ("Usage: > subgraph memsize (in MBytes) nodeListFile inFile outFile\n");
		return 0;
	}

	ApproxMemSize=(ui4)atoi (argv[1]) * 1024*1024;

	if (ApproxMemSize < BYTES_PER_ARC)
	{
		printf ("\nABORT: ApproxMemSize must be at least %lu bytes\n", BYTES_PER_ARC);
		return 0;
	}

	printf ("* ApproxMemSize: %d Bytes\n", ApproxMemSize);

	/*opens input file...*/
    printf("* Open input file %s\n", argv[3]);
	inputFile = fopen (argv[3], "r");
	if (inputFile==NULL)
	{
		printf ("ERROR: Could not open input file\n");
		goto cleanup;
	}

    /* opens node list file */
    nodeIds = LFile_Open (argv[2], LFile_READ);
	if (nodeIds==NULL)
	{
		printf ("ERROR: Could not open node list file\n");
		goto cleanup;
	}
	

	/* PROCESSES NODES */

	/*opens tmp valid nodes file...*/
	LFile_GetTempName (tmpFilename1);
	printf ("1st tmp file (valid nodes): %s\n", tmpFilename1);

	validNodes=fopen (tmpFilename1, "w");
	if (validNodes==NULL)
	{
		printf ("ERROR: Could not open tmp file\n");
		goto cleanup;
	}
	
	/*gets # of nodes...*/
	if (fgets (numNodesString, Buf_Size, inputFile)==NULL)
	{
		printf ("ERROR: Could not read from input file\n");
		goto precleanup;
	}
	numNodes=atoi (numNodesString);
	printf ("# of nodes: %d\n", numNodes);

	/*gets # of valid nodes...*/
    NumValidNodes = LFile_GetSize(nodeIds)/sizeof(ui4);

	if (NumValidNodes!=0)
		printf ("# of valid nodes: %d\n", NumValidNodes);
	else
	{
		printf ("ABORT: No valid nodes\n");
		goto prepreprecleanup;
	}

	printf ("Running streaming algorithm to extract valid nodes\n");
	fflush (stdout);

    /* scan valid nodes and write to temp file 1 their coords */
    while ( totalReadValidNodes < NumValidNodes ) {

        LHashStatic* theHash = LHashStatic_New(ApproxMemSize/BYTES_PER_NODE);
        if (!theHash) goto prepreprecleanup;

	    printf (".");
        fflush (stdout);

        /* fill memory with valid node ids */
        for (j = 0;
             totalReadValidNodes < NumValidNodes && 
             j < ApproxMemSize/BYTES_PER_NODE; 
             ++j) 
        {
            ui4 theReadId;
            LFile_ReadN4(nodeIds, &theReadId);
            //printf ("Node %d\n", theReadId);
            LHashStatic_InsertItem(theHash, NULL, theReadId);
            ++totalReadValidNodes;
			if (totalReadValidNodes % 1000 == 0) {
			    printf(":");
                fflush (stdout);
			}
        }

	    printf ("-");
        fflush (stdout);

    	/*for all nodes...*/
        fclose(inputFile);
      	inputFile = fopen (argv[3], "r");
    	fgets (numNodesString, Buf_Size, inputFile);
    	for (i=0; i<numNodes; i++)
    	{
    		/*reads node id, longitude, latitude...*/
    		fgets (nodeString, Buf_Size, inputFile);
    		/*backup copy...*/
    		LString_Copy (nodeString, nodeString2);
    		/*converts them to numbers*/
    		theToken=LString_Tokenizer (nodeString, " ");
    		nodeId=LString_ToUI4 (theToken);
    		theToken=LString_Tokenizer (NULL, " ");
    		nodeLongitude=LString_ToI4 (theToken);
    		theToken=LString_Tokenizer (NULL, " ");
    		nodeLatitude=LString_ToI4 (theToken);
    		
    		/*if valid node...*/
			if (LHashStatic_IsInTable (theHash, nodeId))
    		{
    			/*adds entry to tmp file #1...*/
    			if (fputs (nodeString2, validNodes)==EOF)
    			{
    				printf ("ERROR: Could not write to 1st tmp file\n");
    				goto preprecleanup;
    			}
    		}
//            else printf("--- %lu is not valid\n", nodeId);
    	}

        LHashStatic_Delete(&theHash);
    }
	
    /* close temp file 1 */
	fclose (validNodes);
    printf("\n");

	/* PROCESSES ARCS */
	
	/*opens tmp valid arcs file...*/
	LFile_GetTempName (tmpFilename2);
	printf ("2nd tmp file (valid arcs): %s\n", tmpFilename2);

	validArcs=fopen (tmpFilename2, "w");
	if (validArcs==NULL)
	{
		printf ("ERROR: Could not open tmp file\n");
		goto preprecleanup;
	}

	/*gets # of arcs...*/
	fgets (numArcsString, Buf_Size, inputFile);
	numArcs=atoi (numArcsString);
	printf ("\n# of arcs: %d\n", numArcs);
	
	/*some init...*/
	tmpArcSlot.sourceNode=FALSE;
	tmpArcSlot.targetNode=FALSE;
	
	printf ("Running streaming algorithm to extract arcs\n");
	fflush (stdout);
	
	/*beginning of streaming algorithm...*/
	while (totalReadArcs < numArcs)
	{

		/*creates arc table...*/
		ArcTable=LArray_New (sizeof (ArcSlot));
	
		/*creates hash tables...*/
		sources=LHash_New ();
		targets=LHash_New ();
	
		/*reads a prefix of arcs from input file...*/
		readArcs=0;
        printf("\nFill memory with arcs\n");
        fflush (stdout);
		
		while ((readArcs < ApproxMemSize/BYTES_PER_ARC) && (totalReadArcs < numArcs))
		{
			/*reads endpoints...*/
			fgets (tmpBuffer, Buf_Size, inputFile);
			/*backup...*/
			//LString_Copy (tmpBuffer, tmpArcSlot.firstLine);
			
			/*converts them to integers...*/
			theToken=LString_Tokenizer (tmpBuffer, " ");
			source=LString_ToUI4 (theToken);
			theToken=LString_Tokenizer (NULL, " ");
			target=LString_ToUI4 (theToken);
			
			/*stores them...*/
			tmpArcSlot.sourceId=source;
			tmpArcSlot.targetId=target;
			
			/*reads other data...*/
			//fgets (tmpArcSlot.secondLine, Buf_Size, inputFile);
			fgets (tmpBuffer, Buf_Size, inputFile);

			/*converts and stores them...*/
			theToken=LString_Tokenizer (tmpBuffer, " ");
			tmpArcSlot.travelTime=LString_ToF8 (theToken);
			theToken=LString_Tokenizer (NULL, " ");
			tmpArcSlot.spatialDistance=LString_ToF8 (theToken);
			theToken=LString_Tokenizer (NULL, " ");
			tmpArcSlot.roadCategory=LString_ToUI4 (theToken);
						
			/* updates arc table...*/
			arcIndex=LArray_AppendItem (ArcTable, &tmpArcSlot);
			
			/*updates hash tables...*/
			
			/*source...*/
			/*checks if it's already in table...*/
			if (LHash_IsInTable (sources, source))
			{
				/*retrieves list...*/
				theList=(LArray *)LHash_GetItemByKey (sources, source);
				/*adds new index...*/
				LArray_AppendItem (theList, &arcIndex);
			}
			else
			{
				/*creates new list...*/
				theList=LArray_New (4);
				/*adds index to newly created list...*/
				LArray_AppendItem (theList, &arcIndex);
				/*adds item to hash table...*/
				LHash_InsertItem (sources, theList, source);
			}
			
			/*target...*/
			/*checks if it's already in table...*/
			if (LHash_IsInTable (targets, target))
			{
				/*retrieves list...*/
				theList=(LArray *)LHash_GetItemByKey (targets, target);
				/*adds new index...*/
				LArray_AppendItem (theList, &arcIndex);
			}
			else
			{
				/*creates new list...*/
				theList=LArray_New (4);
				/*adds index to newly created list...*/
				LArray_AppendItem (theList, &arcIndex);
				/*adds item to hash table...*/
				LHash_InsertItem (targets, theList, target);
			}
			
			/*housekeeping...*/
			readArcs++;
			totalReadArcs++;
		}

		/*scans valid nodes file and sets flags for valid arcs...*/

		/*rewind node id file*/
        printf("Scan valid nodes and flag arcs in memory incident to them\n");
        fflush (stdout);

        LFile_Seek(nodeIds, 0, LFile_START);
		for (i=0; i<NumValidNodes; i++)
		{
			/*reads node id...*/
			LFile_ReadN4 (nodeIds, &nodeId);

			/*looks up sources...*/
			if (LHash_IsInTable (sources, nodeId))
			{
				/*gets list...*/
				theList=(LArray *)LHash_GetItemByKey (sources, nodeId);
				/*for all items...*/
				theListLength=LArray_GetItemsCount (theList);
				for (j=0; j<theListLength; j++)
				{
					/*gets index...*/
					theIndex=*(ui4 *)LArray_ItemAt (theList, j);
					/*gets struct...*/
					tableItem=(ArcSlot *)LArray_ItemAt (ArcTable, theIndex);
					/*sets source flag...*/
					tableItem->sourceNode=TRUE;
				}	
			}
			
			/*looks up targets...*/
			if (LHash_IsInTable (targets, nodeId))
			{
				/*gets list...*/
				theList=(LArray *)LHash_GetItemByKey (targets, nodeId);
				/*for all items...*/
				theListLength=LArray_GetItemsCount (theList);
				for (j=0; j<theListLength; j++)
				{
					/*gets index...*/
					theIndex=*(ui4 *)LArray_ItemAt (theList, j);
					/*gets struct...*/
					tableItem=(ArcSlot *)LArray_ItemAt (ArcTable, theIndex);
					/*sets source flag...*/
					tableItem->targetNode=TRUE;
				}	
			}
		}

		/*scans arc table and copies valid arcs to 2nd tmp file...*/
        printf("Write valid arcs to file\n");
        fflush (stdout);

		theListLength=LArray_GetItemsCount (ArcTable);
		for (i=0; i<theListLength; i++)
		{
			/*retrieves pointer to current item...*/
			tableItem=(ArcSlot *)LArray_ItemAt (ArcTable, i);
			/*if both endpoints in subgraph...*/
			if ((tableItem->sourceNode==TRUE) && (tableItem->targetNode==TRUE) &&
			    (tableItem->sourceId != tableItem->targetId))
			{
				/*writes both lines to 2nd tmp file...*/
				
				/*assembles first line...*/
				sprintf (tmpBuffer, "%d %d\n", tableItem->sourceId, tableItem->targetId);
				/*writes it...*/
				if (fputs (tmpBuffer, validArcs)==EOF)
				{
					printf ("ERROR: Could not write to 2nd tmp file\n");
					
					/*deletes all lists...*/
					/*sources...*/
					theListOfLists=LHash_GetAllItems (sources);
					theListOfListsLength=LArray_GetItemsCount (theListOfLists);
					for (i=0; i<theListOfListsLength; i++)
						LArray_Delete (LArray_ItemAt (theListOfLists, i));
					LArray_Delete (&theListOfLists);
					/*targets...*/
					theListOfLists=LHash_GetAllItems (targets);
					theListOfListsLength=LArray_GetItemsCount (theListOfLists);
					for (i=0; i<theListOfListsLength; i++)
						LArray_Delete (LArray_ItemAt (theListOfLists, i));
					LArray_Delete (&theListOfLists);
		
					/*deletes hash tables...*/
					LHash_Delete (&sources);
					LHash_Delete (&targets);
					/*deletes arc table...*/
					LArray_Delete (&ArcTable);
					
					goto prepreprecleanup;
				}
				
				/*assembles second line...*/
				sprintf (tmpBuffer, "%.18f %.18f %d\n", tableItem->travelTime, tableItem->spatialDistance,
				tableItem->roadCategory);
				/*writes it...*/
				if (fputs (tmpBuffer, validArcs)==EOF)
				{
					printf ("ERROR: Could not write to 2nd tmp file\n");
					
					/*deletes all lists...*/
					/*sources...*/
					theListOfLists=LHash_GetAllItems (sources);
					theListOfListsLength=LArray_GetItemsCount (theListOfLists);
					for (i=0; i<theListOfListsLength; i++)
						LArray_Delete (LArray_ItemAt (theListOfLists, i));
					LArray_Delete (&theListOfLists);
					/*targets...*/
					theListOfLists=LHash_GetAllItems (targets);
					theListOfListsLength=LArray_GetItemsCount (theListOfLists);
					for (i=0; i<theListOfListsLength; i++)
						LArray_Delete (LArray_ItemAt (theListOfLists, i));
					LArray_Delete (&theListOfLists);
		
					/*deletes hash tables...*/
					LHash_Delete (&sources);
					LHash_Delete (&targets);
					/*deletes arc table...*/
					LArray_Delete (&ArcTable);
					
					goto prepreprecleanup;
				}
				
				/*increments counter of valid arcs...*/
				NumValidArcs++;
			}
		}
	
		/*housekeeping... */
	
		/*deletes all lists...*/
		/*sources...*/
		theListOfLists=LHash_GetAllItems (sources);
		theListOfListsLength=LArray_GetItemsCount (theListOfLists);
		for (i=0; i<theListOfListsLength; i++)
			LArray_Delete (LArray_ItemAt (theListOfLists, i));
		LArray_Delete (&theListOfLists);
		/*targets...*/
		theListOfLists=LHash_GetAllItems (targets);
		theListOfListsLength=LArray_GetItemsCount (theListOfLists);
		for (i=0; i<theListOfListsLength; i++)
			LArray_Delete (LArray_ItemAt (theListOfLists, i));
		LArray_Delete (&theListOfLists);
		
		/*deletes hash tables...*/
		LHash_Delete (&sources);
		LHash_Delete (&targets);
		/*deletes arc table...*/
		LArray_Delete (&ArcTable);
	
//		printf (".");
		fflush (stdout);
		numPasses++;
	/*end of streaming algorithm...*/
	}
	
	printf ("\ntotal # of passes: %d\n", numPasses);
	printf ("# of valid arcs: %d\n", NumValidArcs);
	
	/* OUTPUT FILE */
	printf ("Writing to output file...\n");
    fflush (stdout);

	/*opens output file...*/
	outputFile=fopen (argv[4], "w");
	if (outputFile==NULL)
	{
		printf ("ERROR: could not open output file\n");
		goto prepreprecleanup;
	}
	
	/*writes # of nodes...*/
	sprintf (tmpBuffer, "%d\n", NumValidNodes);
	if (fputs (tmpBuffer, outputFile)==EOF)
	{
		printf ("ERROR: Could not write to output file\n");
		fclose (outputFile);
		goto prepreprecleanup;
	}
	
	/*writes nodes...*/
	validNodes=fopen (tmpFilename1, "r");
	while (fgets (tmpBuffer, Buf_Size, validNodes)!=NULL)
	{
		if (fputs (tmpBuffer, outputFile)==EOF)
		{
			printf ("ERROR: Could not write to output file\n");
			fclose (outputFile);
			goto prepreprecleanup;
		}
	}
	
	/*writes # of arcs...*/
	sprintf (tmpBuffer, "%d\n", NumValidArcs);
	if (fputs (tmpBuffer, outputFile)==EOF)
	{
		printf ("ERROR: Could not write to output file\n");
		fclose (outputFile);
		goto prepreprecleanup;
	}
	
	/*writes arcs...*/
	fclose (validArcs);
	validArcs=fopen (tmpFilename2, "r");
	while (fgets (tmpBuffer, Buf_Size, validArcs)!=NULL)
	{
		if (fputs (tmpBuffer, outputFile)==EOF)
		{
			printf ("ERROR: Could not write to output file\n");
			fclose (outputFile);
			goto prepreprecleanup;
		}
	}
	
	/*closes output file...*/
	fclose (outputFile);
		
	printf ("Removing temporary files...\n");
    fflush (stdout);
	
prepreprecleanup:
	/*closes and removes 2nd tmp file...*/
	fclose (validArcs);
	LFile_Remove (tmpFilename2);

preprecleanup:
	/*closes node list file...*/
	if (nodeIds) LFile_Close (&nodeIds);	

precleanup:
	/*closes files...*/
	fclose (inputFile);
	fclose (validNodes);
	/*deletes 1st tmp file...*/
	LFile_Remove (tmpFilename1);
		
cleanup:
	printf ("LMemory_GetBlocksCount() says: %d\n", LMemory_GetBlocksCount ());
    fflush (stdout);

	return 0;
} 

/* Copyright (C) 2006 Camil Demetrescu, Andrea Ribichini

 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA 
*/

