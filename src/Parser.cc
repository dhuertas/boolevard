/*
 * Boolean expression evaluator in C++.
 *
 * @author: Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#include <string>
#include <cassert>

#include "main.hh"
#include "Parser.hh"
#include "Boolean.hh"
#include "Number.hh"
#include "String.hh"
#include "List.hh"
#include "Range.hh"
#include "BinaryOperator.hh"
#include "UnaryOperator.hh"

Parser::Parser(const Lexer &lex) :
    lexer_(lex),
    depth_(0) {

    currentToken_ = lexer_.getNextToken();
}

//------------------------------------------------------------------------------
void Parser::consume(uint8_t tokenType) {

    // Compare the current token type with the passed token
    // type and if they match then "consume" the current token
    // and assign the next token to the currentToken_,
    // otherwise raise an exception.

    bool validSyntax = true;

    if (tokenType == currentToken_.getType()) {
 
        if (tokenType == Token::LPAREN) depth_++;
        if (tokenType == Token::RPAREN) depth_--;

        currentToken_ = lexer_.getNextToken();

        if (depth_ < 0 or (depth_ == 0 and currentToken_.getType() == Token::RPAREN)) {
            validSyntax = false;
        }

    } else {
        validSyntax = false;
    }

    assert(validSyntax);
}

//------------------------------------------------------------------------------
Node *Parser::factor(void) {

    Node *node = NULL;

    Token token = currentToken_;

    // Constants
    if (token.getType() == Token::NUMBER) {
        consume(Token::NUMBER);
        node = new Number(token);
    }

    if (token.getType() == Token::BOOLEAN) {
        consume(Token::BOOLEAN);
        node = new Boolean(token);
    }

    if (token.getType() == Token::STRING) {
        consume(Token::STRING);
        node = new String(token);
    }

    if (token.getType() == Token::LIST) {
        consume(Token::LIST);
        node = new List(token);
    }

    if (token.getType() == Token::RANGE) {
        consume(Token::RANGE);
        node = new Range(token);
    }

    // Parentheses
    if (token.getType() == Token::LPAREN) {
        consume(Token::LPAREN);
        node = expr();
        consume(Token::RPAREN);
    }

    // Binary operators
    if (isBinaryOperator(currentToken_.getType())) {

        token = currentToken_;

        switch (token.getType()) {

            case Token::GREATER: consume(Token::GREATER); break;
            case Token::LESS: consume(Token::LESS); break;
            case Token::EQUAL: consume(Token::EQUAL); break;
            case Token::NOTEQUAL: consume(Token::NOTEQUAL); break;
            case Token::GREQ: consume(Token::GREQ); break;
            case Token::LEQ: consume(Token::LEQ); break;
            case Token::CONTAINS: consume(Token::CONTAINS); break;
            case Token::STARTSWITH: consume(Token::STARTSWITH); break;
            case Token::ENDSWITH: consume(Token::ENDSWITH); break;
            case Token::IN: consume(Token::IN); break;

        }

        node = new BinaryOperator(node, token, factor());
    }

    // Unary operator
    if (token.getType() == Token::NOT) {
        consume(Token::NOT);
        node = new UnaryOperator(token, term());
    }

    assert(node != NULL);

    return node;
}

//------------------------------------------------------------------------------
Node *Parser::term(void) {

    Node *node = factor();

    while (isTerm(currentToken_.getType())) {

        Token token = currentToken_;
        
        switch (token.getType()) {

            case Token::AND: consume(Token::AND); break;
        }

        node = new BinaryOperator(node, token, factor());
    }

    return node;
}

//------------------------------------------------------------------------------
Node *Parser::expr(void) {

    Node *node = term();

    while (isExpr(currentToken_.getType())) {

        Token token = currentToken_;
        
        switch (token.getType()) {

            case Token::OR: consume(Token::OR); break;
        }

        node = new BinaryOperator(node, token, term());
    }

    return node;
}

//------------------------------------------------------------------------------
bool Parser::isBinaryOperator(int8_t tokenType) {

    switch (tokenType) {

        case Token::GREATER:
        case Token::LESS:
        case Token::EQUAL:
        case Token::NOTEQUAL:
        case Token::GREQ:
        case Token::LEQ:
        case Token::CONTAINS:
        case Token::STARTSWITH:
        case Token::ENDSWITH:
        case Token::IN:
            return true;
    }

    return false;
}

//------------------------------------------------------------------------------
bool Parser::isTerm(int8_t tokenType) {

    switch (tokenType) {

        case Token::AND:
            return true;
    }

    return false;
}

//------------------------------------------------------------------------------
bool Parser::isExpr(int8_t tokenType) {

    switch (tokenType) {

        case Token::OR:
            return true;        
    }

    return false;
}

//------------------------------------------------------------------------------
Node *Parser::parse(void) {

    return expr();
}
