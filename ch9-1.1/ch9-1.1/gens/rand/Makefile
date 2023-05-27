# ============================================================================
#  Makefile
# ============================================================================

#  Author(s)       (c) 2005 Andrew Goldberg, Camil Demetrescu
#  Created:        Nov 10, 2005

#  Last changed:   $Date: 2006/03/19 15:55:52 $
#  Changed by:     $Author: goldberg $
#  Revision:       $Revision: 1.2 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

CC       = gcc
CFLAGS   = -O6 -DNDEBUG -DPERMUTE_NODES -I ../../lib -I ../../lib/ll-core/include
#CFLAGS  = -O6 -Wall -DNDEBUG
LDFLAGS  = 
LOADLIBS = -lm        # the name used by the automatic linker rule

LIB      = ../../lib/

all: sprand.exe

sprand.exe: sprand.c $(LIB)random.c $(LIB)permute.c
	$(CC) $(CFLAGS) -o sprand.exe sprand.c $(LOADLIBS) ../../lib/ll-core/src/*.c

clean:
	rm -f *~ sprand.exe

