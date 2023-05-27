# ============================================================================
#  Makefile
# ============================================================================

#  Author:         (c) 2005 Camil Demetrescu, Andrea Ribichini
#  License:        See the end of this file for license information
#  Created:        November 7, 2005
 
#  Last changed:   $Date: 2005/12/13 16:45:28 $
#  Changed by:     $Author: demetres $
#  Revision:       $Revision: 1.4 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

#  Usage: > make        (Build up the binaries)
#  Usage: > make clean  (Clean up the binaries)


LL = ../../lib/ll-core

all: cutter.exe renumber.exe

cutter.exe: cutter.c 
	gcc -O4 -o cutter.exe cutter.c $(LL)/src/*.c  -I $(LL)/include/ -lm

renumber.exe: renumber.c
	gcc -O4 -o renumber.exe renumber.c $(LL)/src/*.c  -I $(LL)/include/ -lm

clean:
	rm -f *~ *.exe

# Copyright (C) 2005 Camil Demetrescu, Andrea Ribichini

 #  This program is free software; you can redistribute it and/or modify
 #  it under the terms of the GNU General Public License as published by
 #  the Free Software Foundation; either version 2 of the License, or
 #  (at your option) any later version.

 #  This program is distributed in the hope that it will be useful,
 #  but WITHOUT ANY WARRANTY; without even the implied warranty of
 #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #  GNU General Public License for more details.

 #  You should have received a copy of the GNU General Public License
 #  along with this program; if not, write to the Free Software
 #  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA 
