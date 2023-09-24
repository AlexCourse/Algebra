#pragma once

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include <unordered_set>
#include <variant>
#define M_PI 3.1415926535897932384626433832795028841971

// #include "vector_cl.h"
// Формат данных : Оператор - символьного типа , Функция - перечеслимого типа Token::Function, Число - int , double , long_arithmetic , Алгеьраический символ - строкового типа.



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
    enum class Function
    {
        EXP,
        LN,
        SIN,
        COS,
        TG,
        CTG,
        ARCSIN,
        ARCCOS,
        ARCTG,
        ARCCTG,
        SH,
        CH,
        TH,
        CTH,
        ARCSH,
        ARCCH,
        ARCTH,
        ARCCTH,
        ABS,
        LOG,
        POW
    };

    const Type type;
    std::variant<std::string, char, int, double, Token::Function> value;
    const int precedence;
    const bool rightAssociative;
    const int index; // Уникальный номер токена.
    const int start_pos; // Индекс первого вхождения токена как подстроки в исходную спаршенную строку. Эти 2 для вывода синтаксической ошибки.
    const int last_pos; // Индекс последнего вхождения токена как подстроки в исходную спаршенную строку.

    Token();
    Token(Type t, const std::string& s, int prec = -1, bool ra = false);
    Token(const Token& other);
    Token(Type t, char c, int prec, bool ra);
    Token(Type t, const int m);
    Token(Type t, const double m);
    Token(Type t, const Token::Function m);

    Token(const Type t, const std::string& s, const int index, const int start_index, const int last_index, const int prec = -1, const bool ra = false);
    Token(const Type t, const std::string& s, const int index, const int start_index, const int last_index);
    Token(const Token& other, int index, int start_index, int last_index);
    Token(const Type t, const char c, const int index, const int prec, const bool ra);
    Token(const Type t, const char c, const int index, const int start_pos, const int last_pos, const int prec, const bool ra);
    Token(const Type t, const int m, const int index, const int start_index, const int last_index);
    Token(const Type t, const double m, const int index, const int start_index, const int last_index);
    Token(const Type t, const Token::Function m, const int index, const int start_index, const int last_index);

    Token operator=(const Token& other);
    bool operator==(const Token& other);
    bool operator == (const int m);
    bool operator == (const double m);
    bool operator == (const std::string m);
    bool operator == (const char c);
    bool operator == (const Token::Function f_able);
    friend std::ostream& operator << (std::ostream& os, const Token& token);
    friend std::ostream& operator << (std::ostream& os, const Token::Type p);
    std::string ToString();

    void SetValue(const std::variant<std::string, char, int, double, Token::Function>& newValue);
    std::variant<std::string, char, int, double, Token::Function> GetValue() const;

    ~Token();
};



class BW
{
public:
    BW() : isCorrect(true) {}
    bool isCorrect;
    std::deque<std::tuple<int, int>> position;
    std::deque<std::tuple<int, int>> broken_pos;
};

bool f_arg(const Token& T);
bool f_opr_two(const Token& T);
bool f_opr_one(const Token& T);
bool f_opr_free(const Token& T);

std::string ToString(const std::variant<std::string, char, int, double, Token::Function>& value);

bool CE(const std::variant<std::string, char, int, double, Token::Function>, const std::string m); // #
bool CE(const std::variant<std::string, char, int, double, Token::Function>, const int m); // #
bool CE(const std::variant<std::string, char, int, double, Token::Function>, const double m); // #
bool CE(const std::variant<std::string, char, int, double, Token::Function> value, const char c);
bool CE(const std::variant<std::string, char, int, double, Token::Function> value, Token::Function p);

Token SetToken(const std::variant<std::string, char, int, double, Token::Function> value);
Token SetToken(const std::variant<std::string, char, int, double, Token::Function> value, int& index);

std::string TokensToStr(const std::deque<Token> fh);
std::deque<Token> exprToTokens(const std::string& expr);
std::deque<Token> exprToTokens(const std::string& expr, BW& C);
std::deque<Token> exprToTokens(const std::string& expr, int& index, std::string q);
std::deque<Token> exprToTokens(const std::string& expr, int& index, BW& C, std::string q);
void Tokenize_u_minus(std::deque<Token>& fh);
std::deque<Token> shuntingYard(const std::deque<Token>& tokens);
double PolishCalculation(std::deque<Token> es);
double PolishCalculation(std::vector<Token> es);


#endif
