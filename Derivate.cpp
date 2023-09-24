
#include "Derivate.h"


#define DEBUG 0
#define X "x" // опеределение глобальной переменной типа char, переменная по которой дифференцируем.

/*
* Обозначения : Символы для замены строке : p - первый операнд ,  q - второй операнд , D - производная первого операнда , d - производная второго операнда.
*/

using namespace std;


Algebra_Node* func_1(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept* W)
{ // ['+' , '-' ]
	if (!(CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		Algebra_Node* Q;
		Q = SetNode('+');
		Algebra_Node& node = *Q;
		node.addLeftNode(D[1]);
		node.addRightNode(D[0]);
		return Q;
	}
	else if (!(CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{
		return D[1];
	}
	else if ((CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		if (c == '+')
		{
			return D[0];
		}
		else if (c == '-')
		{
			Algebra_Node* Q[2];
			Q[0] = SetNode('+'); // # Вычисление на этапе компиляции.
			Algebra_Node& node = *(Q[0]);
			// =================================
			Q[1] = SetNode(-1); // #
			Algebra_Node& node_2 = *(Q[1]);
			node.addLeftNode(Q[1]);
			node.addRightNode(D[0]);
			return Q[0];
		}
	}
	else if ((CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{
		Algebra_Node* Q = SetNode(0);
		Algebra_Node& node = *Q;
		return Q;
	}
}

Algebra_Node* func_1a(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{ // ['+' , '-' ]
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		if (c == '+')
		{
			const string s = "D+d";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[0] , W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1] , W);
		}
		else if (c == '-')
		{
			const string s = "D-d";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[0] , W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
		}

	}
	else if (!(CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{
		const string s = "D";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	}
	else if ((CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		if (c == '+')
		{
			const string s = "d";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W); // При выходе из функции параметр T остался прежним.
			if (DEBUG) while (0);
		}
		else if (c == '-')
		{
			const string s = "(-1)*d";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
			if (DEBUG) while (0);
		}
	}
	else if ((CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{
		const string s = "0";
		T = SetOperatorTree(s);
	}

	return T;
}

Algebra_Node* func_1b(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{
	Algebra_Node* T = SetNode("0");
	if (c == '+')
	{
		const string s = "D+d";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
	}
	else if(c == '-')
	{
		const string s = "D-d";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
	}
	return T;
}

Algebra_Node* func_2(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{ // ['*']

	if (!(CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		if (!(CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
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
		if (!(CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
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
		if ((CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
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
		if ((CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
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
	if (!(CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{
		if (CE(D[1]->data.value, 1))
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
	if ((CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		if (get<int>(D[0]->data.value) == 1)
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
	if ((CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{
		Algebra_Node* Q = SetNode("0");
		return Q;
	}

}

Algebra_Node* func_2a(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{ // ['*']
	Algebra_Node* T = SetNode("0");
	// Символы для замены строке : p - первый операнд ,  q - второй операнд , D - производная первого операнда , d - производная второго операнда.
	if (!(CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		if (!(CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
		{
			const string s = "D*q+d*p";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[0], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
		if ((CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
		{
			const string s = "D*q+p";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
		if (!(CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
		{
			const string s = "q+p*d";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[0], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}

		}
		if ((CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
		{
			const string s = "q+p";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[0], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
	}
	if (!(CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{
		if (!(CE(D[1]->data.value, 1)))
		{ // Умножение на константу p.
			const string s = "d*p";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[0], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
		else
		{
			const string s = "p";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
	}
	if ((CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		if (!(CE(D[0]->data.value, 1)))
		{ // Умножение на константу q.
			const string s = "D*q";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
		else
		{
			const string s = "q";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[0], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
	}
	if ((CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{
		const string s = "0";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}

	return T;

}

Algebra_Node* func_2b(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{
	Algebra_Node* T = SetNode("0");
	const string s = "D*q+d*p";
	T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[1], W);
	T = TreeRExprReplaceOnSubTreeD(T, "q", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[1], W);
	T = TreeRExprReplaceOnSubTreeD(T, "d", D[0], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}
	return T;
}


Algebra_Node* func_3(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{ // ['/']
	if (!(CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		if (!(CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
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
		if ((CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
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
		if (!(CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
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
		if ((CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
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
	if (!(CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{
		if (!(CE(D[0]->data.value, 1)))
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
	if ((CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		if (!(CE(D[1]->data.value, 1)))
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
	if ((CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{
		Algebra_Node* Q = SetNode("0");
		return Q;
	}
}

Algebra_Node* func_3a(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{ // ['/']
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		if (!(CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
		{
			const string s = "(D*q-d*p)/q^2";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
		else if ((CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
		{
			const string s = "(q-d*p)/q^2";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
		else if (!(CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
		{
			const string s = "(D*q-p)/q^2";;
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}

		}
		else if ((CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
		{
			const string s = "(q-p)/q^2";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
	}
	else if ((CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{ // Деление константы p на q.
		if (!(CE(D[1]->data.value, 1)))
		{
			const string s = "(-1)*p*d/q^2";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}

		}
		else
		{
			const string s = "(-1)*p/q^2";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		};
	}
	else if (!(CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{ // Деление p на константу q.
		if (!CE(D[0]->data.value, 1))
		{
			const string s = "D/q";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}

		}
		else
		{
			const string s = "1/q";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		};
	}
	else if ((CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{
		const string s = "0";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}
	return T;
}

Algebra_Node* func_3b(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{
	Algebra_Node* T = SetNode("0");
	const string s = "(D*q-d*p)/q^2";
	T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}
	return T;
}

Algebra_Node* func_4(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{ // ['^']
	if (!(CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		if (!(CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1))) // f(x)^g(x)
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
		if (!(CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
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
		if ((CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
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
		if ((CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
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
	if (!(CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{ // # f(x)^c - степенная функция , f(x) = x^n -> f'(x) = n*x^(n-1), f(x) = P[1], n = P[0]
		Token& T = P[0]->data;
		if (!(CE(D[1]->data.value, 1)))
		{
			if (T.type == Token::Type::Integer || T.type == Token::Type::Real)
			{
				int n = 0;
				if (T.type == Token::Type::Integer)  n = get<int>(T.value); // Извлекаем константный показатель степени.
				else if (T.type == Token::Type::Real) n = get<double>(T.value);
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
			if (!(CE(D[0]->data.value, 1)))
			{
				if (T.type == Token::Type::Integer || T.type == Token::Type::Real)
				{
					int n = 0;
					if (T.type == Token::Type::Integer)  int n = get<int>(T.value); // Извлекаем константный показатель степени.
					else if (T.type == Token::Type::Real) int n = get<double>(T.value);
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
				if (T.type == Token::Type::Integer || T.type == Token::Type::Real)
				{
					int n = 0;
					if (T.type == Token::Type::Integer)  int n = get<int>(T.value); // Извлекаем константный показатель степени.
					else if (T.type == Token::Type::Real) int n = get<double>(T.value);
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
	if ((CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{ // c^f(x) - показательная функция , f(x) = a^x -> f'(x) = a^x*ln(a)
		// g(x) = a^f(x) -> g'(x) = a^f(x) * f'(x) * ln(a) , P[0] = f(x) , P[1] = a
		Token& T = P[1]->data;
		int a = 0;
		if (T.type == Token::Type::Integer)  a = get<int>(T.value); // Извлекаем константный показатель степени.
		else if (T.type == Token::Type::Real) a = get<double>(T.value);
		if (!(CE(D[1]->data.value, 0)))
		{
			if (T.type == Token::Type::Number || T.type == Token::Type::Integer || T.type == Token::Type::Real)
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
			if (T.type == Token::Type::Integer || T.type == Token::Type::Real)
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
	if ((CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{
		Algebra_Node* Q;
		Q = SetNode("0");
		return Q;
	}
}

Algebra_Node* func_4a(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{ // ['^']
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{
		if (!(CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
		{
			const string s = "p^q*(D*q/p +d*ln(p))";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}

		if ((CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
		{
			const string s = "p^q*(q/p +d*ln(p))";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
		if (!(CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
		{
			const string s = "p^q*(D*q/p + ln(p))";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}

		}
		if ((CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
		{
			const string s = "p^q*(q/p + ln(p))";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
	}
	if ((CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{ // Показательная функция
		if (!(CE(D[1]->data.value, 1)))
		{
			const string s = "p^q*ln(p)*d";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
		else
		{
			const string s = "p^q*ln(p)";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}

		}
	}
	if (!(CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{ // Степеннная функция
		if (!(CE(D[0]->data.value, 1)))
		{
			const string s = "D*q*p^(q-1)";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}

		}
		else
		{
			const string s = "q*p^(q-1)";
			T = SetOperatorTree(s);
			if (DEBUG) { 
				int index = W.index;  
				T = SetOperatorTree(s, index);  
				W.index = index; 
				vector<Token> es;
				TreeToPolish(T , es);
				vector<int> ks = CountIndex(es);
				while (0);
			}
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<int> ks = CountIndex(V); // Сбор индексов.
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
	}
	if ((CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{ // Константа в степени константа.
		const string s = "0";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}
	return T;
}

Algebra_Node* func_4b(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{ // ['^']
	const string s = "p^q*(D*q/p +d*ln(p))";
	Algebra_Node* T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}
	return T;
}


Algebra_Node* func_5(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{
	if (!(CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{ //  f(y) = log(y , x) = ln(y)/ln(x) ,  P[1] = x , P[0] = y
	  // f'(y) = (D(y) / y * ln(x) - D(x) / x * ln(y)) / ln^2(x)
		if ((CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
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

			if ((CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
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
		if ((CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
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
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
			return Q[0];
		}
		if (!(CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
		{
			if (!(CE(D[0]->data.value, 1)))
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
					vector<Token> kh(V.rbegin(), V.rend());
					string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
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
					vector<Token> kh(V.rbegin(), V.rend());
					string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
					while (0); // Для точки останова.
				}
				return Q[0];
			}
		}
		if ((CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
		{
			Algebra_Node* Q;
			Q = SetNode("0");
			return Q;
		}
	}
}

Algebra_Node* func_5a(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{ //  f(y) = log(y , x) = ln(y)/ln(x) ,  P[1] = x , P[0] = y
	  // f'(y) = (D(y) / y * ln(x) - D(x) / x * ln(y)) / ln^2(x)
		if (!(CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
		{
			const string s = "(d/q*ln(p)-D/p*ln(q))/(ln(p))^2"; // log(sin(x) , cos(x) ) 'sin(x)*(-1)*(ln(sin(x)))/(cos(x))-cos(x)*(ln(cos(x)))/(sin(x))/(ln(sin(x)))^2'
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
		if (!(CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
		{
			const string s = "(ln(p)/q-D/p*ln(q))/(ln(p))^2";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
		if ((CE(D[0]->data.value, 1)) && !(CE(D[1]->data.value, 1)))
		{
			const string s = "(d/q*ln(p)-ln(q)/p)/(ln(p))^2";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
		if ((CE(D[0]->data.value, 1)) && (CE(D[1]->data.value, 1)))
		{
			const string s = "(ln(p)/q-ln(q)/p)/(ln(p))^2";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}

		}

	}
	if ((CE(D[0]->data.value, 0)) && !(CE(D[1]->data.value, 0)))
	{ // f(y) = log(c , y) - логарифм по постоянному основанию степени.
		  //  f'(y) = D(y)/(y * ln(c)) , P[0] = c , P[1] = y
		if (!(CE(D[1]->data.value, 1)))
		{
			const string s = "d/(q*ln(p))";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}

		}
		else
		{
			const string s = "1/(q*ln(p))";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}

		}
	}
	if (!(CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{ // Логарифм от постоянного числа по переменному основнию.
		if (!(CE(D[0]->data.value, 1)))
		{
			const string s = "(-1)*D*ln(q)/(p*(ln(p))^2)";  
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}
		}
		else
		{
			const string s = "(-1)*ln(q)/(p*(ln(p))^2)";
			T = SetOperatorTree(s);
			if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
			T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
			T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
			if (DEBUG)
			{
				vector<Token> V;
				TreeToPolish(T, V);
				vector<Token> kh(V.rbegin(), V.rend());
				string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
				while (0); // Для точки останова.
			}

		}
	}
	if ((CE(D[0]->data.value, 0)) && (CE(D[1]->data.value, 0)))
	{ // Логарифм постоянного числа по постоянной степени.
		const string s = "0";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}

	return T;
}

Algebra_Node* func_5b(Algebra_Node* P[2], Algebra_Node* D[2], char c, Debug_concept& W)
{
	const string s = "(d/q*ln(p)-D/p*ln(q))/(ln(p))^2"; // log(sin(x) , cos(x) ) 'sin(x)*(-1)*(ln(sin(x)))/(cos(x))-cos(x)*(ln(cos(x)))/(sin(x))/(ln(sin(x)))^2'
	Algebra_Node* T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "q", P[1], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "d", D[1], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}
	return T;
}


Algebra_Node* func_6(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{
	if (!(CE(D[0]->data.value, 1)))
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
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
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
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q;
	}
}

Algebra_Node* func_6a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['exp']
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 1)))
	{
		const string s = "exp(p)*D";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}

	}
	else
	{
		const string s = "exp(p)";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}

	}

	return T;
}


Algebra_Node* func_7(Algebra_Node* P[1], Algebra_Node* D[1],  Debug_concept& W)
{ // ['ln']
	if (!(CE(D[0]->data.value, 1)))
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
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q;
	}
}

Algebra_Node* func_7a(Algebra_Node* P[1], Algebra_Node* D[1],  Debug_concept& W)
{ // ['ln']
	Algebra_Node* T = SetNode("0");
	const string s = "D/p";
	T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}

	return T;
}

Algebra_Node* func_8(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['sin']
	if (!(CE(D[0]->data.value, 1)))
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
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
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
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q;
	}
}

Algebra_Node* func_8a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['sin']
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 1)))
	{
		const string s = "D*cos(p)";
		T = SetOperatorTree(s);
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}
	else
	{
		const string s = "cos(p)";
		T = SetOperatorTree(s);
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}

	}
	return T;
}

Algebra_Node* func_9(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['cos']
	if (!(CE(D[0]->data.value, 1)))
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
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
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
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q[0];
	}
}

Algebra_Node* func_9a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['cos']
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 1)))
	{
		const string s = "(-1)*D*sin(p)";
		T = SetOperatorTree(s);
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}
	else
	{
		const string s = "(-1)*sin(p)";
		T = SetOperatorTree(s);
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}

	}

	return T;
}

Algebra_Node* func_10(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
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
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}
	return Q[0];
}

Algebra_Node* func_10a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['tg']
	Algebra_Node* T = SetNode("0");

	const string s = "D/(cos(p))^2";
	T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}

	return T;
}

Algebra_Node* func_11(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['ctg']
	if (!(CE(D[0]->data.value, 1)))
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
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
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
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
		return Q[0];
	}
}

Algebra_Node* func_11a(Algebra_Node* P[1], Algebra_Node* D[1],  Debug_concept& W)
{ // ['ctg']
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 1)))
	{
		const string s = "(-1)*D/(sin(p))^2";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}

	}
	else
	{
		const string s = "(-1)/(cos(p))^2";
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = SetOperatorTree(s);
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}

	}

	return T;
}

Algebra_Node* func_12(Algebra_Node* P[1], Algebra_Node* D[1],  Debug_concept& W)
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
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}
	return Q[0];
}

Algebra_Node* func_12a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['arcsin']
	Algebra_Node* T = SetNode("0");

	const string s = "D/(1-p^2)^(1/2)";
	T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}

	return T;
}

Algebra_Node* func_13a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['arccos']
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 1)))
	{
		string s = "(-1)*D/(1-p^2)^(1/2)";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}
	else
	{
		string s = "(-1)/(1-p^2)^(1/2)";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}

	}

	return T;
}

Algebra_Node* func_14a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['arctg']
	Algebra_Node* T = SetNode("0");

	string s = "D/(1+p^2)";
	T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}

	return T;
}

Algebra_Node* func_15a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['arcctg']
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 1)))
	{
		string s = "(-1)*D/(1+p^2)";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}
	else
	{
		string s = "(-1)/(1+p^2)";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}
	return T;
}

Algebra_Node* func_16a(Algebra_Node* P[1], Algebra_Node* D[1],  Debug_concept& W)
{ // ['sh']
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 1)))
	{
		string s = "D*ch(p)";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}
	else
	{
		string s = "ch(p)";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}

	}

	return T;
}

Algebra_Node* func_17a(Algebra_Node* P[1], Algebra_Node* D[1],  Debug_concept& W)
{ // ['ch']
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 1)))
	{
		string s = "(-1)*D*sh(p)";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}
	else
	{
		string s = "(-1)*sh(p)";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}

	return T;
}

Algebra_Node* func_18a(Algebra_Node* P[1], Algebra_Node* D[1],  Debug_concept& W)
{ // ['th']
	Algebra_Node* T = SetNode("0");

	string s = "D/(ch(p))^2";
	T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}

	return T;
}

Algebra_Node* func_19a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['cth']
	Algebra_Node* T = SetNode("0");

	if (!(CE(D[0]->data.value, 1)))
	{
		string s = "D/(ch(p))^2";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}
	else
	{
		string s = "(-1)*D/(ch(p))^2";
		T = SetOperatorTree(s);
		if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
		T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
		T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
		if (DEBUG)
		{
			vector<Token> V;
			TreeToPolish(T, V);
			vector<Token> kh(V.rbegin(), V.rend());
			string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
			while (0); // Для точки останова.
		}
	}

	return T;
}

Algebra_Node* func_20a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['arsh']
	Algebra_Node* T = SetNode("0");

	string s = "D/(1+p^2)^(1/2)";
	T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}

	return T;
}

Algebra_Node* func_21a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['arch']
	Algebra_Node* T = SetNode("0");

	string s = "D/(p^2-1)^(1/2)";
	T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}

	return T;
}

Algebra_Node* func_22a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['arth']
	Algebra_Node* T = SetNode("0");

	string s = "D/(1-p^2)";
	T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}

	return T;
}

Algebra_Node* func_23a(Algebra_Node* P[1], Algebra_Node* D[1], Debug_concept& W)
{ // ['arcth']
	Algebra_Node* T = SetNode("0");
	string s = "D/(1-p^2)";
	T = SetOperatorTree(s);
	if (DEBUG) { int index = W.index;  T = SetOperatorTree(s, index);  W.index = index; }
	T = TreeRExprReplaceOnSubTreeD(T, "p", P[0], W);
	T = TreeRExprReplaceOnSubTreeD(T, "D", D[0], W);
	if (DEBUG)
	{
		vector<Token> V;
		TreeToPolish(T, V);
		vector<Token> kh(V.rbegin(), V.rend());
		string r = PostfixToInfix(kh); // В виде строки лучше обозримо.
		while (0); // Для точки останова.
	}

	return T;
}

Algebra_Node* DerivateFunc(Algebra_Node* root , Debug_concept& W) // Следить , чтобы у каждой ветви было возвращающие значение.
{
	Token& T = root->data;
	int index = W.index;
	if (DEBUG)
	{
		W.call_order++;
	}
	if (T.type == Token::Type::Algebra)
	{
		int m;
		if (T.ToString() == X)  m = 1;
		else m = 0;
		Algebra_Node* node = SetNode(m);
		if (DEBUG) node = SetNode(m, index);
		return node;
	}
	else if (T.type == Token::Type::Number || T.type == Token::Type::Real || T.type == Token::Type::Integer)
	{
		Algebra_Node* node = SetNode(0);
		if (DEBUG) node = SetNode(0, index);
		return node;
	}
	else if (f_opr_two(T))
	{
		Algebra_Node* P[2]; // Сюда сохраняются первый и второй операнд.
		Algebra_Node* D[2]; // Сюда сохраняются соответствующие производные этих операндов.
		P[0] = _CloneTree(root->left);
		P[1] = _CloneTree(root->right);
		for (int i = 0; i < 2; i++) D[i] = DerivateFunc( _CloneTree(P[i]) , W);
		string v;
		if (DEBUG)
		{
			cout << endl;
			string r[2];
			vector<Token> V[2];
			for (int i = 0; i < 2; i++)
			{
				TreeToPolish(D[i], V[i]);
				vector<Token> es(V[0].rbegin(), V[0].rend());
				vector<int> ks = CountIndex(V[0]);
				r[i] = PostfixToInfix(es);
				while (0); // Для точки останова.

			}
			TreeToPolish(root, V[0]);
			reverse(V[0].begin(), V[0].end()); // Не работает reverse()
			vector<Token> ks(V[0].rbegin(), V[0].rend());
			v = PostfixToInfix(ks); // Все поддерево.
			while (0); // Для точки останова.

		}
		char c = '0';
		Algebra_Node* node;
		if (T.type == Token::Type::Operator)
		{
			c = get<char>(T.value);
			switch (c)
			{
			    case '+': { node = func_1a(P, D, c, W); break; }
			    case '-': { node = func_1a(P, D, c, W); break; }
			    case '*': { node = func_2a(P, D, c, W); break; }
			    case '/': { node = func_3a(P, D, c, W); break;  }
			    case '^': { node = func_4a(P, D, c, W); break;  }
				default:  { node = SetNode(0);  }
			}
		}
		else if (T.type == Token::Type::Function)
		{
			if ( get<Token::Function>(T.value) == Token::Function::LOG ){ node = func_5a(P, D, c, W); } // func_5b не работает.
		}
		if (DEBUG) { 
			deque<Token> fs; 
			TreeToPolish(node, fs);  
			vector<int> kh = CountIndex(fs); // Проверка верности вычисления численым диффренцированием.
			Algebra_Tree A = Algebra_Tree(root); // Исходная функция 
			Algebra_Tree B = Algebra_Tree(node); // Ее производная для проверки.
			double x = 2.0;
			double y_0, y_1;
			vector<tuple<double, double>> ph;
			y_0 = Numerical_Differentiation(A, x, pow(10, -4), X);
			y_1 = B.FunctionValue_T(x, X);
			ph.push_back(make_tuple(y_0, y_1));
			while (0); // Для точки останова.
			double t = (y_1 - y_0) / (y_0 + y_1);
			if (abs(t) > pow(10, 4))
			{
				set<int> e_box = W.red;
				int index = node->data.index;
				e_box.insert(index);
			}
			int m = W.call_order;
			map<int, set<int>> ds = W.colored;
			if (!ds.count(m)) ds[m] = set<int>();
			// Выполнить union для set()
			for (const auto& p : kh) {
				ds[m].insert(p);
			}
		}
		return node;

	}
	else if (f_opr_one(T))
	{
		Algebra_Node* P[1]; // Сюда сохраняются первый и второй операнд.
		Algebra_Node* D[1]; // Сюда сохраняются соответствующие производные этих операндов.
		P[0] = root->left;
		D[0] = DerivateFunc(P[0] , W);
		string v;
		if (DEBUG)
		{
			cout << endl;
			string r;
			vector<Token> V;
			TreeToPolish(D[0], V);
			vector<Token> ks(V.rbegin(), V.rend());
			vector<int> es = CountIndex(V);
			r = PostfixToInfix(ks);
			TreeToPolish(root, V);
			vector<Token> kh(V.rbegin(), V.rend());
			v = PostfixToInfix(kh); // Все поддерево.

		}
		if (T.type == Token::Type::Function)
		{
			Token::Function c = get<Token::Function>(T.value);
			Algebra_Node* node = SetNode(0);
			switch (c)
			{
			case Token::Function::EXP: { node = func_6a(P, D, W); break;  }
			case Token::Function::LN: {  node = func_7a(P, D, W); break;  }
			case Token::Function::SIN: { node = func_8a(P, D, W); break;  }
			case Token::Function::COS: { node = func_9a(P, D, W); break;  }
			case Token::Function::TG: { node = func_10a(P, D, W); break;  }
			case Token::Function::CTG: { node = func_11a(P, D, W); break;  }
			case Token::Function::ARCSIN: { node = func_12a(P, D, W); break;  }
			case Token::Function::ARCCOS: { node = func_13a(P, D, W); break;  }
			case Token::Function::ARCTG: { node = func_14a(P, D, W); break;  }
			case Token::Function::ARCCTG: { node = func_15a(P, D, W); break;  }
			case Token::Function::SH: { node = func_16a(P, D, W); break;  }
			case Token::Function::CH: { node = func_17a(P, D, W); break;  }
			case Token::Function::TH: { node = func_18a(P, D, W); break;  }
			case Token::Function::CTH: { node = func_19a(P, D, W); break;  }
			case Token::Function::ARSH: { node = func_20a(P, D, W); break;  }
			case Token::Function::ARCH: { node = func_21a(P, D, W); break;  }
			case Token::Function::ARTH: { node = func_22a(P, D, W); break;  }
			case Token::Function::ARCTH: { node = func_23a(P, D, W); break;  }
			default: { node = SetNode(0);  }
			}
			if (DEBUG)
			{
				deque<Token> fs;
				TreeToPolish(node, fs);
				vector<int> kh = CountIndex(fs); // Проверка верности вычисления численым диффренцированием.
				Algebra_Tree A = Algebra_Tree(root); // Исходная функция 
				Algebra_Tree B = Algebra_Tree(node); // Ее производная для проверки.
				double x = 2.0;
				double y_0, y_1;
				vector<tuple<double, double>> ph;
				y_0 = Numerical_Differentiation(A, x, pow(10, -4), X);
				y_1 = B.FunctionValue_T(x, X);
				ph.push_back(make_tuple(y_0, y_1));
				double t = (y_1 - y_0) / (y_0 + y_1);
				if (abs(t) > pow(10, 4))
				{
					set<int> e_box = W.red;
					int index = node->data.index;
					e_box.insert(index);
				}
				int m = W.call_order;
				map<int, set<int>> ds = W.colored;
				if (!ds.count(m)) ds[m] = set<int>();
				// Выполнить union для set()
				for (const auto& p : kh) {
					ds[m].insert(p);
				}
				while (0); // Для точки останова.
			}
			return node;
		}
	}
	else
	{
		Algebra_Node* node = SetNode(0);
		return node;
	}

}

Algebra_Node* DerivateFunction(Algebra_Node* root , Debug_concept& W)
{
	W.call_order = 0;
	Algebra_Node* second_root = DerivateFunc(root , W);
	if (DEBUG)
	{
		const int MODE = 0;
		map<int, set<int>> ds = W.colored;
		set<int> white = W.white;
		set<int> orange = W.orange;
		for (const auto& pair : ds) {
			int p = pair.first;
			if (p % 2 == 0) {
				for (const auto& element : pair.second) {
					white.insert(element);
				}
			}
			else if (p % 2 == 1) {
				for (const auto& element : pair.second) {
					orange.insert(element);
				}
			}
		}
	}
	W = W;
	while (0); // Для точки останова.
	return second_root;
}

Algebra_Node* DerivateFunction(Algebra_Node* root)
{
	Debug_concept W = Debug_concept();
	Algebra_Node* second_root = DerivateFunction(root, W);
	return second_root;
}


double Numerical_Differentiation(Algebra_Tree& treeExpr, double t, double h, string x) {
	// 
	// x - символ переменных для численного дифееренцирования
	// t - точка для численного дифференцирования.
	// h - шаг для численного дифференцирования.
	const bool LOCAL_DEBUG = false;
	double dy = 0;
	double P[] = { -1. / 12 , 8. / 12 , -8. / 12 , 1. / 12 };
	int Q[] = { 2 , 1 , -1 , -2 };
	int m = 1;
	for (int i = 0; i < 4; i++) {
		double k = P[i];
		int n = Q[i];
		double y = treeExpr.FunctionValue_T(t + n * h, "x");
		if (LOCAL_DEBUG)
		{
			treeExpr.TreeToPolish_T();
			vector<Token> es = treeExpr.polish;
			double y_1 = FunctionValue(es, t + n * h, "x");
			while (0);
		}
		y = k * y / pow(h, m);
		dy += y;
		// Здесь "x" переменная по которой берется произодная.
	}
	return dy;
}



