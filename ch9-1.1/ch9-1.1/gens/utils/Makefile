# ============================================================================
#  Makefile
# ============================================================================

#  Author(s)       (c) 2006 Andrew Goldberg, Camil Demetrescu
#  Created:        Jan 12, 2006

CC       = g++
CFLAGS   = -O6 -Wall -DNDEBUG
LDFLAGS  = 

LIB      = ../../lib/

all: potTrans.exe

potTrans.exe: potTrans.c $(LIB)random.c
	$(CC) $(CFLAGS) -o potTrans.exe potTrans.c $(LOADLIBS) -I$(LIB)

clean:
	rm -f *~ potTrans.exe

