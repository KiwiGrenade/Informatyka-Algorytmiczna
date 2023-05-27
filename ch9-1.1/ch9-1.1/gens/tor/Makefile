# ============================================================================
#  Makefile
# ============================================================================

#  Author(s)       (c) 2006 Andrew Goldberg, Camil Demetrescu
#  Created:        jan 12, 2006

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

CC       = gcc
CFLAGS   = -O6 -DNDEBUG -DPERMUTE_NODES  -I ../../lib -I ../../lib/ll-core/include
#CFLAGS  = -O6 -Wall -DNDEBUG
#CFLAGS  = -g -Wall
LDFLAGS  = 
LOADLIBS = -lm        # the name used by the automatic linker rule

LIB      = ../../lib/

all: tor.exe

tor.exe: tor.c $(LIB)random.c $(LIB)permute.c
	$(CC) $(CFLAGS) -o tor.exe tor.c $(LOADLIBS) -I$(LIB) ../../lib/ll-core/src/*.c

clean:
	rm -f *~ tor.exe

