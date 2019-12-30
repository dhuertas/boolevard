#ifndef __NODE_HH__
#define __NODE_HH__

#include <sstream>

#include "Object.hh"
#include "Token.hh"

// Base AST Node definition
class Node : public Object {

public:

    enum Type {
        NONE,
        BOOLEAN,
        NUMBER,
        STRING,
        LIST,
        UNARYOP,
        BINARYOP
    };

    static std::string names_[];

private:

protected:

    Token token_;

public:

    Node(const Token &token) : token_(token) {}

    virtual ~Node() {}

    virtual uint32_t getType(void);

    virtual std::string getName(void);

    Token getToken(void);

    virtual std::string toString(void);
};

#endif