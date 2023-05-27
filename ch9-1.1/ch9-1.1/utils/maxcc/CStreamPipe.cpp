/* ============================================================================
 *  CStreamPipe.cpp
 * ============================================================================

 *  Author:         (C) 2006 Andrea Ribichini
 *  License:        See the end of this file for license information
 *  Created:        January 3, 2006
 *  Module:         ??

 *  Last changed:   $Date: 2006/01/16 20:10:25 $  
 *  Changed by:     $Author: ribbi $
 *  Revision:       $Revision: 1.2 $
*/

#include <stxxl>

#include <stdio.h>

#include "CStreamPipe.hpp"
#include "LMemory.h"
#include "LString.h"
#include "LException.h"

using stxxl::syscall_file;
using stxxl::file;

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
	if (LFile_Exists (inFile))
		theObject.mInputFile=new syscall_file(inFile, file::RDONLY);
	else
		return NULL;
	
	theObject.mInputVector=new stxxl::vector<ui4>(theObject.mInputFile);
	theObject.mIt=new stxxl::vector<ui4>::const_iterator((theObject.mInputVector)->begin ());
	
	/*opens output file (if already exists it is deleted)...*/
	if (LFile_Exists (outFile))
		LFile_Remove (outFile);	
	theObject.mOutputFile=new syscall_file(outFile, file::RDWR|file::CREAT);
	
	theObject.mOutputVector=new stxxl::vector<ui4>(theObject.mOutputFile);
	
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
	delete ((*ThisA)->mInputVector);
	delete ((*ThisA)->mOutputVector);
	delete ((*ThisA)->mIt);

	delete ((*ThisA)->mInputFile);
	delete ((*ThisA)->mOutputFile);
	
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
*  CStreamPipe_Swap
*  ---------------------------------------------------------------------------------
*  Swap */
void CStreamPipe_Swap (CStreamPipe* This)
{	
	/*closes files...*/
	delete (This->mInputVector);
	delete (This->mOutputVector);
	delete (This->mIt);

	delete (This->mInputFile);
	delete (This->mOutputFile);
	
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
	This->mInputFile=new syscall_file(This->mTmpFileName, file::RDONLY);
	This->mInputVector=new stxxl::vector<ui4>(This->mInputFile);
	This->mIt=new stxxl::vector<ui4>::const_iterator(This->mInputVector->begin ());
	
	/*creates new output file...*/
	This->mOutputFile=new syscall_file(This->mOutputFileName, file::RDWR|file::CREAT);	
	This->mOutputVector=new stxxl::vector<ui4>(This->mOutputFile);
}

/* ---------------------------------------------------------------------------------
*  CStreamPipe_ReadNx functions
*  ---------------------------------------------------------------------------------
*  ReadNx */
Bool CStreamPipe_ReadN4 (CStreamPipe* This, void* outItem)
{
	stxxl::vector<ui4>::const_iterator theIt;
	stxxl::vector<ui4>::const_iterator theEnd;

	ui4* theData;

	theIt=*(This->mIt);
	theEnd=This->mInputVector->end ();

	theData=(ui4 *)outItem;

	if ( theIt!=theEnd )
	{
		//debugging...
		//printf ("%d ", *(*(This->mIt)));
		//fflush (stdout);

		*theData=*theIt;
		(*(This->mIt))++;
		return TRUE;
	}
	else
		return FALSE;
}

/* ---------------------------------------------------------------------------------
*  CStreamPipe_WriteNx functions
*  ---------------------------------------------------------------------------------
*  WriteNx */
void CStreamPipe_WriteN4 (CStreamPipe* This, void* outItem)
{
	ui4* theptr=(ui4*)outItem;

	This->mOutputVector->push_back (*theptr);
}


/* Copyright (C) 2006 Andrea Ribichini

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
