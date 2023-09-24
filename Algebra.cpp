
#include <iostream>
#include <deque>
#include "algebra_node.h"
#include "Shanting_yard.h"

#define DEBUG 1

enum Type_expr { // 
	NUMBER,
	FUCTION
};

using namespace std;

int main() {

	// string s = "(1-5*(1/2+5/6-7*(5+8/9*4^3)))";
	// string s = "(x^2-1)*(x-4/5)*(7/8+3*x)^2 + 3*x*(x-1)"
	string s;
	getline(cin, s);

	deque<Token> fs, es;
	deque<Token>::iterator iter;
	fs = exprToTokens(s);
	if (DEBUG)
	{
		for (iter = fs.begin(); iter != fs.end(); iter++) cout << *iter << " ";
		cout << endl;
	}
	es = shuntingYard(fs);
	if (DEBUG)
	{
		for (iter = es.begin(); iter != es.end(); iter++) cout << *iter << " ";
		cout << endl;
	}
	double r = PolishCalculation(es);

	cout << r << endl;

    Algebra_Node* tree = PolishToTree(es);
	Algebra_Tree* operator_tree = new Algebra_Tree(tree);
	if (DEBUG)
	{
		Print_Tree_R(tree, "", true, true);
		for(int i = 0 ; i < 2; i++) cout << endl;
		cout << "Обход дерева в ширину без рекурсии" << endl;
		ByPassTreeW(tree);
		cout << endl;
		cout << "Обход дерева в глубину без рекурсии" << endl;
		ByPassTreeD(tree);
		cout << endl;
	}



    return 0;
}