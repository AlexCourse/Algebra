#include "Shanting_yard.h"
#include "PrintColourConsole.h"
#include <iostream>
#include <vector>
#include <stack>
#define DEBUG 0
#define M_PI 3.1415926535897932384626433832795028841971

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
		case Token::Type::LongArithmetic:
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
			if (!st.empty() && st.top().type == Token::Type::LeftParen)
			{
				st.pop();
				match = true;
			}
			if (st.empty() && !match) {
				std::cout << "RightParen error (" << T.ToString() << ")\n";
				return {};
			}
			break;
		}
		default:
			cout << "error (" << T.ToString() << endl;
			return {};
		}
	}
	while (!st.empty()) { //  output.extend(stack[::-1])
		if (st.top().type == Token::Type::LeftParen) {
			cout << "Mismatched parentheses error" << endl;
			return {};
		}
		eh.push_back(std::move(st.top()));
		st.pop();
	}

	return eh;
}

bool Out_Deffinition_Scope_DIV(double p, double q){
	if (q != 0) return false;
	else return true;
}

bool Out_Deffinition_Scope_POW(double p, const double q)
{ // p ^ q
	if (p == 0 and q <= 0) return true;
	else return false;
}

bool Out_Deffinition_Scope_LN(double x)
{ // Проверка области определения логарифма.
	if (x > 0) return false;
	else return true;
}

bool Out_Deffinition_Scope_LOG(double p, double q)
{ // Логарифм от q по p.
	if (p > 0 and q > 0) return false;
	else return true;
}

bool Out_Deffinition_Scope_TG(double x)
{ // x != Pi/2 + Pi*n  ||   x != 3-> 2/Pi*(1 + 2*n)
	double r = (2 / M_PI * x - 1) / 2;
	if (abs(r - round(r)) < pow(10, -15)) return true; // Проверка r на целое число.
	else return false;
}

bool Out_Deffinition_Scope_CTG(double x)
{ // x != 0 + Pi*n 
	double r = x / M_PI;
	if (abs(r - round(r)) < pow(10, -15)) return true; // Проверка r на целое число.
	else return false;
}

bool Out_Deffinition_Scope_ARCSIN(double x)
{
	if (abs(x) <= 1) return false;
	else return true;
}

bool Out_Deffinition_Scope_ARCCTG(double x)
{
	if (x != 0) return false;
	else return true;
}

bool Out_Deffinition_Scope_ARCCOS(double x)
{
	if (abs(x) <= 1) return false;
	else return true;
}

bool Out_Deffinition_Scope_ARCTG(double x)
{
	if (x != 0) return false;
	else return true;
}

bool Out_Deffinition_Scope_CTH(double x)
{
	if (x != 0) return false;
	else return true;
}


bool Out_Deffinition_Scope_ARCCH(double x)
{
	if (x > 1) return false;
	else return true;
}

bool Out_Deffinition_Scope_ARCTH(double x)
{
	if (abs(x) < 1) return false;
	else return true;
}

bool Out_Deffinition_Scope_ARCCTH(double x)
{
	if (abs(x) > 1) return false;
	else return true;
}

map< Token::Function, string > rFunc_name =
{
	  { Token::Function::EXP , "exp"},
	  { Token::Function::LN   , "ln"} ,
	  { Token::Function::SIN , "sin"} ,
	  { Token::Function::COS , "cos"} ,
	  { Token::Function::TG  , "tg"} ,
	  { Token::Function::CTG , "ctg"} ,
	  { Token::Function::ARCSIN , "arcsin"} ,
	  { Token::Function::ARCCOS , "arccos"} ,
	  { Token::Function::ARCTG , "arctg"} ,
	  { Token::Function::ARCCTG , "arcctg"} ,
	  { Token::Function::SH , "sh"} ,
	  { Token::Function::CH , "ch"} ,
	  { Token::Function::TH , "th"} ,
	  { Token::Function::CTH , "cth"} ,
	  { Token::Function::SH  , "sh"} ,
	  { Token::Function::CH  , "ch"} ,
	  { Token::Function::TH  , "th"} ,
	  { Token::Function::ARCSH  , "arcsh"} ,
	  { Token::Function::ARCCH  , "arcch"} ,
	  { Token::Function::ARCTH  , "arcth"} ,
	  { Token::Function::ARCCTH , "arccth" } ,
	  { Token::Function::ABS , "abs"} ,
	  { Token::Function::LOG , "log"} ,
	  { Token::Function::POW , "pow"} ,
};


void PrintFuncInfoException(const Token::Function c)
{
	string f = rFunc_name[c]; // Добавить вывод красным цветом.
	string s = "The argument of the function" + f + "outside the scope of definition";
	PrintColorText(s, 12);
}

void PrintFuncInfoException(const char c)
{
	string f = string(1, c);
	string s = "The argument of the function" + f + "outside the scope of definition";
	PrintColorText(s, 12);
}

bool CheckValueOfFunctionException(const Token::Function c, const double x)
{
	bool B = true;
	switch (c)
	{
	    case Token::Function::LN: {   B = !Out_Deffinition_Scope_LN(x); break;  }
	    case Token::Function::TG: {   B = !Out_Deffinition_Scope_TG(x); break;  }
	    case Token::Function::CTG: {  B = !Out_Deffinition_Scope_CTG(x); break;  }
	    case Token::Function::ARCSIN: { B = !Out_Deffinition_Scope_ARCSIN(x); break;  }
	    case Token::Function::ARCCOS: { B = !Out_Deffinition_Scope_ARCCOS(x); break;  }
	    case Token::Function::CTH: {  B = !Out_Deffinition_Scope_CTH(x); break;  }
	    case Token::Function::ARCCH: { B = !Out_Deffinition_Scope_ARCCH(x); break; }
		case Token::Function::ARCTH: { B = !Out_Deffinition_Scope_ARCTH(x); break;  }
	    case Token::Function::ARCCTH: { B = !Out_Deffinition_Scope_ARCCTH(x); break;  }
		default: { B = true; break; }
	}
	return B;
}

bool CheckValueOfOperatorException(char c, double p , double q)
{
	bool B = true;
	switch (c)
	{
		case '^' : {   B = !Out_Deffinition_Scope_POW(p , q); break;  }
		case '/' : {   B = !Out_Deffinition_Scope_DIV(p , q); break;  }
		default: { B = true; break; }
	}
	return B;
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
				if (CheckValueOfOperatorException(c , p , q)) 
				{
					switch (c) {
					default:
						cout << "Operator error [" << T.ToString() << "]" << endl;
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
				}
				else
				{
					PrintFuncInfoException(c);
					exit(0);
				}
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
				if (CheckValueOfFunctionException(c, x))
				{
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
					case Token::Function::ARCSH: { st.push(asinh(x)); break; }
					case Token::Function::ARCCH: { st.push(acosh(x));  break; }
					case Token::Function::ARCTH: { st.push(atanh(x));  break;  }
					case Token::Function::ARCCTH: { st.push(atanh(1 / x));  break;  }
					case Token::Function::ABS: { st.push(abs(x)); break;  }
					}
				}
				else
				{
					PrintFuncInfoException(c);
					exit(0);
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
			cout << " Token error" << endl;
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
					if (CheckValueOfOperatorException(c, p , q))
					{
						switch (c) {
						default:
							cout << "Operator error [" << T.ToString() << "]" << endl;
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
			break;
		}
		case Token::Type::Function:
		{
			if (f_opr_one(T))
			{
				const auto x = st.top();
				st.pop();
				Token::Function c = get<Token::Function>(T.value);
				if (CheckValueOfFunctionException(c, x))
				{
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
					case Token::Function::ARCSH: { st.push(asinh(x)); break;  }
					case Token::Function::ARCCH: { st.push(acosh(x)); break;  }
					case Token::Function::ARCTH: { st.push(atanh(x)); break;  }
					case Token::Function::ARCCTH: { st.push(atanh(1 / x)); break;  }
					case Token::Function::ABS: { st.push(abs(x)); break;  }
					}
				}
				else
				{
					PrintFuncInfoException(c);
					exit(0);
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
		if (token.type == Token::Type::LeftParen) balance++;
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
		if (f_opr_one(token)) {}
	}
	if (balance == 0) return true;
	else return false;
}

string PostfixToInfix(vector<Token>& es)
{ // В первом параметре выражение в формате Обратной Польской нотации.
  // Результат возвращается во втором параметре в форме Инфиксной Записи.
	string R[2], s, t;
	// reverse(fs.begin(), fs.end());
	vector<Token> fs(es.rbegin(), es.rend());
	stack<string> st;
	stack<int> st_opr; // Здесь сохраняются приоритеты операторов.
	int m, P[2];
	while (!fs.empty())
	{
		Token T = fs.back();
		fs.pop_back();
		// Для балансировки стека.
		if (T.type == Token::Type::Algebra)
		{
			s = T.ToString();
			st.push(s);
			st_opr.push(-1);
		}
		else if (T.type == Token::Type::Integer || T.type == Token::Type::Real || T.type == Token::Type::Number)
		{
			s = T.ToString();
			st.push(s);
			st_opr.push(-1);
		}
		else if (f_opr_two(T))
		{
			string f = T.ToString();
			R[0] = st.top();
			st.pop();
			R[1] = st.top();
			st.pop();
			P[0] = st_opr.top();
			st_opr.pop();
			P[1] = st_opr.top();
			st_opr.pop();

			m = T.precedence;
			bool ra = T.rightAssociative;
			bool B = false;
			for (int i = 0; i < 2; i++)
			{
				B = false;
				if (P[i] != -1)
				{
					if (P[i] <= m && ra) B = true;
					if (P[i] < m && !ra) B = true;
					if (B) s = "(" + R[i] + ")";
					else s = R[i];
					R[i] = s;
				}
			}
			if (T.type == Token::Type::Operator) s = R[1] + f + R[0];
			if (T.type == Token::Type::Function) s = f + '(' + R[1] + ',' + R[0] + ')';
			st.push(s);
			st_opr.push(m);

		}
		else if (f_opr_one(T))
		{
			string f = T.ToString();
			string p = st.top();
			st.pop();
			s = f + "(" + p + ")";
			st.push(s);
			st_opr.push(5);
		}

	}

	s = st.top();
	st.pop();
	return s;
}

string PostfixToInfix(deque<Token>& fs)
{ // В первом параметре выражение в формате Обратной Польской нотации.
  // Результат возвращается во втором параметре в форме Инфиксной Записи.
	string R[2], s, t;
	// reverse(fs.begin(), fs.end());
	stack<string> st;
	stack<int> st_opr; // Здесь сохраняются приоритеты операторов.
	int m, P[2];
	while (!fs.empty())
	{
		Token T = fs.front();
		fs.pop_front();
		// Для балансировки стека.
		if (T.type == Token::Type::Algebra)
		{
			s = T.ToString();
			st.push(s);
			st_opr.push(-1);
		}
		else if (T.type == Token::Type::Integer || T.type == Token::Type::Real || T.type == Token::Type::Number)
		{
			s = T.ToString();
			st.push(s);
			st_opr.push(-1);
		}
		else if (f_opr_two(T))
		{
			string f = T.ToString();
			R[0] = st.top();
			st.pop();
			R[1]  = st.top();
			st.pop();
			P[0] = st_opr.top();
			st_opr.pop();
			P[1] = st_opr.top();
			st_opr.pop();

			m = T.precedence;
			bool ra = T.rightAssociative;
			bool B = false;
			for (int i = 0; i < 2; i++)
			{
				B = false;
				if (P[i] != -1)
				{
					if (P[i] <= m && ra) B = true;
					if (P[i] < m && !ra) B = true;
					if (B) s = "(" + R[i] + ")";
					else s = R[i];
					R[i] = s;
				}
			}
			if (T.type == Token::Type::Operator ) s = R[1] + f + R[0];
			if ( T.type == Token::Type::Function ) s = f + '(' + R[1] + ',' + R[0] + ')';
			st.push(s);
			st_opr.push(m);

		}
		else if (f_opr_one(T)) // Использование функции.
		{
			string f = T.ToString();
			string p = st.top();
			st.pop();
			s = f + "(" + p + ")";
			st.push(s);
			st_opr.push(5);
		}

	}

	s = st.top();
	st.pop();
	return s;
}


struct HW
{
	HW() :  haveOperator(false), haveFunction(false) {}
	bool haveOperator;
	bool haveFunction;
};


bool CheckSyntaxError(deque<Token> fh, BW& C)
{
	deque<tuple<int, int>> kh;
	deque<tuple<int, int>> ks = C.position;
	deque<Token>::iterator iter[3];
	int n = fh.size();
	if (n <= 3)
	{
		switch (n)
		{
		case 0: { cout << "Пустое выражение" << endl; break; }
		case 1: 
		{
			Token token = fh[0];
			if (!f_arg(token)) kh.push_back(make_tuple(0, 1));
		    break;
		}
		case 2: 
		{
			Token token = fh[0];
			Token C = fh[1];
			if (f_opr_one(token))
			{
				bool B = true;
				if (!f_arg(C)) B = false;
				if (!B) kh.push_back(ks[0]); // В пределах каких границ будет закрашиваться красным.
			}
			break;
		}
		case 3: 
		{  
			Token A = fh[0];
			Token token = fh[1];
		    Token C = fh[2];
		   if (f_opr_two(token))
		   {
			   bool B = true;
			   if (!f_arg(A)) B = false;
			   if (!f_arg(C)) B = false;
			   if (!B) kh.push_back(ks[1]); // В пределах каких границ будет закрашиваться красным.
		   }
			break;}
		}
	}
	else
	{
		iter[0] = fh.begin();
		iter[1] = fh.begin() + 1;
		iter[2] = fh.begin() + 2;
		for (;iter[2] != fh.end(); iter[0] = iter[1] , iter[1] = iter[2] , iter[2]++)
		{
			Token token = *(iter[1]);
			if (f_opr_two(token))
			{
				bool B = true;
				Token A = *(iter[0]);
				Token C = *(iter[2]);
				if (!(f_arg(A) or (A.type == Token::Type::RightParen) or (A.type == Token::Type::Function )) ) B = false;
				if (!(f_arg(C) or (C.type == Token::Type::LeftParen) or (C.type == Token::Type::Function)) ) B = false;
				if (!B)
				{
					int j = iter[1] - fh.begin();
					kh.push_back(ks[j]); // В пределах каких границ будет закрашиваться красным.
				}
			}
			else if (f_opr_one(token))
			{
				bool B = true;
				Token C = *(iter[2]);
				if (!(f_arg(C) or (C.type == Token::Type::LeftParen)) ) B = false;
				if (!B)
				{
					int j = iter[1] - fh.begin();
					kh.push_back(ks[j]); // В пределах каких границ будет закрашиваться красным.
				}
			}
		}
	}
	C.broken_pos = kh;
	return true; // Для заглушки.
}


bool CheckSyntaxBracket(deque<Token> fh, BW& C)
{
	bool const LOCAL_DEBUG = false;
	deque<Token>::iterator iter;
	deque<tuple<int, int>> kh , ks;
	stack<char> st; // стек для '(' и ')'.
	stack<int> st_level; // Величина дисбаланса соответсующая позиции при достижении скобки.
	stack<int> st_index; // Сохраняется индекс последней скобки добавленной в стек.
	stack<tuple<int, int>> st_pos;
	// Последние 3 стека соответствуют друг другу и в них равное число элементов.
	vector<int> ls; // Вектор для отладки соответствие каждого символа строки и его balance.
	ks = C.position;
	kh = C.broken_pos;
	int balance = 1;
	int m = 1;
	char c;
	for (iter = fh.begin(); iter != fh.end(); iter++)
	{
		Token token = *iter;
		if (f_arg(token)) balance--;
		else if (f_opr_two(token)) balance++;
		else if (f_opr_one(token)) {}
		if (LOCAL_DEBUG) ls.push_back(balance);
		if (token.type == Token::Type::LeftParen || token.type == Token::Type::RightParen)
		{
			if (token.type == Token::Type::LeftParen)
			{
				st.push('(');
				st_level.push(balance);
				int j = iter - fh.begin();
				st_pos.push(ks[j]);
				st_index.push(j);

			}
			if (token.type == Token::Type::RightParen)
			{
				c = st.top();
				st.pop();
				m = st_level.top();
				st_level.pop();
				int j = st_index.top();
				st_index.pop();
				Token token_1 = (j == 0) ? fh[j] : fh[j - 1]; // Проверка на наличие функции перед скобками. Если скобки не стоят в начале выражения.
				if (m != balance + 1 and token_1.type != Token::Type::Function ) // Ошибка диссбаланс выражения.
				{
					tuple<int, int> Q = st_pos.top();
					kh.push_back(Q);
				}
				st_pos.pop();
			}
		}
	}
	if (!st.empty())
	{
		while (!st.empty())
		{
			kh.push_back(st_pos.top());
			st_pos.pop();
			st.pop();
		}
	}
	C.broken_pos = kh;
	if (LOCAL_DEBUG)
	{
		vector<int>::iterator iter_1;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		bool B = false;
		for (iter = fh.begin(), iter_1 = ls.begin(); iter != fh.end(); iter++, iter_1++)
		{
			Token token = *iter;
			B = false;
			if (token.type == Token::Type::LeftParen || token.type == Token::Type::RightParen)
			{
				SetConsoleTextAttribute(hConsole, 11);
				B = true;
			}
			std::cout << token << " : " << *iter_1 << std::endl;
			if(B) SetConsoleTextAttribute(hConsole, 15);
		}
	}
	if (kh.empty()) return true;
	else return false;
}

bool IsNumeric(deque<Token> fh)
{
	bool B = true;
	for (Token token : fh)
	{
		if (token.type == Token::Type::Algebra)
		{
			B = false;
			break;
		}
	}
	return B;
}

bool CheckUnknownIdentificator(deque<Token> fh, BW& C)
{
	deque<Token>::iterator iter;
	deque < tuple<int, int>> kh, ks , ls;
	kh = C.broken_pos;
	ks = C.position;
	for (iter = fh.begin(); iter != fh.end(); iter++)
	{
		Token token = *iter;
		if (token.type == Token::Type::Unknown)
		{
			int j = iter - fh.begin();
			ls.push_back(ks[j]);
		}
	}
	for (auto Q : ls) kh.push_back(Q);
	if (ls.empty()) return true;
	else return false;
}

set<int> LiColourProcessing(BW& C)
{
	deque<tuple<int, int>> ks = C.broken_pos;
	set<int> f_box; // Список всех закрашенных красным символов.
	for (auto Q : ks)
	{
		int p , q;
		tie(p, q) = Q;
		for (int i = p; i < q; i++) f_box.insert(i);
	}
	return f_box;
}


deque<Token> FToPolishI(string expr, int& index, Enumerable q)
{ // Функция с обработкой ошибок.
	deque<Token> fh, eh, es;
	set<int> e_box;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор консоли
	bool B;
	BW C = BW();
	switch (q)
	{
	case Enumerable::DEFAULT: { fh = exprToTokens(expr , C); break; }
	case Enumerable::ORDERING: { fh = exprToTokens(expr, index, C, "ORDERING"); break; } // Отладочный.
	}
	deque<tuple<int, int>> kh = C.broken_pos;
	if (!kh.empty()) // Ошибка слишком большое число.
	{
		e_box = LiColourProcessing(C);
		PrintLineWithColorRed(expr, e_box);
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "Too large a number in the expression" << std::endl;
		SetConsoleTextAttribute(hConsole, 7);
		exit(0);
		return fh;
	}
	Tokenize_u_minus(fh);
	B = true;
	B = B and CheckSyntaxError(fh, C);
	B = B and CheckSyntaxBracket(fh, C);
	e_box = LiColourProcessing(C);
	if (!B)
	{
		PrintLineWithColorRed(expr, e_box);
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "Syntax error : " << std::endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
	if (!CheckUnknownIdentificator(fh, C))
	{
		cout << "Unknown Identificator" << endl;
		exit(0);
		return fh;
	}
	if (!Check_Bracket_Matching(fh))
	{
		cout << "Mismatched parentheses error" << endl;
		exit(0);
		return fh;
	}
	if (!CheckBalance(fh))
	{
		cout << "Dissbalance expression error" << endl;
		exit(0);
		return fh;
	}
	eh = ReplaceElementInPolish(fh, M_PI, "Pi");
	es = shuntingYard(eh);
	return es;
}

deque<Token> FToPolish(string expr)
{
	int index = 0;
	deque<Token> fs = FToPolishI(expr, index, Enumerable::DEFAULT);
	return fs;
}


void PrintTokensListInformation(deque<Token> fh)
{
	deque<Token>::iterator iter;
	for (iter = fh.begin(); iter != fh.end(); iter++)
	{
		Token token = *iter;
		const Token::Type t = token.type;
		string symbol = token.ToString();
		const int start_pos = token.start_pos;
		const int last_pos = token.last_pos;
		const int precendence = token.precedence;
		const bool rightAssociative = token.rightAssociative;
		cout << "Type : " << t << "\t";
		cout << "Symbol : " << symbol << "\t";
		// cout << "start_pos : " << start_pos << "\t";
		// cout << "last_pos : " << last_pos << "\t";
		cout << "precendence : " << precendence << "\t";
		cout << "rightAssociative : " << rightAssociative << "\t";
		for(int i =0; i< 2; i++) cout << endl;
	}
}