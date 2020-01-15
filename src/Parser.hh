/*
 * Boolean expression evaluator in C++.
 *
 * @author: Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#ifndef __PARSER_HH__
#define __PARSER_HH__

#include "Object.hh"
#include "Lexer.hh"
#include "Token.hh"

class Node;
class Token;

class Parser : public Object {

private:

protected:

    Lexer lexer_;

    Token currentToken_;

    int depth_;

public:

    Parser(const Lexer &lexer);

    virtual ~Parser(void) { }

    void consume(uint8_t tokenType);

    Node *factor(void);

    Node *term(void);

    Node *expr(void);

    Node *parse(void);

    bool isBinaryOperator(int8_t tokenType);

    bool isTerm(int8_t tokenType);

    bool isExpr(int8_t tokenType);
};

#endif
