traverse(i, [H | T], Stack) :- 
    H =.. [_ | [Son | _]],
    append([Son], [H | T], Stack), !.

traverse(n, [H, Parent | T], Stack) :- 	
    Parent =.. X,
    append(_, [H, Brother | _], X),
    append([Brother], [Parent | T], Stack), !.

traverse(p, [H, Parent | T], Stack) :- 	
    Parent =.. X,
    append(_, [Brother, H | _], X),
    append([Brother], [Parent | T], Stack), !.

traverse(o, [ _ ], _).

traverse(o, [_, Parent | T], Stack) :- 	
    append([Parent], T, Stack), !.

traverse(_, X, X).

readAction([]).
readAction([H | T]) :- 	
    writeq(H),
    write('\ncommand: '),
    read(Command),
    traverse(Command, [H | T], Stack),
    readAction(Stack).

browse(Term) :- 
    readAction([Term]).