/*
 * Boolean expression evaluator in C++.
 *
 * @author: Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#ifndef __TOKEN_HH__
#define __TOKEN_HH__

#include <string>
#include <sstream>
#include <vector>

#include "Object.hh"

class Token : public Object {

public:

    enum Type {
        BOOLEAN,
        NUMBER,
        STRING,
        LIST,
        GREATER,
        LESS,
        EQUAL,
        NOTEQUAL,
        GREQ,
        LEQ,
        OR,
        AND,
        NOT,
        CONTAINS,
        STARTSWITH,
        ENDSWITH,
        IN,
        LPAREN,
        RPAREN,
        EOL
    };

    static std::string names_[]; 

    static std::string getTypeName(uint8_t type) { return names_[type]; }

    static bool isTrue(const std::string &str, size_t pos = 0);

    static bool isFalse(const std::string &str, size_t pos = 0);

    static bool isNumber(const std::string &str, size_t pos = 0);

    static void trim(std::string &str);

private:

protected:

    uint8_t type_;

    std::string value_;

public:

    Token(void) { }

    Token(const uint8_t type, const std::string &value);

    uint8_t getType(void) const { return type_; }

    int64_t getNumber(void) const;

    std::string getString(void) const { return value_; }

    bool getBoolean(void) const;

    std::vector<Token> getList(void) const;

    std::string toString(void) const;

    int64_t compare(const Token &token) const;

    bool operator==(const Token &token) const;
};

#endif