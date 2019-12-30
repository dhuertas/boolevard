/*
 * Boolean expression evaluator in C++.
 *
 * @author: Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#ifndef __BOOLEAN_HH__
#define __BOOLEAN_HH__

#include <sstream>

#include "Node.hh"

class Boolean : public Node {

private:

protected:

    bool value_;

public:

    Boolean(const Token &token) :
        Node(token) {

        value_ = token.getBoolean();
    }

    virtual uint32_t getType(void) { return Node::BOOLEAN; }

    bool getValue(void) { return value_; }

    std::string toString(void) {
        
        std::stringstream ss;
        ss << "Boolean(" << (value_ ? "true" : "false") << ")";
        return ss.str();
    }
};

#endif