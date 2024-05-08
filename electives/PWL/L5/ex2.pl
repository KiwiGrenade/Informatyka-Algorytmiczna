board(N) :-
    hetmany(N, X),
    draw(X, 1, N).

draw(_, Row, N) :-
    Row > N,
    dashed(N),
    nl,
    !.

draw(Queens, Row, N) :-
    dashed(N),
    RowRed is N + 1 - Row,
    row(RowRed, 1, Queens, N),
    row(RowRed, 1, Queens, N),
    Row1 is Row +1,
    draw(Queens, Row1, N),
    !.

row(_, Col, _, N) :-
    N + 1 =:= Col,
    write('|'),
    nl,
    !.

row(Row, Col, Tab, N) :-
    nth1(Col, Tab, Row),
    (   (((Row + N + 1) mod 2 =:= 0, Col mod 2 =:= 1)
        ;((Row + N + 1) mod 2 =:= 1, Col mod 2 =:= 0)
        ) -> write('|:###:') ; write('| ### ')
    ),
    Col1 is Col + 1,
    row(Row, Col1, Tab,N),
    !.

row(Row, Col, Tab, N) :-
    (   (((Row + N + 1) mod 2 =:= 0, Col mod 2 =:= 1)
        ;((Row + N + 1) mod 2 =:= 1, Col mod 2 =:= 0)
        ) -> write('|:::::') ; write('|     ')
    ),
    Col1 is Col + 1,
    row(Row, Col1, Tab,N),
    !.

dashed(0) :-
    write('+'),
    nl,
    !.

dashed(N) :-
    write('+-----'),
    N1 is N - 1,
    dashed(N1).

hetmany(N, P) :-
    between(1, 100, N),
    numlist(1, N, L),
    permutation(L,P),
    dobra(P).

dobra(P) :-
    \+ zla(P).

zla(P) :-
    append(_, [Wi | L1], P),
    append(L2, [Wj | _ ], L1),
    length(L2, K),
    abs(Wi - Wj) =:= K + 1.