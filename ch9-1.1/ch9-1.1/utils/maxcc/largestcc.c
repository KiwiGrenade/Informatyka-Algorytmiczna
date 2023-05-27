/* ============================================================================
 *  largestcc.c
 * ============================================================================

 *  Author:         (C) 2006 Camil Demetrescu
 *  License:        See the end of this file for license information
 *  Created:        Jan 14, 2006
 *  Module:         stream
 *  Notes:          extracts the largest cc

 *  Last changed:   $Date: 2006/02/16 20:53:42 $  
 *  Changed by:     $Author: demetres $
 *  Revision:       $Revision: 1.3 $
*/

/* includes */
#include "LSystem.h"
#include "LString.h"
#include "LMemory.h"
#include "LFile.h"
#include "LHash.h"
#include "CStreamPipe.h"

/* constants */
#define PRINT_CCS        1
#define BYTES_PER_NODE   4
#define APPNAME          "largestcc"

/* types */
typedef struct {
    ui4 mComp, mCount;
} TPair;

int main (int argc, char** argv) {

    ui4    theMemSize, theMaxNodes, i;
    i1*    theInput;
    i1*    theOutput;
    ui4    theReadCCs;
    ui4    thePass = 0;
    Bool   theSelfLoops = FALSE;
    TPair  theMax;
    TPair* theCounters   = NULL;
    LHash* theHash       = NULL;
    CStreamPipe* thePipe = NULL;

    /* param check */
    if (argc < 4) {
        LSystem_Print("Usage: %s memsize input-file output-file\n", APPNAME);
        goto err;
    }

    /* fetch params */
    theMemSize  = LString_ToUI4(argv[1]);
    theInput    = argv[2];
    theOutput   = argv[3];
    theMaxNodes = theMemSize / BYTES_PER_NODE;

    LSystem_Print("[%s] Extracting the largest connected component\n", APPNAME);    
    LSystem_Print("[%s] Input file: %s\n", APPNAME, theInput);    
    LSystem_Print("[%s] Output file: %s\n", APPNAME, theOutput);    
    LSystem_Print("[%s] Max number of CCs per pass: %lu\n", APPNAME, theMaxNodes);    

    /* init data structures */
    theCounters = (TPair*)LMemory_Malloc(theMaxNodes * sizeof(TPair));
    if (theCounters == NULL) {
        LSystem_Print("[%s] Failed to allocate table of counters\n", APPNAME);    
        goto err;
    }

    thePipe = CStreamPipe_New(theInput, theOutput);
    if (thePipe == NULL) {
        LSystem_Print("[%s] Failed to create stream pipeline\n", APPNAME);    
        goto err;
    }

    /* init largest component specifier */
    theMax.mCount = theMax.mComp = 0;

    /* perform passes over the data */
    for (;;) {

        LSystem_Print("[%s] Starting pass %lu\n", APPNAME, ++thePass);

        /* create hash table */
        theHash = LHash_New();
        if (theHash == NULL) {
            LSystem_Print("[%s] Failed to allocate hash table\n", APPNAME);    
            goto err;
        }

        /* reset CC counter */
        theReadCCs = 0;

        /* scan input stream */
        for (;;) {

            ui4  theNode, theComp;
            TPair* thePtr;

            /* read pair (node, component) from input stream */
            if (!CStreamPipe_ReadN4(thePipe, &theNode)) break;
            if (!CStreamPipe_ReadN4(thePipe, &theComp))  {
                LSystem_Print("[%s] Invalid input file format\n", APPNAME);    
                goto err;
            }

            if (theNode == theComp) theSelfLoops = TRUE;

            /* check if the component has already been encountered */
            thePtr = LHash_GetItemByKey(theHash, theComp);

            /* the component is new */
            if (thePtr == NULL) {

                /* no more room for CCs: write pair to output stream */
                if (theReadCCs >= theMaxNodes) {
                    CStreamPipe_WriteN4(thePipe, &theNode);
                    CStreamPipe_WriteN4(thePipe, &theComp);
                }

                /* add CC to the hash table */
                else {
                    thePtr = &theCounters[theReadCCs];
                    thePtr->mComp  = theComp;
                    thePtr->mCount = 1;
                    LHash_InsertItem(theHash, thePtr, theComp);
                    theReadCCs++;
                }
            }

            /* increase component count */
            if (thePtr != NULL) thePtr->mCount++;
        }

        /* delete hash table */
        LHash_Delete(&theHash);

        /* if no more new components were found, then stop */
        if (theReadCCs == 0) break;

        /* find largest component */
        for (i = 0; i < theReadCCs; ++i) {
            if (theCounters[i].mCount > theMax.mCount)
                theMax = theCounters[i];

            #if PRINT_CCS
            LSystem_Print("[%s] Component %-6lu - Size %-6lu\n", 
                APPNAME, theCounters[i].mComp, theCounters[i].mCount);                
            #endif
        }

        /* swap input and output streams */
        CStreamPipe_Swap(thePipe);

        /* print pass report */
        LSystem_Print("[%s] %lu components found in this pass\n", 
            APPNAME, theReadCCs);
        LSystem_Print("[%s] Current largest CC: %lu (size = %lu)\n", 
            APPNAME, theMax.mComp, theMax.mCount);
        LSystem_Print("[%s] %self loops found\n", 
            APPNAME, theSelfLoops ? "S":"No s");
    }

    /* cleanup */
    CStreamPipe_Delete(&thePipe);
    LMemory_Free(&theCounters);
    
    /* skip if empty graph */
    if (theMax.mCount == 0) return 0;
    
    /* create new stream pipeline */
    thePipe = CStreamPipe_New(theInput, theOutput);
    if (thePipe == NULL) {
        LSystem_Print("[%s] Failed to create stream pipeline\n", APPNAME);    
        goto err;
    }

    LSystem_Print("[%s] Writing output file\n", APPNAME);    

    /* write component representative */
    CStreamPipe_WriteN4(thePipe, &theMax.mComp);

    /* scan input stream and write to output stream all nodes in the largest cc */
    for (;;) {
            ui4  theNode, theComp;

            /* read pair (node, component) from input stream */
            if (!CStreamPipe_ReadN4(thePipe, &theNode)) break;
            if (!CStreamPipe_ReadN4(thePipe, &theComp))  {
                LSystem_Print("[%s] Invalid input file format\n", APPNAME);    
                goto err;
            }

            /* write node if it belongs to the largest cc */
            if (theComp == theMax.mComp)
                CStreamPipe_WriteN4(thePipe, &theNode);
    }
    
    LSystem_Print("[%s] Done\n", APPNAME);

    /* cleanup */
    CStreamPipe_Delete(&thePipe);

    return 0;

  err:
    LSystem_Exit();
}


/* Copyright (C) 2006 Camil Demetrescu

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

