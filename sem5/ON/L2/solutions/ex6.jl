# Jakub Jaśków 268416

# function from labor2.pdf
nextX(x, c) = x^2 + c

dist1 = 3
dist2 = 10
dist3 = 20
dist4 = 25

function zad61()
    println("########### c = -2 ###########")

    println(rpad("n", dist1),
    " & ", rpad("\$x_0=1\$", dist2), 
    " & ", rpad("\$x_0=2\$", dist2), 
    " & ", rpad("\$x_0=1.99999999999999\$", dist4), 
    " \\\\\\hline")

    c = -2
    x1 = 1.
    x2 = 2.
    x3 = 1.99999999999999

    for n in 1:40
        x1 = nextX(x1, c)
        x2 = nextX(x2, c)
        x3 = nextX(x3, c)
        println(rpad(n, dist1),
            " & ", rpad(x1, dist2), 
            " & ", rpad(x2, dist2), 
            " & ", rpad(x3, dist3), 
            " \\\\\\hline")
    end
end

function zad62()

println("########### c = -1 ###########")
    c = -1
    x1 = 1.
    x2 = -1.
    x3 = 0.75
    x4 = 0.25
    println(rpad("n", dist1),
            " & ", rpad("\$x_0=1\$", dist2), 
            " & ", rpad("\$x_0=-1\$", dist2), 
            " & ", rpad("\$x_0=0.75\$", dist4), 
            " & ", rpad("\$x_0=0.25\$", dist4), 
            " \\\\\\hline")

    for n in 1:40
        x1 = nextX(x1, c)
        x2 = nextX(x2, c)
        x3 = nextX(x3, c)
        x4 = nextX(x4, c)
        println(rpad(n, dist1),
            " & ", rpad(x1, dist2), 
            " & ", rpad(x2, dist2), 
            " & ", rpad(x3, dist4), 
            " & ", rpad(x4, dist4), 
            " \\\\\\hline")
    end
end

println("\nZadanie 6")
zad61()
zad62()