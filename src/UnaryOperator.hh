#ifndef __UNARYOPERATOR_HH__
#define __UNARYOPERATOR_HH__

#include "main.hh"
#include "Node.hh"
#include "Token.hh"

class UnaryOperator : public Node {

private:

protected:

    Node *right_;

public:

    UnaryOperator(const Token &op, Node *right) :
        Node(op),
        right_(right) {

        DEBUG("UnaryOperator[%p](operator=%s; right=%s)",
            this, op.toString().c_str(), right->toString().c_str());
    }

    virtual ~UnaryOperator() {

        if (right_) {
            delete right_;
        }
    }

    virtual uint32_t getType(void) { return Node::UNARYOP; }

    uint8_t getOperator(void) { return token_.getType(); }

    Node *getRight(void) { return right_; }
};

#endif