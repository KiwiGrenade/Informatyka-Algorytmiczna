merge(IN1,IN2,OUT):-
    freeze(IN1,
    (   IN1 = [H1|R1]
    -> freeze(IN2,
        (   IN2 = [H2|R2]
        -> ( H1 =< H2
            -> OUT = [H1|P],
               merge(R1,IN2,P)
            ;  OUT = [H2|P],
               merge(IN1,R2,P)
            )
        ;   OUT = IN1
        ))
    ;   OUT = IN2
    )).


