even_perm([], []).

even_perm( [X|T], Ys ) :-
	even_perm( T, PrevYs ),
	add_odd( X, PrevYs, Ys ).

even_perm( [X|T], Ys ) :-
	odd_permutation( T, PrevYs ),
	add_even( X, PrevYs, Ys ).

odd_permutation( [X|T], Ys ) :-
	odd_permutation( T, PrevYs ),
	add_odd( X, PrevYs, Ys ).

odd_permutation( [X|T], Ys ) :-
	even_perm( T, PrevYs ),
	add_even( X, PrevYs, Ys ).

add_odd( X, PrevList, [X|PrevList] ).

add_odd( X, [Y,Z|PrevList], [Y,Z|List] ) :-
	add_odd( X, PrevList, List ).

add_even( X, [Y|PrevList], [Y,X|PrevList] ).
add_even( X, [Y,Z|PrevList], [Y,Z|List] ) :-
	add_even( X, PrevList, List ).