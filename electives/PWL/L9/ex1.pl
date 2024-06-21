:- use_module(library(clpfd)).

tasks([
    %D  R1 R2
    [2, 1, 3],
    [3, 2, 1],
    [4, 2, 2],
    [3, 3, 2],
    [3, 1, 1],
    [3, 4, 2],
    [5, 2, 1]
]).

%         R1 R2
resources(5, 5).

mt1([], _, [], [], _).
mt1([[D, R1, _] | L1], H, [task(S, D, E, R1, _) | L2], [S | L3], MS) :-
    S in 0..H,
    E #= S + D, 
    MS #>= E,
    mt1(L1, H, L2, L3, MS).

mt2([], _, [], [], _).
mt2([[D, _, R2] | L1], H, [task(S, D, E, R2, _) | L2], [S | L3], MS) :-
    S in 0..H,
    E #= S + D, 
    MS #>= E,
    mt2(L1, H, L2, L3, MS).

schedule(H, Ss, MS) :-
    tasks(L),
    resources(R1, R2),
    MS in 0..H,
    mt1(L, H, T1, Ss, MS),
    mt2(L, H, T2, Ss, MS),
    cumulative(T1, [limit(R1)]),
    cumulative(T2, [limit(R2)]),
    once(labeling([min(MS), ff], [MS | Ss])).


