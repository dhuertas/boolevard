/*
 * Boolean expression evaluator in C++.
 *
 * @author: Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#ifndef __LEXER_HH__
#define __LEXER_HH__

#include <string>

#include "Object.hh"

class Token;

class Lexer : public Object {

private:

protected:

    std::string expression_;

    size_t pos_;

public:

    Lexer(const std::string &exp);

    Token getNextToken(void);

    std::string getNumber(size_t length);

    size_t getNumberLength(void);

    std::string getString(size_t length);

    size_t getStringLength(void);

    std::string getStruct(size_t length);

    size_t getStructLength(void);

    bool isFalse(void);

    bool isTrue(void);

    bool isNumber(void);

    bool isEqual(void);

    bool isNotEqual(void);

    bool isGreater(void);

    bool isLess(void);

    bool isGreaterOrEqual(void);

    bool isLessOrEqual(void);

    bool isOr(void);

    bool isAnd(void);

    bool isNot(void);

    bool isContains(void);

    bool isStartsWith(void);

    bool isEndsWith(void);

    bool isIn(void);

};

#endif
