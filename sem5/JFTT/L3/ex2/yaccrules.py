# Jakub Jaśków 268416
import gmpy
from lexrules import tokens, P

tokens = tokens[:-3]
rpn = ""
error_msg = ""
precedence = (
    ('left', 'ADD', 'SUB'),
    ('left', 'MUL', 'DIV'),
    ('right', 'NEG'),
    ('nonassoc', 'POW')
)

##################### LINE #####################

def p_line_expr(p):
    'line : expr ENDL'
    global rpn, error_msg
    print(rpn)
    print(f"= {p[1]}\n")
    rpn = ""
    error_msg = ""

def p_line_error(p):
    'line : error ENDL'
    global rpn, error_msg
    if error_msg != "":
        print(f"{error_msg}\n")
    else:
        print("Błąd: zła składnia\n")
    rpn = ""
    error_msg = ""

##################### EXPRESsION #####################

def p_expr_number(p):
    'expr : number'
    global rpn
    number = numConv(p[1], P)
    rpn += f"{number} "
    p[0] = number

def p_expr_paren(p):
    'expr : LPAREN expr RPAREN'
    p[0] = p[2]

def p_expr_neg(p):
    'expr : SUB expr %prec NEG'
    global rpn
    rpn += "~ "
    p[0] = numConv(-p[2], P)

def p_expr_add(p):
    'expr : expr ADD expr'
    global rpn
    rpn += "+ "
    p[0] = numConv(p[1] + p[3], P)

def p_expr_sub(p):
    'expr : expr SUB expr'
    global rpn
    rpn += "- "
    p[0] = numConv(p[1] - p[3], P)

def p_expr_mul(p):
    'expr : expr MUL expr'
    global rpn
    rpn += "* "
    p[0] = numConv(p[1] * p[3], P)

def p_expr_pow(p):
    'expr : expr POW exponent'
    global rpn
    exponent = numConv(p[3], P-1)
    rpn += f"^ "
    p[0] = pow(p[1], exponent, P)

def p_expr_div(p):
    'expr : expr DIV expr'
    global rpn
    rpn += "/ "
    if gmpy.invert(p[3], P) == 0:
        global error_msg
        error_msg = f"Błąd: {p[3]} nie jest odwracalny w GF({P})"
        raise SyntaxError
    p[0] = numConv(p[1] * pow(p[3], -1, P), P)

##################### EXPONENT #####################

def p_exponent_number(p):
    'exponent : exponent_number'
    global rpn
    number = numConv(p[1], P - 1)
    rpn += f"{number} "
    p[0] = number

def p_exponent_paren(p):
    'exponent : LPAREN exponent RPAREN'
    p[0] = p[2]

def p_exponent_neg(p):
    'exponent : SUB exponent %prec NEG'
    global rpn
    rpn += "~ "
    p[0] = numConv(-p[3], P-1)

def p_exponent_add(p):
    'exponent : exponent ADD exponent'
    global rpn
    rpn += "+ "
    p[0] = numConv(p[1] + p[3], P - 1)

def p_exponent_sub(p):
    'exponent : exponent SUB exponent'
    global rpn
    rpn += "- "
    p[0] = numConv(p[1] - p[3], P - 1)

def p_exponent_mul(p):
    'exponent : exponent MUL exponent'
    global rpn
    rpn += "* "
    p[0] = numConv(p[1] * p[3], P)

def p_exponent_div(p):
    'exponent : exponent DIV exponent'
    global rpn
    rpn += "/ "
    if gmpy.invert(p[3], P-1) == 0:
        global error_msg
        error_msg = f"Błąd: {p[3]} nie jest odwracalny w GF({P-1})"
        raise SyntaxError
    p[0] = numConv(p[1] * pow(p[3], -1, P - 1), P - 1)

##################### NUMBER #####################

def p_number_pos(p):
    'number : NUM'
    p[0] = numConv(p[1], P)

def p_number_neg(p):
    'number : SUB number %prec NEG'
    p[0] = numConv(-p[2], P)

##################### EXPONENT NUMBER #####################

def p_exponent_number_pos(p):
    'exponent_number : NUM'
    p[0] = numConv(p[1], P-1)

def p_exponent_number_neg(p):
    'exponent_number : SUB exponent_number %prec NEG'
    p[0] = numConv(-p[2], P-1)

def p_error(p):
    pass

def numConv(a, G):
    return ((a%G)+G)%G