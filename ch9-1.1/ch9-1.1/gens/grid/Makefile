# ============================================================================
#  Makefile
# ============================================================================

#  Author(s)       (c) 2005 Andrew Goldberg, Camil Demetrescu
#  Created:        Nov 10, 2005

#  Last changed:   $Date: 2006/04/13 17:49:58 $
#  Changed by:     $Author: goldberg $
#  Revision:       $Revision: 1.6 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

CC       = gcc
CFLAGS   = -O6 -DNDEBUG -DPERMUTE_NODES  -I ../../lib -I ../../lib/ll-core/include
#CFLAGS   = -O6 -DNDEBUG -I ../../lib -I ../../lib/ll-core/include
#CFLAGS  = -O6 -Wall -DNDEBUG
LDFLAGS  = 
LOADLIBS = -lm        # the name used by the automatic linker rule

LIB      = ../../lib/

all: spgrid.exe

spgrid.exe: spgrid.c $(LIB)random.c $(LIB)permute.c
	$(CC) $(CFLAGS) -o spgrid.exe spgrid.c $(LOADLIBS) -I$(LIB) ../../lib/ll-core/src/*.c

clean:
	rm -f *~ spgrid.exe

