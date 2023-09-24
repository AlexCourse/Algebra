#include "token.h"
#include <regex>
#define DEBUG 1

Token::Token() : type(Type::Unknown), value(""), precedence(-1), rightAssociative(false) {}

Token::Token(Type t, const string& s, int prec, bool ra) : type(t), value(s), precedence(prec), rightAssociative(ra) {}

Token::Token(Type t, const int m) : type(t), value(m), precedence(-1), rightAssociative(false) {}

Token::Token(Type t, const double m) : type(t), value(m), precedence(-1), rightAssociative(false) {}

Token::Token(const Token& other) : type(other.type), value(other.value), precedence(other.precedence), rightAssociative(other.rightAssociative) {}

Token Token::operator=(const Token& other) {
	return Token(other);
}

bool Token::operator==(const Token& other) {
	return (type == other.type  && value == other.value && precedence == other.precedence && rightAssociative == other.rightAssociative);
}

bool Token::operator == (const int m)
{
	auto t = this->value;
	if (holds_alternative<int>(t)) {
		int p = get<int>(t);
		if (p == m) return true;
		else return false;
	}
	else return false;
}

bool Token::operator == (const double m)
{
	auto t = this->value;
	if (holds_alternative<double>(t)) {
		double p = get<double>(t);
		if (p == m) return true;
		else return false;
	}
	else return false;
}

bool Token::operator == (const string s)
{
	auto t = this->value;
	if (holds_alternative<string>(t)) {
		string p = get<string>(t);
		if (p == s) return true;
		else return false;
	}
	else return false;
}


ostream& operator<<(ostream& os, const Token& token) {
	if (holds_alternative<string>(token.value)) {
		string s = get<string>(token.value);
		os << s;
	}
	else if (holds_alternative<int>(token.value)) {
		int m = get<int>(token.value);
		os << m;
	}
	else if (holds_alternative<double>(token.value)) {
		double m = get<double>(token.value);;
		os << m;
	}
	return os;
}

string Token::ToString()
{
	string s ="";
	auto value = this->value;
	if (holds_alternative<string>(value)) {
		s = get<string>(value);
	}
	else if (holds_alternative<int>(value)) {
		int m = get<int>(value);
		s = to_string(m);
	}
	else if (holds_alternative<double>(value)) {
		double m = get<double>(value);;
		s = to_string(m);
	}
	return s;
}

string ToString(const variant<string, int, double>& value)
{
	string s = "";
	if (holds_alternative<string>(value)) {
		s = get<string>(value);
	}
	else if (holds_alternative<int>(value)) {
		int m = get<int>(value);
		s = to_string(m);
	}
	else if (holds_alternative<double>(value)) {
		double m = get<double>(value);;
		s = to_string(m);
	}
	return s;
}

void Token::SetValue(const variant<string, int, double>& newValue) {
	this->value = newValue;
}


variant<string, int, double> Token::GetValue() const {
	return this->value;
}

struct Operator {
	int precedence;
	string associativity;
};


unordered_set<string> operator_info_two = { "+" , "-", "/", "*", "^" };
unordered_set<string> operator_info_one = { "!" };
unordered_set<string> func_info_one = { "sin", "cos", "tg", "ctg", "ln", "exp", "sec", "cosec", "arcsin", "arccos", "arctg", "arcctg",
"sqrt", "sh", "ch", "th", "cth", "arsh", "arch", "arth", "arcth", "abs", "factorial" };
unordered_set<string> func_info_two = { "log" , "pow" , "S" , "Integral" };
unordered_set<string> func_info_free = { "D" , "Z" , "P" , "Derivate" };
unordered_set<string> func_info = { "sin", "cos", "tg", "ctg", "ln", "exp", "sec", "cosec", "arcsin", "arccos", "arctg", "arcctg",
"sqrt", "sh", "ch", "th", "cth", "arsh", "arch", "arth", "arcth", "abs", "factorial" , "log" , "pow" };



map<char, Operator> operator_info = { { '+' , { 2, "L" }} ,
										{'-' , { 2, "L" }},
										{'/' , { 3, "L" }},
										{'*' , { 3, "L" }},
										{'^' , { 4, "R" }},
};

bool f_arg(const Token& T) {
	if (T.type == Token::Type::Algebra || T.type == Token::Type::Number || T.type == Token::Type::Integer || T.type == Token::Type::Real)
		return true;
	else
		return false;
}

bool f_opr_two(const Token& T) {
	string p = get<string>(T.value);
	if (operator_info_two.count(p) || func_info_two.count(p)) {
		return true;
	}
	return false;
}

bool f_opr_one(const Token& T) {
	string p = get<string>(T.value);
	if (operator_info_one.count(p) || func_info_one.count(p)) {
		return true;
	}
	return false;
}

bool f_opr_free(const Token& T) {
	string p = get<string>(T.value);
	if (func_info_free.count(p)) {
		return true;
	}
	return false;
}

bool isliter(char p) {
	if ((p >= 'A' && p <= 'Z') || (p >= 'a' && p <= 'z')) {
		return true;
	}
	else {
		return false;
	}
}

Token::~Token() {
	// Destructor definition
	// Add any necessary cleanup code here
}

template<typename T>
bool _CheckEquality(variant<string, int, double> value, T m) {
	if (holds_alternative<string>(value)) {
		return get<string>(value) == m;
	}
	else if (holds_alternative<int>(value)) {
		return get<int>(value) == m;
	}
	else if (holds_alternative<double>(value)) {
		return get<double>(value) == m;
	}
	return false;
}

// template
bool CheckEquality(variant<string, int, double> value, string s) 
{
		if (holds_alternative<string>(value))
		{
			if (get<string>(value) == s) return true;
			else return false;
		}
		else return false;
}
// template
bool CheckEquality(variant<string, int, double> value, int m) 
{
	if (holds_alternative<string>(value))
	{
		if (get<int>(value) == m) return true;
		else return false;
	}
	else return false;
}
// template
bool CheckEquality(variant<string, int, double> value, double m)
{
	if (holds_alternative<string>(value))
	{
		if (get<double>(value) == m) return true;
		else return false;
	}
	else return false;
}

deque<Token> exprToTokens(const string& expr) {
	deque<Token> tokens;

	for (const auto* p = expr.c_str(); *p; ++p) {
		if (isblank(*p)) {
			// do nothing
		}
		else if (isdigit(*p))
		{
			if ((*p) == '.')
			{
				int pr = -1;
				tokens.push_back(Token{ Token::Type::Unknown, string(p, p), pr,  false });
				cout << "Неверная запись десятичного числа" << endl;
			}
			Token::Type t = Token::Type::Integer;
			const auto* b = p;
			while (isdigit(*p) || (*p) == '.') {
				if ((*p) == '.') t = Token::Type::Real;
				++p;
			}
			const string s = string(b, p);
			if (t == Token::Type::Integer)
			{
				int m = stoi(s);
				tokens.push_back(Token{ t, m });
			}
			else if (t == Token::Type::Real)
			{
				double m = stod(s);
				tokens.push_back(Token{ t, m });
			}
			--p;
		}
		else
			if (isliter(*p))
			{
				const auto* b = p;
				while (isliter(*p)) {
					++p;
				}
				const string s = string(b, p);
				if (func_info.count(s)) tokens.push_back(Token{ Token::Type::Function, s });
				else tokens.push_back(Token{ Token::Type::Algebra, s });
				p--;
				continue;

			}
			else if ((*p) == ',')
			{
				string s = string(p, p + 1);
				tokens.push_back(Token{ Token::Type::Comma , s });
			}
			else {
				Token::Type t = Token::Type::Unknown;
				int pr = -1;            // приоритет
				bool ra = false;        // rightAssociative
				switch (*p) {
				default:                                    break;
				case '(':   t = Token::Type::LeftParen;     break;
				case ')':   t = Token::Type::RightParen;    break;
				case '^':   t = Token::Type::Operator;      pr = 4; ra = true;  break;
				case '*':   t = Token::Type::Operator;      pr = 3; break;
				case '/':   t = Token::Type::Operator;      pr = 3; break;
				case '+':   t = Token::Type::Operator;      pr = 2; break;
				case '-':   t = Token::Type::Operator;      pr = 2; break;
				}
				const auto s = std::string(1, *p);
				tokens.push_back(Token{ t, s, pr, ra });
			}


	}

	return tokens;
}

Token SetToken(int m) // На основе этой функции создать шаблон.
{
	Token T = Token{ Token::Type::Integer, m };
	return T;
}

Token SetToken(double m) // На основе этой функции создать шаблон.
{
	Token T = Token{ Token::Type::Real, m };
	return T;
}



Token SetToken(const string& expr) // фунция возвращает первый токен , если их несколько.
{ // Или можно передать одно отрицательное число.
	int n = expr.size();
	if (n == 1)
	{
		for (const auto* p = expr.c_str(); *p; ++p) {
			if (isblank(*p)) {
				// do nothing
			}
			else if (isdigit(*p))
			{
				if ((*p) == '.')
				{
					int pr = -1;
					Token T = Token{ Token::Type::Unknown, std::string(p, p), pr,  false };
					return T;
				}
				const auto* b = p;
				Token::Type t = Token::Type::Integer;
				while (isdigit(*p) || (*p) == '.') {
					if ((*p) == '.') t = Token::Type::Real;
					++p;
				}
				const auto s = std::string(b, p);
				Token T = Token{ t, s };
				return T;
				--p;
			}
			else
				if (isliter(*p))
				{
					const auto* b = p;
					while (isliter(*p)) {
						++p;
					}
					const string s = string(b, p);
					if (func_info.count(s))
					{
						Token T = Token{ Token::Type::Function, s };
						return T;
					}
					else
					{
						Token T = Token{ Token::Type::Algebra, s };
						return T;
					}
				}
				else {
					Token::Type t = Token::Type::Unknown;
					int pr = -1;            // приоритет
					bool ra = false;        // rightAssociative
					switch (*p) {
					default:                                    break;
					case '(':   t = Token::Type::LeftParen;     break;
					case ')':   t = Token::Type::RightParen;    break;
					case '^':   t = Token::Type::Operator;      pr = 4; ra = true;  break;
					case '*':   t = Token::Type::Operator;      pr = 3; break;
					case '/':   t = Token::Type::Operator;      pr = 3; break;
					case '+':   t = Token::Type::Operator;      pr = 2; break;
					case '-':   t = Token::Type::Operator;      pr = 2; break;
					}
					const auto s = std::string(1, *p);
					Token T = Token{ t, s, pr, ra };
					return T;
				}

		}
		Token T;
		return T;
	}
	else // Случай одного отрицательного числа.
	{
		deque<Token> fs;
		fs = exprToTokens(expr);
		Tokenize_u_minus(fs);
		Token T = fs.front();
		fs.pop_front();
		return T;
	}
}

bool operator == (Token& C , Token& S) 
{
	if (C.value == S.value) return true;
	else return false;
}

void Tokenize_u_minus(deque<Token>& fh) {
	string patthern = "(-";
	deque<Token>::iterator iter[2];
	vector<int> entries;
	iter[0] = iter[1] = fh.begin();
	int n = fh.size();
	if (n >= 2) iter[1]++;
	else return;
	int i = 0;
	while (iter[1] != fh.end())
	{
		
		Token& T_0 = *(iter[0]);
		Token& T_1 = *(iter[1]);
		if (T_0.type == Token::Type::LeftParen)
			if (T_1.type == Token::Type::Operator)
				if (get<string>(T_1.value) == "-") entries.push_back(i);
		iter[0] = iter[1];
		iter[1]++;
		i++;
	}
	while (0); // Для точки останова.

	if (n >= 4) // Ищем (-a) и заменяем на результат (-1)*a , где а - число.
	{
		string f , r;
		if (DEBUG) f = TokensToStr(fh);
		reverse(entries.begin(), entries.end()); // Начинаем с последнего , чтобы не корректировать индексы при удалении.
		for (int p : entries)
		{
			Token& T_0 = fh[p + 3];
			Token& T_1 = fh[p + 2];
			if (T_0.type == Token::Type::RightParen)
			{
				if (T_1.type == Token::Type::Number || T_1.type == Token::Type::Integer || T_1.type == Token::Type::Real )
				{  
					double q = -1;
					if (holds_alternative<int>(T_1.value))
					{
						int q = get<int>(T_1.value);
						q = (-1) * q;
					}
					else if (holds_alternative<double>(T_1.value))
					{
						double q = get<double>(T_1.value);
						q = (-1) * q;
					}
					const deque<Token>::iterator start = fh.begin();
					Token T_2 = SetToken(q);
					if (DEBUG) r = TokensToStr(fh);
					f = r;
					if (DEBUG){  
						const Token T_3 = *(start + p);
						const Token T_4 = *(start + p + 4);
						deque<Token> eh = fh;
						while (0); // Для точки останова.
					}
					if (DEBUG)
					{
						deque<Token> ls;
						copy(fh.begin(), fh.end(), back_inserter(ls));
						deque<Token>::iterator iter;
						int i , j;
						int m = fh.size();
						for (iter = fh.begin(), i = 0; iter != fh.end(); iter++, i++) { cout << i << ":" << *(iter) << endl; }
						r = TokensToStr(fh);
						tie(i, j) = make_pair(16, 19); // Данные для настройки.
						Token T_5 = *(start + i);
						Token T_6 = *(start + j);
						ls.erase(start + i , start + j); // Функция странно удаляет
						string f = TokensToStr(ls);
						int l = 5;
						for (i = 0; i < m - l - 1; i++)
						{
							deque<Token> lh;
							copy(fh.begin(), fh.end(), back_inserter(lh));
							lh.erase(start + i, start + i + l);
							f = TokensToStr(lh);
							cout << f << endl;
						}
						while (0);
					}
					fh.erase(start + p - 1, start + p + 4 - 1); // Функция странно удаляет
					if (DEBUG) r = TokensToStr(fh);
					f = r;
					fh.insert(start + p, T_2);
					if (DEBUG) r = TokensToStr(fh);
					f = r;
				}
				else if (T_1.type == Token::Type::Algebra)
				{
					const deque<Token>::iterator start = fh.begin();
					if (DEBUG) {
						const Token T_3 = *(start + p);
						const Token T_4 = *(start + p + 4);
						deque<Token> eh = fh;
						while (0); // Для точки останова.
					}
					fh.erase(start + p - 1, start + p + 4 - 1);
					if (DEBUG) r = TokensToStr(fh);
					f = r;
					deque<Token> es = exprToTokens("(-1)*a");
					es.pop_back();
					es.push_back(T_1);
					fh.insert(fh.begin() + p, T_1);
					if (DEBUG) r = TokensToStr(fh);
					f = r;
				}
			}
		}
	}
	n = fh.size();
	if (n >= 2)
	{
		Token& T_0 = fh.front();
		Token& T_1 = fh[1];
		if (T_0.type == Token::Type::Operator)
		{
			if (get<string>(T_0.value) == "-")  // Этот случай не пересекается с предыдущим случаем.
			{   // Случай когда унарный минус стоит в начале строки.
				string f, r;
				if (T_1.type == Token::Type::Number || T_1.type == Token::Type::Integer || T_1.type == Token::Type::Real)
				{
					fh.pop_front();
					fh.pop_front();
					double m = -1;
					if (holds_alternative<int>(T_1.value))
					{
						m = get<int>(T_1.value);
					}
					else if (holds_alternative<double>(T_1.value))
					{
						m = get<double>(T_1.value);
					}
					m = (-1) * m;
					Token T_2 = SetToken(m);
					fh.insert(fh.begin(), T_2); // Добавление вперед очереди.
					if (DEBUG) r = TokensToStr(fh);
					f = r;
				}
				else if (T_1.type == Token::Type::Algebra)
				{
					fh.pop_front();
					deque<Token> es = exprToTokens("(-1)*a");
					es.pop_back();
					es.push_back(T_1); // Замена символа a вставка в начало.
					fh.insert(fh.begin(), T_1);
					if (DEBUG) r = TokensToStr(fh);
					f = r;
				}
			}
		}
	}
}




string TokensToStr(deque<Token> fh)
{
	string s = "";
	for (Token t : fh)
	{
		if (holds_alternative<string>(t.value)) {
			string f = get<string>(t.value);
			s = s + f;
		}
		else if (holds_alternative<int>(t.value)) {
			int m = get<int>(t.value);
			s = s + to_string(m);
		}
		else if (holds_alternative<double>(t.value)) {
			double m = get<double>(t.value);
			s = s + to_string(m);
		}
	}
	return s;
}