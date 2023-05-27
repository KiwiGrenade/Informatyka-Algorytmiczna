/* ============================================================================
 *  renumber.c
 * ============================================================================

 *  Author:         Camil Demetrescu
 *  License:        See the end of this file for license information
 *  Created:        Nov 11, 2005

 *  Last changed:   $Date: 2006/10/30 08:09:39 $
 *  Changed by:     $Author: demetres $
 *  Revision:       $Revision: 1.7 $
*/

/* includes */
#include "LException.h"
#include "LMemory.h"
#include "LFile.h"
#include "LString.h"
#include "LArray.h"
#include "LHashStatic.h"
#include "LSystem.h"
#include "LMath.h"
#include <stdio.h>

/* constants */
#define LINE_SIZE       1024
#define BYTES_PER_NODE  50
#define BASE_ID         0    /* TIGER/Line node IDs go from 0 to n-1 */

/* prototypes */
void renumber(i1* inFileName, ui4 inApproxMemSize);

/* ---------------------------------------------------------------------------------
 *  main
 * ---------------------------------------------------------------------------------
*/
int main(int argc, char** argv) {

    /* print header */
    LSystem_Print("\n* 9th DIMACS Implementation Challenge: Shortest Paths\n");
    LSystem_Print(  "* http://www.dis.uniroma1.it/~challenge9\n");
    LSystem_Print(  "* TIGER/Line files node IDs renumbering\n\n");

    if (argc < 3) {
        LSystem_Print("Usage: > renumber memsize (in MBytes) inFileName\n");
        return 1;
    }

    /* start renumbering */
    renumber (argv[2], LString_ToUI4(argv[1]));

    return 0;
}


/* ---------------------------------------------------------------------------------
 *  renumber
 * ---------------------------------------------------------------------------------
*/
void renumber(i1* inFileName, ui4 inApproxMemSize){

    LException* theExc;
    FILE*  theInFile  = NULL;
    FILE*  theOutFile = NULL;
    LHashStatic* theHash    = NULL;

    i1* theToken;
    i1  theLine[LINE_SIZE];
    i1  theInName[LFile_MAX_PATHNAME_LEN];
    i1  theOutName[LFile_MAX_PATHNAME_LEN];

    ui4 theNumNodes, theNumArcs, theNumCached, theNumPasses, theIDCount, i, j;

    inApproxMemSize *= 1024*1024;

    Try {

        /* setup file names */
        LString_Copy(inFileName, theInName);
        LFile_GetTempName(theOutName);

        /* get number of nodes of input graph */
        theInFile = fopen(theInName, "r");
        if (!theInFile) goto err; 

        fgets (theLine, LINE_SIZE, theInFile);
        theNumNodes = LString_ToUI4(theLine);
        fclose(theInFile);

        LSystem_Print("* Number of nodes: %lu\n", theNumNodes);

        theNumCached = inApproxMemSize / BYTES_PER_NODE;
        theNumPasses = (ui4)LMath_Ceil((f8)theNumNodes / theNumCached);

        LSystem_Print("* Renumbered nodes per pass: %lu\n", theNumCached);
        LSystem_Print("* Number of passes to be performed: %lu\n", theNumPasses);
        LSystem_Print("* Temp file location: %s\n\n", theOutName);

        /* init ID counter (node IDs start from BASE_ID) */
        theIDCount = BASE_ID;

        /* make passes over the data */
        for (i=0 ; i < theNumPasses; ++i) {

            i1 theTempName[LFile_MAX_PATHNAME_LEN];

            /* progress report */
            LSystem_Print(">> Running pass %lu...\n", i+1);

            /* create hash table */
            theHash = LHashStatic_New(theNumCached*1.2);
            if (!theHash) goto err;

            /* open input file for read */
            theInFile = fopen(theInName, "r");
            if (!theInFile) goto err; 

            /* open output file for write */
            theOutFile = fopen(theOutName, "w");
            if (!theOutFile) goto err; 

            /* copy number of nodes */
            fgets (theLine, LINE_SIZE, theInFile);
            fprintf(theOutFile, "%s", theLine);

            /* progress report */
            LSystem_Print("-- Start node scanning...\n");

            /* scan nodes */
            for (j=0; j<theNumNodes; ++j) {

                i4 theID, theNewID;
                i4 theX, theY;

                /* read node line */        
                fgets (theLine, LINE_SIZE, theInFile);

                /* get node id */        
    			theToken = LString_Tokenizer (theLine, " ");
                theID = LString_ToI4(theToken);

                /* get x coord */        
    			theToken = LString_Tokenizer (NULL, " ");
                theX = LString_ToI4(theToken);

                /* get y coord */        
    			theToken = LString_Tokenizer (NULL, " ");
                theY = LString_ToI4(theToken);

                /* progress report */
                if (j>0 && (j % (theNumNodes/10)) == 0)
                    LSystem_Print("   * %lu%% done.\n", (ui4)LMath_Ceil(100*(j/(f8)theNumNodes)));

                /* renumbering/caching nodes */
                if (j >= i*theNumCached && j < (i+1)*theNumCached) {

                    /* get new ID */
                    theNewID = theIDCount++;

                    /* add item theNewID with key theID to the hash table */
                    LHashStatic_InsertItem(theHash, (void*)theNewID, theID);
                }

                /* writing through */
                else {
                    /* after the 1st pass, all node ids still to be
                       renumbered become negative */
                    if (i == 0) theNewID = -theID-1;
                    else        theNewID = theID;
                }

                /* format output line */
                LString_Format(theLine, "%ld %ld %ld\n", theNewID, theX, theY);

                /* write node line */
                fprintf(theOutFile, "%s", theLine);
            }

            /* copy number of arcs */
            fgets (theLine, LINE_SIZE, theInFile);
            fprintf(theOutFile, "%s", theLine);
            theNumArcs = LString_ToUI4(theLine);

            /* progress report */
            LSystem_Print("-- Start edge scanning...\n");

            /* scan arcs */
            for (j=0; j<theNumArcs; ++j) {

                i4 theSourceID, theTargetID;

                /* progress report */
                if (j>0 && (j % (theNumArcs/10)) == 0)
                    LSystem_Print("   * %lu%% done.\n", (ui4)LMath_Ceil(100*(j/(f8)theNumArcs)));

                /* read arc endpoins line */        
                fgets(theLine, LINE_SIZE, theInFile);

                /* get source node id */        
    			theToken = LString_Tokenizer (theLine, " ");
                theSourceID = LString_ToI4(theToken);

                /* get target node id */        
    			theToken = LString_Tokenizer (NULL, " ");
                theTargetID = LString_ToI4(theToken);

                /* renumber IDs, if they are in the hash table */
                if (LHashStatic_IsInTable(theHash, theSourceID))
                    theSourceID = (i4)LHashStatic_GetItemByKey(theHash, theSourceID);
                else if (i==0) theSourceID = -theSourceID-1;

                if (LHashStatic_IsInTable(theHash, theTargetID))
                    theTargetID = (i4)LHashStatic_GetItemByKey(theHash, theTargetID);
                else if (i==0) theTargetID = -theTargetID-1;

                /* write arc endpoint IDs line */
                LString_Format(theLine, "%ld %ld\n", theSourceID, theTargetID);
                fprintf(theOutFile, "%s", theLine);

                /* write through attr line */
                fgets (theLine, LINE_SIZE, theInFile);
                fprintf(theOutFile, "%s", theLine);
            }

            /* cleanup */
            fclose(theInFile);
            fclose(theOutFile);
            LHashStatic_Delete(&theHash);

            /* swap input and output file names if not the last pass */
            if (i + 1 < theNumPasses) {
                LString_Copy(theInName, theTempName);
                LString_Copy(theOutName, theInName);
                LString_Copy(theTempName, theOutName);
            }
        }

        /* remove input file */
        LFile_Remove(theInName);

        /* output file must have the same name as input file */
        if (LString_Compare(theOutName, inFileName) != 0)
            LFile_Rename(theOutName, inFileName);
    }

    Catch(theExc) {
        LException_Dump(theExc);
        goto err;
    }

    return;
    
  err:
    LSystem_Print("\n * Error: Cannot renumber node IDs...\n");
    return;   
}


/* Copyright (C) 2005 Camil Demetrescu

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

