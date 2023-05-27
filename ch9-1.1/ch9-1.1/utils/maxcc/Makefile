# ============================================================================
#  Makefile
# ============================================================================

#  Author:         (c) 2005 Camil Demetrescu
#  License:        See the end of this file for license information
#  Created:        Dec 12, 2005
 
#  Last changed:   $Date: 2006/01/19 09:03:49 $
#  Changed by:     $Author: demetres $
#  Revision:       $Revision: 1.8 $

LL = ../../lib/ll-core

all: cc.exe tiger2bin.exe bin2txt.exe largestcc.exe subgraph.exe

tiger2bin.exe:
	gcc -O4 -o tiger2bin.exe tiger2bin.c $(LL)/src/*.c  -I$(LL)/include/ -I. -lm

cc.exe:
	gcc -O4 -o cc.exe cc.c C*.c $(LL)/src/*.c  -I$(LL)/include/ -I. -lm

cc_stxxl.exe:
	g++ -o cc_stxxl.exe cc.c CStreamConn.c CStreamPipe.cpp $(LL)/src/*.c  -I$(LL)/include/ -I. -lm -L/home/ribbi/Dottorato/stxxl/stxxl/lib/ -lstxxl -lpthread -DSORT_OPT_PREFETCHING -DUSE_MALLOC_LOCK -DCOUNT_WAIT_TIME -I/home/ribbi/Dottorato/stxxl/stxxl/ -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -DSTXXL_USE_POSIX_MEMALIGN_ALLOC -D_XOPEN_SOURCE=600 -O3

bin2txt.exe:
	gcc -O4 -o bin2txt.exe bin2txt.c $(LL)/src/*.c  -I$(LL)/include/ -I. -lm

tiger2binEM.exe:
	gcc -O4 -o tiger2binEM.exe tiger2binEM.c $(LL)/src/*.c  -I$(LL)/include/ -I. -lm

largestcc.exe:
	gcc -O4 -o largestcc.exe largestcc.c C*.c $(LL)/src/*.c  -I$(LL)/include/ -I. -lm

subgraph.exe:
	gcc -O4 -o subgraph.exe subgraph.c C*.c $(LL)/src/*.c  -I$(LL)/include/ -I. -lm

clean:
	rm -f *.exe


# Copyright (C) 2005 Camil Demetrescu

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
