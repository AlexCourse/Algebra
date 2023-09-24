#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include <unordered_set>
#include <variant>

using namespace std;


class Token {
public:
    enum class Type {
        Unknown,
        Number,
        Integer,
        Real,
        Operator,
        LeftParen,
        RightParen,
        Algebra,
        Ration,
        Function
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
/*
template<typename T>
bool CheckEquality(variant<string, int, double>, T m); 
*/

bool CheckEquality(variant<string, int, double>, string m); // #
bool CheckEquality(variant<string, int, double>, int m); // #
bool CheckEquality(variant<string, int, double>, double m); // #

Token SetToken(const string& expr);
Token SetToken(int m);
string TokensToStr(deque<Token> fh);
deque<Token> exprToTokens(const string& expr);
void Tokenize_u_minus(deque<Token>& fh);
deque<Token> shuntingYard(const deque<Token>& tokens);
double PolishCalculation(deque<Token> es);
#endif
