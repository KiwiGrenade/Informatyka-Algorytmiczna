all: haskell lisp sml

haskell: ex1.hs
	ghc ex1.hs -o ex1-haskell

clean-haskell:
	rm -f ex1-haskell ex1.hi ex1.o

# To run lisp: clisp ex1.lisp
# To run sml: sml < ex1.sml
# To run prolog:
# 	1. $ prolog
#	2. ? - [ex2.pl].
clean: clean-haskell
