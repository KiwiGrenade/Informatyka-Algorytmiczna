# Shortest paths with nagative cycle detection
# Written by Andrew V. Goldberg and Boris V. Cherkassky, 1996, 1998

CCOMP = g++
CFLAGS = -O4 -DNDEBUG -DWALL -I../../lib
#CFLAGS = -g -DWALL -I../../lib

all: bfct.exe gorc.exe bfctC.exe gorcC.exe

bfct.exe: types_simp.h queue.h parser_gr.cc parser_ss.cc globals.h bfct.c usef_def.h spc.c
	$(CCOMP) $(CFLAGS) -o bfct.exe -Dbfct spc.c

bfctC.exe: types_simp.h queue.h parser_gr.cc parser_ss.cc globals.h bfct.c usef_def.h spc.c
	$(CCOMP) $(CFLAGS) -DCHECKSUM -o bfctC.exe -Dbfct spc.c

gorc.exe: types_gor.h stack.h parser_gr.cc parser_ss.cc globals.h gorc.c usef_def.h spc.c
	$(CCOMP) $(CFLAGS) -o gorc.exe -Dgorc spc.c

gorcC.exe: types_gor.h stack.h parser_gr.cc parser_ss.cc globals.h gorc.c usef_def.h spc.c
	$(CCOMP) $(CFLAGS) -DCHECKSUM -o gorcC.exe -Dgorc spc.c

clean:
	rm -f *~ bfct.exe gorc.exe bfctC.exe gorcC.exe

