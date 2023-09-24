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
// ������ ������ : �������� - ����������� ���� , ������� - ������������� ���� Token::Function, ����� - int , double , long_arithmetic , �������������� ������ - ���������� ����.

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
            EXP ,
            LN,
            SIN,
            COS ,
            TG,
            CTG ,
            ARCSIN,
            ARCCOS,
            ARCTG,
            ARCCTG,
            SH,
            CH,
            TH,
            CTH,
            ARSH,
            ARCH,
            ARTH,
            ARCTH,
            ABS ,
            LOG , 
            POW
        };

        const Type type;
        std::variant<std::string, char ,int, double , Token::Function> value;
        const int precedence;
        const bool rightAssociative;
        const int index;

        Token();
        Token(Type t, const std::string& s, int prec = -1, bool ra = false);
        Token(const Token& other);
        Token(Type t, char c, int prec, bool ra);
        Token(Type t, const int m);
        Token(Type t, const double m);
        Token(Type t, const Token::Function m);

        Token(Type t, const std::string& s, int index ,int prec = -1, bool ra = false);
        Token(Type t, const std::string& s, int index);
        Token(const Token& other, int index);
        Token(Type t, char c, int index, int prec, bool ra);
        Token(Type t, const int m, int index);
        Token(Type t, const double m, int index);
        Token(Type t, const Token::Function m, int index);

        Token operator=(const Token& other);
        bool operator==(const Token& other);
        bool operator == (const int m);
        bool operator == (const double m);
        bool operator == (const std::string m);
        friend std::ostream& operator << (std::ostream& os, const Token& token);
        std::string ToString();

        void SetValue(const std::variant<std::string, char, int, double, Token::Function>& newValue);
        std::variant<std::string, char, int, double, Token::Function> GetValue() const;

        ~Token();
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
    Token SetToken(const std::variant<std::string, char, int, double, Token::Function> value , int& index);

    std::string TokensToStr(std::deque<Token> fh);
    std::deque<Token> exprToTokens(const std::string& expr);
    std::deque<Token> exprToTokens(const std::string& expr , int& index , std::string q);
    void Tokenize_u_minus(std::deque<Token>& fh);
    std::deque<Token> shuntingYard(const std::deque<Token>& tokens);
    double PolishCalculation(std::deque<Token> es);
    double PolishCalculation(std::vector<Token> es);

#endif
