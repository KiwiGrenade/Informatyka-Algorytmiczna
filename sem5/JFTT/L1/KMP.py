import sys


# FIXME: Fix indexing
def compPrefixFunc(P, m):
    prefixFunc = [0]
    k = 0

    for q in range(1, m):
        while k > 0 and P[k+1] != P[q]:
            k = prefixFunc[k]
        if P[k+1] == P[q]:
            k = k + 1
        prefixFunc[q] = k
    return prefixFunc


def KMP(P, T):
    m = len(P)
    n = len(T)
    shiftList = []
    prefixFunc = compPrefixFunc(P, m)
    q = 0

    # watch out for indexing
    for i in range(n):
        while q > 0 and P[q + 1] != T[i]:
            q = prefixFunc[q]
        if P[q + 1] == T[i]:
            q = q + 1
        if q == m:
            shiftList.append(i + 1 - m)
            q = prefixFunc[q]
    return shiftList


if __name__ == "__main__":
    args = sys.argv[1:]
    fileName = args[1]
    file = open(fileName)

    P = args[0]
    T = file.read()
    print(KMP(P, T))
