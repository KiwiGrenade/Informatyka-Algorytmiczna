arc(a, b).
arc(b, a).
arc(b, c).
arc(c, d).

% osiągalny/2 checks if Y is reachable from X
osiągalny(X, X).
osiągalny(X, Y) :- reachable(X, Y, [X]).

% reachable/3 checks if Y is reachable from X with a list of visited nodes L
reachable(X, Y, Visited) :-
    arc(X, Z),
    \+ member(Z, Visited),
    (
        Y = Z
        ;
        reachable(Z, Y, [Z | Visited])
    ).

