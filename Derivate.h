#pragma once

#include "Algebra_Node.h"
#include "Shunting_yard.h"
#include "Enumerate.h"
#include <ratio>


Algebra_Node* DerivateFunction(Algebra_Node* root);
Algebra_Node* DerivateFunction(Algebra_Node* root, Debug_concept& W);
double Numerical_Differentiation(Algebra_Tree& tree, double t, double h, std::string x);
