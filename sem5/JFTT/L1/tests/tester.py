from fa import *
from kmp import *

NUM_OF_TESTS = 5

for i in range(1, NUM_OF_TESTS+1):
    text_path = './t' + str(i) + '/tekst.txt'
    with open(text_path, "r", encoding="utf-8") as f:
        text = f.read()
    results_path = './t' + str(i) + '/wynik.txt'
    with open(results_path, "r", encoding="utf-8") as f:
        cases = f.readlines()
    
    for case in cases:
        tokens = case.split(maxsplit=1)
        pattern = tokens[0]
        pattern = pattern[1:-1]
        correct_result = tokens[1]
        flag = correct_result[-2] != ']'
        correct_result = correct_result[1:-2] if not flag else correct_result[1:-1]

        comp = list(map(int, correct_result.split(','))) if len(correct_result) > 0 else []
        assert finite_automata_search(pattern, text) == comp
        assert knuth_morris_pratt_search(pattern, text) == comp

    print("TESTSET ", i ," DONE")
print("ALL TESTS PASSED SUCCESFULLY✅")