#pragma once
#include "Algebra_Node.h"
#include "PrintColourConsole.h"

void simplify_F(Algebra_Node*& root);
void simplify_E(Algebra_Node*& root);
void simplify_D(Algebra_Node*& root);


class SM
{
public:
    SM(const int level, Algebra_Node* const parent, Algebra_Node*const branche, const char direcect) {}
    int level;
    Algebra_Node* parent;
    Algebra_Node* branche;
    char direct;
};