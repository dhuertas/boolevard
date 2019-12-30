/*
 * Boolean expression evaluator in C++.
 *
 * @author: Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#ifndef __INTERPRETER_HH__
#define __INTERPRETER_HH__

#include "NodeVisitor.hh"
#include "Parser.hh"

class Interpreter : public NodeVisitor {

private:

protected:

    Parser parser_;

    Node *root_;

public:

    Interpreter(const Parser &parser);

    virtual ~Interpreter();

    bool visitUnaryOperator(Node *node);

    bool visitBinaryOperator(Node *node);

    bool visitBoolean(Node *node);

    int64_t visitNumber(Node *node);

    bool interpret(void);

    bool visit(Node *node);

    bool greater(Node *left, Node *right);

    bool less(Node *left, Node *right);

    bool equal(Node *left, Node *right);

    bool greaterOrEqual(Node *left, Node *right);

    bool lessOrEqual(Node *left, Node *right);

    bool contains(Node *left, Node *right);

    bool startsWith(Node *left, Node *right);

    bool endsWith(Node *left, Node *right);

    bool in(Node *left, Node *right);
};

#endif