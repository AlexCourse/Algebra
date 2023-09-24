#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include <unordered_set>

using namespace std;


class Token {
public:
    enum class Type {
        Unknown,
        Number, // [0-9]
        Operator, // +,-,*,/,^,
        LeftParen, //'('
        RightParen, //')'
        Algebra,  //[a-z][A-Z]
        Ration,  // =,>=,<=,<,>
        Function, // sin(x), cos(x)
    };

    Token();
    Token(Type t, const string& s, int prec = -1, bool ra = false);
    Token(const Token& other);
    Token operator=(const Token other);
    bool operator == (const Token other);
    friend ostream& operator<<(ostream& os, const Token& token);

    const Type type;
    string str;
    const int precedence;
    const bool rightAssociative;
    const char Associative = 0;
};

bool f_arg(const Token& T);
bool f_opr_two(const Token& T);
bool f_opr_one(const Token& T);
bool f_opr_free(const Token& T);

Token SetToken(const string& expr);
Token SetToken(int m);
string TokensToStr(deque<Token> fh);
deque<Token> exprToTokens(const string& expr);
void Tokenize_u_minus(deque<Token>& fh);
deque<Token> shuntingYard(const deque<Token>& tokens);
double PolishCalculation(deque<Token> es);
#endif
