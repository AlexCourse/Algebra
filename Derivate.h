#include "Algebra_Node.h"
#include "Shanting_yard.h"
#include "Enumerate.h"
#include <ratio>

class Debug_concept
{
public:
	Debug_concept();
	int index;
	int call_order; // Уровень вызова в производной.
	std::map<int, std::set<int>> colored;
	std::set<int> red; // Узлы в которых неверно вычислена производная.
	std::set<int> orange; // Узлы нечетного уровня.
	std::set<int> white; // Узлы четного уровня.
};


Algebra_Node* DerivateFunction(Algebra_Node* root, Debug_concept& W);
double Numerical_Differentiation(Algebra_Tree& tree, double t, double h, std::string x);