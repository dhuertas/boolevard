/*
 * Boolean expression evaluator in C++.
 *
 * @author: Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#ifndef __NODEVISITOR_HH__
#define __NODEVISITOR_HH__

#include "Object.hh"
#include "Node.hh"

class NodeVisitor : public Object {

private:

protected:

public:

    virtual ~NodeVisitor() {}

    virtual bool visit(Node *node) = 0;
};

#endif