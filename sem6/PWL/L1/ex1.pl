% Jakub Jaśków 268416
mężczyzna(jan).
mężczyzna(paweł).
mężczyzna(dominik).

kobieta(agata).
kobieta(izabela).
kobieta(eustacha).
kobieta(maria).


rodzic(jan, paweł).
rodzic(paweł, dominik).
rodzic(agata, paweł).
rodzic(izabela, dominik).
rodzic(eustacha, jan).
rodzic(agata, maria).

ojciec(X, Y) :-
	rodzic(X, Y),
	mężczyzna(X),
	X\=Y.

matka(X, Y) :-
	rodzic(X,Y),
	kobieta(X),
	X\=Y.

jest_matką(X) :-
	matka(X,Y),
	X\=Y .

jest_ojcem(X) :-
	ojciec(X,Y),
	X\=Y.

% każdy człowiek musi mieć rodzica, więc każdy mężczyzna jest czyimś synem.
jest_synem(X) :-
	mężczyzna(X).

dziadek(X, Y) :-
	ojciec(X, P),
	rodzic(P, Y).

rodzeństwo(X, Y) :-
	rodzic(P, X),
	rodzic(P, Y),
	X\=Y.
	
siostra(X, Y) :-
	rodzeństwo(X, Y),
	kobieta(X),
	X\=Y.
