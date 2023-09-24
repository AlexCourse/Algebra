#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include <unordered_set>
#include <variant>

// #include "vector_cl.h"

using namespace std;


class Token {
public:
    enum class Type {
        Unknown,
        Number,
        Integer,
        Real,
        LongArithmetic,
        Operator,
        LeftParen,
        RightParen,
        Algebra,
        Ration,
        ComplexNumber,
        Function,
        Comma,
    };

    const Type type;
    variant<string, int, double> value;
    const int precedence;
    const bool rightAssociative;

    Token();
    Token(Type t, const string& s, int prec = -1, bool ra = false);
    Token(const Token& other);
    Token(Type t, const int m);
    Token(Type t, const double m);
    Token operator=(const Token& other);
    bool operator==(const Token& other);
    bool operator == (const int m);
    bool operator == (const double m);
    bool operator == (const string m);
    friend ostream& operator << (ostream& os, const Token& token);
    string ToString();

    void SetValue(const variant<string, int, double>& newValue);
    variant<string, int, double> GetValue() const;

    ~Token();
};

bool f_arg(const Token& T);
bool f_opr_two(const Token& T);
bool f_opr_one(const Token& T);
bool f_opr_free(const Token& T);

string ToString(const variant<string, int, double>& value);

bool CE(const variant<string, int, double>, const string m); // #
bool CE(const variant<string, int, double>, const int m); // #
bool CE(const variant<string, int, double>, const double m); // #

Token SetToken(const variant<int, double, string> value);

string TokensToStr(deque<Token> fh);
deque<Token> exprToTokens(const string& expr);
void Tokenize_u_minus(deque<Token>& fh);
deque<Token> shuntingYard(const deque<Token>& tokens);
double PolishCalculation(deque<Token> es);
double PolishCalculation(vector<Token> es);

#endif
