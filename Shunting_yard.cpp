#include "Shanting_yard.h"
#include <iostream>
#include <vector>
#include <stack>
#define DEBUG 1

using namespace std;


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
				char c = get<char>(T.value);
				switch (c) {
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
			break;
		}
		case Token::Type::Function:
		{
			if (f_opr_one(T))
			{
				const auto x = st.top();
				st.pop();
				Token::Function c = get<Token::Function>(T.value);
				switch (c)
				{
				case Token::Function::EXP: { st.push(exp(x)); break;  }
				case Token::Function::LN: { st.push(log(x));  break;  }
				case Token::Function::SIN: { st.push(sin(x));  break;  }
				case Token::Function::COS: { st.push(cos(x)); break;  }
				case Token::Function::TG: { st.push(tan(x)); break;  }
				case Token::Function::CTG: { st.push(1 / tan(x)); break;  }
				case Token::Function::ARCSIN: { st.push(asin(x)); break;  }
				case Token::Function::ARCCOS: { st.push(acos(x)); break;  }
				case Token::Function::ARCTG: { st.push(atan(x));  break;  }
				case Token::Function::ARCCTG: { st.push(atan(1 / x));  break;  }
				case Token::Function::SH: { st.push(sinh(x));  break;  }
				case Token::Function::CH: { st.push(cosh(x));  break; }
				case Token::Function::TH: { st.push(tanh(x));  break; }
				case Token::Function::CTH: { st.push(1 / tanh(x)); break;  }
				case Token::Function::ARSH: { st.push(asinh(x)); break; }
				case Token::Function::ARCH: { st.push(acosh(x));  break; }
				case Token::Function::ARTH: { st.push(atanh(x));  break;  }
				case Token::Function::ARCTH: { st.push(atanh(1 / x));  break;  }
				case Token::Function::ABS: { st.push(abs(x)); break;  }
				}
			}
			else if (f_opr_two(T))
			{
				const auto p = st.top();
				st.pop();
				const auto q = st.top();
				st.pop();
				Token::Function c = get<Token::Function>(T.value);
				switch (c)
				{
				    case Token::Function::POW: { st.push(pow(q, p)); break;  }
				    case Token::Function::LOG: { st.push(log(p) / log(q)); break;  }
				}
			}
			break;
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
				char c = get<char>(T.value);
				switch (c) {
				default:
					printf("Operator error [%s]\n", T.ToString());
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
			break;
		}
		case Token::Type::Function:
		{
			if (f_opr_one(T))
			{
				const auto x = st.top();
				st.pop();
				Token::Function c = get<Token::Function>(T.value);
				switch (c)
				{
				case Token::Function::EXP: { st.push(exp(x)); break;  }
				case Token::Function::LN: { st.push(log(x));  break;  }
				case Token::Function::SIN: { st.push(sin(x)); break;  }
				case Token::Function::COS: { st.push(cos(x)); break;  }
				case Token::Function::TG: { st.push(tan(x));  break;  }
				case Token::Function::CTG: { st.push(1 / tan(x)); break;  }
				case Token::Function::ARCSIN: { st.push(asin(x)); break;  }
				case Token::Function::ARCCOS: { st.push(acos(x)); break;  }
				case Token::Function::ARCTG: { st.push(atan(x)); break;  }
				case Token::Function::ARCCTG: { st.push(atan(1 / x)); break;  }
				case Token::Function::SH: { st.push(sinh(x)); break;  }
				case Token::Function::CH: { st.push(cosh(x)); break;  }
				case Token::Function::TH: { st.push(tanh(x)); break;  }
				case Token::Function::CTH: { st.push(1 / tanh(x)); break;  }
				case Token::Function::ARSH: { st.push(asinh(x)); break;  }
				case Token::Function::ARCH: { st.push(acosh(x)); break;  }
				case Token::Function::ARTH: { st.push(atanh(x)); break;  }
				case Token::Function::ARCTH: { st.push(atanh(1 / x)); break;  }
				case Token::Function::ABS: { st.push(abs(x)); break;  }
				}
			}
			else if (f_opr_two(T))
			{
				const auto p = st.top();
				st.pop();
				const auto q = st.top();
				st.pop();
				Token::Function c = get<Token::Function>(T.value);
				switch (c)
				{
				case Token::Function::POW: { st.push(pow(q, p));  break;  }
				case Token::Function::LOG: { st.push(log(p) / log(q)); break;  }
				}
			}
			break;
		}
		default:
			printf("Token error\n");
			// exit(0);
		}

	}
	return st.top();

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
// Проверка синтаксической корректности.
bool Check_Bracket_Matching(deque<Token> fh)
{ // Функция применяется после функции exprToTokens().
	int balance = 0;
	deque<Token>::iterator iter;
	for (iter = fh.begin(); iter != fh.end(); iter++)
	{
		Token token = *iter;
		if (token.type == Token::Type::LeftParen) balance ++;
		if (token.type == Token::Type::RightParen) balance--;
	}
	if (balance == 0) return true;
	else return false;
}

bool CheckBalance(deque<Token> fh)
{ // Функция применяется после функции exprToTokens().
	int balance = 1;
	deque<Token>::iterator iter;
	for (iter = fh.begin(); iter != fh.end(); iter++)
	{
		Token token = *iter;
		if (f_arg(token)) balance--;
		if (f_opr_two(token)) balance++;
		if (f_opr_one(token)){}
	}
	if (balance == 0) return true;
	else return false;
}

string PostfixToInfix(vector<Token>& fs)
{ // В первом параметре выражение в формате Обратной Польской нотации.
  // Результат возвращается во втором параметре в форме Инфиксной Записи.
	string p, q, s, t;
	reverse(fs.begin(), fs.end());
	stack<string> st;
	stack<int> st_opr; // Здесь сохраняются приоритеты операторов.
	int m, n;
	while (!fs.empty())
	{
		Token T = fs.back();
		fs.pop_back();
		// st_opr.push(0); // Для балансировки стека.
		if (T.type == Token::Type::Algebra)
		{
			s = T.ToString();
			st.push(s);
		}
		else if (T.type == Token::Type::Integer)
		{
			s = T.ToString();
			st.push(s);
		}
		else if (T.type == Token::Type::Real)
		{
			s = T.ToString();
			st.push(s);
		}
		else if (f_opr_two(T))
		{
			string f = T.ToString();
			q = st.top();
			st.pop();
			p = st.top();
			st.pop();
			m = T.precedence;
			bool ra = T.rightAssociative;
			for (int i = 0; i < 2; i++)
			{
				if (st_opr.empty()) break;
				n = st_opr.top();
				st_opr.pop();
				bool B = false;
				if (n < m && ra) B = true;
				if (n <= m && !ra) B = true;
				if (!B)
				{
					if (i == 0) p = "(" + p + ")";
					if (i == 1) p = "(" + q + ")";
				}
			}
			s = p + f + q;
			st.push(s);
			st_opr.push(m);

		}
		else if (f_opr_one(T))
		{
			string f = T.ToString();
			p = st.top();
			st.pop();
			s = f + "(" + p + ")";
			st.push(s);
		}

	}

	s = st.top();
	st.pop();
	return s;
}

string PostfixToInfix(deque<Token>& fs)
{ // В первом параметре выражение в формате Обратной Польской нотации.
  // Результат возвращается во втором параметре в форме Инфиксной Записи.
	string p, q, s, t;
	// reverse(fs.begin(), fs.end());
	stack<string> st;
	stack<int> st_opr; // Здесь сохраняются приоритеты операторов.
	int m, n;
	while (!fs.empty())
	{
		Token T = fs.front();
		fs.pop_front();
		st_opr.push(0); // Для балансировки стека.
		if (T.type == Token::Type::Algebra)
		{
			s = T.ToString();
			st.push(s);
		}
		else if (T.type == Token::Type::Integer || T.type == Token::Type::Real || T.type == Token::Type::Number)
		{
			s = T.ToString();
			st.push(s);
		}
		else if (f_opr_two(T))
		{
			string f = T.ToString();
			p = st.top();
			st.pop();
			q = st.top();
			st.pop();
			n = st_opr.top();
			m = T.precedence;
			bool ra = T.rightAssociative;
			st_opr.pop();
			bool B = false;
			if (n < m && ra) B = true;
			if (n <= m && !ra) B = true;

			if (!B) s = "(" + q + f + p + ")";
			else s = q + f + p;
			st.push(s);
			st_opr.push(m);

		}
		else if (f_opr_one(T))
		{
			p = st.top();
			st.pop();
			s = "(" + p + ")";
			st.push(s);
		}

	}

	s = st.top();
	st.pop();
	return s;
}

deque<Token> FToPolishI(string expr , int& index , Enumerable q)
{
	deque<Token> fh, eh;
	bool B;
	switch (q)
	{
	    case Enumerable::DEFAULT : fh = exprToTokens(expr);
	    case Enumerable::ORDERING : fh = exprToTokens(expr, index, "ORDERING"); // Отладочный.
	}
	B = Check_Bracket_Matching(fh);
	if (!B)
	{
		printf("Mismatched parentheses error\n");
		return fh;
	}
	B = CheckBalance(fh);
	if (!B)
	{
		printf("Dissbalance operator error\n");
		return fh;
	}
	Tokenize_u_minus(fh);
	eh = shuntingYard(fh);
	return eh;
}

deque<Token> FToPolish(string expr)
{
	int index = 0;
	deque<Token> fs = FToPolishI(expr, index , Enumerable::DEFAULT);
	return fs;
}