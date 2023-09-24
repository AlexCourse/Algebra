#pragma once

#include <deque>
#include <set>
#include <string>
#include <map>
#include <math.h>
#include "Token.h"


using namespace std;

deque<Token> FToPolish(string expr);
double FunctionValue(deque<Token> fh, double value, string symbol);
double FunctionValue(vector<Token> fh, double value, string symbol);
vector<Token> ReplaceElementInPolish(vector<Token> fh, double x, string symbol);
deque<Token> ReplaceElementInPolish(deque<Token> fh, double x, string symbol);

