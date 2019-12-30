#ifndef __LIST_HH__
#define __LIST_HH__

#include <vector>
#include <algorithm>

#include "Node.hh"

class List : public Node {

private:

protected:

    std::vector<Token> value_;

public:

    List(const Token &token) :
        Node(token) {

        value_ = token_.getList();
    }

    virtual uint32_t getType(void) { return Node::LIST; }

    size_t size(void) { return value_.size(); }

    std::vector<Token> getValue(void) { return value_; }

    Token getValue(size_t idx) { return value_[idx]; }

    bool find(const Token &token) {

        std::vector<Token>::iterator it = 
            std::find(value_.begin(), value_.end(), token);

        return it != value_.end();
    }

    std::string toString(void) {

        std::stringstream ss;
        ss << "List(" << token_.toString() << ")";
        return ss.str();
    }
};

#endif