# Jakub Jaśków 268416
# Universal function for printing the resulting 4 tuple of Utils's methods

function printResults(r, v, it, err)
    println(rpad("r: $(r)", 25), " && ", rpad(" v: $(v)", 25), " && ", rpad(" it: $(it)", 10), " && ", rpad("err: $(err)", 10), "\\\\\\hline")
end