# Jakub Jaśków 268416

function zad5()
    A = Float32(0.01)
    B = Float64(0.01)
    r = 3

    dist1 = 3
    dist2 = 20
    dist3 = 25
    
    nextP(p) = p + r*p*(1-p)
    
    println(rpad("n", dist1),
                " & ", rpad("Float32", dist2), 
                " & ", rpad("Float32 z obcięciem", dist2), 
                " & ", rpad("Float64", dist3), 
                "\\\\\\hline")
    
    for n in 0:9
        println(rpad(n, dist1),
                " & ", rpad(A, dist2), 
                " & ", rpad(A, dist2), 
                " & ", rpad(B, dist3), 
                "\\\\\\hline")
        A = nextP(A)
        B = nextP(B)
    end

    A2 = Float32(0.722) # p2 dotychczas było identyczne jak A, teraz następuje ucięcie

    for n in 10:40
        println(rpad(n, dist1),
                " & ", rpad(A, dist2), 
                " & ", rpad(A2, dist2), 
                " & ", rpad(B, dist3), 
                "\\\\\\hline")
        A = nextP(A)
        A2 = nextP(A2)
        B = nextP(B)
    end
end

println("Zadanie 5")
zad5()