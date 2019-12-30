/*
 * Boolean expression evaluator in C++.
 *
 * @author: Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#ifndef __BINARYOPERATOR_HH__
#define __BINARYOPERATOR_HH__

#include "main.hh"
#include "Node.hh"
#include "Token.hh"

class BinaryOperator : public Node {

private:

protected:

    Node *left_;

    Node *right_;

public:

    BinaryOperator(Node *left, const Token &op, Node *right) :
        Node(op),
        left_(left),
        right_(right) {

        DEBUG("BinaryOperator[%p](left=%s; operator=%s; right=%s)",
            this, left->toString().c_str(),
            op.toString().c_str(), right->toString().c_str());
    }

    virtual ~BinaryOperator() {

        if (left_) {
            delete left_;
        }

        if (right_) {
            delete right_;
        }
    }

    virtual uint32_t getType(void) { return Node::BINARYOP; }

    uint8_t getOperator(void) { return token_.getType(); }

    Node *getLeft(void) { return left_; }

    Node *getRight(void) { return right_; }
};

#endif