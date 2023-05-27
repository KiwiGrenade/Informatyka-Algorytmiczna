/* ============================================================================
 *  CStreamConn.c
 * ============================================================================

 *  Author:         (C) 2005 Andrea Ribichini
 *  License:        See the end of this file for license information
 *  Created:        September 19, 2005
 *  Module:         stream

 *  Last changed:   $Date: 2006/02/21 21:45:33 $  
 *  Changed by:     $Author: demetres $
 *  Revision:       $Revision: 1.11 $
*/

#include <stdio.h>

#include "CStreamConn.h"
#include "CStreamPipe.h"
#include "LQuickFind.h"
#include "LHash.h"
#include "LArray.h"
#include "LTime.h"

/* constants */
#define DUMMY_PASS 1  /* if set to 1 performs an initial dummy pass */
#define REPORT_TIME 0

#if REPORT_TIME
#include <sys/times.h>
#include <time.h>
#include <sys/param.h>
#endif

/* PUBLIC METHODS */

/* ---------------------------------------------------------------------------------
*  CStreamConn_BuildInstance
*  ---------------------------------------------------------------------------------
*  Constructor */
void CStreamConn_BuildInstance (i1* inFile, i1* outFile, ui4 inMemSize)
{
	/*time structs...*/
	#if REPORT_TIME
	struct tms theTMS_begin, theTMS_end;
	f8 init_clock, end_clock;
	#endif

	LQuickFind* theQuickFind;
	CStreamPipe* theStreamPipe;
	LHash* theHashTable;
	
	ui4 theVertex0, theVertex1;
	Bool theNEOF;
	ui4 theBytesRead;
	
	ui4 theSet0, theSet1;
	ui4 theDummyVertex=0xffffffff;
	Bool theSet0_flag, theSet1_flag;
	
	LArray* theVh;
	ui4 thelengthVh;
	ui4 i;
	ui4 theVhVertex, theVhVertexSet;
	
	/*BOOTSTRAP...*/
	
	/*creates streampipe data struct...*/
	theStreamPipe=CStreamPipe_New (inFile, outFile);
	if (theStreamPipe==NULL) /*input file must exist...*/
	{
		printf ("Could not create streampipe data struct!\n");
		return;
	}

	//debugging...
	//dummy pass... speeds up the whole computation
	#if DUMMY_PASS
	CStreamPipe_ReadN4 (theStreamPipe, &theVertex0);
	theNEOF=CStreamPipe_ReadN4 (theStreamPipe, &theVertex1);
	while (theNEOF)
	{
		CStreamPipe_WriteN4 (theStreamPipe, &theVertex0);
		CStreamPipe_WriteN4 (theStreamPipe, &theVertex1);
		
		CStreamPipe_ReadN4 (theStreamPipe, &theVertex0);
		theNEOF=CStreamPipe_ReadN4 (theStreamPipe, &theVertex1);
	}
	CStreamPipe_Swap (theStreamPipe);
	#endif
	//dummy copy...
	/*{
		CStreamPipe* dcsp=CStreamPipe_New ("dummy.bin", "dummy2.bin");

		CStreamPipe_ReadN4 (dcsp, &theVertex0);
		theNEOF=CStreamPipe_ReadN4 (dcsp, &theVertex1);
		while (theNEOF)
		{
			CStreamPipe_WriteN4 (dcsp, &theVertex0);
			CStreamPipe_WriteN4 (dcsp, &theVertex1);
		
			CStreamPipe_ReadN4 (dcsp, &theVertex0);
			theNEOF=CStreamPipe_ReadN4 (dcsp, &theVertex1);
		}

		CStreamPipe_Delete (&dcsp); 
	}*/
	
	/*algorithm begins...*/
	printf ("Running streaming algorithm\n");
	fflush (stdout);

	/*fetches initial times...*/
	#if REPORT_TIME
	times (&theTMS_begin);
	init_clock=LTime_GetUserTime ();
	#endif

	while (1)
	{
	/*creates quickfind data struct...*/
	theQuickFind=LQuickFind_New ();

	/*creates hash table...*/
	theHashTable=LHash_New ();	
	
	/*PHASE 1...*/
	printf ("Phase 1\n");
	fflush (stdout);
	
	/*init...*/
	theBytesRead=0;
	
	/*reads first arc...*/
	CStreamPipe_ReadN4 (theStreamPipe, &theVertex0);
	theNEOF=CStreamPipe_ReadN4 (theStreamPipe, &theVertex1);
	/*error condition (input file doesn't contain any arcs)...*/
	if (!theNEOF)
		goto error;
	/*termination condition (Ai empty)...*/
	if (theVertex1 == 0xffffffff)
		goto exit;
	
	/*only 'not previously encountered' vertices end up in quickfind data struct...*/
	if (theVertex0==theVertex1)
	{
		if (LQuickFind_Find (theQuickFind, theVertex0)==LQuickFind_BAD_ITEM)
			theBytesRead=theBytesRead+4;
	}
	else
	{
		if (LQuickFind_Find (theQuickFind, theVertex0) == LQuickFind_BAD_ITEM)
			theBytesRead=theBytesRead+4;
		if (LQuickFind_Find (theQuickFind, theVertex1) == LQuickFind_BAD_ITEM)
			theBytesRead=theBytesRead+4;
	}
	//theBytesRead=theBytesRead+8;
	
	while ( theNEOF && (theBytesRead <= inMemSize) && (theVertex1 != 0xffffffff) )
	{
		/*stores vertices (MakeSet checks whether item already exists)...*/
		LQuickFind_MakeSet (theQuickFind, theVertex0);
		LQuickFind_MakeSet (theQuickFind, theVertex1);
		
		/*updates spanning forest (Union works between items as well as sets)...*/
		LQuickFind_Union (theQuickFind, theVertex0, theVertex1);
		
		/*reads next arc...*/
		CStreamPipe_ReadN4 (theStreamPipe, &theVertex0);
		theNEOF=CStreamPipe_ReadN4 (theStreamPipe, &theVertex1);

		/*only 'not previously encountered' vertices end up in quickfind data struct...*/
		if (theVertex0==theVertex1)
		{
			if (LQuickFind_Find (theQuickFind, theVertex0)==LQuickFind_BAD_ITEM)
				theBytesRead=theBytesRead+4;
		}
		else
		{
			if (LQuickFind_Find (theQuickFind, theVertex0) == LQuickFind_BAD_ITEM)
				theBytesRead=theBytesRead+4;
			if (LQuickFind_Find (theQuickFind, theVertex1) == LQuickFind_BAD_ITEM)
				theBytesRead=theBytesRead+4;
		}
		//theBytesRead=theBytesRead+8;
	}

	//debugging...
	/*some reports...*/
	if (!theNEOF)
		printf ("File ended.\n");
	if (theBytesRead>inMemSize)
		printf ("Memory full.\n");
	if (theVertex1==0xffffffff)
		printf ("Encountered marker.\n");
	{
	LArray *theQuickItems;
	ui4 theQuickLength;

	theQuickItems=LQuickFind_GetAllItems (theQuickFind);
	theQuickLength=LArray_GetItemsCount (theQuickItems);
	printf ("# of items in LQuickFind data struct: %d\n", theQuickLength);
	fflush (stdout);
	LArray_Delete (&theQuickItems);
	}
	
	/*PHASE 2...*/
	printf ("Phase 2\n");
	fflush (stdout);
	
	while ( theNEOF && (theVertex1 != 0xffffffff) )
	{
		/*determines c(u) and c(v)...*/
		theSet0=LQuickFind_Find (theQuickFind, theVertex0);
		if (theSet0==LQuickFind_BAD_ITEM)
		{
			theSet0=theVertex0;
			theSet0_flag=FALSE;
		}
		else
		/*vertex of Vh might be written to Ai+1*/
		theSet0_flag=TRUE;
			
		theSet1=LQuickFind_Find (theQuickFind, theVertex1);
		if (theSet1==LQuickFind_BAD_ITEM)
		{
			theSet1=theVertex1;
			theSet1_flag=FALSE;
		}
		else
		/*vertex of Vh might be written to Ai+1*/
		theSet1_flag=TRUE;
		
		/*if different ends writes arc to output stream...*/
		if (theSet0 != theSet1)
		{
			CStreamPipe_WriteN4 (theStreamPipe, &theSet0);
			CStreamPipe_WriteN4 (theStreamPipe, &theSet1);
			
			/*keeps track of vertices of Vh that are written to Ai+1...*/
			if (theSet0_flag)
				LHash_InsertItem (theHashTable, NULL, theSet0);
			if (theSet1_flag)
				LHash_InsertItem (theHashTable, NULL, theSet1);
				
		}

		/*reads next arc...*/
		CStreamPipe_ReadN4 (theStreamPipe, &theVertex0);
		theNEOF=CStreamPipe_ReadN4 (theStreamPipe, &theVertex1);
			
	}
	
	/*marks end of Ai+1...*/
	CStreamPipe_WriteN4 (theStreamPipe, &theDummyVertex);
	CStreamPipe_WriteN4 (theStreamPipe, &theDummyVertex);
	
	/*PHASE 3...*/
	printf ("Phase 3\n");
	fflush (stdout);
	
	/*reads next arc...*/
	CStreamPipe_ReadN4 (theStreamPipe, &theVertex0);
	theNEOF=CStreamPipe_ReadN4 (theStreamPipe, &theVertex1);

	while (theNEOF)
	{		
		/*determines c(v)...*/
		theSet1=LQuickFind_Find (theQuickFind, theVertex1);
		if (theSet1==LQuickFind_BAD_ITEM)
			theSet1=theVertex1;
			
		/*writes arc (u, c(v)) to output stream...*/
		CStreamPipe_WriteN4 (theStreamPipe, &theVertex0);
		CStreamPipe_WriteN4 (theStreamPipe, &theSet1);	

		/*reads next arc...*/
		CStreamPipe_ReadN4 (theStreamPipe, &theVertex0);
		theNEOF=CStreamPipe_ReadN4 (theStreamPipe, &theVertex1);	
	}
	
	/*PHASE 4...*/
	printf ("Phase 4\n");
	fflush (stdout);
	
	/*gets all vertices in Vh...*/
	theVh=LQuickFind_GetAllItems (theQuickFind);
	thelengthVh=LArray_GetItemsCount (theVh);
	
	for (i=0; i<thelengthVh; i++)
	{
		theVhVertex=*(ui4 *)LArray_ItemAt (theVh, i);
		/*if vertex not in Ai+1...*/
		if (!LHash_IsInTable (theHashTable, theVhVertex))
		{
			/*writes (v, c(v)) to output stream...*/
			theVhVertexSet=LQuickFind_Find (theQuickFind, theVhVertex); /*cannot be BAD_ITEM...*/
			if (theVhVertexSet!=theVhVertex)
			{
				CStreamPipe_WriteN4 (theStreamPipe, &theVhVertex);
				CStreamPipe_WriteN4 (theStreamPipe, &theVhVertexSet);
			}
		}
	}
	
	/*deletes LArray...*/
	LArray_Delete (&theVh);

	/*deletes LQuickFind...*/
	LQuickFind_Delete (&theQuickFind);

	/*deletes LHash...*/
	LHash_Delete (&theHashTable);

	/*pass ends...*/
	CStreamPipe_Swap (theStreamPipe);
	printf ("End of pass.\n");
	fflush (stdout);
	}
	
	/*HOUSEKEEPING...*/
	
error:
	printf ("Input file not valid!\n");
	
	/*deletes streampipe data struct...*/
	CStreamPipe_Delete (&theStreamPipe);
	
	/*deletes quickfind data struct...*/
	LQuickFind_Delete (&theQuickFind);
	
	/*deletes hash table...*/
	LHash_Delete (&theHashTable);

	return;
			
exit:
	/*fetches final times...*/
	#if REPORT_TIME
	times (&theTMS_end);
	end_clock=LTime_GetUserTime ();
	/*reports times...*/
	printf ("\nCLOCKS_PER_SEC = %d\n", CLOCKS_PER_SEC);
	printf ("HZ = %d\n", HZ);
	printf ("Total elapsed time: %f seconds\n", end_clock-init_clock);
	printf ("User time: %f seconds\n", (f8)((theTMS_end.tms_utime)-(theTMS_begin.tms_utime))/HZ);
	printf ("System time: %f seconds\n", (f8)((theTMS_end.tms_stime)-(theTMS_begin.tms_stime))/HZ);
	printf ("User time (children): %f seconds\n", (f8)((theTMS_end.tms_cutime)-(theTMS_begin.tms_cutime))/HZ);
	printf ("System time (children): %f seconds\n", (f8)((theTMS_end.tms_cstime)-(theTMS_begin.tms_cstime))/HZ);
	#endif

	printf ("\nCopying final stream\n");
	/*makes a copy of final stream...*/
	CStreamPipe_ReadN4 (theStreamPipe, &theVertex0);
	theNEOF=CStreamPipe_ReadN4 (theStreamPipe, &theVertex1);
	while (theNEOF)
	{
		CStreamPipe_WriteN4 (theStreamPipe, &theVertex0);
		CStreamPipe_WriteN4 (theStreamPipe, &theVertex1);

		CStreamPipe_ReadN4 (theStreamPipe, &theVertex0);
		theNEOF=CStreamPipe_ReadN4 (theStreamPipe, &theVertex1);
	}
	
	/*deletes streampipe data struct...*/
	CStreamPipe_Delete (&theStreamPipe);
	
	/*deletes quickfind data struct...*/
	LQuickFind_Delete (&theQuickFind);
	
	/*deletes hash table...*/
	LHash_Delete (&theHashTable);
	
	return;
}

/* Copyright (C) 2005 Andrea Ribichini

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
