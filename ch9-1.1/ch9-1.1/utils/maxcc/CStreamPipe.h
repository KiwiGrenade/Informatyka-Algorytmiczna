/* ============================================================================
 *  CStreamPipe.h
 * ============================================================================

 *  Author:         (C) 2005 Andrea Ribichini
 *  License:        See the end of this file for license information
 *  Created:        September 14, 2005
 *  Module:         ??

 *  Last changed:   $Date: 2006/01/16 15:41:13 $
 *  Changed by:     $Author: demetres $   
 *  Revision:       $Revision: 1.3 $    
*/

#ifndef __CStreamPipe__
#define __CStreamPipe__

#include "LType.h"
#include "LFile.h"

#ifdef __cplusplus
extern "C" {
#endif

/* COMPONENT ID */
#define CStreamPipe_ID   ????

/* defines */

typedef struct CStreamPipe CStreamPipe;

struct CStreamPipe 
{
    i1*    mInputFileName;
    LFile* mInputFile;
    
    i1*    mOutputFileName;
    LFile* mOutputFile;
    
    i1     mTmpFileName[LFile_MAX_PATHNAME_LEN];
    Bool   mNoSwapYet;
};

CStreamPipe*    CStreamPipe_New                   (i1* inFile, i1* outFile);
void            CStreamPipe_Delete                (CStreamPipe** ThisA);

Bool            CStreamPipe_Read                  (CStreamPipe* This, void* outItem, ui4 inItemSize);
void            CStreamPipe_Write                 (CStreamPipe* This, void* outItem, ui4 inItemSize);
void            CStreamPipe_Swap                  (CStreamPipe* This);

Bool            CStreamPipe_ReadN1                (CStreamPipe* This, void* outItem);
Bool            CStreamPipe_ReadN2                (CStreamPipe* This, void* outItem);
Bool            CStreamPipe_ReadN4                (CStreamPipe* This, void* outItem);
Bool            CStreamPipe_ReadN8                (CStreamPipe* This, void* outItem);

void            CStreamPipe_WriteN1               (CStreamPipe* This, void* outItem);
void            CStreamPipe_WriteN2               (CStreamPipe* This, void* outItem);
void            CStreamPipe_WriteN4               (CStreamPipe* This, void* outItem);
void            CStreamPipe_WriteN8               (CStreamPipe* This, void* outItem);

#ifdef __cplusplus
}
#endif

#endif


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
