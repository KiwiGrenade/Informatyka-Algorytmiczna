base_wyrazenie([X], X, X).
base_wyrazenie(List, Result, X+Y) :-
    apply_operator(List, X, Y, Temp1, Temp2),
    Result is Temp1+Temp2.
base_wyrazenie(List, Result, X-Y) :-
    apply_operator(List, X, Y, Temp1, Temp2),
    Result is Temp1-Temp2.
base_wyrazenie(List, Result, X*Y) :-
    apply_operator(List, X, Y, Temp1, Temp2),
    Result is Temp1*Temp2.
base_wyrazenie(List, Result, X/Y) :-
    apply_operator(List, X, Y, Temp1, Temp2),
    Temp2=\=0,
    Result is Temp1/Temp2.

apply_operator(List, Expr1, Expr2, Temp1, Temp2) :-
    append([List1|List2], [List3|List4], List),
    base_wyrazenie([List1|List2], Temp1, Expr1),
    base_wyrazenie([List3|List4], Temp2, Expr2).

wyrazenie(L, V, E) :-
    base_wyrazenie(L, V, E), !.