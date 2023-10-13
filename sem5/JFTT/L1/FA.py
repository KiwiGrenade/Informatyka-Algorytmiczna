import sys


def comp_trans_func(P, m):
    utf8_len = 1112064 - 1
    # fuck python and those fucking shitty 2d lists. Who the fuck uses ShAloOw LiSt$
    trans_func = [[0 for i in range(utf8_len)] for j in range(m + 1)]  # counting 0 we have m+1 states
    for q in range(m + 1):
        for a in range(utf8_len):
            k = min(m, q + 1)
            while not (str(P[:q] + chr(a)).endswith(P[:k])):
                k = k - 1
            trans_func[q][a] = k
    return trans_func


def FA():
    args = sys.argv[1:]  # cut off script name
    P = args[0]
    m = len(P)

    transition_function = comp_trans_func(P, m)

    # get text
    file_name = args[1]
    file = open(file_name)
    T = file.read()
    n = len(T)

    q = 0

    for i in range(n):
        q = transition_function[q][ord(T[i])]
        if q == m:
            print(f'Pattern occurs with shift: {i + 1 - m}')

    return 0


if __name__ == '__main__':
    FA()
