# boolean-expression-evaluator
Boolean expression evaluator in C++ using the interpreter pattern:
```
               +-------+                  +--------+             +-------------+
expression --> | Lexer | --- [Tokens] --> | Parser | --- AST --> | Interpreter | --> True|False
               +-------+                  +--------+             +-------------+
```

To compile the code use make (requires g++):
```
make release
```

Here's an example of how to use the program in the command line:
```bash
./bxe '3 in [1, 2, 3, 4, 5] or (-2 < 3 and 3 < 5)'
true
```

Basic types are:

| Type     | Example                       |
| -------- | ----------------------------- |
| Boolean  | `True, False`                 |
| Integers | `1, -3, 1000`                 |
| Decimals | `1.2, -0.5`                   |
| Strings  | `"This is a string"`          |
| Lists    | `[1, 2, 3, True, ["a", "b"]]` |
| Ranges   | `[1..4]`                      |

Available operators are:

| Operator         | Example    |
| ---------------- | ---------- |
| not              | `not`      |
| equal            | `==`       |
| not equal        | `!=`       |
| greater          | `>`        |
| less             | `<`        |
| greater or equal | `>=`       |
| less or equal    | `<=`       |
| contains         | `contains` |
| starts with      | `sw`       |
| ends with        | `ew`       |
| in               | `in`       |

Use variables in expression:
```bash
./bxe -a res=`echo 2*6|bc` 'res eq 12'
true
```

Numeric output:
```bash
./bxe -n 'True'; echo $?
0
./bxe -n 'False'; echo $?
1
```

The numeric output is aligned to support the following command line structure:
```bash
./bxe -n 'True' && echo "Hello World!" || echo "Nope"
Hello World!
./bxe -n 'False' && echo "Hello World!" || echo "Nope"
Nope
```

Check the test script for more examples.

## TODOs

- [ ] Better error handling
- [ ] Add more operator alternatives, e.g. `<` as `lt` (less than)
- [ ] Add XOR operator
- [x] Add ranges
- [x] Use variables in expression
