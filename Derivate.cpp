
#include "Derivate.h"


#define DEBUG 1
#define X "x" // опеределение глобальной переменной типа char, переменная по которой дифференцируем.

/*
* Обозначения : Символы для замены строке : p - первый операнд ,  q - второй операнд , D - производная первого операнда , d - производная второго операнда.
*/

Algebra_Node* func_1(Algebra_Node* P[2], Algebra_Node* D[2] , string c)
{ // ['+' , '-' ]
	if (!(D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		Algebra_Node* Q;
		Q = SetNode("+");
		Algebra_Node& node = *Q;
		node.addLeftNode(D[1]);
		node.addRightNode(D[0]);
		return Q;
	}
	else if ((D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		return D[1];
	}
	else if (!(D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{
		if (c == "+")
		{
			return D[0];
		}
		else if (c == "-")
		{
			Algebra_Node* Q[2];
			Q[0] = SetNode("+"); // # Вычисление на этапе компиляции.
			Algebra_Node& node = *(Q[0]);
			// =================================
			Q[1] = SetNode("-1"); // #
			Algebra_Node& node_2 = *(Q[1]);
			node.addLeftNode(Q[1]);
			node.addRightNode(D[0]);
			return Q[0];
		}
	}
	else if ((D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{
		Algebra_Node* Q = SetNode("0");
		Algebra_Node& node = *Q;
		return Q;
	}
}

Algebra_Node* func_1a(Algebra_Node* P[2], Algebra_Node* D[2], string c)
{ // ['+' , '-' ]
	Algebra_Node* T = SetNode("0");

	if (!(D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		if (c == "+")
		{
			const string s = "D+d";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T ,"D", D[0]);
			TreeRExprReplaceOnSubTreeD(T ,"d", D[1]);
		}
		else if (c == "-")
		{
			const string s = "D-d";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T ,"D", D[0]);
			TreeRExprReplaceOnSubTreeD(T ,"d", D[1]);
		}

	}
	else if ((D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		const string s = "D";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T ,"D", D[0]);
	}
	else if (!(D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{
		if (c == "+")
		{
			const string s = "d";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T ,"d", D[1]);
		}
		else if (c == "-")
		{
			const string s = "(-1)*d";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T ,"d", D[1]);
		}
	}
	else if ((D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{
		const string s = "0";
		T = SetOperatorTree(s);
	}

	return T;
}

Algebra_Node* func_2(Algebra_Node* P[2], Algebra_Node* D[2] , string c)
{ // ['*']

	if (!(D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		if (!(D[0]->data.str == "1") && !(D[1]->data.str == "1"))
		{
			Algebra_Node* Q[3];
			Q[0] = SetNode("+"); // #  # Вычисление на этапе компиляции.
			Q[1] = SetNode("*"); // #
			Q[2] = SetNode("*"); // #
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			node.addLeftNode(Q[1]);
			node.addRightNode(Q[2]);
			node_1.addLeftNode(P[1]);
			node_1.addRightNode(D[0]);
			node_2.addLeftNode(P[0]);
			node_2.addRightNode(D[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];
		}
		if ((D[0]->data.str == "1") && !(D[1]->data.str == "1"))
		{
			Algebra_Node* Q[2];
			Q[0] = SetNode("+"); // #
			Q[1] = SetNode("*"); // #
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			node.addLeftNode(Q[1]);
			node.addRightNode(P[1]);
			node_1.addLeftNode(P[0]);
			node_1.addRightNode(D[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];
		}
		if (!(D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{
			Algebra_Node* Q[2];
			Q[0] = SetNode("+"); // #
			Q[1] = SetNode("*"); // #
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			node.addLeftNode(Q[1]);
			node.addRightNode(P[0]);
			node_1.addLeftNode(P[1]);
			node_1.addRightNode(D[0]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];
		}
		if ((D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{
			Algebra_Node* Q = SetNode("+"); // #
			Algebra_Node& node = *Q;
			node.addLeftNode(P[0]);
			node.addRightNode(P[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q, V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q;
		}

	}
	if ((D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		if (D[1]->data.str == "1")
		{
			Algebra_Node* Q = SetNode("*");
			Algebra_Node& node = *Q;
			node.addLeftNode(P[0]);
			node.addRightNode(D[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q, V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q;
		}
		else return P[0];
	}
	if (!(D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{
		if (D[0]->data.str == "1")
		{
			Algebra_Node* Q = SetNode("*");
			Algebra_Node& node = *Q;
			node.addLeftNode(P[1]);
			node.addRightNode(D[0]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q, V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q;
		}
		else return P[1];
	}
	if ((D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{
		Algebra_Node* Q = SetNode("0");
		return Q;
	}
	
}

Algebra_Node* func_2a(Algebra_Node* P[2], Algebra_Node* D[2], string c)
{ // ['*']
	Algebra_Node* T = SetNode("0");
  // Символы для замены строке : p - первый операнд ,  q - второй операнд , D - производная первого операнда , d - производная второго операнда.
	if (!(D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		if (!(D[0]->data.str == "1") && !(D[1]->data.str == "1"))
		{
			const string s = "D*q+d*p";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
			TreeRExprReplaceOnSubTreeD(T, "d", D[1]);
		}
		if ((D[0]->data.str == "1") && !(D[1]->data.str == "1"))
		{
			const string s = "q+d*p";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "d", D[1]);
		}
		if (!(D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{
			const string s = "D*q+p";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "D", D[0]);

		}
		if ((D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{
			const string s = "q+p";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
		}
	}
	if ((D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		if (!(D[1]->data.str == "1"))
		{ // Умножение на константу p.
			const string s = "d*p";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "d", D[1]);
		}
		else
		{
			const string s = "p";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		}	
	}
	if (!(D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{
		if (!(D[0]->data.str == "1"))
		{ // Умножение на константу q.
			const string s = "D*q";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
		}
		else
		{
			const string s = "q";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
		}
	}
	if ((D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{
		const string s = "0";
		T = SetOperatorTree(s);
	}

	return T;

}

Algebra_Node* func_3(Algebra_Node* P[2], Algebra_Node* D[2], string c)
{ // ['/']
	if (!(D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		if (!(D[0]->data.str == "1") && !(D[1]->data.str == "1"))
		{
			Algebra_Node* Q[6];
			Q[0] = SetNode("/"); // #
			Q[1] = SetNode("^"); // #
			Q[2] = SetNode("2"); // #
			Q[3] = SetNode("-"); // #
			Q[4] = SetNode("*"); // #
			Q[5] = SetNode("*"); // #
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			Algebra_Node& node_3 = *(Q[3]);
			Algebra_Node& node_4 = *(Q[4]);
			Algebra_Node& node_5 = *(Q[5]);
			node_5.addLeftNode(P[0]);
			node_5.addRightNode(D[1]);
			node_4.addLeftNode(P[1]);
			node_4.addRightNode(D[0]);
			node_3.addLeftNode(Q[5]);
			node_3.addRightNode(Q[4]);
			node_1.addLeftNode(P[0]);
			node_1.addRightNode(Q[2]);
			node.addLeftNode(Q[3]);
			node.addRightNode(Q[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];

		}
		if (!(D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{
			Algebra_Node* Q[5];
			Q[0] = SetNode("/");
			Q[1] = SetNode("^");
			Q[2] = SetNode("2");
			Q[3] = SetNode("-");
			Q[4] = SetNode("*");
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			Algebra_Node& node_3 = *(Q[3]);
			Algebra_Node& node_4 = *(Q[4]);
			node_4.addLeftNode(D[1]);
			node_4.addRightNode(P[0]);
			node_3.addLeftNode(Q[4]);
			node_3.addRightNode(P[1]);
			node_1.addLeftNode(P[0]);
			node_1.addRightNode(Q[2]);
			node.addLeftNode(Q[3]);
			node.addRightNode(Q[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];

		}
		if ((D[0]->data.str == "1") && !(D[1]->data.str == "1"))
		{
			Algebra_Node* Q[5];
			Q[0] = SetNode("/");
			Q[1] = SetNode("^");
			Q[2] = SetNode("2");
			Q[3] = SetNode("-");
			Q[4] = SetNode("*");
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			Algebra_Node& node_3 = *(Q[3]);
			Algebra_Node& node_4 = *(Q[4]);
			node_4.addLeftNode(D[0]);
			node_4.addRightNode(P[1]);
			node_3.addLeftNode(P[0]);
			node_3.addRightNode(Q[4]);
			node_1.addLeftNode(P[0]);
			node_1.addRightNode(Q[2]);
			node.addLeftNode(Q[3]);
			node.addRightNode(Q[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];
		}
		if ((D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{
			Algebra_Node* Q[4];
			Q[0] = SetNode("/");
			Q[1] = SetNode("^");
			Q[2] = SetNode("2");
			Q[3] = SetNode("-");
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			Algebra_Node& node_3 = *(Q[3]);
			node_3.addLeftNode(P[0]);
			node_3.addRightNode(P[1]);
			node_1.addLeftNode(P[0]);
			node_1.addRightNode(Q[2]);
			node.addLeftNode(Q[3]);
			node.addRightNode(Q[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];
		}
	}
	if ((D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		if (!(D[1]->data.str == "1"))
		{
			Algebra_Node* Q;
			Q = SetNode("/");
			Algebra_Node& node = *Q;
			node.addLeftNode(D[1]);
			node.addRightNode(P[0]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q, V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q;
		}
		else
		{
			Algebra_Node* Q[2];
			Q[0] = SetNode("/");
			Q[1] = SetNode("1");
			Algebra_Node& node = *(Q[0]);
			node.addLeftNode(Q[1]);
			node.addRightNode(P[0]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];
		}
	}
	if (!(D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{
		if (!(D[0]->data.str == "1"))
		{
			Algebra_Node* Q[6];
			Q[0] = SetNode("/");
			Q[1] = SetNode("^");
			Q[2] = SetNode("2");
			Q[3] = SetNode("*");
			Q[4] = SetNode("*");
			Q[5] = SetNode("-1");
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			Algebra_Node& node_3 = *(Q[3]);
			Algebra_Node& node_4 = *(Q[4]);
			Algebra_Node& node_5 = *(Q[5]);
			node_4.addLeftNode(D[0]);
			node_4.addRightNode(Q[5]);
			node_3.addLeftNode(P[1]);
			node_3.addRightNode(Q[4]);
			node_1.addLeftNode(P[0]);
			node_1.addRightNode(Q[2]);
			node.addLeftNode(Q[3]);
			node.addRightNode(Q[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];
		}
		else
		{
			Algebra_Node* Q[5];
			Q[0] = SetNode("/");
			Q[1] = SetNode("^");
			Q[2] = SetNode("2");
			Q[3] = SetNode("*");
			Q[4] = SetNode("-1");
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			Algebra_Node& node_3 = *(Q[3]);
			Algebra_Node& node_4 = *(Q[4]);
			node_3.addLeftNode(Q[4]);
			node_3.addRightNode(P[1]);
			node_1.addLeftNode(P[0]);
			node_1.addRightNode(Q[2]);
			node.addLeftNode(Q[3]);
			node.addRightNode(Q[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];

		}
	}
	if ((D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{
		Algebra_Node* Q = SetNode("0");
		return Q;
	}
}

Algebra_Node* func_3a(Algebra_Node* P[2], Algebra_Node* D[2], string c)
{ // ['/']
	Algebra_Node* T = SetNode("0");

	if (!(D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		if (!(D[0]->data.str == "1") && !(D[1]->data.str == "1"))
		{
			const string s = "(D*q+d*p)/q^2";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
			TreeRExprReplaceOnSubTreeD(T, "d", D[1]);
		}
		if ((D[0]->data.str == "1") && !(D[1]->data.str == "1"))
		{
			const string s = "(q+d*p)/q^2";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "d", D[1]);
		}
		if (!(D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{
			const string s = "(D*q+p)/q^2";;
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "D", D[0]);

		}
		if ((D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{
			const string s = "(q+p)/q^2";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
		}
	}
	if ((D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{ // Деление константы p на q.
		if (!(D[1]->data.str == "1"))
		{
			const string s = "(-1)*p*d/q^2";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);

		}
		else
		{
			const string s = "(-1)*p/q^2";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
		};
	}
	if (!(D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{ // Деление p на константу q.
		if (D[1]->data.str == "1")
		{
			const string s = "p*D/q";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "D", D[0]);

		}
		else
		{
			const string s = "p/q";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
		};
	}
	if ((D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{
		const string s = "0";
		T = SetOperatorTree(s);
	}
	return T;
}

Algebra_Node* func_4(Algebra_Node* P[2], Algebra_Node* D[2], string c)
{ // ['^']
	if (!(D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		if (!(D[0]->data.str == "1") && !(D[1]->data.str == "1")) // f(x)^g(x)
		{
			Algebra_Node* Q[7];
			Q[0] = SetNode("*");
			Q[1] = SetNode("+");
			Q[2] = SetNode("*");
			Q[3] = SetNode("ln");
			Q[4] = SetNode("/");
			Q[5] = SetNode("*");
			Q[6] = SetNode("^");
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			Algebra_Node& node_3 = *(Q[3]);
			Algebra_Node& node_4 = *(Q[4]);
			Algebra_Node& node_5 = *(Q[5]);
			Algebra_Node& node_6 = *(Q[6]);
			node_6.addLeftNode(D[0]);
			node_6.addRightNode(P[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];

		}
		if ((D[0]->data.str == "1") && !(D[1]->data.str == "1"))
		{ // f(x) = F^x -> F^x * (D(F) * x / F + ln(F))
			Algebra_Node* Q[6];
			Q[0] = SetNode("*");
			Q[1] = SetNode("^");
			Q[2] = SetNode("+");
			Q[3] = SetNode("/");
			Q[4] = SetNode("*");
			Q[5] = SetNode("ln");
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			Algebra_Node& node_3 = *(Q[3]);
			Algebra_Node& node_4 = *(Q[4]);
			Algebra_Node& node_5 = *(Q[5]);
			node_5.addLeftNode(P[1]);
			node_4.addLeftNode(P[0]);
			node_4.addRightNode(D[1]);
			node_3.addLeftNode(Q[4]);
			node_3.addRightNode(P[1]);
			node_2.addLeftNode(Q[5]);
			node_2.addRightNode(Q[3]);
			node_1.addLeftNode(P[1]);
			node_1.addRightNode(P[0]);
			node.addLeftNode(Q[2]);
			node.addRightNode(Q[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];

		}
		if (!(D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{ // f(x) = x^G -> x^G * (G / F + D(G)*ln(F))
			Algebra_Node* Q[6];
			Q[0] = SetNode("*");
			Q[1] = SetNode("^");
			Q[2] = SetNode("+");
			Q[3] = SetNode("/");
			Q[4] = SetNode("*");
			Q[5] = SetNode("ln");
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			Algebra_Node& node_3 = *(Q[3]);
			Algebra_Node& node_4 = *(Q[4]);
			Algebra_Node& node_5 = *(Q[5]);
			node_5.addLeftNode(P[1]);
			node_4.addLeftNode(D[0]);
			node_4.addRightNode(Q[5]);
			node_3.addLeftNode(P[0]);
			node_3.addRightNode(P[1]);
			node_2.addLeftNode(Q[4]);
			node_2.addRightNode(Q[3]);
			node_1.addLeftNode(P[1]);
			node_1.addRightNode(P[0]);
			node.addLeftNode(Q[2]);
			node.addRightNode(Q[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];

		}
		if ((D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{ // # f'(x) = F^G * (G / F + ln(F)) , (x+a)^(x+b) , a , b - постоянные.
			Algebra_Node* Q[6];
			Q[0] = SetNode("*");
			Q[1] = SetNode("^");
			Q[2] = SetNode("+");
			Q[3] = SetNode("/");
			Q[4] = SetNode("ln");
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			Algebra_Node& node_3 = *(Q[3]);
			Algebra_Node& node_4 = *(Q[4]);
			node_4.addLeftNode(P[1]);
			node_3.addLeftNode(P[0]);
			node_3.addRightNode(P[1]);
			node_2.addLeftNode(Q[4]);
			node_2.addRightNode(Q[3]);
			node_1.addLeftNode(P[1]);
			node_1.addRightNode(P[0]);
			node.addLeftNode(Q[2]);
			node.addRightNode(Q[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];
		}
	}
	if ((D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{ // # f(x)^c - степенная функция , f(x) = x^n -> f'(x) = n*x^(n-1), f(x) = P[1], n = P[0]
		Token& T = P[0]->data;
		if (!(D[1]->data.str == "1"))
		{
			if (T.type == Token::Type::Number)
			{
				int n = stoi(T.str); // Извлекаем константный показатель степени.
				Algebra_Node* Q[4];
				Q[0] = SetNode("*");
				Q[1] = SetNode("*");
				Q[2] = SetNode("^");
				Q[3] = SetNode(n - 1);
				Algebra_Node& node = *(Q[0]);
				Algebra_Node& node_1 = *(Q[1]);
				Algebra_Node& node_2 = *(Q[2]);
				Algebra_Node& node_3 = *(Q[3]);
				node_2.addLeftNode(P[1]);
				node_2.addRightNode(Q[3]);
				node_1.addLeftNode(P[0]);
				node_1.addRightNode(D[1]);
				node.addLeftNode(Q[2]);
				node.addRightNode(Q[1]);
				if (DEBUG)
				{
					vector<Token> V;
					TreeToPolish(Q[0], V);
					string r = PostfixToInfix(V); // В виде строки лучше обозримо.
					while (0); // Для точки останова.
				}
				return Q[0];

			}
			else if (T.type == Token::Type::Algebra)
			{
				Algebra_Node* Q[5];
				Q[0] = SetNode("*");
				Q[1] = SetNode("*");
				Q[2] = SetNode("^");
				Q[3] = SetNode("-");
				Q[4] = SetNode("1");
				Algebra_Node& node = *(Q[0]);
				Algebra_Node& node_1 = *(Q[1]);
				Algebra_Node& node_2 = *(Q[2]);
				Algebra_Node& node_3 = *(Q[3]);
				node_3.addLeftNode(P[0]);
				node_3.addRightNode(Q[4]);
				node_2.addLeftNode(P[1]);
				node_2.addRightNode(Q[2]);
				node_1.addLeftNode(D[1]);
				node_1.addRightNode(P[0]);
				node.addLeftNode(Q[2]);
				node.addRightNode(Q[1]);
				if (DEBUG)
				{
					vector<Token> V;
					TreeToPolish(Q[0], V);
					string r = PostfixToInfix(V); // В виде строки лучше обозримо.
					while (0); // Для точки останова.
				}
				return Q[0];
			}
		}
		else // f(x) = (x+a)^n ->  f'(x) = n*(x+a)^(n-1)
		{
			if (!(D[1]->data.str == "1"))
			{
				if (T.type == Token::Type::Number)
				{
					int n = stoi(T.str); // Извлекаем константное основание степени.
					Algebra_Node* Q[4];
					Q[0] = SetNode("*");
					Q[1] = SetNode(n);
					Q[2] = SetNode("^");
					Q[3] = SetNode(n - 1);
					Algebra_Node& node = *(Q[0]);
					Algebra_Node& node_1 = *(Q[1]);
					Algebra_Node& node_2 = *(Q[2]);
					Algebra_Node& node_3 = *(Q[3]);
					node_2.addLeftNode(P[1]);
					node_2.addRightNode(Q[3]);
					node.addLeftNode(Q[2]);
					node.addRightNode(Q[1]);
					if (DEBUG)
					{
						vector<Token> V;
						TreeToPolish(Q[0], V);
						string r = PostfixToInfix(V); // В виде строки лучше обозримо.
						while (0); // Для точки останова.
					}
					return Q[0];
				}
				else if (T.type == Token::Type::Algebra)
				{
					Algebra_Node* Q[4];
					Q[0] = SetNode("*");
					Q[1] = SetNode("^");
					Q[2] = SetNode("-");
					Q[3] = SetNode("1");
					Algebra_Node& node = *(Q[0]);
					Algebra_Node& node_1 = *(Q[1]);
					Algebra_Node& node_2 = *(Q[2]);
					Algebra_Node& node_3 = *(Q[3]);
					node_2.addLeftNode(P[0]);
					node_2.addRightNode(Q[2]);
					node_1.addLeftNode(P[1]);
					node_1.addRightNode(Q[2]);
					node.addLeftNode(Q[2]);
					node.addRightNode(Q[1]);
					if (DEBUG)
					{
						vector<Token> V;
						TreeToPolish(Q[0], V);
						string r = PostfixToInfix(V); // В виде строки лучше обозримо.
						while (0); // Для точки останова.
					}
					return Q[0];
				}
			}
			else
			{
				if (T.type == Token::Type::Number)
				{
					int n = stoi(T.str); // Извлекаем константное основание степени.
					Algebra_Node* Q[4];
					Q[0] = SetNode("*");
					Q[1] = SetNode(n);
					Q[2] = SetNode("^");
					Q[3] = SetNode(n - 1);
					Algebra_Node& node = *(Q[0]);
					Algebra_Node& node_1 = *(Q[1]);
					Algebra_Node& node_2 = *(Q[2]);
					Algebra_Node& node_3 = *(Q[3]);
					node_2.addLeftNode(P[1]);
					node_2.addRightNode(Q[3]);
					node.addLeftNode(Q[2]);
					node.addRightNode(Q[1]);
					if (DEBUG)
					{
						vector<Token> V;
						TreeToPolish(Q[0], V);
						string r = PostfixToInfix(V); // В виде строки лучше обозримо.
						while (0); // Для точки останова.
					}
					return Q[0];

				}
				else if (T.type == Token::Type::Algebra)
				{
					Algebra_Node* Q[4];
					Q[0] = SetNode("*");
					Q[1] = SetNode("^");
					Q[2] = SetNode("-");
					Q[3] = SetNode("1");
					Algebra_Node& node = *(Q[0]);
					Algebra_Node& node_1 = *(Q[1]);
					Algebra_Node& node_2 = *(Q[2]);
					Algebra_Node& node_3 = *(Q[3]);
					node_2.addLeftNode(P[0]);
					node_2.addRightNode(Q[3]);
					node_1.addLeftNode(P[1]);
					node_1.addRightNode(Q[2]);
					node.addLeftNode(P[0]);
					node.addRightNode(Q[1]);
					if (DEBUG)
					{
						vector<Token> V;
						TreeToPolish(Q[0], V);
						string r = PostfixToInfix(V); // В виде строки лучше обозримо.
						while (0); // Для точки останова.
					}
					return Q[0];
				}
			}
		}

	}
	if (!(D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{ // c^f(x) - показательная функция , f(x) = a^x -> f'(x) = a^x*ln(a)
		// g(x) = a^f(x) -> g'(x) = a^f(x) * f'(x) * ln(a) , P[0] = f(x) , P[1] = a
		Token& T = P[1]->data;
		int a = stoi(T.str);
		if (!(D[0]->data.str == "0"))
		{
			if (T.type == Token::Type::Number)
			{
				Algebra_Node* Q[6];
				Q[0] = SetNode("*");
				Q[1] = SetNode("*");
				Q[2] = SetNode("^");
				Q[3] = SetNode(a);
				Q[4] = SetNode("ln");
				Q[5] = SetNode(a);
				Algebra_Node& node = *(Q[0]);
				Algebra_Node& node_1 = *(Q[1]);
				Algebra_Node& node_2 = *(Q[2]);
				Algebra_Node& node_3 = *(Q[3]);
				Algebra_Node& node_4 = *(Q[4]);
				Algebra_Node& node_5 = *(Q[5]);
				node_4.addLeftNode(Q[5]);
				node_2.addLeftNode(Q[3]);
				node_2.addRightNode(P[0]);
				node_1.addLeftNode(D[0]);
				node_1.addRightNode(Q[2]);
				node.addLeftNode(Q[2]);
				node.addRightNode(Q[1]);
				if (DEBUG)
				{
					vector<Token> V;
					TreeToPolish(Q[0], V);
					string r = PostfixToInfix(V); // В виде строки лучше обозримо.
					while (0); // Для точки останова.
				}
				return Q[0];
			}
			else if (T.type == Token::Type::Algebra)
			{
				Algebra_Node* Q[4];
				Q[0] = SetNode("*");
				Q[1] = SetNode("*");
				Q[2] = SetNode("^");
				Q[3] = SetNode("ln");
				Algebra_Node& node = *(Q[0]);
				Algebra_Node& node_1 = *(Q[1]);
				Algebra_Node& node_2 = *(Q[2]);
				Algebra_Node& node_3 = *(Q[3]);
				node_3.addLeftNode(P[1]);
				node_2.addLeftNode(P[1]);
				node_2.addRightNode(P[0]);
				node_1.addLeftNode(D[0]);
				node_1.addRightNode(Q[2]);
				node.addRightNode(Q[2]);
				node.addLeftNode(Q[1]);
				if (DEBUG)
				{
					vector<Token> V;
					TreeToPolish(Q[0], V);
					string r = PostfixToInfix(V); // В виде строки лучше обозримо.
					while (0); // Для точки останова.
				}
				return Q[0];
			}
		}
		else
		{
			if (T.type == Token::Type::Number)
			{
				Algebra_Node* Q[5];
				Q[0] = SetNode("*");
				Q[1] = SetNode("ln");
				Q[2] = SetNode(a);
				Q[3] = SetNode("^");
				Q[4] = SetNode(a);
				Algebra_Node& node = *(Q[0]);
				Algebra_Node& node_1 = *(Q[1]);
				Algebra_Node& node_2 = *(Q[2]);
				Algebra_Node& node_3 = *(Q[3]);
				Algebra_Node& node_4 = *(Q[4]);
				node_3.addLeftNode(Q[4]);
				node_3.addRightNode(P[0]);
				node_1.addLeftNode(Q[2]);
				node.addLeftNode(Q[3]);
				node.addRightNode(Q[1]);
				if (DEBUG)
				{
					vector<Token> V;
					TreeToPolish(Q[0], V);
					string r = PostfixToInfix(V); // В виде строки лучше обозримо.
					while (0); // Для точки останова.
				}
				return Q[0];

			}
			else if (T.type == Token::Type::Algebra)
			{
				Algebra_Node* Q[3];
				Q[0] = SetNode("*");
				Q[1] = SetNode("ln");
				Q[2] = SetNode("^");
				Algebra_Node& node = *(Q[0]);
				Algebra_Node& node_1 = *(Q[1]);
				Algebra_Node& node_2 = *(Q[2]);
				node_2.addLeftNode(P[1]);
				node_2.addRightNode(P[0]);
				node_1.addLeftNode(P[1]);
				node.addLeftNode(Q[2]);
				node.addRightNode(Q[1]);
				if (DEBUG)
				{
					vector<Token> V;
					TreeToPolish(Q[0], V);
					string r = PostfixToInfix(V); // В виде строки лучше обозримо.
					while (0); // Для точки останова.
				}
				return Q[0];
			}
		}

	}
	if ((D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{
		Algebra_Node* Q;
		Q = SetNode("0");
		return Q;
	}
}

Algebra_Node* func_4a(Algebra_Node* P[2], Algebra_Node* D[2], string c)
{ // ['^']
	Algebra_Node* T =  SetNode("0");

	if (!(D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{
		if (!((D[0]->data.str == "1") && !(D[1]->data.str == "1")))
		{
			const string s = "p^q*(D*q/p +d*ln(p))";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
			TreeRExprReplaceOnSubTreeD(T, "d", D[1]);
		}

		if ((D[0]->data.str == "1") && !(D[1]->data.str == "1"))
		{
			const string s = "p^q*(q/p +d*ln(p))";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "d", D[1]);
		}
		if (!(D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{
			const string s = "p^q*(D*q/p + ln(p))";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "D", D[0]);

		}
		if ((D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{
			const string s = "p^q*(q/p + ln(p))";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
		}
	}
	if ((D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{ // Показательная функция
		if (!(D[1]->data.str == "1"))
		{
			const string s = "p^q*ln(p)*d";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "d", D[1]);
		}
		else
		{
			const string s = "p^q*ln(p)";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);

		}
	}
	if (!(D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{ // Степеннная функция
		if (!(D[1]->data.str == "1"))
		{
			const string s = "D*q*p^(q-1)";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "D", D[0]);

		}
		else
		{
			const string s = "q*p^(q-1)";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
		}
	}
	if ((D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{ // Константа в степени константа.
		const string s = "0";
		T = SetOperatorTree(s);
	}
	return T;
}



Algebra_Node* func_5(Algebra_Node* P[2] , Algebra_Node* D[2], string c)
{
	if (!(D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{ //  f(y) = log(y , x) = ln(y)/ln(x) ,  P[1] = x , P[0] = y
	  // f'(y) = (D(y) / y * ln(x) - D(x) / x * ln(y)) / ln^2(x)
		if (!((D[0]->data.str == "1") && (D[1]->data.str == "1")))
		{
			Algebra_Node* Q[11];
			Q[0] = SetNode("/");
			Q[1] = SetNode("^");
			Q[2] = SetNode("2");
			Q[3] = SetNode("ln");
			Q[4] = SetNode("-");
			Q[5] = SetNode("/");
			Q[6] = SetNode("*");
			Q[7] = SetNode("ln");
			Q[8] = SetNode("/");
			Q[9] = SetNode("*");
			Q[10] = SetNode("ln");
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			Algebra_Node& node_3 = *(Q[3]);
			Algebra_Node& node_4 = *(Q[4]);
			Algebra_Node& node_5 = *(Q[5]);
			Algebra_Node& node_6 = *(Q[6]);
			Algebra_Node& node_7 = *(Q[7]);
			Algebra_Node& node_8 = *(Q[8]);
			Algebra_Node& node_9 = *(Q[9]);
			Algebra_Node& node_10 = *(Q[10]);
			node_10.addLeftNode(P[1]);
			node_9.addLeftNode(D[0]);
			node_9.addRightNode(Q[10]);
			node_8.addLeftNode(Q[9]);
			node_8.addRightNode(P[0]);
			node_7.addLeftNode(P[0]);
			node_6.addLeftNode(D[1]);
			node_6.addRightNode(Q[7]);
			node_5.addLeftNode(Q[6]);
			node_5.addRightNode(P[1]);
			node_4.addLeftNode(Q[8]);
			node_4.addRightNode(Q[5]);
			node_3.addLeftNode(P[1]);
			node_1.addLeftNode(Q[3]);
			node_1.addRightNode(Q[2]);
			node.addLeftNode(Q[4]);
			node.addRightNode(Q[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];

			if ((D[0]->data.str == "1") && (D[1]->data.str == "1"))
			{
				Algebra_Node* Q[9];
				Q[0] = SetNode("/");
				Q[1] = SetNode("^");
				Q[2] = SetNode("2");
				Q[3] = SetNode("ln");
				Q[4] = SetNode("-");
				Q[5] = SetNode("/");
				Q[6] = SetNode("ln");
				Q[7] = SetNode("/");
				Q[8] = SetNode("ln");
				Algebra_Node& node = *(Q[0]);
				Algebra_Node& node_1 = *(Q[1]);
				Algebra_Node& node_2 = *(Q[2]);
				Algebra_Node& node_3 = *(Q[3]);
				Algebra_Node& node_4 = *(Q[4]);
				Algebra_Node& node_5 = *(Q[5]);
				Algebra_Node& node_6 = *(Q[6]);
				Algebra_Node& node_7 = *(Q[7]);
				Algebra_Node& node_8 = *(Q[8]);
				node_8.addLeftNode(P[1]);
				node_7.addLeftNode(Q[8]);
				node_7.addRightNode(P[0]);
				node_6.addLeftNode(P[0]);
				node_5.addLeftNode(Q[6]);
				node_5.addRightNode(P[1]);
				node_4.addLeftNode(Q[7]);
				node_4.addRightNode(Q[5]);
				node_3.addLeftNode(P[1]);
				node_1.addLeftNode(Q[3]);
				node_1.addRightNode(Q[2]);
				node.addLeftNode(Q[4]);
				node.addRightNode(Q[1]);
				if (DEBUG)
				{
					vector<Token> V;
					TreeToPolish(Q[0], V);
					string r = PostfixToInfix(V); // В виде строки лучше обозримо.
					while (0); // Для точки останова.
				}
				return Q[0];
			}

		}
		if (!(D[0]->data.str == "0") && (D[1]->data.str == "0"))
		{ // f(y) = log(c , y) - логарифм по постоянному основанию степени.
		  //  f'(y) = D(y)/(y * ln(c)) , P[0] = c , P[1] = y
			Algebra_Node* Q[3];
			Q[0] = SetNode("/");
			Q[1] = SetNode("*");
			Q[2] = SetNode("ln");
			Algebra_Node& node = *(Q[0]);
			Algebra_Node& node_1 = *(Q[1]);
			Algebra_Node& node_2 = *(Q[2]);
			node_2.addLeftNode(P[1]);
			node_1.addLeftNode(P[0]);
			node_1.addRightNode(Q[2]);
			node.addLeftNode(D[0]);
			node.addRightNode(Q[1]);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(Q[0], V);
				string r = PostfixToInfix(V); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];
		}
		if ((D[0]->data.str == "0") && !(D[1]->data.str == "0"))
		{
			if (!(D[1]->data.str == "1"))
			{
				Algebra_Node* Q[9];
				Q[0] = SetNode("/");
				Q[1] = SetNode("*");
				Q[2] = SetNode("^");
				Q[3] = SetNode("2");
				Q[4] = SetNode("ln");
				Q[5] = SetNode("*");
				Q[6] = SetNode("-1");
				Q[7] = SetNode("*");
				Q[8] = SetNode("ln");
				Algebra_Node& node = *(Q[0]);
				Algebra_Node& node_1 = *(Q[1]);
				Algebra_Node& node_2 = *(Q[2]);
				Algebra_Node& node_3 = *(Q[3]);
				Algebra_Node& node_4 = *(Q[4]);
				Algebra_Node& node_5 = *(Q[5]);
				Algebra_Node& node_6 = *(Q[6]);
				Algebra_Node& node_7 = *(Q[7]);
				Algebra_Node& node_8 = *(Q[8]);
				node_8.addLeftNode(P[0]);
				node_7.addLeftNode(D[1]);
				node_7.addRightNode(Q[8]);
				node_5.addLeftNode(Q[6]);
				node_5.addRightNode(Q[7]);
				node_4.addLeftNode(P[1]);
				node_2.addLeftNode(Q[4]);
				node_2.addRightNode(Q[3]);
				node_1.addLeftNode(Q[1]);
				node_1.addRightNode(P[1]);
				node.addLeftNode(Q[5]);
				node.addRightNode(Q[1]);
				if (DEBUG)
				{
					vector<Token> V;
					TreeToPolish(Q[0], V);
					string r = PostfixToInfix(V); // В виде строки лучше обозримо.
					while (0); // Для точки останова.
				}
				return Q[0];

			}
			else
			{
				Algebra_Node* Q[8];
				Q[0] = SetNode("/");
				Q[1] = SetNode("*");
				Q[2] = SetNode("^");
				Q[3] = SetNode("2");
				Q[4] = SetNode("ln");
				Q[5] = SetNode("*");
				Q[6] = SetNode("-1");
				Q[7] = SetNode("ln");
				Algebra_Node& node = *(Q[0]);
				Algebra_Node& node_1 = *(Q[1]);
				Algebra_Node& node_2 = *(Q[2]);
				Algebra_Node& node_3 = *(Q[3]);
				Algebra_Node& node_4 = *(Q[4]);
				Algebra_Node& node_5 = *(Q[5]);
				Algebra_Node& node_6 = *(Q[6]);
				Algebra_Node& node_7 = *(Q[7]);
				node_7.addLeftNode(P[0]);
				node_5.addLeftNode(Q[7]);
				node_5.addRightNode(Q[6]);
				node_4.addLeftNode(P[1]);
				node_2.addLeftNode(Q[4]);
				node_2.addRightNode(Q[3]);
				node_1.addLeftNode(P[1]);
				node_1.addRightNode(Q[2]);
				node.addLeftNode(Q[5]);
				node.addRightNode(Q[1]);
				if (DEBUG)
				{
					vector<Token> V;
					TreeToPolish(Q[0], V);
					string r = PostfixToInfix(V); // В виде строки лучше обозримо.
					while (0); // Для точки останова.
				}
				return Q[0];
			}
		}
		if ((D[0]->data.str == "0") && (D[1]->data.str == "0"))
		{
			Algebra_Node* Q;
			Q = SetNode("0");
			return Q;
		}
	}
}

Algebra_Node* func_5a(Algebra_Node* P[2], Algebra_Node* D[2], string c)
{
	Algebra_Node* T = SetNode("0");

	if (!(D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{ //  f(y) = log(y , x) = ln(y)/ln(x) ,  P[1] = x , P[0] = y
	  // f'(y) = (D(y) / y * ln(x) - D(x) / x * ln(y)) / ln^2(x)
		if (!((D[0]->data.str == "1") && !(D[1]->data.str == "1")))
		{
			const string s = "(D/p*ln(q)-d/q*ln(p))/(ln(q))^2";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
			TreeRExprReplaceOnSubTreeD(T, "d", D[1]);
		}
		if ((D[0]->data.str == "1") && !(D[1]->data.str == "1"))
		{
			const string s = "(ln(q)/p-d/q*ln(p))/(ln(q))^2";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "d", D[1]);
		}
		if (!((D[0]->data.str == "1") && (D[1]->data.str == "1")))
		{
			const string s = "(D/p*ln(q)-ln(p)/q)/(ln(q))^2";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
		}
		if ((D[0]->data.str == "1") && (D[1]->data.str == "1"))
		{
			const string s = "(ln(q)/p-ln(p)/q)/(ln(q))^2";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);

		}

	}
	if (!(D[0]->data.str == "0") && (D[1]->data.str == "0"))
	{ // f(y) = log(c , y) - логарифм по постоянному основанию степени.
		  //  f'(y) = D(y)/(y * ln(c)) , P[0] = c , P[1] = y
		if (!(D[1]->data.str == "1"))
		{
			const string s = "d/(q*ln(p))";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);

		}
		else
		{
			const string s = "1/(q*ln(p))";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);

		}
	}
	if ((D[0]->data.str == "0") && !(D[1]->data.str == "0"))
	{ // Логарифм от постоянного числа по переменному основнию.
		if (!(D[1]->data.str == "1"))
		{
			const string s = "(-1)*d*ln(p)/(q*ln(q))^2";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);
			TreeRExprReplaceOnSubTreeD(T, "d", D[1]);
		}
		else
		{
			const string s = "(-1)*ln(p)/(q*ln(q))^2";
			T = SetOperatorTree(s);
			TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
			TreeRExprReplaceOnSubTreeD(T, "q", P[1]);

		}
	}
	if ((D[0]->data.str == "0") && (D[1]->data.str == "0"))
    { // Логарифм постоянного числа по постоянной степени.
		const string s = "0";
		T = SetOperatorTree(s);
	}

	return T;
}


Algebra_Node* func_6(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{
	if (!(D[0]->data.str == "1"))
	{
		Algebra_Node* Q[2];
		Q[0] = SetNode("*");
		Q[1] = SetNode("exp");
		Algebra_Node& node = *(Q[0]);
		Algebra_Node& node_1 = *(Q[1]);
		node_1.addLeftNode(P[0]);
		node.addRightNode(D[0]);
		node.addRightNode(Q[1]);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(Q[0], V);
			string r = PostfixToInfix(V); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q[0];
	}
	else
	{
		Algebra_Node* Q;
		Q = SetNode("exp");
		Algebra_Node& node = *Q;
		node.addLeftNode(P[0]);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(Q, V);
			string r = PostfixToInfix(V); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q;
	}
}

Algebra_Node* func_6a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['exp']
	Algebra_Node* T = SetNode("0");

	if (!(D[0]->data.str == "1"))
	{
		const string s = "exp(p)*D";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		TreeRExprReplaceOnSubTreeD(T, "D", D[0]);

	}
	else
	{
		const string s = "exp(p)";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);

	}

	return T;
}

Algebra_Node* func_7(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['ln']
	if (!(D[0]->data.str == "1"))
	{
		Algebra_Node* Q;
		Q = SetNode("ln");
		Algebra_Node& node = *Q;
		node.addLeftNode(D[0]);
		node.addRightNode(P[0]);
		node.addLeftNode(P[0]);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(Q, V);
			string r = PostfixToInfix(V); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q;
	}
}

Algebra_Node* func_7a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['ln']
	Algebra_Node* T = SetNode("0");
	const string s = "D/p";
	T = SetOperatorTree(s);
	TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
	TreeRExprReplaceOnSubTreeD(T, "D", D[0]);

	return T;
}

Algebra_Node* func_8(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['sin']
	if (!(D[0]->data.str == "1"))
	{
		Algebra_Node* Q[2];
		Q[0] = SetNode("*");
		Q[1] = SetNode("cos");
		Algebra_Node& node = *(Q[0]);
		Algebra_Node& node_1 = *(Q[1]);
		node_1.addLeftNode(P[0]);
		node.addLeftNode(Q[1]);
		node.addRightNode(D[0]);
		node.addLeftNode(P[0]);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(Q[0], V);
			string r = PostfixToInfix(V); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q[0];
	}
	else
	{
		Algebra_Node* Q;
		Q = SetNode("cos");
		Algebra_Node& node = *Q;
		node.addLeftNode(P[0]);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(Q, V);
			string r = PostfixToInfix(V); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q;
	}
}

Algebra_Node* func_8a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['sin']
	Algebra_Node* T = SetNode("0");

	if (!(D[0]->data.str == "1"))
	{
		const string s = "D*cos(p)";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	}
	else
	{
		const string s = "cos(p)";
		T = SetOperatorTree(s);	
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);

	}

	return T;
}

Algebra_Node* func_9(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['cos']
	if (!(D[0]->data.str == "1"))
	{
		Algebra_Node* Q[4];
		Q[0] = SetNode("*");
		Q[1] = SetNode("-1");
		Q[2] = SetNode("*");
		Q[3] = SetNode("sin");
		Algebra_Node& node = *(Q[0]);
		Algebra_Node& node_1 = *(Q[1]);
		Algebra_Node& node_2 = *(Q[2]);
		Algebra_Node& node_3 = *(Q[3]);
		node_3.addLeftNode(P[0]);
		node_2.addLeftNode(D[0]);
		node_2.addRightNode(Q[3]);
		node.addLeftNode(Q[2]);
		node.addRightNode(Q[1]);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(Q[0], V);
			string r = PostfixToInfix(V); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q[0];
	}
	else
	{
		Algebra_Node* Q[3];
		Q[0] = SetNode("*");
		Q[1] = SetNode("-1");
		Q[2] = SetNode("sin");
		Algebra_Node& node = *(Q[0]);
		Algebra_Node& node_1 = *(Q[1]);
		Algebra_Node& node_2 = *(Q[2]);
		node_2.addLeftNode(P[0]);
		node.addLeftNode(Q[2]);
		node.addRightNode(Q[1]);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(Q[0], V);
			string r = PostfixToInfix(V); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q[0];
	}
}

Algebra_Node* func_9a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['cos']
	Algebra_Node* T = SetNode("0");

	if (!(D[0]->data.str == "1"))
	{
		const string s = "(-1)*D*sin(p)";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	}
	else
	{
		const string s = "(-1)*cos(p)";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);

	}

	return T;
}

Algebra_Node* func_10(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['tg']

	Algebra_Node* Q[4];
	Q[0] = SetNode("/");
	Q[1] = SetNode("^");
	Q[2] = SetNode("2");
	Q[3] = SetNode("cos");
	Algebra_Node& node = *(Q[0]);
	Algebra_Node& node_1 = *(Q[1]);
	Algebra_Node& node_2 = *(Q[2]);
	Algebra_Node& node_3 = *(Q[3]);
	node_3.addLeftNode(P[0]);
	node_1.addLeftNode(Q[3]);
	node_1.addRightNode(Q[2]);
	node.addLeftNode(D[0]);
	node.addRightNode(Q[1]);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(Q[0], V);
		string r = PostfixToInfix(V); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}
	return Q[0];
}

Algebra_Node* func_10a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['tg']
	Algebra_Node* T = SetNode("0");

	const string s = "D/(cos(p))^2";
	T = SetOperatorTree(s);
	TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
	TreeRExprReplaceOnSubTreeD(T, "D", D[0]);

	return T;
}

Algebra_Node* func_11(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['ctg']
	if (!(D[0]->data.str == "1"))
	{
		Algebra_Node* Q[6];
		Q[0] = SetNode("/");
		Q[1] = SetNode("^");
		Q[2] = SetNode("2");
		Q[3] = SetNode("sin");
		Q[4] = SetNode("*");
		Q[5] = SetNode("-1");
		Algebra_Node& node = *(Q[0]);
		Algebra_Node& node_1 = *(Q[1]);
		Algebra_Node& node_2 = *(Q[2]);
		Algebra_Node& node_3 = *(Q[3]);
		Algebra_Node& node_4 = *(Q[4]);
		Algebra_Node& node_5 = *(Q[5]);
		node_4.addLeftNode(Q[5]);
		node_4.addRightNode(D[0]);
		node_3.addLeftNode(P[0]);
		node_1.addLeftNode(Q[3]);
		node_1.addRightNode(Q[2]);
		node.addLeftNode(Q[4]);
		node.addRightNode(Q[1]);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(Q[0], V);
			string r = PostfixToInfix(V); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q[0];
	}
	else
	{
		Algebra_Node* Q[5];
		Q[0] = SetNode("/");
		Q[1] = SetNode("^");
		Q[2] = SetNode("2");
		Q[3] = SetNode("sin");
		Q[4] = SetNode("-1");
		Algebra_Node& node = *(Q[0]);
		Algebra_Node& node_1 = *(Q[1]);
		Algebra_Node& node_2 = *(Q[2]);
		Algebra_Node& node_3 = *(Q[3]);
		Algebra_Node& node_4 = *(Q[4]);
		node_3.addLeftNode(P[0]);
		node_1.addLeftNode(Q[3]);
		node_1.addRightNode(Q[2]);
		node.addLeftNode(Q[4]);
		node.addRightNode(Q[1]);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(Q[0], V);
			string r = PostfixToInfix(V); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q[0];
	}
}

Algebra_Node* func_11a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['ctg']
	Algebra_Node* T = SetNode("0");

	if (!(D[0]->data.str == "1"))
	{
		const string s = "(-1)*D/(cos(p))^2";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
		
	}
	else
	{
		const string s = "(-1)/(cos(p))^2";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);

	}

	return T;
}

Algebra_Node* func_12(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['arcsin']
	Algebra_Node* Q[9];
	Q[0] = SetNode("/");
	Q[1] = SetNode("^");
	Q[2] = SetNode("2");
	Q[3] = SetNode("sin");
	Q[4] = SetNode("-1");
	Algebra_Node& node = *(Q[0]);
	Algebra_Node& node_1 = *(Q[1]);
	Algebra_Node& node_2 = *(Q[2]);
	Algebra_Node& node_3 = *(Q[3]);
	Algebra_Node& node_4 = *(Q[4]);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(Q[0], V);
		string r = PostfixToInfix(V); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}
	return Q[0];
}

Algebra_Node* func_12a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['arcsin']
	Algebra_Node* T = SetNode("0");

	const string s = "D/(1-p^2)^(1/2)";
	T = SetOperatorTree(s);
	TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
	TreeRExprReplaceOnSubTreeD(T, "D", D[0]);

	return T;	
}

Algebra_Node* func_13a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['arccos']
	Algebra_Node* T = SetNode("0");

	if (!(D[0]->data.str == "1"))
	{
		string s = "(-1)*D/(1-p^2)^(1/2)";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	}
	else
	{
		string s = "(-1)/(1-p^2)^(1/2)";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);

	}

	return T;
}

Algebra_Node* func_14a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['arctg']
	Algebra_Node* T = SetNode("0");

	string s = "D/(1+p^2)";
	T = SetOperatorTree(s);
	TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
	TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	
	return T;
}

Algebra_Node* func_15a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['arcctg']
	Algebra_Node* T = SetNode("0");

	if (!(D[0]->data.str == "1"))
	{
		string s = "(-1)*D/(1+p^2)";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	}
	else
	{
		string s = "(-1)/(1+p^2)";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	}
	return T;
}

Algebra_Node* func_16a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['sh']
	Algebra_Node* T = SetNode("0");

	if (!(D[0]->data.str == "1"))
	{
		string s = "D*ch(p)";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	}
	else
	{
		string s = "ch(p)";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);

	}

	return T;
}

Algebra_Node* func_17a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['ch']
	Algebra_Node* T = SetNode("0");

	if (!(D[0]->data.str == "1"))
	{
		string s = "(-1)*D*sh(p)";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	}
	else
	{
		string s = "(-1)*sh(p)";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	}

	return T;
}

Algebra_Node* func_18a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['th']
	Algebra_Node* T = SetNode("0");

	string s = "D/(ch(p))^2";
	T = SetOperatorTree(s);
	TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
	TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	
	return T;
}

Algebra_Node* func_19a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['cth']
	Algebra_Node* T = SetNode("0");

	if (!(D[0]->data.str == "1"))
	{
		string s = "D/(ch(p))^2";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	}
	else
	{
		string s = "(-1)*D/(ch(p))^2";
		T = SetOperatorTree(s);
		TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
		TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	}

	return T;
}

Algebra_Node* func_20a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['arsh']
	Algebra_Node* T = SetNode("0");

	string s = "D/(1+p^2)^(1/2)";
	T = SetOperatorTree(s);
	TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
	TreeRExprReplaceOnSubTreeD(T, "D", D[0]);
	
	return T;
}

Algebra_Node* func_21a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['arch']
	Algebra_Node* T = SetNode("0");

	string s = "D/(p^2-1)^(1/2)";
	T = SetOperatorTree(s);
	TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
	TreeRExprReplaceOnSubTreeD(T, "D", D[0]);

	return T;
}

Algebra_Node* func_22a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['arth']
	Algebra_Node* T = SetNode("0");

	string s = "D/(1-p^2)";
	T = SetOperatorTree(s);
	TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
	TreeRExprReplaceOnSubTreeD(T, "D", D[0]);

	return T;
}

Algebra_Node* func_23a(Algebra_Node* P[1], Algebra_Node* D[1], string c)
{ // ['arcth']
	Algebra_Node* T = SetNode("0");

	string s = "D/(1-p^2)";
	T = SetOperatorTree(s);
	TreeRExprReplaceOnSubTreeD(T, "p", P[0]);
	TreeRExprReplaceOnSubTreeD(T, "D", D[0]);

	return T;
}



Algebra_Node* DerivateFunc(Algebra_Node* root) // Следить , чтобы у каждой ветви было возвращающие значение.
{
	Token& T = root->data;
	if (T.type == Token::Type::Algebra || T.type == Token::Type::Number)
	{
		string s;
		if (T.str == X)  s = "1";
		else s = "0";
		Algebra_Node* node = SetNode(s);
		return node;
	}
	if (f_opr_two(T))
	{
		Algebra_Node* P[2]; // Сюда сохраняются первый и второй операнд.
		Algebra_Node* D[2]; // Сюда сохраняются соответствующие производные этих операндов.
		P[0] = root->left;
		P[1] = root->right;
		for (int i = 0; i < 2; i++) D[i] = DerivateFunc(P[i]);
		string v;
		if (DEBUG)
		{
			cout << endl;
			string r[2];
			vector<Token> V[2];
			for (int i = 0; i < 2; i++)
			{
				TreeToPolish(D[i], V[i]);
				r[i] = PostfixToInfix(V[i]);
				while (0); // Для точки останова.
				
			}
			TreeToPolish(root, V[0]);
			v = PostfixToInfix(V[0]); // Все поддерево.
			
		}
		string c = T.str;
		Algebra_Node* node;
		if (c == "+" || c == "-") node = func_1a(P, D, c);
		if (c == "*") node = func_2a(P, D, c);
		else if (c == "/") node = func_3a(P, D, c);
		else if (c == "^") node = func_4a(P, D, c);
		else if (c == "log") node = func_5a(P, D, c);
		
	}
	else if (f_opr_one(T))
	{
		Algebra_Node* P[1]; // Сюда сохраняются первый и второй операнд.
		Algebra_Node* D[1]; // Сюда сохраняются соответствующие производные этих операндов.
		P[0] = root->left;
		D[0] = DerivateFunc(P[0]);
		string v;
		if (DEBUG)
		{
			cout << endl;
			string r;
			vector<Token> V;
			TreeToPolish(D[0], V);
			r = PostfixToInfix(V);
			TreeToPolish(root, V);
			v = PostfixToInfix(V); // Все поддерево.

		}
		string c = T.str;
		Algebra_Node* node;
		if (c == "exp") node = func_6a(P, D, c);
		else if (c == "ln") node = func_7a(P, D, c);
		else if (c == "sin")  node = func_8a(P, D, c);
		else if (c == "cos") node = func_9a(P, D, c);
		else if (c == "tg") node = func_10a(P, D, c);
		else if (c == "ctg") node = func_11a(P, D, c);
		else if (c == "arcsin") node = func_12a(P, D, c);
		else if (c == "arccos") node = func_13a(P, D, c);
		else if (c == "arctg") node = func_14a(P, D, c);
		else if (c == "arcctg") node = func_15a(P, D, c);
		else if (c == "sh") node = func_16a(P, D, c);
		else if (c == "ch") node = func_17a(P, D, c);
		else if (c == "th") node = func_18a(P, D, c);
		else if (c == "cth") node = func_19a(P, D, c);
		else if (c == "arsh") node = func_20a(P, D, c);
		else if (c == "arch") node = func_21a(P, D, c);
		else if (c == "arth") node = func_22a(P, D, c);
		else if (c == "arcth") node = func_23a(P, D, c);
	}
		
}
