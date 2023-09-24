#include "token.h"

Token::Token() : type(Type::Unknown), str(""), precedence(-1), rightAssociative(false) {}

Token::Token(Type t, const std::string& s, int prec, bool ra)
    : type(t), str(s), precedence(prec), rightAssociative(ra) {}

Token::Token(const Token& other)
    : type(other.type), str(other.str), precedence(other.precedence), rightAssociative(other.rightAssociative) {}

Token Token::operator=(const Token other) {
    return Token(other);
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token.str;
    return os;
}

