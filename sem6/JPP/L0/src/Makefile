.PHONY: all clean

PROGRAMS = c cpp java go haskell ada clisp sml prolog

all: $(PROGRAMS)

c: HelloWorld.c	
	$(CC) -o c HelloWorld.c
	./c
	@echo

cpp: HelloWorld.cpp
	$(CXX) -o cpp HelloWorld.cpp
	./cpp
	@echo

java: HelloWorld.java
	javac HelloWorld.java
	java HelloWorld
	@echo

go: HelloWorld.go
	go run HelloWorld.go
	@echo

haskell: HelloWorld.hs
	ghc -o haskell HelloWorld.hs
	./haskell
	@echo

ada: HelloWorld.adb	
	gnatmake -o ada HelloWorld.adb
	./ada
	@echo

clisp: HelloWorld.lisp	
	clisp -q HelloWorld.lisp
	@echo

sml: HelloWorld.sml	
	sml < HelloWorld.sml
	@echo

prolog: HelloWorld.pl	
	swipl -q -s HelloWorld.pl -t main
	@echo

clean:
	rm -f $(PROGRAMS)
	rm -f HelloWorld.class
	rm -f *.o
	rm -f *.ali

