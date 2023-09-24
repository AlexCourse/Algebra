#include "Shanting_yard.h"
#include <iostream>
#include <vector>
#include <stack>
#define DEBUG 1


deque<Token> shuntingYard(const deque<Token>& tokens) {
	deque<Token> eh;
	stack<Token> st;

	// Пока есть токены для чтения:
	for (auto T : tokens) {
		// Читать токен
		if (DEBUG)
		{
			eh = eh;
			st = st;
			while (0);  // Для точки останова
		}
		switch (T.type) {
		case Token::Type::Number:
			eh.push_back(T); // Если токен представляет собой число, то добавьте его в очередь вывода
			break;
		case Token::Type::Integer:
			eh.push_back(T); // Если токен представляет собой число, то добавьте его в очередь вывода
			break;
		case Token::Type::Real:
			eh.push_back(T); // Если токен представляет собой число, то добавьте его в очередь вывода
			break;
		case Token::Type::Ration:
			eh.push_back(T);
			break;
		case Token::Type::ComplexNumber:
			eh.push_back(T);
			break;
		case Token::Type::Algebra:
			eh.push_back(T);
			break;
		case Token::Type::Function:
			st.push(T);
			break;
		case Token::Type::Comma:
		{
			bool B = false;
			while (!st.empty())
			{
				Token T_1 = st.top();
				if (T_1.type == Token::Type::LeftParen) { B = true; break; }
				else
				{
					eh.push_back(T_1);
					st.pop();
				}
			}
			while (0);
			break;

		}
		case Token::Type::Operator:
		{
			// Если токен является оператором, o1, то:
			const auto o1 = T;
			// пока есть токен оператора,
			while (!st.empty()) {

				// o2, в верхней части стека, и
				const auto o2 = st.top();

				// либо o1 является левоассоциативным, и его приоритет равен
				// *меньше или равно* значению o2,
			   // или o1, если ассоциативно справа, и имеет приоритет

				if (
					(!o1.rightAssociative && o1.precedence <= o2.precedence)
					|| (o1.rightAssociative && o1.precedence < o2.precedence) || o2.type == Token::Type::Function
					) {
					if (o2.type == Token::Type::RightParen) break;
					st.pop();
					eh.push_back(o2);
					continue;
				}
				break;
			}
			st.push(o1);
		}
		break;

		case Token::Type::LeftParen:
			st.push(T);
			break;

		case Token::Type::RightParen:
		{
			bool match = false;

			while (!st.empty() && st.top().type != Token::Type::LeftParen) {
				eh.push_back(st.top());
				st.pop();
				match = true;
			}
			if (!st.empty() && st.top().type == Token::Type::LeftParen) st.pop();
			if (!match && st.empty()) {
				printf("RightParen error (%s)\n", T.ToString());
				return {};
			}
			break;
		}
		default:
			printf("error (%s)\n", get<string>(T.value));
			return {};
		}
	}
	while (!st.empty()) {
		if (st.top().type == Token::Type::LeftParen) {
			printf("Mismatched parentheses error\n");
			return {};
		}
		eh.push_back(std::move(st.top()));
		st.pop();
	}

	return eh;
}

double PolishCalculation(deque<Token> es)
{
	stack<double> st;
	vector<string> cst;
	string s;
	int n = es.size();
	if (n == 0) return 0;

	while (!es.empty()) {
		if (DEBUG) st = st;
		string op;
		Token T = es.front();
		es.pop_front();
		switch (T.type) {
		case Token::Type::Integer:
			st.push(get<int>(T.value));
			if (DEBUG) op = "Push " + T.ToString();
			break;
		case Token::Type::Real:
			st.push(get<double>(T.value));
			if (DEBUG) op = "Push " + T.ToString();
			break;
		case Token::Type::Algebra:
		{
			cst.push_back(get<string>(T.value));
			if (DEBUG) op = "Push" + T.ToString();

		}
		case Token::Type::Operator:
		{
			if (f_opr_two(T))
			{
				const auto p = st.top();
				st.pop();
				const auto q = st.top();
				st.pop();
				switch (get<string>(T.value)[0]) {
				default:
					printf("Operator error [%s]\n", get<string>(T.value));
					// exit(0);
					break;
				case '^':
					st.push(static_cast<double>(pow(q, p)));
					break;
				case '*':
					st.push(q * p);
					break;
				case '/':
					st.push(q / p);
					break;
				case '+':
					st.push(q + p);
					break;
				case '-':
					st.push(q - p);
					break;
				}

				op = "Push " + to_string(q) + " " + T.ToString() + " " + to_string(p);
				break;
			}
		}
		case Token::Type::Function:
		{
			if (f_opr_one(T))
			{
				const auto x = st.top();
				st.pop();
				string c = get<string>(T.value);
				if (c == "exp") { st.push(exp(x)); }
				if (c == "ln") { st.push(log1p(x)); }
				if (c == "sin") { st.push(sin(x)); }
				if (c == "cos") { st.push(cos(x)); }
				if (c == "tg") { st.push(tan(x)); }
				if (c == "ctg") { st.push(1 / tan(x)); }
				if (c == "arcsin") { st.push(asin(x)); }
				if (c == "arccos") { st.push(acos(x)); }
				if (c == "arctg") { st.push(atan(x)); }
				if (c == "arcctg") { st.push(atan(1 / x)); }
				if (c == "sh") { st.push(sinh(x)); }
				if (c == "ch") { st.push(cosh(x)); }
				if (c == "th") { st.push(tanh(x)); }
				if (c == "cth") { st.push(1 / tanh(x)); }
				if (c == "arsh") { st.push(asinh(x)); }
				if (c == "arch") { st.push(acosh(x)); }
				if (c == "arth") { st.push(atanh(x)); }
				if (c == "arcth") { st.push(atanh(1 / x)); }
				if (c == "abs") { st.push(abs(x)); }

			}
			if (f_opr_two(T))
			{
				const auto p = st.top();
				st.pop();
				const auto q = st.top();
				st.pop();
				string c = get<string>(T.value);
				if (c == "pow") { st.push(pow(q, p)); }
				if (c == "log") { st.push(log(p) / log(q)); }
			}
		}
		default:
			printf("Token error\n");
			// exit(0);
		}

	}
	return st.top();

}

double PolishCalculation(const vector<Token> es)
{
	stack<double> st;
	vector<string> cst;
	string s;
	vector<Token> eh(es.rbegin(), es.rend());
	int n = es.size();
	if (n == 0) return 0;
	while (0);

	while (!eh.empty()) {
		if (DEBUG) st = st;
		string op;
		Token T = eh.back();
		eh.pop_back(); // странно удаляется всегда с конца у вектора.
		switch (T.type) {
		case Token::Type::Integer:
			st.push(get<int>(T.value));
			if (DEBUG) op = "Push " + T.ToString();
			break;
		case Token::Type::Real:
			st.push(get<double>(T.value));
			if (DEBUG) op = "Push " + T.ToString();
			break;
		case Token::Type::Algebra:
		{
			cst.push_back(get<string>(T.value));
			if (DEBUG) op = "Push" + T.ToString();

		}
		case Token::Type::Operator:
		{
			if (f_opr_two(T))
			{
				const auto p = st.top();
				st.pop();
				const auto q = st.top();
				st.pop();
				switch (get<string>(T.value)[0]) {
				default:
					printf("Operator error [%s]\n", get<string>(T.value));
					// exit(0);
					break;
				case '^':
					st.push(static_cast<double>(pow(q, p)));
					break;
				case '*':
					st.push(q * p);
					break;
				case '/':
					st.push(q / p);
					break;
				case '+':
					st.push(q + p);
					break;
				case '-':
					st.push(q - p);
					break;
				}

				op = "Push " + to_string(q) + " " + T.ToString() + " " + to_string(p);
				break;
			}
		}
		case Token::Type::Function:
		{
			if (f_opr_one(T))
			{
				const auto x = st.top();
				st.pop();
				string c = get<string>(T.value);
				if (c == "exp") { st.push(exp(x)); }
				if (c == "ln") { st.push(log1p(x)); }
				if (c == "sin") { st.push(sin(x)); }
				if (c == "cos") { st.push(cos(x)); }
				if (c == "tg") { st.push(tan(x)); }
				if (c == "ctg") { st.push(1 / tan(x)); }
				if (c == "arcsin") { st.push(asin(x)); }
				if (c == "arccos") { st.push(acos(x)); }
				if (c == "arctg") { st.push(atan(x)); }
				if (c == "arcctg") { st.push(atan(1 / x)); }
				if (c == "sh") { st.push(sinh(x)); }
				if (c == "ch") { st.push(cosh(x)); }
				if (c == "th") { st.push(tanh(x)); }
				if (c == "cth") { st.push(1 / tanh(x)); }
				if (c == "arsh") { st.push(asinh(x)); }
				if (c == "arch") { st.push(acosh(x)); }
				if (c == "arth") { st.push(atanh(x)); }
				if (c == "arcth") { st.push(atanh(1 / x)); }
				if (c == "abs") { st.push(abs(x)); }

			}
			if (f_opr_two(T))
			{
				const auto p = st.top();
				st.pop();
				const auto q = st.top();
				st.pop();
				string c = get<string>(T.value);
				if (c == "pow") { st.push(pow(q, p)); }
				if (c == "log") { st.push(log(p) / log(q)); }
			}
		}
		default:
			printf("Token error\n");
			// exit(0);
		}

	}
	return st.top();

}


deque<Token> FToPolish(string expr)
{
	deque<Token> fh, eh;
	fh = exprToTokens(expr);
	Tokenize_u_minus(fh);
	eh = shuntingYard(fh);
	return eh;
}

double FunctionValue(deque<Token> fh, double x, string symbol)
{ // Подстановка в функцию заданную Обратной Польской Нотацией.
	// x - подставляемое значение.
	// symbol - строковой символ , который заменяем.
	deque<Token>::iterator iter;
	deque<Token> kh;
	for (iter = fh.begin(); iter != fh.end(); iter++)
	{
		if (CE(iter->value, symbol))
		{
			Token T = SetToken(x);
			kh.push_back(T);
		}
		else
		{
			Token T = *iter;
			kh.push_back(T);
		}
	}
	double r = PolishCalculation(kh);
	return r;
}


double FunctionValue(vector<Token> fh, double x, string symbol)
{ // Подстановка в функцию заданную Обратной Польской Нотацией.
	// x - подставляемое значение.
	// symbol - строковой символ , который заменяем.
	vector<Token>::iterator iter;
	vector<Token> kh;
	for (iter = fh.begin(); iter != fh.end(); iter++)
	{
		if (CE(iter->value, symbol))
		{
			Token T = SetToken(x);
			kh.push_back(T);
		}
		else
		{
			Token T = *iter;
			kh.push_back(T);
		}
	}
	double r = PolishCalculation(kh);
	return r;
}

deque<Token> ReplaceElementInPolish(deque<Token> fh, double x, string symbol)
{ // Подстановка в функцию заданную Обратной Польской Нотацией.
	// x - подставляемое значение.
	// symbol - строковой символ , который заменяем.
	deque<Token>::iterator iter;
	deque<Token> kh;
	for (iter = fh.begin(); iter != fh.end(); iter++)
	{
		if (CE(iter->value, symbol))
		{
			Token T = SetToken(x);
			kh.push_back(T);
		}
		else
		{
			Token T = *iter;
			kh.push_back(T);
		}
	}
	return kh;
}


vector<Token> ReplaceElementInPolish(vector<Token> fh, double x, string symbol)
{ // Подстановка в функцию заданную Обратной Польской Нотацией.
	// x - подставляемое значение.
	// symbol - строковой символ , который заменяем.
	vector<Token>::iterator iter;
	vector<Token> kh;
	for (iter = fh.begin(); iter != fh.end(); iter++)
	{
		if (CE(iter->value, symbol))
		{
			Token T = SetToken(x);
			kh.push_back(T);
		}
		else
		{
			Token T = *iter;
			kh.push_back(T);
		}
	}
	return kh;
}