% counts the number of elements in a list
liczba_elementów([_|Tail], Count) :-
    liczba_elementów(Tail, CountTail),
    Count is CountTail + 1,
    !.
liczba_elementów([_|_], 1).

% finds the middle element of a list
środkowy(List, Middle) :-
    liczba_elementów(List, Count),
    MiddleIndex is round(Count / 2),
    MiddleIndex =:= (Count / 2) + 0.5,
    nth1(MiddleIndex, List, Middle).

