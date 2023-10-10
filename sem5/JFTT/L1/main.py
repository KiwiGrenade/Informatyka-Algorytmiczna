import sys

def comp_trans_func(pattern):
    utf8_len = 1112064
    for q in range(pattern):
        for c in range(utf8_len):
            


def main():
    args = sys.argv[1:]  # cut off script name
    pattern = args[0]

    transition_function = comp_trans_func(pattern)

    # get text
    file_name = args[1]
    file = open(file_name)
    text = file.read()

    q = 0

    for i in range(len(text)):
        q = transition_function



    print("fuck off")
    return 0
