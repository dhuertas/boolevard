#ifndef __NUMBER_HH__
#define __NUMBER_HH__

#include <sstream>

#include "Node.hh"

class Number : public Node {
    
private:

protected:

    int64_t value_;

public:

    Number(const Token &token) :
        Node(token) {

        value_ = token.getNumber();
    }

    virtual uint32_t getType(void) { return Node::NUMBER; }

    int64_t getValue(void) { return value_; }

    std::string toString(void) {
        
        std::stringstream ss;
        ss << "Number(" << value_ << ")";
        return ss.str();
    }
};

#endif