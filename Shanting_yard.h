#pragma once

#include <deque>
#include <set>
#include <string>
#include <map>
#include <math.h>
#include "Token.h"


std::deque<Token> FToPolish(std::string expr);
double FunctionValue(std::deque<Token> fh, double value, std::string symbol);
double FunctionValue(std::vector<Token> fh, double value, std::string symbol);
std::vector<Token> ReplaceElementInPolish(std::vector<Token> fh, double x, std::string symbol);
std::deque<Token> ReplaceElementInPolish(std::deque<Token> fh, double x, std::string symbol);

