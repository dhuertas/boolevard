#include "Node.hh"

std::string Node::names_[] = {
    "NONE",
    "BOOLEAN",
    "NUMBER",
    "STRING",
    "LIST",
    "UNARYOP",
    "BINARYOP"
};

//------------------------------------------------------------------------------
uint32_t Node::getType(void) {

    return NONE;
}

//------------------------------------------------------------------------------
std::string Node::getName(void) {

    return names_[getType()];
}

//------------------------------------------------------------------------------
Token Node::getToken(void) {

    return token_;
}

//------------------------------------------------------------------------------
std::string Node::toString(void) {

    std::stringstream ss;
    ss << "Node(" << this << ")";
    return ss.str();
}