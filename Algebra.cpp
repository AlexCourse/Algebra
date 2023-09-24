
#include <iostream>
#include <deque>
#include "algebra_node.h"
#include "Shanting_yard.h"
#include "Algebra.h"
#include "Derivate.h"

#define DEBUG 1

enum Type_expr { // 
	NUMBER,
	FUCTION
};

using namespace std;


void test_1() // Тестирование функций exprToTokens() , shuntingYard().
{
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
	// double r = PolishCalculation(es);

	// cout << r << endl;

	Algebra_Node* tree = PolishToTree(es);
	Algebra_Tree* first_tree = new Algebra_Tree(tree);
	if (DEBUG)
	{
		Print_Tree_R(tree, "", true, true);
		for (int i = 0; i < 2; i++) cout << endl;
		cout << "Обход дерева в ширину без рекурсии" << endl;
		BypassTreeW(tree);
		cout << endl;
		cout << "Обход дерева в глубину без рекурсии" << endl;
		BypassTreeD(tree);
		cout << endl;
	}
	Algebra_Tree second_tree = first_tree->CopyTree();
	second_tree.TreeExprReplaceD_T("x", "5");
	second_tree.Print_Tree_T();
	string f = "x";
	es = exprToTokens(f);
	Token Q = es.front();
	Algebra_Node* third_node = new Algebra_Node(Q);
	Algebra_Tree third_tree = second_tree.AddSubtree(third_node, LR::LEFT);
	for (int i = 0; i < 2; i++) cout << endl;
	third_tree.Print_Tree_T();
}

void test_2() // Тестирование функции PolishToTree()
{
	string s , f;
	deque<Token> fs, es, fh, eh;
	getline(cin, s);
	getline(cin, f);
	fh = exprToTokens(s);
	eh = exprToTokens(f);
	fs = shuntingYard(fh);
	es = shuntingYard(eh);
	Algebra_Node* first_node;
	Algebra_Node* second_node;
	Algebra_Tree* tree[2];
	first_node = PolishToTree(fs);
	second_node = PolishToTree(es);
	tree[0] = new Algebra_Tree(first_node);
	tree[1] = new Algebra_Tree(second_node);
	Algebra_Tree& first_tree = *(tree[0]);
	Algebra_Tree& second_tree = *(tree[1]);
	// Algebra_Tree& third_tree = first_tree + second_tree;
}


void test_3() // Тестирование функции FindValueD_T()
{
	string s;
	deque<Token> fh, fs;
	getline(cin, s);
	fh = exprToTokens(s);
	fs = shuntingYard(fh);
	Algebra_Node* node = PolishToTree(fs);
	Algebra_Tree* tree = new Algebra_Tree(node);
	Algebra_Tree& T = *tree;
	vector<vector<char>> paths;
	map<string, Cane> all_paths;
	// =====================================
	T.FindValueD_T("+", paths);
	Cane* Q = new Cane();
	Q->paths = paths;
	all_paths["+"] = *Q;
	cout << '+' << endl;
	Print_paths(paths);
	paths.clear();
	for (int i = 0; i < 1; i++) cout << endl;
	T.FindValueW_T("+", paths);
	Q->paths = paths;
	all_paths["+"] = *Q;
	Print_paths(paths);
	paths.clear();
	for (int i = 0; i < 2; i++) cout << endl;
	// =====================================
	T.FindValueD_T("-", paths);
	Q = new Cane();
	Q->paths = paths;
	all_paths["-"] = *Q;
	cout << '-' << endl;
	Print_paths(paths);
	paths.clear();
	for (int i = 0; i < 1; i++) cout << endl;
	T.FindValueW_T("-", paths);
	Q->paths = paths;
	all_paths["-"] = *Q;
	Print_paths(paths);
	paths.clear();
	for (int i = 0; i < 2; i++) cout << endl;
	// =====================================
	T.FindValueD_T("*", paths);
	Q = new Cane();
	Q->paths = paths;
	all_paths["*"] = *Q;
	cout << '*' << endl;
	Print_paths(paths);
	paths.clear();
	for (int i = 0; i < 1; i++) cout << endl;
	T.FindValueW_T("*", paths);
	Q->paths = paths;
	all_paths["*"] = *Q;
	Print_paths(paths);
	paths.clear();
	for (int i = 0; i < 2; i++) cout << endl;
	// =====================================
	T.FindValueD_T("/", paths);
	Q = new Cane();
	Q->paths = paths;
	all_paths["/"] = *Q;
	cout << '/' << endl;
	Print_paths(paths);
	paths.clear();
	for (int i = 0; i < 1; i++) cout << endl;
	T.FindValueW_T("/", paths);
	Q->paths = paths;
	all_paths["/"] = *Q;
	Print_paths(paths);
	paths.clear();
	for (int i = 0; i < 2; i++) cout << endl;
	// =====================================
	T.FindValueD_T("^", paths);
	Q = new Cane();
	Q->paths = paths;
	all_paths["^"] = *Q;
	cout << '^' << endl;
	Print_paths(paths);
	paths.clear();
	for (int i = 0; i < 1; i++) cout << endl;
	T.FindValueW_T("^", paths);
	Q->paths = paths;
	all_paths["^"] = *Q;
	Print_paths(paths);
	paths.clear();
	for (int i = 0; i < 2; i++) cout << endl;
	// ======================================
	T.FindValueD_T("x", paths);
	Q = new Cane();
	Q->paths = paths;
	all_paths["x"] = *Q;
	cout << 'x' << endl;
	Print_paths(paths);
	paths.clear();
	for (int i = 0; i < 1; i++) cout << endl;
	T.FindValueW_T("x", paths);
	Q->paths = paths;
	all_paths["x"] = *Q;
	Print_paths(paths);
	paths.clear();
	for (int i = 0; i < 2; i++) cout << endl;
}

void test_4() // Тестирование функции CompareTrees()
{
	string s, f;
	deque<Token> fs, es, fh, eh;
	getline(cin, s);
	getline(cin, f);
	fh = exprToTokens(s);
	eh = exprToTokens(f);
	fs = shuntingYard(fh);
	es = shuntingYard(eh);
	Algebra_Node* first_node;
	Algebra_Node* second_node;
	Algebra_Tree* tree[2];
	first_node = PolishToTree(fs);
	second_node = PolishToTree(es);
	bool B = false;
    B = CompareTrees(first_node , second_node);
	cout << B << endl;
}

void test_5() // Тестирование функции PostfixToInfix()
{
	string s , f;
	deque<Token> fh, fs;
	vector<Token> es;
	Token T;
	getline(cin, s);
	fh = exprToTokens(s);
	fs = shuntingYard(fh);
	f = PostfixToInfix(es);
	while (!fs.empty())
	{
		Token T = fs.front();
		fs.pop_front();
		es.push_back(T);
	}
	cout << f << endl;
}

void test_6() // Тестирование функции TreeToPolish_T()
{
	string s, f;
	deque<Token> fh, fs;
	vector<Token> es;
	getline(cin, s);
	fh = exprToTokens(s);
	fs = shuntingYard(fh);
	Algebra_Node* node = PolishToTree(fs);
	Algebra_Tree* tree = new Algebra_Tree(node);
	Algebra_Tree& T = *tree;
	T.TreeToPolish_T();
	es = T.polish;
	f = PostfixToInfix(es);
	cout << f << endl;

}

void test_7() // Тестирование функции DerivateFunc()
{  // (x+1)/(x-1) , возникает ошибка из-за неверной обработки унарных минусов в разделении на Token
	// Простейши йнеработающий пример 2*(x-1) , x-2-x
	double x = 2.0;
	string s;
	deque<Token> fh, fs, es;
	getline(cin, s);
	fh = exprToTokens(s);
	fs = shuntingYard(fh);
	Algebra_Node* node = PolishToTree(fs);
	Algebra_Tree* K = new Algebra_Tree(node);
	Algebra_Tree& first_tree = *K;
	Algebra_Tree& second_tree = first_tree.CopyTree();
	double r = Numerical_Differentiation(second_tree , x , pow(10 , -4) , "x");
	Algebra_Node* D = DerivateFunc(node);
	Algebra_Tree* d_tree = new Algebra_Tree(D);
	Algebra_Tree& T = *d_tree;
	T.Print_Tree_T();
	double t = T.FunctionValue_T(x , "x");
}

void test_8() // Тестирование фунции SetToken()
{
	// Token T = SetToken("*");
	Token T = SetToken("1");
	cout << T << endl;

}

void test_9()  // Тестирование функции SetNode()
{
	Algebra_Node* node = SetNode("1");
	node = SetNode("-1"); // fail
	vector<Token> es;
	TreeToPolish(node , es);
	vector<Token>::iterator iter;
	for (iter = es.begin(); iter != es.end(); iter++) cout << *iter << " ";
	cout << endl;
	string s = PostfixToInfix(es);
	cout << s << endl;
}

void test_10()
{
	string s = "-1+x";  // функция не обрабатывает минус впереди
	deque<Token> fs, es;
	fs = exprToTokens(s); 
	es = shuntingYard(fs);
	while (0);
}

void test_11() // Тестирование функции Tokenize_u_minus()
{
	string s = "(-1)+x+(-1)*x^2*((-1)+3*x))";
	// s = "(-1)";
	s = "-1+x";
	deque<Token> fs, es;
	fs = exprToTokens(s);
	Tokenize_u_minus(fs);
	string f = TokensToStr(fs);
	cout << f << endl;
	while (0);
}

void test_12() // Тестирование функции SetToken()
{
	string s;
	s = "-1";
	Token T = SetToken(s);
	cout << T << endl;
}

void test_13() // Тестирование функции SetAlgebricTree()
{
	string s;
	getline(cin, s);
	Algebra_Tree& T = SetAlgebricTree(s);
	T.Print_Tree_T();
}

void test_14()
{  // Тестирование функции TreeRExprReplaceOnSubTreeD()
	string s;
	s = "3*(x+c)+c*x^2*(x-c)+8*x*c"; 
	s = "4*x^2*(x^2-c^2)+3*x*(x-c/x)";
	s = "(x-c)^2";
	// s = "x-c";
	Algebra_Tree& first_tree = SetAlgebricTree(s);
	s = "x+3";
	Algebra_Node*  node = SetOperatorTree(s);
	string f = "c";
	first_tree.Print_Tree_T();
	first_tree.TreeRExprReplaceOnSubTreeD_T(f, node);
	for (int i = 0; i < 42; i++) cout << '=';
	cout << endl;
	first_tree.Print_Tree_T();
}

void test_15()
{  // Тестирование функции TreeRExprReplaceOnSubTreeW()
	string s;
	s = "3*(x+c)+c*x^2*(x-c)+8*x*c";
	s = "4*x^2*(x^2-c^2)+3*x*(x-c/x)";
	s = "(x-c)^2*x*c +3*c";
	// s = "(x-c)^2";
	// s = "x-c";
	Algebra_Tree& first_tree = SetAlgebricTree(s);
	string t = "x+3";
	Algebra_Node* node = SetOperatorTree(t);
	string f = "c";
	first_tree.Print_Tree_T();
	first_tree.TreeRExprReplaceOnSubTreeW_T(f, node);
	for (int i = 0; i < 42; i++) cout << '=';
	cout << endl;
	first_tree.Print_Tree_T();

}


int main() {

	const int n = 7;
	switch (n)
	{
	    case 1: test_1();
		case 2: test_2();
		case 3: test_3();
		case 4: test_4();
		case 5: test_5();
		case 6: test_6();
		case 7: test_7();
		case 8: test_8();
		case 9: test_9();
		case 10: test_10();
		case 11: test_11();
		case 12: test_12();
		case 13: test_13();
		case 14: test_14();
		case 15: test_15();
	}	
}