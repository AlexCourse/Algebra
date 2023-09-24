#include "Algebra_Node.h"
#include "Shanting_yard.h"
#include "Enumerate.h"
#include <ratio>

class Debug_concept
{
public:
	Debug_concept();
	int index;
	int call_order; // ������� ������ � �����������.
	std::map<int, std::set<int>> colored;
	std::set<int> red; // ���� � ������� ������� ��������� �����������.
	std::set<int> orange; // ���� ��������� ������.
	std::set<int> white; // ���� ������� ������.
};


Algebra_Node* DerivateFunction(Algebra_Node* root, Debug_concept& W);
double Numerical_Differentiation(Algebra_Tree& tree, double t, double h, std::string x);