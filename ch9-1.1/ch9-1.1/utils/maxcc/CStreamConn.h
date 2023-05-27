/* ============================================================================
 *  CStreamConn.h
 * ============================================================================

 *  Author:         (C) 2005 Andrea Ribichini
 *  License:        See the end of this file for license information
 *  Created:        September 19, 2005
 *  Module:         ??

 *  Last changed:   $Date: 2005/12/14 15:08:50 $
 *  Changed by:     $Author: ribbi $   
 *  Revision:       $Revision: 1.2 $    
*/

#ifndef __CStreamConn__
#define __CStreamConn__

#include "LType.h"
#include "LFile.h"

#ifdef __cplusplus
extern "C" {
#endif

/* COMPONENT ID */
#define CStreamConn_ID   ????

void            CStreamConn_BuildInstance         (i1* inFile, i1* outFile, ui4 inMemSize);

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
