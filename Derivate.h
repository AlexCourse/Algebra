#include "Algebra_Node.h"
#include "Shanting_yard.h"
#include <ratio>


Algebra_Node* DerivateFunction(Algebra_Node* root);
double Numerical_Differentiation(Algebra_Tree& tree, double t, double h, std::string x);