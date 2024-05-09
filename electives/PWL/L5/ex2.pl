main(X):-
    hetmany(_,X),
    board(X).

board(X):-
    length(X,L),
    rysuj(X,1,L).

rysuj(_,Nk,Roz):-
    Nk > Roz,
    draw_dotted(Roz),
    nl,
    !.

rysuj(Tab,Nk,Roz):-
    draw_dotted(Roz),
    Y is Roz - Nk +1,
    draw_line(1,Y,Tab,Roz),
    draw_line(1,Y,Tab,Roz),
    Nk1 is Nk +1,
    rysuj(Tab,Nk1,Roz),
    !.

draw_line(Nw,_,_,Roz):-
    Roz + 1 =:= Nw,
    write('|'),
    nl,
    !.

draw_line(Nw,Nk,Tab,Roz):-
    nth1(Nw,Tab,Nk),
    (   ((Nw mod 2 =:= 0, Nk mod 2 =:= 1)
        ;(Nw mod 2 =:= 1, Nk mod 2 =:= 0)
        ) -> write('|:###:') ; write('| ### ')
    ),
    Nw1 is Nw + 1,
    draw_line(Nw1,Nk,Tab,Roz),
    !.

draw_line(Nw,Nk,Tab,Roz):-
    (   ((Nw mod 2 =:= 0, Nk mod 2 =:= 1)
        ;(Nw mod 2 =:= 1, Nk mod 2 =:= 0)
        ) -> write('|:::::') ; write('|     ')
    ),
    Nw1 is Nw + 1,
    draw_line(Nw1,Nk,Tab,Roz),
    !.



draw_dotted(0):-
    write('+'),
    nl,
    !.
draw_dotted(Rozmiar):-
    write('+-----'),
    R is Rozmiar -1,
    draw_dotted(R).

hetmany(N, P):-
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
