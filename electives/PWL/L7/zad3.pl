filozofowie():-
    mutex_create(F1),
    mutex_create(F2),
    mutex_create(F3),
    mutex_create(F4),
    mutex_create(F5),
    thread_create(filozof(1,F1,F5),_,[detached(true)]),
    thread_create(filozof(2,F2,F1),_,[detached(true)]),
    thread_create(filozof(3,F3,F2),_,[detached(true)]),
    thread_create(filozof(4,F4,F3),_,[detached(true)]),
    thread_create(filozof(5,F5,F4),_,[detached(true)]).
filozof(ID,FL,FR):-
    random(R1),
    R is R1/200,
    sleep(R),
    format('[~w] mysli~n',[ID]),
    format('[~w] chce prawy widelec~n',[ID]),
    mutex_lock(FR),
    format('[~w] podniosl prawy widelec~n',[ID]),
    format('[~w] chce lewy widelec~n',[ID]),
    mutex_lock(FL),
    format('[~w] podniosl lewy widelec~n',[ID]),
    format('[~w] je~n',[ID]),
    format('[~w] odklada lewy widelec~n',[ID]),
    mutex_unlock(FL),
    format('[~w] odklada prawy widelec~n',[ID]),
    mutex_unlock(FR),
    filozof(ID,FL,FR).

