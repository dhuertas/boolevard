/*
 * Boolean expression evaluator in C++.
 *
 * @author: Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#ifndef __STRING_HH__
#define __STRING_HH__

#include <sstream>

#include "Node.hh"

class String : public Node {

private:

protected:

    std::string value_;

public:

    String(const Token &token) :
        Node(token) {

        value_ = token.getString();
    }

    virtual uint32_t getType(void) { return Node::STRING; }

    size_t size(void) { return value_.size(); }

    std::string getValue(void) { return value_.substr(1, value_.size()-2); }

    std::string toString(void) {

        std::stringstream ss;
        ss << "String(" << value_ << ")";
        return ss.str();
    }
};

#endif