#pragma once

#include <deque>
#include <set>
#include <string>
#include <map>
#include "Token.h"


using namespace std;


bool isliter(char p);
deque<Token> exprToTokens(const string& expr);
deque<Token> shuntingYard(const deque<Token>& tokens);
double PolishCalculation(deque<Token> es);

