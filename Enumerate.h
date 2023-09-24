#pragma once
#include "Token.h"
#include <set>

std::set<int> CountIndex(std::deque<Token> fs);
std::set<int> CountIndex(std::vector<Token> fs);