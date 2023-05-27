/* ============================================================================
 *  CStreamPipe.hpp
 * ============================================================================

 *  Author:         (C) 2006 Andrea Ribichini
 *  License:        See the end of this file for license information
 *  Created:        January 3, 2006
 *  Module:         ??

 *  Last changed:   $Date: 2006/01/04 15:25:21 $
 *  Changed by:     $Author: ribbi $   
 *  Revision:       $Revision: 1.1 $    
*/

#ifndef __CStreamPipe__
#define __CStreamPipe__

#include <stxxl>

#include "LType.h"
#include "LFile.h"

#ifdef __cplusplus
extern "C" {
#endif

/* COMPONENT ID */
#define CStreamPipe_ID   ????

/* defines */

using stxxl::syscall_file;
using stxxl::file;

typedef struct CStreamPipe CStreamPipe;

struct CStreamPipe 
{
    i1*                                 mInputFileName;
    syscall_file*                       mInputFile;
    stxxl::vector<ui4>*                 mInputVector;
    stxxl::vector<ui4>::const_iterator* mIt;
    
    i1*                                 mOutputFileName;
    syscall_file*                       mOutputFile;
    stxxl::vector<ui4>*                 mOutputVector;
    
    i1                                  mTmpFileName[LFile_MAX_PATHNAME_LEN];
    Bool                                mNoSwapYet;
};

CStreamPipe*    CStreamPipe_New                   (i1* inFile, i1* outFile);
void            CStreamPipe_Delete                (CStreamPipe** ThisA);
void            CStreamPipe_Swap                  (CStreamPipe* This);
Bool            CStreamPipe_ReadN4                (CStreamPipe* This, void* outItem);
void            CStreamPipe_WriteN4               (CStreamPipe* This, void* outItem);

#ifdef __cplusplus
}
#endif

#endif


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
