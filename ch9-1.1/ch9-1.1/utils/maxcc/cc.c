/* ============================================================================
 *  cc.c
 * ============================================================================

 *  Author:         (c) 2005 Camil Demetrescu, Andrea Ribichini
 *  License:        See the end of this file for license information
 *  Created:        Dec 12, 2005
 
 *  Last changed:   $Date: 2006/01/16 15:41:13 $
 *  Changed by:     $Author: demetres $
 *  Revision:       $Revision: 1.5 $

 *  Notes:          compute the connected components of a graph given as list
 *                  of edges in big-endian binary format (ui4 pairs)
*/

#include "LSystem.h"
#include "LFile.h"
#include "LString.h"
#include "CStreamConn.h"

int main (int argc, char** argv)
{

	ui4  theApproxMemSize;
    /*Bool theRes;*/

	if (argc < 4) {
        LSystem_Print("Usage: cc.exe memSize inFile outFile\n");
        LSystem_Exit();
	}

	theApproxMemSize = LString_ToUI4(argv[1])*1024;

    LSystem_Print("Computing connected components\n\n");
    LSystem_Print("Input file: [%s]\n", argv[2]);
    LSystem_Print("Output file: [%s]\n", argv[3]);
    LSystem_Print("Working memory size: %lu bytes\n", theApproxMemSize);

    /*theRes =*/ CStreamConn_BuildInstance(argv[2], argv[3], theApproxMemSize);

    /*LSystem_Print("Input file %s is %s\n", argv[2], theRes ? "connected" : "not connected");*/

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
