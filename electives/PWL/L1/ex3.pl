% Jakub Jaśków 268416
% Check if number is prime
is_prime(2).
is_prime(3).
is_prime(P) :- 
   integer(P), 
   P > 3, 
   P mod 2 =\= 0, 
   \+ has_factor(P, 3).  

has_factor(N, L) :- 
   N mod L =:= 0.
has_factor(N,L) :- 
   L * L < N, 
   L2 is L + 2, 
   has_factor(N,L2).

% List prime numbers
prime(LO, HI, N) :- 
   A1 is (LO // 2) * 2 + 1, 
   p_list(A1, HI, N).

p_list(LO, HI, []) :- 
   LO > HI,
   !.
p_list(LO, HI, [LO|N]) :- 
   is_prime(LO), 
   !, 
   next(LO, A1), 
   p_list(A1, HI, N).

p_list(LO, HI, N) :- 
   next(LO, A1), 
   p_list(A1, HI, N).

next(2, 3) :- 
   !.
next(LO, A1) :- 
   A1 is LO + 2.

