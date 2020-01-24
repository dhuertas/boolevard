/*
 * Boolean expression evaluator in C++.
 *
 * @author Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#ifndef __FLOAT_HH__
#define __FLOAT_HH__

#include <sstream>

#include "Node.hh"

class Float : public Node {
    
private:

protected:

    double value_;

public:

    Float(const Token &token) :
        Node(token) {

        value_ = token.getFloat();
    }

    virtual uint32_t getType(void) { return Node::FLOAT; }

    double getValue(void) { return value_; }

    std::string toString(void) {
        
        std::stringstream ss;
        ss << "Float(" << value_ << ")";
        return ss.str();
    }
};

#endif
