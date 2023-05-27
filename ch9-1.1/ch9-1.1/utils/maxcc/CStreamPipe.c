/* ============================================================================
 *  CStreamPipe.c
 * ============================================================================

 *  Author:         (C) 2005-2006 Andrea Ribichini, Camil Demetrescu
 *  License:        See the end of this file for license information
 *  Created:        September 14, 2005
 *  Module:         ??

 *  Last changed:   $Date: 2006/01/16 20:10:25 $  
 *  Changed by:     $Author: ribbi $
 *  Revision:       $Revision: 1.5 $
*/

#include <stdio.h>

#include "CStreamPipe.h"
#include "LMemory.h"
#include "LString.h"
#include "LException.h"

/* PUBLIC METHODS */

/* ---------------------------------------------------------------------------------
*  CStreamPipe_New
*  ---------------------------------------------------------------------------------
*  Constructor */

CStreamPipe* CStreamPipe_New (i1* inFile, i1* outFile) 
{
	CStreamPipe theObject={0};
	ui4 thelength;
	
	/*opens input file (must exist)...*/
	Try
		theObject.mInputFile=LFile_Open (inFile, LFile_READ);
	CatchAny
		return NULL;
	
	/*opens output file (if already exists it is deleted)...*/
	Try
		theObject.mOutputFile=LFile_Open (outFile, LFile_WRITE);
	CatchAny
	{
		/*cleanup...*/
		LFile_Close (&(theObject.mInputFile));
		return NULL;
	}
	
	/*gets filename for temporary file...*/
	LFile_GetTempName (theObject.mTmpFileName);
	printf ("CStreamPipe tmp file name: %s\n", theObject.mTmpFileName);

	/*copies inFile string...*/
	thelength=LString_Len (inFile);
	theObject.mInputFileName=(i1 *)LMemory_Malloc (thelength+1);
	LString_Copy (inFile, theObject.mInputFileName);
	
	/*copies outFile string...*/
	thelength=LString_Len (outFile);
	theObject.mOutputFileName=(i1 *)LMemory_Malloc (thelength+1);
	LString_Copy (outFile, theObject.mOutputFileName);
	
	/*sets NoSwapYet flag...*/
	theObject.mNoSwapYet=TRUE;
    
	return LMemory_NewObject (CStreamPipe, theObject);
}

/* ---------------------------------------------------------------------------------
*  CStreamPipe_Delete
*  ---------------------------------------------------------------------------------
*  Destructor */

void CStreamPipe_Delete (CStreamPipe** ThisA)
{
	/*closes files...*/
	LFile_Close (&((*ThisA)->mInputFile));
	LFile_Close (&((*ThisA)->mOutputFile));
	
	/*if there have been swaps...*/
	if ( !(*ThisA)->mNoSwapYet )
		/*deletes tmp file...*/
		LFile_Remove ((*ThisA)->mTmpFileName);
		
	/*deallocates strings...*/
	LMemory_Free (&((*ThisA)->mInputFileName));
	LMemory_Free (&((*ThisA)->mOutputFileName));
		
	/*deletes object...*/
	LMemory_DeleteObject (ThisA);
}

/* ---------------------------------------------------------------------------------
*  CStreamPipe_Read
*  ---------------------------------------------------------------------------------
*  Read */
Bool CStreamPipe_Read (CStreamPipe* This, void* outItem, ui4 inItemSize)
{
	ui4 thebytesread;
	
	/*reads item from input file...*/
	thebytesread=LFile_Read (This->mInputFile, outItem, inItemSize);
	
	/*if item read returns true, otherwise false (end of file reached or possibly file not properly formatted)...*/
	if (thebytesread==inItemSize)
		return TRUE;
	else
		return FALSE;
}

/* ---------------------------------------------------------------------------------
*  CStreamPipe_Write
*  ---------------------------------------------------------------------------------
*  Write */
void CStreamPipe_Write (CStreamPipe* This, void* outItem, ui4 inItemSize)
{
	/*appends item to output file...*/
	LFile_Write (This->mOutputFile, outItem, inItemSize);
}

/* ---------------------------------------------------------------------------------
*  CStreamPipe_Swap
*  ---------------------------------------------------------------------------------
*  Swap */
void CStreamPipe_Swap (CStreamPipe* This)
{	
	/*closes files...*/
	LFile_Close (&(This->mInputFile));
	LFile_Close (&(This->mOutputFile));
	
	/*if not first swap...*/
	if (!This->mNoSwapYet)
	{
		/*deletes tmp (previos input) file...*/
		LFile_Remove (This->mTmpFileName);
	}
	else
	{
		/*resets flag...*/
		This->mNoSwapYet=FALSE;
	}
		
	
	/*renames previous output file (becomes new input file)...*/
	Try
		LFile_Rename (This->mOutputFileName, This->mTmpFileName);
	CatchAny
	{
		printf ("\nCould not rename %s to %s\n", This->mOutputFileName, This->mTmpFileName);
		fflush (stdout);
	}
	/*opens new input file...*/
	This->mInputFile=LFile_Open (This->mTmpFileName, LFile_READ);
	
	/*creates new output file...*/
	This->mOutputFile=LFile_Open (This->mOutputFileName, LFile_WRITE);	
}

/* ---------------------------------------------------------------------------------
*  CStreamPipe_ReadNx functions
*  ---------------------------------------------------------------------------------
*  ReadNx */
Bool CStreamPipe_ReadN1 (CStreamPipe* This, void* outItem)
{
	Try
		LFile_ReadN1 (This->mInputFile, outItem);
	CatchAny
		return FALSE;
		
	return TRUE;
}

Bool CStreamPipe_ReadN2 (CStreamPipe* This, void* outItem)
{
	Try
		LFile_ReadN2 (This->mInputFile, outItem);
	CatchAny
		return FALSE;
		
	return TRUE;
}

Bool CStreamPipe_ReadN4 (CStreamPipe* This, void* outItem)
{
	Try
		LFile_ReadN4 (This->mInputFile, outItem);
	CatchAny
		return FALSE;
		
	return TRUE;
}

Bool CStreamPipe_ReadN8 (CStreamPipe* This, void* outItem)
{
	Try
		LFile_ReadN8 (This->mInputFile, outItem);
	CatchAny
		return FALSE;
		
	return TRUE;
}

/* ---------------------------------------------------------------------------------
*  CStreamPipe_WriteNx functions
*  ---------------------------------------------------------------------------------
*  WriteNx */
void CStreamPipe_WriteN1 (CStreamPipe* This, void* outItem)
{
	LFile_WriteN1 (This->mOutputFile, outItem);
}

void CStreamPipe_WriteN2 (CStreamPipe* This, void* outItem)
{
	LFile_WriteN2 (This->mOutputFile, outItem);
}

void CStreamPipe_WriteN4 (CStreamPipe* This, void* outItem)
{
	LFile_WriteN4 (This->mOutputFile, outItem);
}

void CStreamPipe_WriteN8 (CStreamPipe* This, void* outItem)
{
	LFile_WriteN8 (This->mOutputFile, outItem);
}

/* Copyright (C) 2005-2006 Andrea Ribichini, Camil Demetrescu

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
