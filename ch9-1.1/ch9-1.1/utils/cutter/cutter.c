/* ============================================================================
 *  cutter.c
 * ============================================================================

 *  Author:         (c) 2005 Camil Demetrescu, Andrea Ribichini
 *  License:        See the end of this file for license information
 *  Created:        November 7, 2005
 
 *  Last changed:   $Date: 2005/12/13 16:45:28 $
 *  Changed by:     $Author: demetres $
 *  Revision:       $Revision: 1.5 $
*/

#include <stdio.h>
#include <stdlib.h>

#include "LException.h"
#include "LMemory.h"
#include "LFile.h"
#include "LString.h"
#include "LArray.h"
#include "LHash.h"

#define Buf_Size 4096

int main (int argc, char *argv[])
{
	i4 x1, x2, y1, y2;
	ui4 ApproxMemSize;
	
	i1 tmpFilename1[LFile_MAX_PATHNAME_LEN], tmpFilename2[LFile_MAX_PATHNAME_LEN], tmpFilename3[LFile_MAX_PATHNAME_LEN];
	
	FILE *inputFile, *outputFile, *validNodes, *validArcs;
	
	LFile *nodeIds;
	
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
	ui4 totalReadArcs=0;
	
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
    LSystem_Print(  "* TIGER/Line graph cutter\n\n");

	if (argc!=8)
	{
		printf ("Usage: > cutter memsize (in MBytes) inFile outFile x1 y1 x2 y2\n");
		return 0;
	}

	ApproxMemSize=(ui4)atoi (argv[1]) * 1024*1024;

	if (ApproxMemSize<160)
	{
		printf ("\nABORT: ApproxMemSize must be at least 160 bytes!\n");
		return 0;
	}

	printf ("* ApproxMemSize: %d MBytes\n", ApproxMemSize);
	
	x1=atoi (argv[4]);
	y1=atoi (argv[5]);
	x2=atoi (argv[6]);
	y2=atoi (argv[7]);
	printf ("top left coords: %d , %d\nbottom right coords: %d , %d\n", x1, y1, x2, y2);
	
	/*opens input file...*/
	inputFile=fopen (argv[2], "r");
	if (inputFile==NULL)
	{
		printf ("ERROR: Could not open input file\n");
		goto cleanup;
	}
	
	/*opens tmp valid nodes file...*/
	LFile_GetTempName (tmpFilename1);
	printf ("1st tmp file: %s\n", tmpFilename1);
	
	validNodes=fopen (tmpFilename1, "w");
	if (validNodes==NULL)
	{
		printf ("ERROR: Could not open tmp file\n");
		fclose (inputFile);
		goto cleanup;
	}
	
	/*opens tmp node id file...*/
	LFile_GetTempName (tmpFilename2);
	printf ("2nd tmp file: %s\n", tmpFilename2);
	
	Try
	{
		nodeIds=LFile_Open (tmpFilename2, LFile_WRITE);
	}	
	CatchAny
	{
		printf ("ERROR: Could not open 2nd tmp file\n");
		goto precleanup;
	}
	
	/*opens tmp valid arcs file...*/
	LFile_GetTempName (tmpFilename3);
	printf ("3rd tmp file: %s\n", tmpFilename3);
	
	validArcs=fopen (tmpFilename3, "w");
	if (validArcs==NULL)
	{
		printf ("ERROR: Could not open tmp file\n");
		goto preprecleanup;
	}
	
	/* PROCESSES NODES */
	
	/*gets # of nodes...*/
	if (fgets (numNodesString, Buf_Size, inputFile)==NULL)
	{
		printf ("ERROR: Could not read from input file\n");
		goto precleanup;
	}
	numNodes=atoi (numNodesString);
	printf ("# of nodes: %d\n", numNodes);
	
	/*for all nodes...*/
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
		if (nodeLongitude>=x1 && nodeLongitude<=x2 && nodeLatitude<=y1 && nodeLatitude>=y2)
		{
			/*adds entry to tmp file #1...*/
			if (fputs (nodeString2, validNodes)==EOF)
			{
				printf ("ERROR: Could not write to 1st tmp file\n");
				goto preprecleanup;
			}
			
			/*adds numeric id to tmp file #2...*/
			Try
				LFile_WriteN4 (nodeIds, &nodeId);
			CatchAny
			{
				printf ("ERROR: Could not write to 2nd tmp file\n");
				goto preprecleanup;
			}
			
			/*keeps track of # of valid nodes...*/
			NumValidNodes++;
		}
	}
	
	if (NumValidNodes!=0)
		printf ("# of valid nodes: %d\n", NumValidNodes);
	else
	{
		printf ("ABORT: No valid nodes!\n");
		goto prepreprecleanup;
	}
	
	/* PROCESSES ARCS */
	
	/*gets # of arcs...*/
	fgets (numArcsString, Buf_Size, inputFile);
	numArcs=atoi (numArcsString);
	printf ("# of arcs: %d\n", numArcs);
	
	/*some init...*/
	tmpArcSlot.sourceNode=FALSE;
	tmpArcSlot.targetNode=FALSE;
	
	printf ("Running streaming algorithm");
	fflush (stdout);
	
	/*beginning of streaming algorithm...*/
	while (totalReadArcs < numArcs)
	{
	
		/*closes 2nd tmp file, and reopens it in read mode...*/
		LFile_Close (&nodeIds);
		nodeIds=LFile_Open (tmpFilename2, LFile_READ);
	
		/*creates arc table...*/
		ArcTable=LArray_New (sizeof (ArcSlot));
	
		/*creates hash tables...*/
		sources=LHash_New ();
		targets=LHash_New ();
	
		/*reads a prefix of arcs from input file...*/
		readArcs=0;
		while ((readArcs < ApproxMemSize/160) && (totalReadArcs < numArcs))
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
		
		/*scans arc table and copies valid arcs to 3rd tmp file...*/
		theListLength=LArray_GetItemsCount (ArcTable);
		for (i=0; i<theListLength; i++)
		{
			/*retrieves pointer to current item...*/
			tableItem=(ArcSlot *)LArray_ItemAt (ArcTable, i);
			/*if both endpoints in clipping rect...*/
			if ((tableItem->sourceNode==TRUE) && (tableItem->targetNode==TRUE))
			{
				/*writes both lines to 3rd tmp file...*/
				
				/*assembles first line...*/
				sprintf (tmpBuffer, "%d %d\n", tableItem->sourceId, tableItem->targetId);
				/*writes it...*/
				if (fputs (tmpBuffer, validArcs)==EOF)
				{
					printf ("ERROR: Could not write to 3rd tmp file\n");
					
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
					printf ("ERROR: Could not write to 3rd tmp file\n");
					
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
	
		printf (".", numPasses);
		fflush (stdout);
		numPasses++;
	/*end of streaming algorithm...*/
	}
	
	printf ("\ntotal # of passes: %d\n", numPasses);
	printf ("# of valid arcs: %d\n", NumValidArcs);
	
	/* OUTPUT FILE */
	printf ("Writing to output file...\n");
	
	/*opens output file...*/
	outputFile=fopen (argv[3], "w");
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
	fclose (validNodes);
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
	validArcs=fopen (tmpFilename3, "r");
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
	
prepreprecleanup:
	/*closes and removes 3rd tmp file...*/
	fclose (validArcs);
	LFile_Remove (tmpFilename3);
preprecleanup:
	/*closes and removes 2nd tmp file...*/
	LFile_Close (&nodeIds);	
	LFile_Remove (tmpFilename2);	
precleanup:
	/*closes files...*/
	fclose (inputFile);
	fclose (validNodes);
	/*deletes 1st tmp file...*/
	LFile_Remove (tmpFilename1);
		
cleanup:
	printf ("LMemory_GetBlocksCount() says: %d\n", LMemory_GetBlocksCount ());

	return 0;
} 

/* Copyright (C) 2005 Camil Demetrescu, Andrea Ribichini

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
