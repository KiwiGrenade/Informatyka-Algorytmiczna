% Merging two sorted lists
merge([], L2, L2).
merge(L1, [], L1).
merge([Head1|Tail1], [Head2|Tail2], [Head1|T]) :-
    Head1 =< Head2,
    merge(Tail1, [Head2|Tail2], T).
merge([Head1|Tail1], [Head2|Tail2], [Head2|T]) :-
    Head1 > Head2,
    merge([Head1|Tail1], Tail2, T).

% Splitting a list into two halves
split([], [], []).
split([X], [X], []).
split([Head1,Head2|Tail], [Head1|Tail1], [Head2|Tail2]) :-
    split(Tail, Tail1, Tail2).

% Merge sort implementation
mergesort([], []).
mergesort([X], [X]).
mergesort(List, Sorted) :-
    List = [_,_|_], % At least two elements
    split(List, List1, List2),
    mergesort(List1, Sorted1),
    mergesort(List2, Sorted2),
    merge(Sorted1, Sorted2, Sorted).

% Greatest Common Divisor (GCD) using Extended Euclidean Algorithm
gcd(A, 0, A, 1, 0).
gcd(A, B, G, X, Y) :-
    B \= 0,
    Q is A // B,
    R is A mod B,
    gcd(B, R, G, X1, Y1),
    X is Y1,
    Y is X1 - Q * Y1.

% Solving Diophantine equation
diophantine_equation(A, B, X, Y, G) :-
    gcd(A, B, G, X, Y).

% Prime number check
is_prime(2).
is_prime(3).
is_prime(N) :-
    N > 3,
    N mod 2 =\= 0,
    \+ has_factor(N, 3).

% Checking for factors
has_factor(N, F) :-
    N mod F =:= 0.
has_factor(N, F) :-
    F * F < N,
    F2 is F + 2,
    has_factor(N, F2).

% Finding the smallest prime factor
smallest_prime_factor(N, F) :-
    smallest_prime_factor(N, F, 2).

smallest_prime_factor(N, N, _) :- is_prime(N).
smallest_prime_factor(N, F, D) :-
    D * D =< N,
    (N mod D =:= 0 -> F = D ; D1 is D + 1, smallest_prime_factor(N, F, D1)).

% Prime factorization
prime_factors(1, []).
prime_factors(N, [F|Factors]) :-
    N > 1,
    smallest_prime_factor(N, F),
    N1 is N // F,
    prime_factors(N1, Factors).

% GCD without extended results
gcd_simple(A, 0, A).
gcd_simple(A, B, G) :-
    B \= 0,
    R is A mod B,
    gcd_simple(B, R, G).

% Euler's Totient function
totient(1, 1).
totient(N, T) :-
    N > 1,
    totient(N, N, 0, T).

totient(_, 0, Acc, Acc).
totient(N, I, Acc, T) :-
    I > 0,
    gcd_simple(N, I, 1),
    NewAcc is Acc + 1,
    NewI is I - 1,
    totient(N, NewI, NewAcc, T).
totient(N, I, Acc, T) :-
    I > 0,
    \+ gcd_simple(N, I, 1),
    NewI is I - 1,
    totient(N, NewI, Acc, T).

% Sieve of Eratosthenes
sieve([], []).
sieve([P|Xs], [P|Ys]) :-
    exclude(multiple_of(P), Xs, Zs),
    sieve(Zs, Ys).

multiple_of(P, X) :-
    X mod P =:= 0.

% Generate list of numbers from 2 to N
numlist(2, N, List) :- findall(X, between(2, N, X), List).

% Find primes up to N
primes(N, Primes) :-
    N >= 2,
    numlist(2, N, List),
    sieve(List, Primes).

test_all :-
    
    nl,
    mergesort([10, 22, 18, 12091, 2, 3, 4, 2, 1, 3], S),
    write('mergesort([10, 22, 18, 12091, 2, 3, 4, 2, 1, 3], S) = '), write(S), nl,
    
    nl,
    diophantine_equation(20, 25, X, Y, G),
    write('diophantine_equation(20, 25, X, Y, G) = '), write((X, Y, G)), nl,
    
    nl,
    prime_factors(50, F),
    write('prime_factors(100, F) = '), write(F), nl,
    
    nl,
    totient(50, V),
    write('totient(100, V) = '), write(V), nl,
    
    nl,
    primes(50, P),
    write('primes(100, P) = '), write(P), nl.
