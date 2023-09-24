#include <iostream>
#include <deque>
#include "algebra_node.h"
#include "Shanting_yard.h"
#include "Algebra.h"
#include "Derivate.h"
#include "simplify.h"
#include <algorithm>


#define M_PI 3.1415926535897932384626

#define DEBUG 0

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
						  "sin(3)*cos(1)", // - , 
						  "sin(x^2-3*x+2)*sin(7/4)",
						  "log(x , 2)",
						  "1-2",
						  "4+7*3", // +
						  "(4+5)*6", // +
						  "7+(8+4)^2*(7-4/5)+3+7-2*3", // - , 10
						  "(4-7)*(1+9)",
		                  "arsh(x^2)",
		                  "arch(x/2)" ,
		                  "arth(2*x)" ,
		                  "arccth(x+1)"
	};
	const double x = 2;
	string s = fh[10];
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
	double r = FunctionValue(es, x, "x");

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
	second_tree.TreeExprReplaceD_T("x", 5); // Здесь исключение.
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
	string t = first_tree->TreeToInfix_T();
	es = FToPolish(t);
	double r_1 = FunctionValue(es, x, "x");
	vector<tuple<double, double>> ph;
	ph.push_back(make_tuple(r, r_1));
	for (const auto& element : ph) {
		cout << "(" << get<0>(element) << ", " << get<1>(element) << ")" << endl;
	}
	cout << t << endl;
	while (0);
	delete first_tree;
	second_tree.~Algebra_Tree(); 
	third_tree.~Algebra_Tree();
}

void test_2() // Тестирование перегруженного оператора для класса AlgebraTree.
{
	string s, f;
	deque<Token> fs, es, fh, eh;
	//  getline(cin, s);
	// getline(cin, f);
	s = "x+x";
	f = "x-3";
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
	Algebra_Tree third_tree = first_tree + second_tree;
	// third_tree.Print_Tree_T();
	while (0);
	third_tree.~Algebra_Tree();
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
	T.~Algebra_Tree();
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
	delete first_node;
	delete second_node;
}

void test_5() // Тестирование функции PostfixToInfix()
{ // Лишние скобки.
	string s, f;
	deque<Token> fh, fs;
	vector<Token> es;
	Token T;
	string eh[] = { "x" , // + , 0
					 "3" , // +
					 "5.0" , // +
					 "-5.0" , // +
					 "-2" , // +
					 "4+(1/7-6/9+5*(4-7/8))" , // +
					 "x/2+ x*x*(x+2*x^2)-3*x - 2*x^2", // +
		             "1+2*x^(2-1)"
	};
	// getline(cin, s);
	s = eh[7];
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

void test_6() // Тестирование функции TreeToPolish_T() , ~Algebra_Tree()
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
	vector<Token> kh(es.rbegin(), es.rend());
	f = PostfixToInfix(kh);
	cout << f << endl;
	while (0);
	T.~Algebra_Tree();
	while (0);
}

void test_7() // Тестирование функции DerivateFunc()
{
	vector<tuple<double, double>> ph;
	string eh[] = { "2*(x-1)" , // + ,0
					  "x-2-x" , // +
						"sin(x)" , // +
						 "cos(x^2)" , // +
						 "x+2" , // +
						  "x-2-x+5+x+x+x-3-x+6+x+4+x" , // +
						  "x*x", // +
						  "x*x*x", // +
						  "3*x*x*(x-1)*(x-1)+7*(x-1)*x+5-9*x", // + 
						   "x^3", // +
							"5*x^7", // + , 10
							"2*(x+1)", // +
							 "0.5*x*(x+1)", // +
							 "x+4+x+7+x+5+x", // +
							 "5+x+3", // +
							 "x+1+x+0.5", // +
							 "x+1+x", // +
							 "1+x+x", // +
							 "x+x+x", // +
							  "x-7",  // +
							  "7-x",  // + , 20
							 "sin(x^2)" ,
							 "x-4-x+7-x", // +
							 "x*7", // +
							 "x^5 + x^4 + x^3 + x^2 + 1", // + 
							 "x^11", // +
							 "(x*(x*x-1)+5*x*(1+1/x))/(2*x+0.25*x*x+x*(x-1))", // +
							"(x+1)/x", // +
						   "(2+5*x*(x^2+1)-4*x^2)/(1+2*x*(x-1)^2+8*x^2*(x+1)+7*x)^2", // +
						   "x^2", // +
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
						   "x*(x+2)*(x-3)*(x+4)*(x-5)/(1+x^2*(x+1)^2) - 5*x^2*(x+3)^2*(x^2+1)*(1-1/x)^2", // +  , 50
						   "x*(x-1)*(x+2)*(x-3)" , // +
						   "cos(x^5 + x^4 + x^3 + x^2 + 1)", // +
						   "tg(x^5 + x^4 + x^3 + x^2 + 1)", // +
						   "ctg(x^5 + x^4 + x^3 + x^2 + 1)", // +
						   "ln(x^5 + x^4 + x^3 + x^2 + 1)", // +
						   "ln(x^2)", // +
						   "exp((x-1)/(x^5 + x^4 + x^3 + x^2 + 1))", // +
						   "sh((x-1)/(x^5 + x^4 + x^3 + x^2 + 1))" , // +
						   "ch((x-1)/(x^5 + x^4 + x^3 + x^2 + 1))" , // + 
						   "th((x-1)/(x^5 + x^4 + x^3 + x^2 + 1))", // + , 60
						   "arcsin((1+x*(x+1))/(1+(x^5 + x^4 + x^3 + x^2 + 1)^2))", // +
						   "arccos((1+x*(x+1))/(1+(x^5 + x^4 + x^3 + x^2 + 1)^2))", // +
						   "arctg((1+x*(x+1))/(1+(x^5 + x^4 + x^3 + x^2 + 1)^2))", // +
						   "arcctg((1+x*(x+1))/(1+(x^5 + x^4 + x^3 + x^2 + 1)^2))", // +
						   "arcsh(1+(x^5 + x^4 + x^3 + x^2 + 1)^2)" , // - , exception
						   "arcch(1+(x^5 + x^4 + x^3 + x^2 + 1)^2)" , // - , exception
						   "arcth(1/(x^5 + x^4 + x^3 + x^2 + 1)^2)" , // +
						   "arccth(1+(x^5 + x^4 + x^3 + x^2 + 1)^2)" ,// - , exception
						   "log(sin(x) , cos(x))" , // + 
						   "log( cos(x) , sin(x) )" ,// + , 70 
						   "log( x+1 , cos(x))" , // + 
						   "log( sin(x) , x+5)" ,// + 
						   "log( x+1 , x + 9 )" ,// +
						   "log( x+1 , x+7 )" , // + 
						   "log(2 , x+4 )",  // + 
						   "log( 2 , sin(x))",   // +
						   "log( x+3 , 2)",     // +
						   "log( cos(x) , 2)",  // +
						   "log(4 , 32)",   // + 
						   "ln(x)" , // + , 80
						   "sin(x^2)*(x^2 + 1/(3-cos(x^2)) + x )*x+sin(x)*(x^2-3*x+1-x)^2+7", // +
						   "3*x*(x-1)*cos(4*x)+(x-7)^2*(x+4)*tg(x)", // + 
						   "3*x*(x-1)*cos(4*x)", // +
						   "(x-7)^2*(x+4)*tg(x)", // +
						   "x*tg(x)", // +  
						   "(x+4)*tg(x)", // +
						   "(x-7)^2*tg(x)", // + 
						   "sin(x)^cos(x)", // + , func_5a
						   "sin(x)^(x+1)" , // + 
						   "(x+5)^cos(x)" , // + , 90
						   "(x+1)^(x+7)" , // +
						   "sin(x)^4" , // +
						   "(x+3)^4" , // +
						   "3^(x+1)" , // +
						   "2^(cos(x))" , // +
						   "5^7"  , // +
						   "x^4+x^2+1", // +
						   "x^4",  // +
						   "x^2" , // +
						   "3*x*x*(x-1)*(x-1)" , // + , 100
						   "3*x*x*(x-1)", // +
						   "3*x*x", // +
						   "x*x*x", // + 
						   "x*(x+2)*(x-3)*(x+4)*(x-5)/(1+x^2*(x+1)^2)", // +
						   "5*x^2*(x+3)^2*(x^2+1)*(1-1/x)^2" , //  +
						   "(1-1/x)^2", // +
						   "(1/x)^2", // +
						   "1/x", // +
						   "x*(x^2+1)*x*(x-1)*(x+2)^5*(x-3)^2*(x+4)^(3/2)*(x-5)^3", // +
						   "x^(sin(x))*(1+x*cos(x^2))*x*(x^2+1)^2*x^(cos(x))", // + , 110
						   "x^(sin(x))*(1+x*cos(x^2))", // +
						   "x^(sin(x))", // +
						   "sin(x)", // +
						   "x^x", // +
						   "(x^2+1)^(x+3/2)" , //  + 
						   "(x-1)^2*(x^2*(x+3*(x+1))+3*x*(x-1)/(x+4*x^2+1+1/x))/((x-1)^2*(x+3)^2*(x-5)*(x+7)^2)", // +
						   "sin(x)*cos(x)", // +
						   "sin(x^2)", // +
						   "(x^2+3*x+7+1/x)^(1/(1+x^2))", // +
						   "x*sin(x)", // + 
						   "cos(x)*x", // + , 120
						   "sin(x+3*x^2/(x^3+1))*cos(3*x)*( x^4/(x^7+sin(x)*x^10) + 2*x^2+ln(x)*x*sin(7*x) )", // +
						   "log(2 , x)", // +
						   "log(x , 2)", // +
						   "x+4" , // +
						   "x-4" , // +
						   "4+x" , // +
						   "4-x" , // +
						   "sin(x) + 4", // +
							"sin(x) - 4" , // +
						   "4 + cos(x)", // + , 130
						   "4 - cos(x)" , // +
						   "x + cos(x)" , // +
							"x - cos(x)", // +
							"sin(x) + x" , // +
							"sin(x) - x" , // +
							"x^2*sin(x^2)*(cos(x))^2*( 1 + 1/(x+1)*sin(3*x) - 3/(x+3)*cos(5*x) + 5/(x+5)*sin(7*x) - 7/(x+7)*cos(7*x)  )^2*x + x^2*sin(x+2)*x + tg(x^2)", // +
							"cos( 1 / ( 4+cos(x) )^2  )", // +
							"sin(x-1)*cos(x^2-1)*sin(x^3-1)",
							"sin(x)*cos(2*x)/(1+x*(x^2+1)^2)", // 140
							   "x^2/(x*sin(x)+1)^2",// + , 
							   "arcsh(x)" , // +
							   "arcch(3*x)" , // +
							   "arcth(x)" , // +
							   "arccth(3*x)", 
							   "x*x*x", // +
							   "0", // +
							   "2", // +
							   "-7", // -
							   "3*x", //  + , 150
							   "(3/4*(1-7/91+11/437)^2+1)/(1+(1-1/3*(3/4+6/7)^2+(3/4+7)^2))", // +
							   "(x)", // +
							   "(3)", // +
							   "(-2)", // +
							   "((x+3)*5+4/7)", // +
							   "arcsh(1+x^2)", // +
							   "arcch(1+x^2)", // +
							   "arcth(x^2)", // + // arcth - nan.
							   "arccth(1+x^2)",// +
							   "(x+2*(7/19+6*x*(x+1) ))/(2/7+x^2*(x-1)+(x-4)^2*(x+3) )" //  , 160

	};
	// Два раза один и тот же символ в строке - причина повторения индекса.
	const double x = M_PI / 4;
	const int MODE = 0;
	// x = M_PI/4;
	double Q[2];
	int n = 60;
	for (int i = 0; i < 160; i++) // 149
	{
		string s = eh[i];
		deque<Token> fh, fs, es;
		// getline(cin, s);
		int index = 0;
		fs = FToPolishI(s, index, Enumerable::ORDERING);
		Algebra_Node* node = PolishToTree(fs);
		Algebra_Tree* K = new Algebra_Tree(node);
		Algebra_Tree& A = *K;
		Algebra_Tree& B = A.SetIndexTree_T();
		if (DEBUG)
		{
			cout << "test_7() : A " << endl;
			A.Print_Tree_T();
			cout << "test_7() : B " << endl;
			if (MODE == 1) B.Print_Tree_T();
			if (MODE == 1)
			{
				A.TreeToPolish_T();
				vector<Token> ks = A.polish;
				vector<int> ls = CountIndex(ks);
				sort(ls.begin(), ls.end());
				cout << "IndexCouter : " << endl; // Идет проверка уникальности индексов.
				for (auto p : ls) cout << p << " ";
				cout << endl;
			}
		}
		Q[0] = Numerical_Differentiation(A, x, pow(10, -4), "x");
		Debug_concept W = Debug_concept(index);
		Algebra_Node* D = DerivateFunction(node, W);
		Algebra_Tree* d_tree = new Algebra_Tree(D);
		Algebra_Tree& T = *d_tree;
		cout << "test_7() : T" << endl;
		T.Print_Tree_T();
		Algebra_Tree& DI = T.SetIndexTree_T();
		cout << "test_7() : DI" << endl;
		if (MODE == 1) DI.Print_Tree_T();

		if (MODE == 1)
		{
			T.TreeToPolish_T();
			vector<Token> ks = T.polish;
			vector<int> ls = CountIndex(ks);
			sort(ls.begin(), ls.end());
			cout << "IndexCouter : " << endl; // Идет проверка уникальности индексов.
			for (auto p : ls) cout << p << " ";
			cout << endl;
		}

		Q[1] = T.FunctionValue_T(x, "x");
		string f = T.TreeToInfix_T();
		ph.push_back(make_tuple(Q[0], Q[1]));
		cout << endl;
		cout << f << endl;
	}
	int i = 0;
	double t = 0;
	double p, q;
	for (int i = 0; i < 2; i++) std::cout << std::endl;
	for (const auto& element : ph) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		p = get<0>(element);
		q = get<1>(element);
		t = (p - q) / (p + q);
		bool B = false;
		if (abs(t) > pow(10, -4))
		{
			SetConsoleTextAttribute(hConsole, 12);
			B = true;
		}
		std::cout << ++i << ":" << "(" << get<0>(element) << ", " << get<1>(element) << ")" << std::endl;
		if (B) SetConsoleTextAttribute(hConsole, 7);
	}
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
	T.~Token();
	while (0);

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
					  "sin(1-4/7+3/13*(1+4/9)^2)*cos(1-(4/11)^2)", // - , -
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
					   "sin(3)*cos(1)", // - , - , простейший неработающий пример
					   "2*(2-1)",
					   "abs(-3)", // - , не проходит tokenize_u_minus.
					   "ln(2)", // 30
					   "log(2 , 16)",
		               "tg(Pi/4)*cos(Pi/6)*sin(Pi/6)"


	};
	for (int i = 0; i < 1; i++)
	{
		string s = fh[32];
		deque<Token> fs, es;
		es = FToPolish(s);
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
	T.~Algebra_Tree();
}


void test_14()
{  // Тестирование функции TreeRExprReplaceOnSubTreeD() , неверно работает с функцией с одним параметром.
	const int X = 5;
	vector<tuple<double, double>> ph;
	string fh[] = { "3*(x+c)+c*x^2*(x-c)+8*x*c", // + , 0
					 "4*x^2*(x^2-c^2)+3*x*(x-c/x)" , // +
						"(x-c)^2" , // +
						  "x-c" , // +
					  "c*(x-c)+3*c*x" , // +
					   "c*(x+c)" , // +
						 "c" , // + , exception
						 "2" ,  // +
						 "x", // +
						 "x+c" , // +
						 "c+x", // + , 10
						 "sin(c)", // 
						 "sin(x)*cos(x)*(x+c)"
	};
	string s, r, f;
	tie(s, f, r) = make_tuple(fh[12], "c", "x+3"); // A , B , C , 104
	Algebra_Tree& A = SetAlgebricTree(s);
	Algebra_Node* node = SetOperatorTree(r);
	cout << "A:" << endl;
	A.Print_Tree_T();
	Algebra_Tree B = A.TreeExprReplaceD_T("x", X); 
	for (int i = 0; i < 42; i++) cout << "=";
	cout << endl;
	cout << "B:" << endl;
	// B.Print_Tree_T();
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
		cout << "(" << get<0>(Q) << " : " << get<1>(Q) << ")" << endl;
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
	RecursiveDestructor(node);

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
	delete node;
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
	A.~Algebra_Tree();
	B.~Algebra_Tree();
	while (0);
}



void test_20() // Тестирование шаблонной версии функции: SetOperatorTree()
{
	const string fh[] = { "3*x^2*(x+1)-x+x^2" , "(-1)*x+(-1)" , "3*x^2*(x-1)+5/3*x*(1-4/5)" , "(-1)*p/q^2" };
	const string s = fh[3];
	Algebra_Node* root = SetOperatorTree(s);
	Print_Tree_R(root, "", true, true);
	RecursiveDestructor(root);
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
		A.~Algebra_Tree();
		B.~Algebra_Tree();
		C.~Algebra_Tree();
		while (0);
	}
	while (0);
}

void test_23() // Тестирование обоих перегрузок PolishCalculation()
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
	RecursiveDestructor(root);
}

void test_24() // Тестирование функции simplify_F()
{
	string fh[] = { "1+x*0" , // 0 , +
					 "7+0*(x+1)+1*0" ,  // +  -
					  "0*(x-7)" , // +
					  "(x+4)*0" , // +
					   "11/17 + x*0*(x+1)", // + , +
					  "11/15 + (x+4)*0", // + , +
					  "11/23 + x^2*0 - 6*x*0*(x-2)*(x+1)", // + , -
					  "11/23 + 7*x*0*(x+1)*(x-2)", // + , -
					  "3/7+ 0*(x+4)", // +
					"(1+x*(x+1))^1" , // +
					 "3/4 + (1+x*(x+1))^1", // + ,10
					 "0.25 + (1+x*(x+1))^1", // + 
					  "(x+(x+1)^1+7)^1" , // +
					"(sin(x)^0+x)^0" , // +
					"7/11+ (x^2+1/4)^0", // +
					"(x^2+x+1)/1", // +
					"cos(x)/1" , // +
					"sin(x^2+1)*1", // + , 
					"1*(1+(1+x^2))^2", //  + 
					"(x*(x-1)*(x+3)+1)^2+0", // +
					"4+0+x+0", //  , 20
					"x+1-0-5-1/x-0" , // +
					"0/(x^2+1)" , // +
					"3 + 0/(x^2+1)", // + 
					"1^(x+1)" , // +
					"0.5 + 1^(x+1)", // + 
					"3+1^(x+1)", // + , 
					"0^(x^2*cos(x)+16)", // +
					"0^2", // +
					"1*(1+3*(x^2+1)/1*x/1*1 +0*x^2-0*sin(x)+(x+1)^1*x^0)", // -
					"(1/2+(x+1)^1*x^0)", // + , 30
					"(x^2+4*5*6*(x+1)^(1/2*2)+4*2*x-9*4/5*(x-1))*x+(x-3/4*7/11)", // -
					"x^2+4*5",
					"3/4+(x+1)*1", // +
					"4/5+1*(x+1)", // +
					"11/15 + (x+4)*0" ,
					"11/15 + (0 + (x+4))",
					"11/15 + ((x+4) + 0)"
	};
	for (int i = 0; i < 1; i++)
	{
		string s = fh[1];
		Algebra_Node* first_node = SetOperatorTree(s);
		simplify_F(first_node);
		Algebra_Tree A = Algebra_Tree(first_node);
		A.Print_Tree_T();
	}
	char c;
	cin >> c;
}

void test_25() // Тестирование функции simplify_D()
{
	string fh[] = { "1", // +
					"x+4*3", // +
					"x^2+4*5",
					"1^2+4*5", // - , к числу прививается
					"4*(3+1)", // +
					"4*(3+7/9)", // +
					"3*(1+5/7+6/11*7/41)^2+0.25", // -
	};
	string s = fh[6];
	Algebra_Node* first_node = SetOperatorTree(s);
	simplify_D(first_node);
	Algebra_Tree A = Algebra_Tree(first_node);
	A.Print_Tree_T();
}

void test_26() // Тестирование индексного копирования дерева.
{
	string lh[] = { "3*(1+5/7+6/11*7/41)^2+0.25" };
	string s = lh[0];
	int index = 0;
	Algebra_Node* A = SetOperatorTree(s, index);
	Debug_concept W = Debug_concept(index);
	Algebra_Node* B = _CloneTree(A, W);
	vector<Token> fh, eh;
	TreeToPolish(A, fh);
	TreeToPolish(B, eh);
	vector<int> fs, es;
	fs = CountIndex(fh);
	es = CountIndex(eh);
	while (0);
	vector<int>::iterator iter;
	for (iter = fs.begin(); iter != fs.end(); iter++) cout << *iter << " ";
	cout << endl;
	for (iter = es.begin(); iter != es.end(); iter++) cout << *iter << " ";
	cout << endl;
}

void test_27() // Тестирование функции PostfixToInfix() , TokensToStr() , ToString().
{
	string fh[] = { "(1-5*(1/2+5/6-7*(5+8/9*4^3)))" // + , 0
					, "(x^2-1)*(x-4/5)*(7/8+3*x)^2 + 3*x*(x-1)" ,  // +
						 "1+2/3*(1+7/8-6/9+2*(1-6/11+9/15))^2" , // + 
							  "cos(x^2)", // +
							  "sin(3)*cos(1)", // + ,
							  "sin(x^2-3*x+2)*sin(7/4)", // +
							  "log(x , 2)", // +
							  "1-2", // +
							  "4+7*3", // +
							  "(4+5)*6", // +
							  "7+(8+4)^2*(7-4/5)+3+7-2*3", // + , 10
							  "(4-7)*(1+9)", // +
		                      "2*x^(2-1)", // +
		                       "2*x^(2-1)", // +
		                       "2*x^(2-1)*cos(x^2)", // +
		                       "x*x + x*(x+x)", // +
		                       "(x)", // +
		                       "(3)" , // +
		                       "(0.5)", // +
		                       "(-2)", // +
	};
	for (int i = 19; i < 20; i++)
	{
		string s = fh[i];
		deque<Token> eh = FToPolish(s);
		deque<Token> es = exprToTokens(s);
		deque<Token>::iterator iter;
		string f = "";
		string t, r = "";
		for (iter = es.begin(); iter != es.end(); iter++)
		{
			Token token = *iter;
			s = token.ToString();
			t = ToString(token.value);
			f = f + s;
			r = r + t;
		}
		cout << f << endl;
		s = PostfixToInfix(eh); // deque
		cout << "deque: " << s << endl;
		f = TokensToStr(es);
		deque<Token>::iterator v_iter;
		vector<Token> kh;
		Tokenize_u_minus(es);
		es = shuntingYard(es);
		for (v_iter = es.begin(); v_iter != es.end(); v_iter++)
		{
			Token token = *v_iter;
			kh.push_back(token);
		}
		reverse(kh.begin(), kh.end());
		vector<Token> ks(kh.rbegin(), kh.rend());
		s = PostfixToInfix(kh); // vector
		cout << "vector:" << s << endl;
	}
	while (0);
}

void test_28() // Тестирование функции _CloneTree()
{ 
	string fh[] = {
		"sin(x)*x+0.25*x^2" , // + , + , -
		"sin(x)",
		"x*x*x"
	};
	string s = fh[2];
	Debug_concept W = Debug_concept();
	Algebra_Node* A = SetOperatorTree(s);
	// Algebra_Node* B = _CloneTree(A);
	Algebra_Node* C = _CloneTree(A, W); // Ошибка в копировании функций.
	Print_Tree_R(A, "", false, false);
	// Print_Tree_R(B, "", false, false);
	Print_Tree_R(C, "", false, false);
}

void test_29() // Тестирование метода Token::GetValue()
{
	string fh[] = { "sin(x)" };
	string s = fh[0];
	deque<Token> fs = exprToTokens(s);
	for (auto token : fs)
	{
		variant<string, char, int, double, Token::Function> value = token.GetValue();
		string f = ToString(value);
		cout << f << " ";
	}
	cout << endl;
}

void test_30()
{
	string fh[] = { "sin(x)*cos(2*x)/(1+x*(x^2+1)^2)" , "sin(x)/x" };
	string s = fh[1];
	Algebra_Node* node = SetOperatorTree(s);
	Algebra_Node* second_root = node;
	for (int i = 0; i < 8; i++)
	{
		second_root = DerivateFunction(node);
		node = second_root;
	}
	Print_Tree_R(second_root, "", false, false);
	vector<Token> eh;
	TreeToPolish(second_root, eh);
	int n = eh.size();
	cout << n << endl;
}

void test_31()
{ // Тестирование функции ~Algebra_Tree()
	string fh[] = { "x+x" , "x^2+3*x-2" };
	string s = fh[1];
	Algebra_Tree A = SetAlgebricTree(s);
	A.Print_Tree_T();
	while (0);
	A.~Algebra_Tree();
	while (0);
}

void test_32()
{ // Тестирование перегрузки операторов + , - , * , /
	string s = "x+x";
	string f = "x-3";
	Algebra_Tree A = SetAlgebricTree(s);
	Algebra_Tree B = SetAlgebricTree(f);
	Algebra_Tree C = A + B;
	Algebra_Tree D = A - B;
	Algebra_Tree E = A * B;
	Algebra_Tree F = A / B;
	Algebra_Tree G = A ^ B;
	for (int i = 0; i < 2; i++) cout << endl;
	cout << "A : " << endl;
	A.Print_Tree_T();
	for (int i = 0; i < 2; i++) cout << endl;
	cout << "B : " << endl;
	B.Print_Tree_T();
	for (int i = 0; i < 2; i++) cout << endl;
	cout << "C : " << endl;
	C.Print_Tree_T();
	for (int i = 0; i < 2; i++) cout << endl;
	cout << "D : " << endl;
	D.Print_Tree_T();
	for (int i = 0; i < 2; i++) cout << endl;
	cout << "E : " << endl;
	E.Print_Tree_T();
	for (int i = 0; i < 2; i++) cout << endl;
	cout << "F : " << endl;
	F.Print_Tree_T();
	for (int i = 0; i < 2; i++) cout << endl;
	cout << "G : " << endl;
	G.Print_Tree_T();
	while (0);
}


void Verify() {

	const int n = 10;  // 27 
	switch (n)
	{
	case 1: { test_1(); break; } // +
	case 2: { test_2(); break; } // +
	case 3: { test_3(); break; } // +
	case 4: { test_4(); break; } // +
	case 5: {test_5(); break; } // +
	case 6: { test_6(); break; } // +
	case 7: { test_7(); break; }
	case 8: { test_8(); break; } // -
	case 9: { test_9(); break; } // -
	case 10: { test_10(); break; } // +
	case 11: { test_11(); break; } // 
	case 12: { test_12(); break; } // +
	case 13: { test_13(); break; } // +
	case 14: { test_14(); break; } // -
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
	case 26: { test_26(); break;  }
	case 27: { test_27(); break;  }
	case 28: { test_28(); break;  } // +
	case 29: { test_29(); break;  }
	case 30: { test_30(); break;  }
	case 31: { test_31(); break;  }
	case 32: { test_32(); break;  }
	}
	char c;
	cin >> c;
}

string examples_1[12] = { "(1+3/4)^2*(1-5/7*4/11)*2+(1+5/6)" ,
                          "4*(3+7)^2" , 
	                      "2*6/(3+4/5)*(1-2/(3+4/5-9/71)+7/9-7/23)^2",
	                      "cos(1)*sin(2)",
	                      "arcsin(11/679)",
	                      "arccos(5/17)" ,
	                      "arctg(1 + exp(3^2))",
	                      "tg(11*Pi/16)" , 
	                      "sin(Pi/4)*cos(Pi/6)*sin(Pi/6)",
	                      "log(16 , 64)",
	                      "ln(2+1/901)",
	                      "ln(3/4+8/91)*6/7*(1+7/29)/(1+tg(3/4*Pi)*9/13*(3/4-8/11)^2)"
};

string examples_3[12] = { "x" , 
                      "x^2" ,
                      "1+x+x^2",
                     "x*tg(x)" , 
	                 "x^2/(x*sin(x)+1)^2" ,
	                 "(x+2*(7/19+6*x*(x+1) ))/(2/7+x^2*(x-1)+(x-4)^2*(x+3) )" , 
                     "sh(x)/(1+3*ch(x))", 
	                 "arcsin(1/(1+3*x^2))" ,
	                 "x*(x^2+x*sin(x))^2 + x*(x-1)/(x+2)" , 
	                 "x^5+x^4+x^3+x^2+1" , 
	                 "sin(x)*cos(2*x)*(3*sin(x/2)-5*cos(x/2))" , 
	                 "x/(x^2+3*tg(x))^2"
                   };

void task_1()
{
	std::cout << "Enter a numerical expression" << std::endl;
	std::cout << "If you want us to show an example of a function, introduce -man" << std::endl;
	string s;
	cin >> s;
	while (0);
	if (s == "-man")
	{
		int m = examples_1->size();
		int r = std::rand() % m;
		s = examples_1[r];
		cout << "Example of a function for calculating a derivate function : " << endl;
		cout << s << endl;
	}
	{
		deque<Token> fh = FToPolish(s);
		if (!IsNumeric(fh)) PrintColorText("Expression is not numeric", 13);
		else
		{
			double r = PolishCalculation(fh);
			cout << "The value of this expression is : " << r << endl;
		}
	}

}

void task_2()
{
	std::cout << "Enter an expression to show it as a tree." << std::endl;
	std::cout << "If you want us to show an example of a function, introduce -man" << std::endl;
	string s;
	cin >> s;
	if (s == "-man")
	{
		int m = examples_3->size();
		int r = std::rand() % m;
		s = examples_3[r];
		cout << "Example of a function for calculating a derivate function : " << endl;
		cout << s << endl;
	}
	{
		Algebra_Node* root = SetOperatorTree(s);
		Print_Tree_R(root , "" , true , true);
	}
}

void task_3()
{
	std::cout << "Enter the function for diphrency" << std::endl;
	std::cout << "If you want us to show an example of a function, introduce -man" << std::endl;
	string s;
	cin >> s;
	while (0);
	if (s == "-man")
	{
		int m = examples_3->size();
		int r = std::rand() % m;
		s = examples_3[r];
		cout << "Example of a function for calculating a derivate function : " << endl;
		cout << s << endl;
	}
	{
		deque<Token> fh = FToPolish(s);
		Algebra_Node* root = PolishToTree(fh);
		Algebra_Node* second_root = DerivateFunction(root);
		deque<Token> fs;
		TreeToPolish(second_root, fs);
		string f = PostfixToInfix(fs);
		cout << "The expression for the derivative of the function is" << endl;
		cout << f << endl;
		RecursiveDestructor(root);
		RecursiveDestructor(second_root);
		while (0);
	}
}


int main()
{
	string tasks[] = { "1 : CALCULATOR" , "2 : SHOW_OPERATOR_TREE"  , "3 : CALC_DERIVATE"};
	if(DEBUG) Verify();
	else
	{
		int n = tasks->size();
		cout << "Select a task number from 1 to 3 and enter number:" << endl;
		for (string s : tasks)
		{
			cout << s << endl;
		}
		int p;
		cin >> p;
		switch (p)
		{
		case 1: { task_1(); break; }
		case 2: { task_2(); break; }
		case 3: { task_3(); break; }
		}

	}
	return 0;
}




