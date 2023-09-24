#pragma once
#pragma once

#include <deque>
#include <set>
#include <string>
#include <map>
#include <math.h>
#include "Token.h"

enum Enumerable
{
	DEFAULT,
	ORDERING
};

bool IsNumeric(std::deque<Token> fh);
std::string PostfixToInfix(std::vector<Token>& fs);
std::string PostfixToInfix(std::deque<Token>& fs);
std::deque<Token> FToPolish(std::string expr);
std::deque<Token> FToPolishI(std::string expr, int& index, Enumerable q);
double FunctionValue(std::deque<Token> fh, double value, std::string symbol);
double FunctionValue(std::vector<Token> fh, double value, std::string symbol);
std::vector<Token> ReplaceElementInPolish(std::vector<Token> fh, double x, std::string symbol);
std::deque<Token> ReplaceElementInPolish(std::deque<Token> fh, double x, std::string symbol);
void PrintTokensListInformation(std::deque<Token> fh);
