sum_list([],0).

sum_list([A|B],S) :-
	sum_list(B,Tmp),
	S is A + Tmp.

iterate([],_,0).

iterate([A|B],A,R) :-
	iterate(B,A,Rest),
	R is (A-A)*(A-A) + Rest.

avg(L,A,Len) :-
	sum_list(L,S),
	length(L,Len),
	Len>0,
	A is S/Len.

wariancja(L,D) :-
	avg(L,A,Len),
	iterate(L,A,R),
	D is R/Len.