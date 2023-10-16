import sys


# FIXME: Fix indexing
def compPrefixFunc(P, m):
    prefixFunc = [0] * m
    k = 0
    for q in range(1, m):
        while k > 0 and P[k] != P[q]:
            k = prefixFunc[k-1]
        if P[k] == P[q]:
            k = k + 1
        prefixFunc[q] = k
    return prefixFunc


def KMP(P, T):
    m = len(P)
    n = len(T)
    shiftList = []
    print(f'Pattern: {P}')
    prefixFunc = compPrefixFunc(P, m)
    q = 0

    # watch out for indexing
    for i in range(n):
        while q > 0 and P[q] != T[i]:   # changed
            q = prefixFunc[q-1]
        if P[q] == T[i]:    # changed
            q = q + 1
        if q == m:
            shiftList.append(i + 1 - m)
            q = prefixFunc[q-1]
    print(f'Shifts: {shiftList}')
    return shiftList


if __name__ == "__main__":
    args = sys.argv[1:]
    fileName = args[1]
    file = open(fileName)

    P = args[0]
    T = file.read()
    print(KMP(P, T))
