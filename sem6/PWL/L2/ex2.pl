% jednokrotnie/2 checks if an element occurs only once in a list
jednokrotnie(X, L) :-
    select(X, L, L1),
    \+ member(X, L1).

% dwukrotnie/2 checks if an element occurs exactly twice in a list
dwukrotnie(E,L) :- 
    append(B1,[E|A1],L), 
    \+ member(E,B1), 
    append(B2,[E|A2],A1), 
    \+ member(E,B2), 
    \+ member(E,A2).
