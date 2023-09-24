#include <iostream>
#include <deque>
#include "algebra_node.h"
#include "Shanting_yard.h"
#include "Algebra.h"
#include "Derivate.h"
#include "simplify.h"
#define M_PI 3.1415926535897932384626

#define DEBUG 1

enum Type_expr { // 
	NUMBER,
	FUCTION
};

using namespace std;


void test_1() // Тестирование функций exprToTokens() , shuntingYard() , CopyTree() , PolishToTree() , TreeToInfix() , FunctionValue()
{
	const int MODE = 0;
	string fh[] = { "(1-5*(1/2+5/6-7*(5+8/9*4^3)))" // + , 0
				, "(x^2-1)*(x-4/5)*(7/8+3*x)^2 + 3*x*(x-1)" ,  // +
					 "1+2/3*(1+7/8-6/9+2*(1-6/11+9/15))^2" , // + 
						  "cos(x^2)", // -
						  "sin(3)*cos(1)", // - , не работает PolishToTree()
						  "sin(x^2-3*x+2)*sin(7/4)",
						  "log(x , 2)",
		                  "1-2",
		                  "4+7*3", // +
		                  "(4+5)*6", // +
		                  "7+(8+4)^2*(7-4/5)+3+7-2*3", // - , 10
						  "(4-7)*(1+9)"
	};
	const double x = 2;
	string s = fh[12];
	if (MODE == 1) getline(cin, s);

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
	double r = FunctionValue(es , x , "x");

	// cout << r << endl;

	Algebra_Node* tree = PolishToTree(es);
	Algebra_Tree* first_tree = new Algebra_Tree(tree);
	if (DEBUG)
	{
		cout << "first_tree : " << endl;
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
	cout << "second_tree : " << endl;
	second_tree.Print_Tree_T();
	string f = "cos";
	es = exprToTokens(f);
	Token Q = es.front();
	Algebra_Node* third_node = new Algebra_Node(Q);
	Algebra_Tree third_tree = second_tree.AddSubtree(third_node, LR::LEFT);
	for (int i = 0; i < 2; i++) cout << endl;
	// cout << "third_tree : " << endl;
	// third_tree.Print_Tree_T();
	string t = first_tree->TreeToInfix_T(); // Не корректно работает с функциями
	es = FToPolish(t);
	double r_1 = FunctionValue(es, x, "x");
	vector<tuple<double, double>> ph;
	ph.push_back(make_tuple(r, r_1));
	for (const auto& element : ph) {
		cout << "(" << get<0>(element) << ", " << get<1>(element) << ")" << endl;
	}
	cout << t << endl;
}

void test_2() // Тестирование перегруженного оператора для класса AlgebraTree.
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
	B = CompareTrees(first_node, second_node);
	cout << B << endl;
}

void test_5() // Тестирование функции PostfixToInfix()
{ // Лишние скобки.
	string s, f;
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
	vector<tuple<double, double>> ph;
	string eh[] = { "2*(x-1)" , // + ,0
					  "x-2-x" , // +
						"sin(x)" , // +
					     "cos(x^2)" , // -
						 "x+2" , // +
						  "x-2-x+5+x+x+x-3-x+6+x+4+x" , // +
						  "x*x", // +
						  "x*x*x", // +
						  "3*x*x*(x-1)*(x-1)+7*(x-1)*x+5-9*x", // + (b) , - (a)
						   "x^3", // -
							"5*x^7", // + , 10
							"2*(x+1)", // +
							 "0.5*x*(x+1)", // -
							 "x+4+x+7+x+5+x", // +
							 "5+x+3", // +
							 "x+1+x+0.5", // +
							 "x+1+x", // +
							 "1+x+x", // +
							 "x+x+x", // +
		                      "x-7",  // +
		                      "7-x",  // - , 20
							 "sin(x^2)" ,
		                     "x-4-x+7-x", // +
		                     "x*7", // +
							 "x^5 + x^4 + x^3 + x^2 + 1", // +
		                     "x^11", // +
		                     "(x*(x*x-1)+5*x*(1+1/x))/(2*x+0.25*x*x+x*(x-1))", // +
		                    "(x+1)/x", // +
		                   "(2+5*x*(x^2+1)-4*x^2)/(1+2*x*(x-1)^2+8*x^2*(x+1)+7*x)^2", // +
		                   "x^2", 
		                   "sin(x)*tg(x)", // + , 30 , func_2a
		                   "sin(x)*(x+1)", // +
		                   "(x+2)*sin(x)", // +
		                   "(x-1)*cos(x)", // +
		                   "cos(x)", // +
		                   "(x+1)*(x-9)", // +
		                   "5*(x+5)", // +
		                   "(x-3)*7", // +
		                   "6*11", // +
		                   "sin(x)-cos(x)", // + , func_1a
		                   "sin(x)-x", // + , 40
		                   "x-tg(x)", // +
		                   "sin(x)/cos(x)", // + , func_3a
		                   "sin(x)/(x+4)", // +
		                   "(x+5)/sin(x)", // +
		                   "(x+5)/(x-1)", // +
		                   "sin(x)/3", // +
		                   "(x+7)/2", // +
		                   "5/sin(x)", // +
		                   "(x+4)/sin(x)", // +
		                   "x*(x+2)*(x-3)*(x+4)*(x-5)/(1+x^2*(x+1)^2) - 5*x^2*(x+3)^2*(x^2+1)*(1-1/x)^2", // + ( b) , - ,(a) , 50
		                   "x*(x-1)*(x+2)*(x-3)" , // +
		                   "cos(x^5 + x^4 + x^3 + x^2 + 1)", // +
						   "tg(x^5 + x^4 + x^3 + x^2 + 1)", // +
						   "ctg(x^5 + x^4 + x^3 + x^2 + 1)", // +
						   "ln(x^5 + x^4 + x^3 + x^2 + 1)", // -
		                   "ln(x^2)", // -
						   "exp((x-1)/(x^5 + x^4 + x^3 + x^2 + 1))", // +
						   "sh((x-1)/(x^5 + x^4 + x^3 + x^2 + 1))" , // +
						   "ch((x-1)/(x^5 + x^4 + x^3 + x^2 + 1))" , // - , не тот знак.
						   "th((x-1)/(x^5 + x^4 + x^3 + x^2 + 1))", // + , 60
		                   "arcsin((1+x*(x+1))/(1+(x^5 + x^4 + x^3 + x^2 + 1)^2))", // +
						   "arccos((1+x*(x+1))/(1+(x^5 + x^4 + x^3 + x^2 + 1)^2))", // +
						   "arctg((1+x*(x+1))/(1+(x^5 + x^4 + x^3 + x^2 + 1)^2))", // +
						   "arcctg((1+x*(x+1))/(1+(x^5 + x^4 + x^3 + x^2 + 1)^2))", // +
						   "arcsh(1+(x^5 + x^4 + x^3 + x^2 + 1)^2)" , // +
						   "arcch(1+(x^5 + x^4 + x^3 + x^2 + 1)^2)" , // +
						   "arcth(1+(x^5 + x^4 + x^3 + x^2 + 1)^2)" , // +
						   "arccth(1+(x^5 + x^4 + x^3 + x^2 + 1)^2)" ,// +
		                   "log(sin(x) , cos(x))" , // + , func_5a
		                   "log( cos(x) , sin(x) )" ,// - , 70
		                   "log( x+1 , cos(x))" , // + 
		                   "log( sin(x) , x+5)" ,// +
		                   "log( x+1 , x + 9 )" ,// +
		                   "log( x+1 , x+7 )" , // +
		                   "ln(x)" , // +
		               	                  
	};
	const double x = 2;
	// x = M_PI/4;
	double Q[2];
	string s = eh[50];
	deque<Token> fh, fs, es;
	// getline(cin, s);
	fh = exprToTokens(s);
	fs = shuntingYard(fh);
	Algebra_Node* node = PolishToTree(fs);
	Algebra_Tree* K = new Algebra_Tree(node);
	Algebra_Tree& first_tree = *K;
	if (DEBUG)
	{
		cout << "test_7() : " << endl;
		first_tree.Print_Tree_T();
	}
	Q[0] = Numerical_Differentiation(first_tree, x, pow(10, -4), "x");
	Algebra_Node* D = DerivateFunc(node);
	Algebra_Tree* d_tree = new Algebra_Tree(D);
	Algebra_Tree& T = *d_tree;
	T.Print_Tree_T();
	Q[1] = T.FunctionValue_T(x, "x");
	string f = T.TreeToInfix_T();
	ph.push_back(make_tuple(Q[0], Q[1]));
	for (const auto& element : ph) {
		cout << "(" << get<0>(element) << ", " << get<1>(element) << ")" << endl;
	}
	cout << f << endl;
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
	TreeToPolish(node, es);
	vector<Token>::iterator iter;
	for (iter = es.begin(); iter != es.end(); iter++) cout << *iter << " ";
	cout << endl;
	s = PostfixToInfix(es);
	cout << s << endl;
}

void test_10() // Тестирование функции PolishCalculation()
{
	vector< tuple<double, double>> ph;
	string fh[] = { "0.5*0.25" , // + , + , 0
					"0.5*0.7*(1.5+1)"  , // + , +
					"1+0.7*(3-4+5*0.5*0.25*(1-4*3))", // + , +
					 "1+2/3*(1+7/8-6/9+2*(1-6/11+9/15))^2", // + , +
					  "sin(1-4/7+3/13*(1+4/9)^2)*cos(1-(4/11)^2)", // + , +
					   "3/4*sin(1+11/157)", // + , +
					   "(3/4)*sin(1+11/157)", // + , +
					   "sin(2*5)", // + , +
					   "tg(3-0.6^2*(1+3/4)^3)", // + , +
					   "tg(17/23)", // + , +
					   "ctg(2-0.6^2)", // + , + , 10
					   "arcsin((5/7)^2)", // + , +
					   "arcsin(3/4)", // + , +
					   "arccos(11/19)", // + , +
					   "arctg(2/(2^2+1/17)^2)", // + , +
					   "2/(2^2+1/17)^2", // + , +
					   "arcctg(13/17)", // + , +
					   "sh(1+0.5^2*(1-7/9)^3)", // + , +
					   "ch(1+0.35^2)", // + , +
					   "th(1+0.5*0.4^2)", // + , +
					   "cth(19^2*7/51^2)", // + , + , 20
					   "arsh(1-0.5*(2+4/7))", // + , +
					   "arch(1+0.9^2)", // + , +
					   "pow(2 , 3)",  // + , +
					   "log(16 , 2)", // + , +
					   "1-2", // + , +
					   "5/7", // + , +
					   "sin(3)*cos(1)", // + , +
					   "2*(2-1)",
					   "abs(-3)", // - , не проходит tokenize_u_minus.
		               "ln(2)", // 30
		               "log(2 , 16)"

	};
	for (int i = 0; i < 30; i++)
	{
		string s = fh[i];
		deque<Token> fs, es;
		fs = exprToTokens(s);
		Tokenize_u_minus(fs);
		es = shuntingYard(fs);
		Algebra_Tree A = SetAlgebricTree(s);
		A.TreeToPolish_T();
		vector<Token> eh = A.polish;
		double r_0 = 0, r_1 = 0;
		r_0 = PolishCalculation(es); // Версия deque
		r_1 = PolishCalculation(eh); // Версия vector
		cout << i << " :" << endl;
		cout << "PolishCalculation : DEQUE : " << r_0 << endl;
		cout << "PolishCalculation : VECTOR : " << r_1 << endl;
		ph.push_back(make_tuple(r_0, r_1));
		while (0);
	}
	while (0);
}

void test_11() // Тестирование функции Tokenize_u_minus()
{
	string fh[4] = { "(-1)+x+(-1)*x^2*((-1)+3*x))" ,// -
					   "-1+x" , // +
					   "(-1)" , // +
		               "(-1)*x" // -
	};
	string s = fh[3];
	deque<Token> fs, es;
	fs = exprToTokens(s);
	Tokenize_u_minus(fs);
	string f = TokensToStr(fs);
	cout << f << endl;
	while (0);
}

void test_12() // Тестирование функции SetToken()
{
	string fh[2] = { "-1" , "0" };
	string s = fh[1];
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
{  // Тестирование функции TreeRExprReplaceOnSubTreeD() , неверно работает с функцией с одним параметром.
	const int X = 5;
	vector<tuple<double, double>> ph;
	string fh[12] = { "3*(x+c)+c*x^2*(x-c)+8*x*c", // +
					 "4*x^2*(x^2-c^2)+3*x*(x-c/x)" , // +
						"(x-c)^2" , // +
						  "x-c" , // +
					  "c*(x-c)+3*c*x" , // +
					   "c*(x+c)" , // +
						 "c" , // +
						 "2" ,  // +
						 "x", // +
						 "x+c" , // +
						 "c+x", // +
		                 "sin(c)"
	};
	string s, r, f;
	tie(s, f, r) = make_tuple(fh[11], "c", "x+3"); // A , B , C , 104
	Algebra_Tree& A = SetAlgebricTree(s);
	Algebra_Node* node = SetOperatorTree(r);
	cout << "A:" << endl;
	A.Print_Tree_T();
	Algebra_Tree B = A.TreeExprReplaceD_T("x", X); // Здесь ошибка.
	for (int i = 0; i < 42; i++) cout << "=";
	cout << endl;
	cout << "B:" << endl;
	B.Print_Tree_T();
	A.TreeRExprReplaceOnSubTreeD_T(f, node);
	for (int i = 0; i < 42; i++) cout << '=';
	cout << endl;
	cout << "A:" << endl;
	A.Print_Tree_T();
	deque<Token> ks = FToPolish(r);
	deque<Token> es = FToPolish(r);
	double y = FunctionValue(es, double(X), "x");
	map<string, double> ds;
	ds["x"] = double(X);
	ds["c"] = y;
	Algebra_Tree C = B.TreeExprReplaceD_T("c", y);
	cout << "C:" << endl;
	C.Print_Tree_T();
	vector<Token> eh;
	C.TreeToPolish_T();
	eh = C.polish;
	double y_3 = PolishCalculation(eh);
	double y_1 = FunctionValueM(s, ds);
	double y_2 = A.FunctionValue_T(double(X), "x");
	while (0);
	vector<tuple<double, double>>::iterator iter;
	ph.push_back(make_tuple(y_2, y_3));
	while (0);
	for (iter = ph.begin(); iter != ph.end(); iter++)
	{
		tuple<double, double> Q = *iter;
	}


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


void test_19() // Тестирование функции TreeExprReplaceRT()
{
	string fh[6] = { "x*(x-3)+x" // +
				, "(x^2-1)*(x-4/5)*(7/8+3*x)^2 + 3*x*(x-1)" };

	string s = fh[1];
	Algebra_Tree A = SetAlgebricTree(s);
	A.Print_Tree_T();
	for (int i = 0; i < 42; i++) cout << "=";
	cout << endl;
	Algebra_Tree B = A.TreeExprReplaceD_T("x", 5);
	B.Print_Tree_T();
	while (0);
}



void test_20() // Тестирование шаблонной версии функции: SetOperatorTree()
{
	const string fh[3] = { "3*x^2*(x+1)-x+x^2" , "(-1)*x+(-1)" , "3*x^2*(x-1)+5/3*x*(1-4/5)" };
	const string s = fh[2];
	Algebra_Node* root = SetOperatorTree(s);
	Print_Tree_R(root, "", true, true);
	while (0);
}

void test_21()
{
	vector<int> eh = { 5, 1, 3, 7, 5 };
	// ReverseVector(eh);
	vector<int>::iterator iter;
	for (iter = eh.begin(); iter != eh.end(); iter++) {
		cout << *iter << " ";
	}
}

void test_22() // Тестирование функции FunctionValueM()
{
	vector<tuple<double, double>> ph;
	string fh[6] = { "3*(x+c)+c*x^2*(x-c)+8*x*c", // +
					 "4*x^2*(x^2-c^2)+3*x*(x-c/x)" , // +
					   "(x-c)^2" ,  // +
					   "x-c" ,  // +
					 "c*(x-c)+3*c*x" ,  // +
					   "c*(x+c)" // +
	};
	for (string s : fh)
	{
		map <string, double> ds;
		ds["x"] = 2.0;
		ds["c"] = 5.0;
		double y_0 = FunctionValueM(s, ds);
		Algebra_Tree A = SetAlgebricTree(s);
		Algebra_Tree B = A.TreeExprReplaceD_T("x", ds["x"]);
		Algebra_Tree C = B.TreeExprReplaceW_T("c", ds["c"]);
		C.TreeToPolish_T();
		vector<Token> eh = C.polish;
		double y_1 = PolishCalculation(eh);
		cout << y_0 << endl;
		cout << y_1 << endl;
		ph.push_back(make_tuple(y_0, y_1));
		while (0);
	}
	while (0);
}

void test_23()
{
	vector<tuple<double, double, double>> ph;
	string fh[] = { "3*(1-1/4)*(3+17/33)-2*(3+3/4)^2" , "0.5*(2-1)" , "2-3" };
	string s = fh[2];
	deque<Token> eh = FToPolish(s);
	double y_0 = PolishCalculation(eh);
	Algebra_Node* root = PolishToTree(eh);
	deque<Token> kh;
	vector<Token> ks;
	TreeToPolish(root, kh);
	TreeToPolish(root, ks);
	double y_1 = PolishCalculation(kh);
	double y_2 = PolishCalculation(ks);
	ph.push_back(make_tuple(y_0, y_1, y_2));
	cout << "BEFORE : " << y_0 << endl;
	cout << "DEQUE : " << y_1 << endl;
	cout << "VECTOR : " << y_2 << endl;
	while (0);
}

void test_24()
{
	string fh[] = { "1+x*0" , // 0
		             "7+0*(x+1)+1*0" , 
		              "0*(x-7)" , // -
		              "(x+4)*0" ,
		               "11/17 + x*0*(x+1)", 
		              "11/15 + (x+4)*0", // +
		              "11/23 + x^2*0 - 6*x*0*(x-2)*(x+1)", // -
		              "11/23 + 7*x*0*(x+1)*(x-2)", 
		              "3/7+ 0*(x+4)", // +
		            "(1+x*(x+1))^1" , 
		             "0.25 + (1+x*(x+1))^1", // - , 10
		              "(x+(x+1)^1+7)^1" , //
		            "(sin(x)^0+x)^0" , // 
		            "7/11+ (x^2+1/4)^0", // 
		            "(x^2+x+1)/1", //
		            "cos(x)/1" , // 
		            "sin(x^2+1)*1", // 
		            "1*(1+(1+x^2))^2", // 
		            "(x*(x-1)*(x+3)+1)^2+0",
		            "4+0+x+0",
		            "x+1-0-5-1/x-0" , // 20
		            "0/(x^2+1)" , // 
		            "3 + 0/(x^2+1)", // + 
		            "1^(x+1)" , // 
		            "0.5 + 1^(x+1)", // + 
		            "3+1^(x+1)", // + , 
		            "0^(x^2*cos(x)-4)" //
	             };
	string s = fh[4];
	Algebra_Node* first_node = SetOperatorTree(s);
	Algebra_Node* second_node = simplify_F(first_node);
	Algebra_Tree A = Algebra_Tree(second_node);
	A.Print_Tree_T();
}

void test_25() // Вывод цветного текста
{
	std::cout << "\e[1;31m This is red text \e[0m" << std::endl;
}


int main() {

	const int n = 25;  // 7 , 1 PostfixToInfix()
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
	case 10: { test_10(); break; } // +
	case 11: { test_11(); break; } // 
	case 12: { test_12(); break; } // +
	case 13: { test_13(); break; } // +
	case 14: { test_14(); break; } // +
	case 15: { test_15(); break; } // +
	case 16: { test_16(); break; } // +
	case 17: { test_17(); break; } // +
	case 18: { test_18(); break; } // +
	case 19: { test_19(); break; } // +
	case 20: { test_20(); break; } // +
	case 21: { test_21(); break; } // +
	case 22: { test_22(); break; } // +
	case 23: { test_23(); break; }
	case 24: { test_24(); break;  }
	case 25: { test_25(); break;  }
	}
}