#include "Algebra_Node.h"
#include "Shanting_yard.h"
#include <ratio>


Algebra_Node* DerivateFunc(Algebra_Node* root);
double Numerical_Differentiation(Algebra_Tree& tree, double t, double h, string x);