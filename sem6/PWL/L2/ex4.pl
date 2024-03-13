
%Generowanie tablicy posortowanej od 1 do n, ktora wykorzystamy
%do utworzenia oczekiwanej listy
lista(N, X) :-
    numlist(1,N,Available),
    odd([1], [], [1], 2, Available, X).

%EvenIndex informuje nas o tym, iz pierwsze wystapienie danego elementu znajduje sie 
%na pozycji o indeksie parzystym
%Analogicznie OddIndex informuje o nieparzystym indeksie polozenia pierwszego elementu
%Waznym jest, aby element znajdujacy sie w tablicy EvenIndex (odpowiednio OddIndex) nie pojawil sie
%ponownie na parzystej (odpowiednio nieparzystej) pozycji, gdyz wtedy nie zostanie zachowany warunek 
%"parzystego odstepu miedzy elementami" (gdzie przed odstep rozumiemy liczbe elementow roznych od wybranego)
%Wynika to z faktu, iz miedzy dwoma liczbami parzystymi (odpowiednio nieparzystymi)
%znajduje sie nieparzysta liczba liczb
%Answer jest tablica przechowujaca aktualny wynik operacji, docelowo zawiera wygenerowana permutacje
%spelniajaca wymogi zadania
%Unused informuje nas o minimalnym elemencie, ktorego jeszcze nie uzylismy (zwiazane jest to z tym,
%ze pierwsze wystapienie liczby k moze nastapic dopiero po tym, jak przynajmniej jedna z liczb ze zbioru
%{1,...,k-1} zostanie juz uzyta
%Avaiable zawiera elementy, ktore jeszcze nie zostaly w calosci rozdysponowane
%Program konczy prace, gdy nie ma juz elementow do rozdysponowania
%X czysto sztucznie sluzy do wypisania otrzymanego wyniku (gdyz wywolanie wyglada tak: lista(N,X))



odd(EvenIndex, OddIndex, Answer, Unused, Available, X) :-
    member(Current, Available),
    Current < Unused,
    member(Current, EvenIndex),
    select(Current, Available, NewAvailable),
    append(Answer, [Current], NewAnswer),
    even(EvenIndex, OddIndex, NewAnswer, Unused, NewAvailable, X).

odd(EvenIndex,OddIndex,Answer,Unused,Available,X) :-
    member(Current, Available),
    Current =:= Unused,
    NextUnused is Unused + 1,
    append([Current], OddIndex, NewEvenIndex),
    append(Answer, [Current], NewAnswer),
    even(EvenIndex, NewEvenIndex, NewAnswer, NextUnused, Available, X).

even(EvenIndex, OddIndex, Answer, Unused, Available, X) :-
    member(Current, Available),
    Current < Unused,
    member(Current, OddIndex),
    select(Current, Available, NewAvailable),
    append(Answer, [Current], NewAnswer),
    odd(EvenIndex, OddIndex, NewAnswer, Unused, NewAvailable, X).

even(EvenIndex,OddIndex,Answer,Unused,Available,X) :-
    member(Current,Available),
    Current =:= Unused,
    NextUnused is Unused + 1,
    append([Current], EvenIndex, NewOddIndex),
    append(Answer, [Current], NewAnswer),
    odd(NewOddIndex, OddIndex, NewAnswer, NextUnused, Available, X).

%Zwrocenie odpowiedzi odbedzie sie zawsze w kroku zwiazanym z dodaniem parzystego
%elementu do tablicy ze wzgledu na to, iz kazda z tablic zawiera 2*n elementow
%a indeksy są numerowane od 0 (czyli naleza do zbioru {0,...,2*(n-1)})
%oraz, gdy nie ma juz elementow dostepnych do rozdysponowania
even(_, _, Answer, _, [], X) :-
    X=Answer.
