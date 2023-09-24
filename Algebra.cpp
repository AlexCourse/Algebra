
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
	string fh[4] = { "(1-5*(1/2+5/6-7*(5+8/9*4^3)))" // +
		        , "(x^2-1)*(x-4/5)*(7/8+3*x)^2 + 3*x*(x-1)" ,  // +
		             "1+2/3*(1+7/8-6/9+2*(1-6/11+9/15))^2" , // + 
		                  "cos(x^2)" // -
	};
	string s = fh[3];
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
	second_tree.TreeExprReplaceD_T("x", "5"); // Здесь исключение.
	second_tree.Print_Tree_T();
	string f = "x";
	es = exprToTokens(f);
	Token Q = es.front();
	Algebra_Node* third_node = new Algebra_Node(Q);
	Algebra_Tree third_tree = second_tree.AddSubtree(third_node, LR::LEFT);
	for (int i = 0; i < 2; i++) cout << endl;
	third_tree.Print_Tree_T();
}

void test_2() // Тестирование перегруженного оператора для класса AlgebraTree.
{
	string s , f;
	deque<Token> fs, es, fh, eh;
	getline(cin, s);
	getline(cin, f);
	fh = exprToTokens(s);
	eh = exprToTokens(f);
	Tokenize_u_minus(fh);
	Tokenize_u_minus(eh);
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
	Tokenize_u_minus(fh);
	Tokenize_u_minus(eh);
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
{ // Лишние скобки.
	string s , f;
	deque<Token> fh, fs;
	vector<Token> es;
	Token T;
	string eh[7] = { "x" , // +
		             "3" , // +
		             "5.0" , // +
		             "-5.0" , // +
		             "-2" , // +
		             "4+(1/7-6/9+5*(4-7/8))" , // +
		             "x/2+ x*x*(x+2*x^2)-3*x - 2*x^2" // +
	};
	// getline(cin, s);
	s = eh[4];
	fh = exprToTokens(s);
	Tokenize_u_minus(fh);
	fs = shuntingYard(fh);
	f = PostfixToInfix(fs);
	while (!fs.empty())
	{
		Token T = fs.front();
		fs.pop_front();
		es.push_back(T);
	}
	cout << f << endl;
}

void test_6() // Тестирование функции TreeToPolish_T()
{ // Лишние скобки.
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
{    
	// Простейший неработающий пример 2*(x-1) , x-2-x
	double x = 2.0;
	double Q[2];
	string s;
	deque<Token> fh, fs, es;
	getline(cin, s);
	fh = exprToTokens(s);
	fs = shuntingYard(fh);
	Algebra_Node* node = PolishToTree(fs);
	Algebra_Tree* K = new Algebra_Tree(node);
	Algebra_Tree& first_tree = *K;
	Q[0] = Numerical_Differentiation(first_tree, x, pow(10, -4), "x");
	Algebra_Node* D = DerivateFunc(node);
	Algebra_Tree* d_tree = new Algebra_Tree(D);
	Algebra_Tree& T = *d_tree;
	T.Print_Tree_T();
	Q[1] = T.FunctionValue_T(x, "x");
	while (0);
}

void test_8() // Тестирование фунции SetToken()
{
	string fh[6] = { "*" , // +
		            "1" ,  // +
		            "-1" ,  // +
		            "-2" ,   // +
		            "3.0" ,  // +
		            "-3.0"   // +
	                 }; 
	string s = fh[5];
	Token T = SetToken(s);
	cout << T << endl;

}

void test_9()  // Тестирование функции SetNode()
{
	string fh[6] = { "x" , // +
					"1" ,  // +
					"-1" ,  // +
					"-2" ,   // +
					"3.0" ,  // +
					"-3.0"   // +
	};
	string s = fh[5];
	Algebra_Node* node = SetNode(s);
	vector<Token> es;
	TreeToPolish(node , es);
	vector<Token>::iterator iter;
	for (iter = es.begin(); iter != es.end(); iter++) cout << *iter << " ";
	cout << endl;
	s = PostfixToInfix(es);
	cout << s << endl;
}

void test_10() // Тестирование функции PolishCalculation()
{
	string fh[7] = { "0.5*0.25" , // +
		            "0.5*0.7*(1.5+1)"  , // +
		            "1+0.7*(3-4+5*0.5*0.25*(1-4*3))", // +
		             "1+2/3*(1+7/8-6/9+2*(1-6/11+9/15))^2", // +
		              "sin(1-4/7+3/13*(1+4/9)^2)*cos(1-(4/11)^2)", // +
		               "3/4*sin(1+11/157)", // -
					   "(3/4)*sin(1+11/157)" // + , Token error.
	};
	string s = fh[5];
	deque<Token> fs, es;
	fs = exprToTokens(s); 
	Tokenize_u_minus(fs);
	es = shuntingYard(fs);
	double r = PolishCalculation(es);
	while (0);
}

void test_11() // Тестирование функции Tokenize_u_minus()
{
	string fh[3] = { "(-1)+x+(-1)*x^2*((-1)+3*x))" // -
		              , "-1+x" , // +
		               "(-1)" // +
	};
	string s = fh[0];
	deque<Token> fs, es;
	fs = exprToTokens(s);
	Tokenize_u_minus(fs);
	string f = TokensToStr(fs);
	cout << f << endl;
	while (0);
}

void test_12() // Тестирование функции SetToken()
{
	string fh[1] = { "-1" };
	string s = fh[0];
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

void test_16()
{

	Token T = SetToken("2");
	cout << T << endl;
	T = SetToken("3.5");
	cout << T << endl;
	while (0);
	
}

void test_17() 
{
	Token T(Token::Type::Unknown, "");
	T = Token(Token::Type::Number, "2");
	cout << T << endl;
	T.~Token();
	T = Token(Token::Type::Number, "3.5");
	cout << T << endl;
	T.~Token();
	while (0);

}

void test_18() // Тестирование функции SetToken()
{
	Token T = SetToken("2");
	Algebra_Node* node = new Algebra_Node(T);
	node->data.~Token();
	node->data = SetToken("1");
	Token K = node->data;
	cout << K << endl;
}


void test_19()
{
	/*
	Token T_1(Token::Type::Number, "42");
	int intValue = T_1.GetValue<int>(); // Returns 42
	cout << intValue << endl;

	Token T_2(Token::Type::Real, 3.14);
	double doubleValue = T_2.GetValue<double>(); // Returns 3.14
	cout << doubleValue << endl;

	Token T_3(Token::Type::Algebra, "x");
	string strValue = T_3.GetValue<string>(); // Returns "x"
	cout << strValue << endl;
	*/

}

void test_20()
{
	/*
	Algebra_Node* root = new Algebra_Node(SetToken("x"));
	root->left = new Algebra_Node(SetToken("y"));
	root->right = new Algebra_Node(SetToken("z"));

	// Call the TreeExprReplaceR function
	Algebra_Node* newRoot = TreeExprReplaceRT(root, "x", 5);

	// Print the modified tree
	cout << newRoot->toString() << endl;

	// Clean up memory
	delete newRoot;
	*/
}

void test_21() // Тестирование шаблонной версии функции: FindValueD
{
	const string s[2] = { "3*x^2*(x+1)-x+x^2" , "(-1)*x+(-1)" };
	const string t = s[1];
	Algebra_Node* root = SetOperatorTree(t);
	vector<vector<char>> paths;
	// _FindValueD(root, 5 , paths);
	while (0);
}


int main() {

	const int n = 1; 
	switch (n)
	{
	case 1: { test_1(); break; } // +
	case 2: { test_2(); break; } // +
	case 3: { test_3(); break; } // +
	case 4: { test_4(); break; } // +
	case 5: {test_5(); break; } // +
	case 6: { test_6(); break; } // +
	case 7: { test_7(); break; }
	case 8: { test_8(); break; } // +
	case 9: { test_9(); break; } // +
	case 10: { test_10(); break; }
	case 11: { test_11(); break; }
	case 12: { test_12(); break; }
	case 13: { test_13(); break; }
	case 14: { test_14(); break; }
	case 15: { test_15(); break; }
	case 16: { test_16(); break; }
	case 17: { test_17(); break; }
	case 18: { test_18(); break; }
	case 19: { test_19(); break; }
	case 20: { test_20(); break; }
	case 21: { test_21(); break; }
	}	
}