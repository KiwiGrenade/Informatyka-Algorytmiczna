C = gcc
CC = g++

CFLAGS   = -ansi -O6 -DNDEBUG -I ../../lib -I ../../lib/ll-core/include
CCFLAGS   = -ansi -O6 -DNDEBUG -I ../../lib -I ../../lib/ll-core/include
#CCFLAGS = -ansi -Wall -O6 -g -DALLSTATS
LDFLAGS = 
LOADLIBES = -lm        # the name used by the automatic linker rule
MLBFLAGS = -DMLB

SRCS = main.cc sp.cc smartq.cc parser_gr.cc
CODES = mb.exe

all: $(CODES)


mb.exe: $(SRCS)
	$(C) -c $(CCFLAGS) $(MLBFLAGS) ../../lib/ll-core/src/*.c
	$(CC) $(CCFLAGS) $(MLBFLAGS) -o mb.exe $(SRCS) *.o  $(LOADLIBES)
clean:
	rm -f *~ mb.exe *.o

