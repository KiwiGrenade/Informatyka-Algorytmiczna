# Jakub Jaśków 268416

from ply import lex, yacc

import lexrules
import yaccrules


def main():
    lexer = lex.lex(module=lexrules)
    parser = yacc.yacc(module=yaccrules)
    while True:
        text = ""
        while True:
            try:
                text += input()
            except EOFError:
                return
            text += '\n'
            if not text.endswith('\\\n'):
                break
        parser.parse(text, lexer=lexer)


if __name__ == "__main__":
    main()
