is_left(X, Y, [X, Y | _]).
is_left(X, Y, [_ | Z]) :-
    is_left(X, Y, Z).

adjacent(X, Y, List) :-
    is_left(X, Y, List).
adjacent(X, Y, List) :-
    is_left(Y, X, List).

rybki(Owner) :-
    Houses = [[1, _, norweg, _, _, _],
              [2, _, _, _, _, _],
              [3, _, _, _, mleko, _],
              [4, _, _, _, _, _],
              [5, _, _, _, _, _]],
    member([_, czerwony, anglik, _, _, _], Houses),
    member([_, _, dunczyk, _, herbata, _], Houses),
    member([_, zolty, _, _, _, cygara], Houses),
    member([_, _, niemiec, _, _, fajka], Houses),
    member([_, _, _, ptaki, _, bez_filtra], Houses),
    member([_, _, szwed, psy, _, _], Houses),
    adjacent([_, _, norweg, _, _, _], [_, niebieski, _, _, _, _], Houses),
    adjacent([_, _, _, konie, _, _], [_, zolty, _, _, _, _], Houses),
    member([_, _, _, _, piwo, mentolowe], Houses),
    member([_, zielony, _, _, kawa, _], Houses),
    adjacent([_, _, _, _, _, light], [_, _, _, _, woda, _], Houses),
    adjacent([_, _, _, _, _, light], [_, _, _, koty, _, _], Houses),
    is_left([_, zielony, _, _, _, _], [_, bialy, _, _, _, _], Houses), 
    member([_, _, Owner, rybki, _, _], Houses).