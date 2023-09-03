# Makefile

all: main

main: main.o palindrome.o
	clang -o main main.o palindrome.o

main.o: main.c
	clang -c main.c

palindrome.o: palindrome.c
	clang -c palindrome.c

clean:
	rm -f main 	*.o*`
