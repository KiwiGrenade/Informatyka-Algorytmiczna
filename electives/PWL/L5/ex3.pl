in(i).
out(o).
next(n).
prev(p).

browse(Drzewo):-
    browse(Drzewo,[],[]).

browse(Korzen,Lewo,Prawo):-
    writeln(Korzen),
    write('command: '),
    read(Polecenie),
    (   in(Polecenie) -> (   Korzen =..[_,Korzen1 | Lewo1] ->
                             (   browse(Korzen1,Lewo1, []))
                         ; true
                         ) ; true
    ),
    (   next(Polecenie) ->
           (Lewo = [H2|R2] ->
                        (   I2 is 1,
                            append([Korzen],Prawo,Prawo2),
                            browse(H2, R2, Prawo2)
                        ) ; I2 is 0
           ) ; I2 is 0
    ),
    (   prev(Polecenie) ->
           (Prawo = [H3|R3] ->
                        (   I3 is 1,
                            append([Korzen], Lewo, Lewo3),
                            browse(H3, Lewo3, R3)
                        ) ;   I3 is 0
           ) ; I3 is I2
    ),
    (   (out(Polecenie); I3 = 1)-> true; browse(Korzen,Lewo,Prawo)).

