#ifndef __RANGE_HH__
#define __RANGE_HH__

#include "Node.hh"

class Range : public Node {

private:

protected:

    int64_t from_;

    int64_t to_;

public:

    Range(const Token &token) :
        Node(token) {

        std::vector<int64_t> r = token_.getRange();
        from_ = r[0];
        to_ = r[1];
    }

    virtual uint32_t getType(void) { return Node::RANGE; }

    int64_t getFrom(void) { return from_; }

    int64_t getTo(void) { return to_; }

    std::string toString(void) {

        std::stringstream ss;
        ss << "Range([" << from_ << ".." << to_ << "])";
        return ss.str();
    }
};

#endif
