/*
 * Boolean expression evaluator in C++.
 *
 * @author: Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#include <cctype>
#include <cassert>

#include "Lexer.hh"
#include "Token.hh"

Lexer::Lexer(const std::string &expr) : 
    expression_(expr),
    pos_(0) {

}

//------------------------------------------------------------------------------
Token Lexer::getNextToken(void) {

    bool validToken = true;

    size_t length = 0;

    while (pos_ < expression_.size()) {

        if (expression_[pos_] == ' '  or 
            expression_[pos_] == '\n' or 
            expression_[pos_] == '\t') {

            pos_++;
            continue;
        }

        if (isFalse()) {
            pos_ += 5;
            return Token(Token::BOOLEAN, "false");
        }

        if (isTrue()) {
            pos_ += 4;
            return Token(Token::BOOLEAN, "true");
        }

        if (isNumber()) {
            length = getNumberLength();
            std::string value = getNumber(length);
            pos_ += length;
            return Token(Token::NUMBER, value);
        }

        if (expression_[pos_] == '"') {
            length = getStringLength();
            std::string value = getString(length);
            pos_ += length;
            return Token(Token::STRING, value);
        }

        if (expression_[pos_] == '[') {
            size_t length = getStructLength();
            std::string value = getStruct(length);
            pos_ += length;

            int64_t from = 0, to = 0;
            if (sscanf(value.c_str(), "[%ld..%ld]", &from, &to) == 2) {
                return Token(Token::RANGE, value);
            }

            return Token(Token::LIST, value);
        }

        if (isGreater()) {
            pos_++;
            return Token(Token::GREATER, ">");
        }

        if (isLess()) {
            pos_++;
            return Token(Token::LESS, "<");
        }

        if (isEqual()) {
            pos_ += 2;
            return Token(Token::EQUAL, "==");
        }

        if (isNotEqual()) {
            pos_ += 2;
            return Token(Token::NOTEQUAL, "!=");
        }

        if (isGreaterOrEqual()) {
            pos_ += 2;
            return Token(Token::GREQ, ">=");
        }

        if (isLessOrEqual()) {
            pos_ += 2;
            return Token(Token::LEQ, "<=");
        }

        if (isOr()) {
            pos_ += 2;
            return Token(Token::OR, "or");
        }

        if (isAnd()) {
            pos_ += 3;
            return Token(Token::AND, "and");
        }

        if (isNot()) {
            pos_ += 3;
            return Token(Token::NOT, "not");
        }

        if (isContains()) {
            pos_ += 8;
            return Token(Token::CONTAINS, "contains");
        }

        if (isStartsWith()) {
            pos_ += 2;
            return Token(Token::STARTSWITH, "sw");
        }

        if (isEndsWith()) {
            pos_ += 2;
            return Token(Token::ENDSWITH, "ew");
        }

        if (isIn()) {
            pos_ += 2;
            return Token(Token::IN, "in");
        }

        if (expression_[pos_] == '(') {
            pos_++;
            return Token(Token::LPAREN, "(");
        }

        if (expression_[pos_] == ')') {
            pos_++;
            return Token(Token::RPAREN, ")");
        }

        if (isVariable(&length)) {
 
            std::string name = getString(length);
            pos_+= length;

            if (variables_.find(name) != variables_.end()) {
                return variables_[name];
            }
        }

        validToken = false;
        assert(validToken == true);
    }

    return Token(Token::EOL, "eol");
}

//------------------------------------------------------------------------------
std::string Lexer::getNumber(size_t length) {

    return expression_.substr(pos_, length);
}

//------------------------------------------------------------------------------
size_t Lexer::getNumberLength(void) {

    size_t i = pos_;

    // allow negative numbers
    if (expression_[i] == '-') i++;

    while (i < expression_.size() and isdigit(expression_[i])) {
        i++;
    }

    return  i - pos_;
}

//------------------------------------------------------------------------------
std::string Lexer::getString(size_t length) {

    return expression_.substr(pos_, length);
}

//------------------------------------------------------------------------------
size_t Lexer::getStringLength(void) {

    size_t res = pos_;

    res++;

    while (res < expression_.size()) {
        if (expression_[res] == '"') break;
        res++;
    }

    res++;

    return res - pos_;
}

//------------------------------------------------------------------------------
std::string Lexer::getStruct(size_t length) {

    return expression_.substr(pos_, length);
}

//------------------------------------------------------------------------------
size_t Lexer::getStructLength(void) {

    size_t res = pos_;

    res++;

    uint32_t depth = 0;

    while (res < expression_.size()) {
        
        if (expression_[res] == '[') depth++;

        else if (expression_[res] == ']') {
            if (depth == 0) break;
            depth--;
        }

        res++;
    }

    res++;

    return res - pos_;
}

//------------------------------------------------------------------------------
bool Lexer::isFalse(void) {

    return Token::isFalse(expression_, pos_);
}

//------------------------------------------------------------------------------
bool Lexer::isTrue(void) {

    return Token::isTrue(expression_, pos_);
}

//------------------------------------------------------------------------------
bool Lexer::isNumber(void) {

    return Token::isNumber(expression_, pos_);
}

//------------------------------------------------------------------------------
bool Lexer::isEqual(void) {

    return (expression_.compare(pos_, 3, "== ") == 0 or 
            expression_.compare(pos_, 3, "eq ") == 0 or 
            expression_.compare(pos_, 3, "EQ ") == 0);
}

//------------------------------------------------------------------------------
bool Lexer::isNotEqual(void) {

    return (expression_.compare(pos_, 3, "!= ") == 0 or 
            expression_.compare(pos_, 3, "ne ") == 0 or 
            expression_.compare(pos_, 3, "NE ") == 0);
}

//------------------------------------------------------------------------------
bool Lexer::isGreater(void) {

    return (expression_.compare(pos_, 2, "> ") == 0);
}

//------------------------------------------------------------------------------
bool Lexer::isLess(void) {

    return (expression_.compare(pos_, 2, "< ") == 0);
}

//------------------------------------------------------------------------------
bool Lexer::isGreaterOrEqual(void) {

    return (expression_.compare(pos_, 3, ">= ") == 0 or 
            expression_.compare(pos_, 3, "ge ") == 0 or 
            expression_.compare(pos_, 3, "GE ") == 0);
}

//------------------------------------------------------------------------------
bool Lexer::isLessOrEqual(void) {

    return (expression_.compare(pos_, 3, "<= ") == 0 or 
            expression_.compare(pos_, 3, "le ") == 0 or 
            expression_.compare(pos_, 3, "LE ") == 0);
}

//------------------------------------------------------------------------------
bool Lexer::isOr(void) {

    return (expression_.compare(pos_, 3, "or ") == 0 or 
            expression_.compare(pos_, 3, "OR ") == 0);
}

//------------------------------------------------------------------------------
bool Lexer::isAnd(void) {

    return (expression_.compare(pos_, 4, "and ") == 0 or 
            expression_.compare(pos_, 4, "AND ") == 0);
}

//------------------------------------------------------------------------------
bool Lexer::isNot(void) {

    return (expression_.compare(pos_, 4, "not ") == 0 or 
            expression_.compare(pos_, 4, "NOT ") == 0);

}

//------------------------------------------------------------------------------
bool Lexer::isContains(void) {

    return (expression_.compare(pos_, 9, "contains ") == 0 or 
            expression_.compare(pos_, 9, "CONTAINS ") == 0);  
}

//------------------------------------------------------------------------------
bool Lexer::isStartsWith(void) {

    return (expression_.compare(pos_, 3, "sw ") == 0 or 
            expression_.compare(pos_, 3, "SW ") == 0);

}

//------------------------------------------------------------------------------
bool Lexer::isEndsWith(void) {

    return (expression_.compare(pos_, 3, "ew ") == 0 or 
            expression_.compare(pos_, 3, "EW ") == 0);
}

//------------------------------------------------------------------------------
bool Lexer::isIn(void) {

    return (expression_.compare(pos_, 3, "in ") == 0 or 
            expression_.compare(pos_, 3, "IN ") == 0);
}

//------------------------------------------------------------------------------
bool Lexer::isVariable(size_t *length) {

    size_t res = pos_;

    while (expression_[res] != ' ' and res < expression_.size()) {
        res++;
    }

    if (variables_.find(expression_.substr(pos_, res - pos_)) != variables_.end())  {
        *length = res - pos_;
        return true;
    }

    return false;
}
