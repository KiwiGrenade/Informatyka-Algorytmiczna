base_wyrazenie([X], X, X).
base_wyrazenie(List, Result, X+Y) :-
    apply_operator(List, X, Y, Value1, Value2),
    Result is Value1+Value2.
base_wyrazenie(List, Result, X-Y) :-
    apply_operator(List, X, Y, Value1, Value2),
    Result is Value1-Value2.
base_wyrazenie(List, Result, X*Y) :-
    apply_operator(List, X, Y, Value1, Value2),
    Result is Value1*Value2.
base_wyrazenie(List, Result, X/Y) :-
    apply_operator(List, X, Y, Value1, Value2),
    Value2=\=0,
    Result is Value1/Value2.

apply_operator(List, Expr1, Expr2, Value1, Value2) :-
    append([List1|List2], [List3|List4], List),
    base_wyrazenie([List1|List2], Value1, Expr1),
    base_wyrazenie([List3|List4], Value2, Expr2).

wyrazenie(L, V, E) :-
    base_wyrazenie(L, V, E),
    !.