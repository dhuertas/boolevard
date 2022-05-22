/*
 * Boolean expression evaluator in C++.
 *
 * @author Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#include "main.hh"
#include "Interpreter.hh"
#include "Boolean.hh"
#include "Number.hh"
#include "Float.hh"
#include "String.hh"
#include "List.hh"
#include "Range.hh"

#include "BinaryOperator.hh"
#include "UnaryOperator.hh"

Interpreter::Interpreter(const Parser &parser) : 
    parser_(parser),
    root_(NULL) {

}

//------------------------------------------------------------------------------
Interpreter::~Interpreter() {

    if (root_ != NULL) delete root_;
}

//------------------------------------------------------------------------------
bool Interpreter::visitUnaryOperator(Node *node) {

    DEBUG("Visiting UnaryOperator(%p)", node);

    UnaryOperator *uo = (UnaryOperator *)node;

    Node *right = uo->getRight();

    switch (uo->getOperator()) {

        case Token::NOT: return not visit(right);
    }

    return false;
}

//------------------------------------------------------------------------------
bool Interpreter::visitBinaryOperator(Node *node) {

    DEBUG("Visiting BinaryOperator(%p)", node);

    BinaryOperator *bo = (BinaryOperator *)node;

    Node *left = bo->getLeft();
    Node *right = bo->getRight();

    switch (bo->getOperator()) {

        case Token::GREATER:    return greater(left, right);
        case Token::LESS:       return less(left, right);
        case Token::EQUAL:      return equal(left, right);
        case Token::NOTEQUAL:   return not equal(left, right);
        case Token::GREQ:       return greaterOrEqual(left, right);
        case Token::LEQ:        return lessOrEqual(left, right);
        case Token::CONTAINS:   return contains(left, right);
        case Token::STARTSWITH: return startsWith(left, right);
        case Token::ENDSWITH:   return endsWith(left, right);
        case Token::IN:         return in(left, right);

        case Token::AND:        return (visit(left) and visit(right));
        case Token::OR:         return (visit(left) or visit(right));
        case Token::XOR:        return (visit(left) xor visit(right));

        default:
            INFO("Invalid operator");
    }

    return false;
}

//------------------------------------------------------------------------------
int64_t Interpreter::visitNumber(Node *node) const {

    DEBUG("Visiting Number: %s", node->toString().c_str());
    return ((Number *)node)->getValue();
}

//------------------------------------------------------------------------------
double Interpreter::visitFloat(Node *node) const {

    DEBUG("Visiting Float: %s", node->toString().c_str());
    return ((Float *)node)->getValue();
}

//------------------------------------------------------------------------------
bool Interpreter::visitBoolean(Node *node) const {

    DEBUG("Visiting Boolean: %s", node->toString().c_str());
    return ((Boolean *)node)->getValue();
}

//------------------------------------------------------------------------------
bool Interpreter::interpret(void) {

    if (root_ == NULL) {
        root_ = parser_.parse();
    }

    bool res = visit(root_);

    return res;
}

//------------------------------------------------------------------------------
bool Interpreter::visit(Node *node) {

    switch (node->getType()) {

        case Node::BOOLEAN: return visitBoolean(node);
        case Node::NUMBER: return visitNumber(node) != 0;
        case Node::FLOAT: return visitFloat(node) != 0.0;
        case Node::UNARYOP: return visitUnaryOperator(node);
        case Node::BINARYOP: return visitBinaryOperator(node);
    }

    return false;
}

//------------------------------------------------------------------------------
bool Interpreter::greater(Node *left, Node *right) {

    if ((left->getType() == Node::FLOAT and right->getType() == Node::NUMBER) or 
        (left->getType() == Node::NUMBER and right->getType() == Node::FLOAT)) { 

        if (left->getType() == Node::FLOAT) {
            Float *l = (Float *)left;
            Number *r = (Number *)right;
 
            return l->getValue() > r->getValue();

        } else {
            Number *l = (Number *)left;
            Float *r = (Float *)right;
 
            return l->getValue() > r->getValue();
        }
    }

    if (left->getType() != right->getType()) {
        return false;
    }

    if (left->getType() == Node::BOOLEAN) {
        Boolean *l = (Boolean *)left;
        Boolean *r = (Boolean *)right;

        return l->getValue() > r->getValue();
    }

    if (left->getType() == Node::NUMBER) {
        Number *l = (Number *)left;
        Number *r = (Number *)right;

        return l->getValue() > r->getValue();
    }

    if (left->getType() == Node::FLOAT) {
        Float *l = (Float *)left;
        Float *r = (Float *)right;

        return l->getValue() > r->getValue();
    }

    if (left->getType() == Node::STRING) {
        String *l = (String *)left;
        String *r = (String *)right;

        return l->size() > r->size();
    }

    if (left->getType() == Node::LIST) {
        List *l = (List *)left;
        List *r = (List *)right;

        return l->size() > r->size();
    }

    return false;
}

//------------------------------------------------------------------------------
bool Interpreter::less(Node *left, Node *right) {

    if ((left->getType() == Node::FLOAT and right->getType() == Node::NUMBER) or 
        (left->getType() == Node::NUMBER and right->getType() == Node::FLOAT)) { 

        if (left->getType() == Node::FLOAT) {
            Float *l = (Float *)left;
            Number *r = (Number *)right;
 
            return l->getValue() < r->getValue();

        } else {
            Number *l = (Number *)left;
            Float *r = (Float *)right;
 
            return l->getValue() < r->getValue();
        }
    }

    if (left->getType() != right->getType()) {
        return false;
    }

    if (left->getType() == Node::BOOLEAN) {
        Boolean *l = (Boolean *)left;
        Boolean *r = (Boolean *)right;

        return l->getValue() < r->getValue();
    }

    if (left->getType() == Node::NUMBER) {
        Number *l = (Number *)left;
        Number *r = (Number *)right;

        return l->getValue() < r->getValue();
    }

    if (left->getType() == Node::FLOAT) {
        Float *l = (Float *)left;
        Float *r = (Float *)right;

        return l->getValue() < r->getValue();
    }

    if (left->getType() == Node::STRING) {
        String *l = (String *)left;
        String *r = (String *)right;

        return l->size() < r->size();
    }

    if (left->getType() == Node::LIST) {
        List *l = (List *)left;
        List *r = (List *)right;

        return l->size() < r->size();
    }

    return false;
}

//------------------------------------------------------------------------------
bool Interpreter::equal(Node *left, Node *right) {

    if ((left->getType() == Node::FLOAT and right->getType() == Node::NUMBER) or 
        (left->getType() == Node::NUMBER and right->getType() == Node::FLOAT)) { 

        if (left->getType() == Node::FLOAT) {
            Float *l = (Float *)left;
            Number *r = (Number *)right;
 
            return l->getValue() == r->getValue();

        } else {
            Number *l = (Number *)left;
            Float *r = (Float *)right;
 
            return l->getValue() == r->getValue();
        }
    }

    if (left->getType() != right->getType()) {
        return false;
    }

    if (left->getType() == Node::BOOLEAN) {
        Boolean *l = (Boolean *)left;
        Boolean *r = (Boolean *)right;

        return l->getValue() == r->getValue();
    }

    if (left->getType() == Node::NUMBER) {
        Number *l = (Number *)left;
        Number *r = (Number *)right;

        return l->getValue() == r->getValue();
    }
    
    if (left->getType() == Node::FLOAT) {
        Float *l = (Float *)left;
        Float *r = (Float *)right;

        return l->getValue() == r->getValue();
    }

    if (left->getType() == Node::STRING) {
        String *l = (String *)left;
        String *r = (String *)right;

        return (l->getValue().compare(r->getValue()) == 0);
    }

    if (left->getType() == Node::LIST) {
        List *l = (List *)left;
        List *r = (List *)right;

        bool res = (l->size() == r->size());

        for (size_t idx = 0; res and idx < l->size(); idx++) {
            res = res and l->getValue(idx).compare(r->getValue(idx)) == 0;
        }
 
        return res;
    }
    
    if (left->getType() == Node::RANGE) {
        Range *l = (Range *)left;
        Range *r = (Range *)right;

        return (l->getFrom() == r->getFrom() and l->getTo() == r->getTo());
    }

    return false;
}

//------------------------------------------------------------------------------
bool Interpreter::greaterOrEqual(Node *left, Node *right) {

    if ((left->getType() == Node::FLOAT and right->getType() == Node::NUMBER) or 
        (left->getType() == Node::NUMBER and right->getType() == Node::FLOAT)) { 

        if (left->getType() == Node::FLOAT) {
            Float *l = (Float *)left;
            Number *r = (Number *)right;
 
            return l->getValue() >= r->getValue();

        } else {
            Number *l = (Number *)left;
            Float *r = (Float *)right;
 
            return l->getValue() >= r->getValue();
        }
    }

    if (left->getType() != right->getType()) {

        return false;
    }

    if (left->getType() == Node::BOOLEAN) {

        return true;
    }

    if (left->getType() == Node::NUMBER) {
        Number *l = (Number *)left;
        Number *r = (Number *)right;

        return l->getValue() >= r->getValue();
    }
    
    if (left->getType() == Node::FLOAT) {
        Float *l = (Float *)left;
        Float *r = (Float *)right;

        return l->getValue() >= r->getValue();
    }

    if (left->getType() == Node::STRING) {
        String *l = (String *)left;
        String *r = (String *)right;

        return l->size() >= r->size();
    }

    if (left->getType() == Node::LIST) {
        List *l = (List *)left;
        List *r = (List *)right;

        return l->size() >= r->size();
    }

    return false;
}

//------------------------------------------------------------------------------
bool Interpreter::lessOrEqual(Node *left, Node *right) {

    if ((left->getType() == Node::FLOAT and right->getType() == Node::NUMBER) or 
        (left->getType() == Node::NUMBER and right->getType() == Node::FLOAT)) { 

        if (left->getType() == Node::FLOAT) {
            Float *l = (Float *)left;
            Number *r = (Number *)right;
        
            return l->getValue() <= r->getValue();

        } else {
            Number *l = (Number *)left;
            Float *r = (Float *)right;
        
            return l->getValue() <= r->getValue();
        }
    }

    if (left->getType() != right->getType()) {

        return false;
    }

    if (left->getType() == Node::BOOLEAN) {

        return true;
    }

    if (left->getType() == Node::NUMBER) {
        Number *l = (Number *)left;
        Number *r = (Number *)right;

        return l->getValue() <= r->getValue();
    }

    if (left->getType() == Node::FLOAT) {
        Float *l = (Float *)left;
        Float *r = (Float *)right;

        return l->getValue() <= r->getValue();
    }

    if (left->getType() == Node::STRING) {
        String *l = (String *)left;
        String *r = (String *)right;

        return l->size() <= r->size();
    }

    if (left->getType() == Node::LIST) {
        List *l = (List *)left;
        List *r = (List *)right;

        return l->size() <= r->size();
    }

    return false;
}

//------------------------------------------------------------------------------
bool Interpreter::contains(Node *left, Node *right) {

    if (left->getType() != right->getType()) {

        return false;
    }

    if (left->getType() != Node::STRING) {

        return false;
    }

    String *l = (String *)left;
    String *r = (String *)right;

    return l->getValue().find(r->getValue()) != std::string::npos;
}

//------------------------------------------------------------------------------
bool Interpreter::startsWith(Node *left, Node *right) {

    if (left->getType() != right->getType()) {

        return false;
    }

    if (left->getType() != Node::STRING) {

        return false;
    }

    String *l = (String *)left;
    String *r = (String *)right;

    return l->getValue().find(r->getValue()) == 0;
}

//------------------------------------------------------------------------------
bool Interpreter::endsWith(Node *left, Node *right) {

    if (left->getType() != right->getType()) {

        return false;
    }

    if (left->getType() != Node::STRING) {

        return false;
    }

    String *l = (String *)left;
    String *r = (String *)right;

    if (l->size() < r->size()) {

        return false;
    }

    return l->getValue().find(r->getValue()) == (l->size() - r->size());
}

//------------------------------------------------------------------------------
bool Interpreter::in(Node *left, Node *right) {

    if (right->getType() == Node::LIST) {
        List *r = (List *)right;
        return r->find(left->getToken());
    }

    if (left->getType() == Node::NUMBER and right->getType() == Node::RANGE) {
        Number *l = (Number *)left;
        Range *r = (Range *)right;

        return (r->getFrom() <= l->getValue() and l->getValue() <= r->getTo());
    }

    if (left->getType() == Node::FLOAT and right->getType() == Node::RANGE) {
        Float *l = (Float *)left;
        Range *r = (Range *)right;

        return (r->getFrom() <= l->getValue() and l->getValue() <= r->getTo());
    }

    return false;
}
