/*
 * Boolean expression evaluator in C++.
 *
 * @author: Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#include <cctype>
#include <algorithm>

#include "Token.hh"

std::string Token::names_[] = {
    "BOOLEAN",
    "NUMBER",
    "STRING",
    "LIST",
    "RANGE",
    "GREATER",
    "LESS",
    "EQUAL",
    "NOTEQUAL",
    "GREQ",
    "LEQ",
    "OR",
    "AND",
    "NOT",
    "CONTAINS",
    "STARTSWITH",
    "ENDSWITH",
    "IN",
    "LPAREN",
    "RPAREN",
    "EOL"
};

//------------------------------------------------------------------------------
bool Token::isTrue(const std::string &str, size_t pos) {

return (str.compare(pos, 4, "true") == 0 or 
        str.compare(pos, 4, "True") == 0 or
        str.compare(pos, 4, "TRUE") == 0);
}

//------------------------------------------------------------------------------
bool Token::isFalse(const std::string &str, size_t pos) {

return (str.compare(pos, 5, "false") == 0 or 
        str.compare(pos, 5, "False") == 0 or 
        str.compare(pos, 5, "FALSE") == 0);
}

//------------------------------------------------------------------------------
bool Token::isNumber(const std::string &str, size_t pos) {

    bool res = false;

    size_t i = pos;

    // allow negative numbers
    if (str[i] == '-') i++;

    while (i < str.size() and isdigit(str[i])) {

        if ( ! res) res = true;
        i++;
    }

    return (res and i > pos);
}

//------------------------------------------------------------------------------
void Token::trim(std::string &str) {

    size_t i = 0;
    while (str[i] == ' ' and i < str.size()) i++;
    size_t j = str.size() - 1;
    while (str[j] == ' ' and j > 0) j--;
    str = str.substr(i, j-i+1);
}

//------------------------------------------------------------------------------
Token::Token(const uint8_t type, const std::string &value) :
  type_(type),
  value_(value) {

}

//------------------------------------------------------------------------------
int64_t Token::getNumber(void) const {

    int64_t res = 0;

    sscanf(value_.c_str(), "%ld", &res);

    return res;
}

//------------------------------------------------------------------------------
bool Token::getBoolean(void) const {

    // Allowed values are true, True or TRUE
    return (type_ == Token::BOOLEAN) and (
        value_.compare("true") == 0 or 
        value_.compare("TRUE") == 0 or 
        value_.compare("True") == 0);
}

//------------------------------------------------------------------------------
std::vector<Token> Token::getList(void) const {

    std::vector<Token> tokens;

    size_t pos = 0, i = 0;

    uint32_t depth = 0;

    if (value_[i] == '[') i++;

    pos = i;

    for ( ; i < value_.size(); i++) {

        if (value_[i] == '[') depth++;
        else if (value_[i] == ']') depth--;
        else if (value_[i] == ',') {

            if (depth == 0) {

                std::string token(value_.substr(pos, i-pos));
                trim(token);

                if (isTrue(token) or isFalse(token)) {
                    tokens.push_back(Token(Token::BOOLEAN, token));
                }

                if (isNumber(token)) {
                    tokens.push_back(Token(Token::NUMBER, token));
                }

                if (token[0] == '[') {
                    int64_t from = 0, to = 0;
                    if (sscanf(token.c_str(), "[%ld..%ld]", &from, &to) == 2) {
                        tokens.push_back(Token(Token::RANGE, token));
                    } else {
                        tokens.push_back(Token(Token::LIST, token));
                    }
                }

                if (token[0] == '"') {
                    tokens.push_back(Token(Token::STRING, token));
                }

                pos = i+1;
            }
        }
    }

    // Last item
    if (pos < i) {

        std::string token(value_.substr(pos, i-pos-1));
        trim(token);

        if (isTrue(token) or isFalse(token)) {
            tokens.push_back(Token(Token::BOOLEAN, token));
        }

        if (isNumber(token)) {
            tokens.push_back(Token(Token::NUMBER, token));
        }

        if (token[0] == '[') {
            int64_t from = 0, to = 0;
            if (sscanf(token.c_str(), "[%ld..%ld]", &from, &to) == 2) {
                tokens.push_back(Token(Token::RANGE, token));
            } else {
                tokens.push_back(Token(Token::LIST, token));
            }
        }

        if (token[0] == '"') {
            tokens.push_back(Token(Token::STRING, token));
        }
    }

    return tokens;
}

//------------------------------------------------------------------------------
std::vector<int64_t> Token::getRange(void) const {

    std::vector<int64_t> res;
    int64_t from = 0, to = 0;

    sscanf(value_.c_str(), "[%ld..%ld]", &from, &to);

    res.push_back(from);
    res.push_back(to);

    return res;
}

//------------------------------------------------------------------------------
std::string Token::toString(void) const {

    std::stringstream ss;
    ss << "Token(" << getTypeName(type_) << ", " << value_ << ")";

    return ss.str();
}

//------------------------------------------------------------------------------
int64_t Token::compare(const Token &token) const {

    int64_t res = token.getType() - type_;

    if (res != 0) return res;

    // NOTE return 0 when equal
    switch (type_) {

        case BOOLEAN:
            return (getBoolean() - token.getBoolean());
        case NUMBER:
            return (getNumber() - token.getNumber());
        case STRING:
            return value_.compare(token.getString());
        case LIST: {
            std::vector<Token> a = getList();
            std::vector<Token> b = token.getList();
            return not std::equal(b.begin(), b.end(), a.begin());
        }
        case RANGE: {
            std::vector<int64_t> a = getRange();
            std::vector<int64_t> b = token.getRange();

            return not (a[0] == b[0] and a[1] == b[1]);
        }
    }

    return -1;
}

//------------------------------------------------------------------------------
bool Token::operator==(const Token &token) const {

    return compare(token) == 0;
}
