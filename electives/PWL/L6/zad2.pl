:- consult('zad1.pl').
:- consult('lexer.pl').
:- consult('interpreter.pl').

wykonaj(X) :- 	
    open(X, read, FD),
    scanner(FD, Tokens),
    close(FD),
    phrase(program(Instructions), Tokens),
    interpreter(Instructions).