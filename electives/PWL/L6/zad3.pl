g1 --> [].
g1 --> 
    [a], 
    g1, 
    [b].

g2 --> 
    a(X), 
    b(X), 
    c(X).

a(0) --> [].
a(N) --> 
    [a], 
    a(N1), 
    {N is N1 + 1}.
b(0) --> [].
b(N) --> 
    [b], 
    b(N1), 
    {N is N1 + 1}.
c(0) --> [].
c(N) --> 
    [c], 
    c(N1),
    {N is N1 + 1}.

fib(0, 0).
fib(1, 1).
fib(N, FIB_N) :-
    N > 1,
    N2 is N - 2,
    N1 is N - 1,
    fib(N2, FIB_N2),
    fib(N1, FIB_N1),
    FIB_N is FIB_N1 + FIB_N2.

g3 --> 
    a(N), 
    b(FIB_N), 
    {fib(N, FIB_N)}.

p([]) --> [].
p([X|Xs]) -->
    [X],
    p(Xs).

% phrase(p(L1), L2, L3).