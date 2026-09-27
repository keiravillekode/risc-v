FUNC_PROTO = """\
#include "vendor/unity.h"

extern void solve(char *puzzle);
"""


def gen_func_body(prop, inp, expected):
    puzzle = inp["puzzle"].replace("==", "=")
    if expected is None:
        solution = ""
    else:
        solution = "".join(str(expected.get(ch, ch)) for ch in puzzle)

    str_list = []
    str_list.append(f'char puzzle[] = "{puzzle}";\n')
    str_list.append(f"{prop}(puzzle);\n")
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{solution}", puzzle);\n')
    return "".join(str_list)
