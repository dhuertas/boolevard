# boolean-evaluator
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
```
./interpreter '3 in [1, 2, 3, 4, 5] or (-2 < 3 and 3 < 5)'
true
```

Basic types are:

* Boolean: `True, False`
* Numbers: `1, -3, 1000`
* String: `"This is a string"`
* Lists: `[1, 2, 3, True, ["nested", "lists!"]]`
* Ranges: `[1..4]`

Available operators are:

* not: `not`
* equal: `==`
* not equal: `!=`
* greater: `>`
* less: `<`
* greater or equal: `>=`
* less or equal: `<=`
* contains: `contains`
* starts with: `sw`
* ends with: `ew`
* in: `in`

Check the test script for more examples.

## TODOs

* Better error handling
* Add more operator alternatives, e.g. `<` as `lt` (less than)
* Add XOR operator
