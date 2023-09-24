#include "token.h"
#include <regex>
#define DEBUG 1

using namespace std;

Token::Token() : type(Type::Unknown), value(""), precedence(-1), rightAssociative(false) , index(0) {}

Token::Token(Type t, const string& s, int prec, bool ra) : type(t), value(s), precedence(prec), rightAssociative(ra) , index(0) {}

Token::Token(Type t, const int m) : type(t), value(m), precedence(-1), rightAssociative(false) , index(0) {}

Token::Token(Type t, const double m) : type(t), value(m), precedence(-1), rightAssociative(false) , index(0) {}

Token::Token(Type t, const Token::Function m) : type(t), value(m), precedence(1), rightAssociative(false), index(0) {}

Token::Token(Type t , char c , int prec , bool ra) : type(t) , value(c) , precedence(prec), rightAssociative(ra), index(0) {}

Token::Token(const Token& other) : type(other.type), value(other.value), precedence(other.precedence), rightAssociative(other.rightAssociative) , index(other.index) {}



Token::Token(Type t, const string& s, int index ,int prec, bool ra) : type(t), value(s), precedence(prec), rightAssociative(ra), index(index) {}

Token::Token(Type t, const string& s, int index) : type(t), value(s), precedence(-1), rightAssociative(false), index(index) {}

Token::Token(Type t, const int m, int index) : type(t), value(m), precedence(-1), rightAssociative(false), index(index) {}

Token::Token(Type t, const double m, int index) : type(t), value(m), precedence(-1), rightAssociative(false), index(index) {}

Token::Token(const Token& other, int index) : type(other.type), value(other.value), precedence(other.precedence), rightAssociative(other.rightAssociative), index(index) {}

Token::Token(Type t, char c , int index , int prec , bool ra) : type(t), value(c), precedence(prec), rightAssociative(ra), index(index) {}

Token::Token(Type t, const Token::Function m, int index) : type(t), value(m), precedence(1), rightAssociative(false), index(index) {}

void Token::SetValue(const variant<string, char, int, double, Token::Function>& newValue) {
	this->value = newValue;
}


variant<string, char, int, double, Token::Function> Token::GetValue() const {
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

map< string, Token::Function> func_name = 
  { { "exp" , Token::Function::EXP },
	{ "ln" , Token::Function::LN   } ,
	  {"sin" , Token::Function::SIN} ,
	  { "cos" , Token::Function::COS} ,
	  { "tg"  , Token::Function::TG } ,
	  { "ctg"  , Token::Function::CTG } ,
	  { "arcsin"  , Token::Function::ARCSIN } ,
	  { "arccos"  , Token::Function::ARCCOS } ,
	  { "arctg"   , Token::Function::ARCTG } ,
	  { "arcctg"  , Token::Function::ARCCTG } ,
	  { "sh"      , Token::Function::SH } ,
	  { "ch"      , Token::Function::CH } ,
	  { "th"      , Token::Function::TH } ,
	  { "cth"     , Token::Function::CTH } ,
	  { "sh"      , Token::Function::SH } ,
	  { "ch"      , Token::Function::CH } ,
	  { "th"      , Token::Function::TH } ,
	  { "arsh"     , Token::Function::ARSH } ,
	  { "arch"     , Token::Function::ARCH } ,
	  { "arth"     , Token::Function::ARTH } ,
	  { "arcth"    , Token::Function::ARCTH } ,
	  { "abs"      , Token::Function::ABS } ,
	  { "log"      , Token::Function::LOG } ,
	  { "pow"      , Token::Function::POW }
};

map< Token::Function, string > rfunc_name =
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
	  { Token::Function::ARSH  , "arsh"} ,
	  { Token::Function::ARCH  , "arch"} ,
	  { Token::Function::ARTH  , "arth"} ,
	  { Token::Function::ARCTH , "arcth" } ,
	  { Token::Function::ABS , "abs"} ,
	  { Token::Function::LOG , "log"} ,
	  { Token::Function::POW , "pow"}
};

Token Token::operator=(const Token& other) {
	return Token(other);
}

bool Token::operator==(const Token& other) {
	return (type == other.type && value == other.value && precedence == other.precedence && rightAssociative == other.rightAssociative);
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

bool Token::operator == (const char c)
{
	auto t = this->value;
	if (holds_alternative<char>(t)) {
		char p = get<char>(t);
		if (p == c) return true;
		else return false;
	}
	else return false;
}

bool Token::operator == (const Token::Function f_able)
{
	auto t = this->value;
	if (holds_alternative<Token::Function>(t)) {
		Token::Function g_able = get<Token::Function>(t);
		if (g_able == f_able) return true;
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
	else if (holds_alternative<char>(token.value)) {
		char c = get<char>(token.value);
		os << c;
	}
	else if (holds_alternative<Token::Function>(token.value)) {
		Token::Function p = get<Token::Function>(token.value);
		string s = rfunc_name[p];
		os << s;
	}
	return os;
}

string Token::ToString()
{
	string s = "";
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
	else if (holds_alternative<char>(value)) {
		char c = get<char>(value);
		s = string(1, c);
	}
	else if (holds_alternative<Token::Function>(value)) {
		Token::Function p = get<Token::Function>(value);
		s = rfunc_name[p];
	}
	return s;
}

string ToString(const variant<string, char, int, double, Token::Function>& value)
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
	else if (holds_alternative<char>(value)) {
		char c = get<char>(value);;
		s = string(1, c);
	}
	else if (holds_alternative<Token::Function>(value)) {
		Token::Function p = get<Token::Function>(value);
		s = rfunc_name[p];
	}
	return s;
}

bool f_arg(const Token& T) {
	if (T.type == Token::Type::Algebra || T.type == Token::Type::Number || T.type == Token::Type::Integer || T.type == Token::Type::Real)
		return true;
	else
		return false;
}

bool f_opr_two(const Token& T) {
	Token token = T;
	bool B = false;
	if(T.type == Token::Type::Operator)
		B = true;
	else if(T.type == Token::Type::Function)
	{
		Token::Function p = get<Token::Function>(T.value);
		switch (p)
		{
		    case Token::Function::LOG: { B = true; break; }
			case Token::Function::POW : { B = true; break; }
		}
	}
	return B;
}

bool f_opr_one(const Token& T) {
	Token token = T;
	bool B = true;
	if (T.type == Token::Type::Operator)
		B = false;
	else if (T.type == Token::Type::Function)
	{
		Token::Function p = get<Token::Function>(T.value);
		switch (p)
		{
		case Token::Function::LOG: { B = false; break; }
		case Token::Function::POW: { B = false; break; }
		}
	}
	return B;
}


bool f_opr_free(const Token& T) {
	Token token = T;
	string p = token.ToString();
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

bool CE(const variant<string, char, int, double, Token::Function> value, const string s)
{
	if (holds_alternative<string>(value))
	{
		if (get<string>(value) == s) return true;
		else return false;
	}
	else return false;
}

bool CE(const variant<string, char, int, double, Token::Function> value, const int m)
{
	if (holds_alternative<int>(value))
	{
		if (get<int>(value) == m) return true;
		else return false;
	}
	else return false;
}

bool CE(const variant<string, char, int, double, Token::Function> value, const double m)
{
	if (holds_alternative<double>(value))
	{
		if (get<double>(value) == m) return true;
		else return false;
	}
	else return false;
}

bool CE(const variant<string, char, int, double, Token::Function> value, const char c)
{
	if (holds_alternative<char>(value))
	{
		if (get<char>(value) == c) return true;
		else return false;
	}
	else return false;
}

bool CE(const variant<string, char, int, double, Token::Function> value, Token::Function p)
{
	if (holds_alternative<Token::Function>(value))
	{
		if (get<Token::Function>(value) == p) return true;
		else return false;
	}
	else return false;
}

deque<Token> exprToTokens(const string& expr , int& index , string q ="DEFAULT") {
	// q принимает 2 значения - DEFAULT и ORDERING.
	deque<Token> tokens;
	if (q == "DEFAULT") index = 0;

	for (const auto* p = expr.c_str(); *p; ++p) {
		char c = *p;
		if (isblank(c)) {
			// do nothing
		}
		else if (isdigit(c))
		{
			if (c == '.')
			{
				int pr = -1;
				tokens.push_back(Token{ Token::Type::Unknown, string(p, p), index++ ,pr,  false });
				cout << "Неверная запись десятичного числа" << endl;
			}
			Token::Type t = Token::Type::Integer;
			const auto* b = p;
			while (isdigit(c) || c == '.') {
				if (c == '.') t = Token::Type::Real;
				++p;
				c = *p;
			}
			const string s = string(b, p);
			if (t == Token::Type::Integer)
			{
				int m = stoi(s);
				tokens.push_back(Token{ t, m , index++});
			}
			else if (t == Token::Type::Real)
			{
				double m = stod(s);
				tokens.push_back(Token{ t, m , index++});
			}
			--p;
		}
		else
			if (isliter(c))
			{
				const auto* b = p;
				while (isliter(c)) {
					++p;
					c = *p;
				}
				const string s = string(b, p);
				if (func_info.count(s)) tokens.push_back(Token{ Token::Type::Function, func_name[s] , index++});
				else tokens.push_back(Token{ Token::Type::Algebra, s , index++ , -1 , false});
				p--;
				continue;

			}
			else if (c == ',')
			{
				string s = string(p, p + 1);
				tokens.push_back(Token{ Token::Type::Comma , c , index++ , -1 , false});
			}
			else {
				Token::Type t = Token::Type::Unknown;
				int pr = -1;            // приоритет
				bool ra = false;        // rightAssociative
				switch (c) {
				default:                                    break;
				case '(':   t = Token::Type::LeftParen;     break;
				case ')':   t = Token::Type::RightParen;    break;
				case '^':   t = Token::Type::Operator;      pr = 4; ra = true;  break;
				case '*':   t = Token::Type::Operator;      pr = 3; break;
				case '/':   t = Token::Type::Operator;      pr = 3; break;
				case '+':   t = Token::Type::Operator;      pr = 2; break;
				case '-':   t = Token::Type::Operator;      pr = 2; break;
				}
				// const auto s = string(1, c);
				tokens.push_back(Token{ t, c, index++ , pr, ra });
				while (0); // Для точки останова.
			}
	}
	return tokens;
}

deque<Token> exprToTokens(const string& expr)
{
	int index = 0;
	deque<Token> fs = exprToTokens(expr, index, "DEFAULT");
	return fs;
}

Token _SetToken(const int m) 
{
	Token T = Token{ Token::Type::Integer, m };
	return T;
}

Token _SetToken(const double m)
{
	Token T = Token{ Token::Type::Real, m};
	return T;
}

Token _SetToken(const int m , int& index)
{
	Token T = Token{ Token::Type::Integer, m , index++};
	return T;
}

Token _SetToken(const double m , int& index)
{
	Token T = Token{ Token::Type::Real, m , index++};
	return T;
}

Token _SetToken(const string& expr , int& index) // фунция возвращает первый токен , если их несколько.
{ // Или можно передать одно отрицательное число.
	int n = expr.size();
	if (n == 1)
	{
		for (const auto* p = expr.c_str(); *p; ++p) {
			char c = *p;
			if (isblank(c)) {
				// do nothing
			}
			else if (isdigit(*p))
			{
				if (c == '.')
				{
					int pr = -1;
					Token T = Token{ Token::Type::Unknown, string(p, p), index++ , pr,  false };
					return T;
				}
				const auto* b = p;
				Token::Type t = Token::Type::Integer;
				while (isdigit(c) || c == '.') {
					if (c == '.') t = Token::Type::Real;
					++p;
					c = *p;
				}
				const string s = string(b, p);
				if (t == Token::Type::Integer)
				{
					int m = stoi(s);
					Token T = Token{ t, m , index++};
					return T;
				}
				else if (t == Token::Type::Real)
				{
					double m = stod(s);
					Token T = Token{ t, m ,index++};
					return T;
				}
				--p;
			}
			else
				if (isliter(c))
				{
					const auto* b = p;
					while (isliter(c)) {
						++p;
						c = *p;
					}
					const string s = string(b, p);
					if (func_info.count(s))
					{
						Token T = Token{ Token::Type::Function, func_name[s] , index++};
						return T;
					}
					else
					{
						Token T = Token{ Token::Type::Algebra, s , index++ , -1 , false};
						return T;
					}
				}
				else {
					Token::Type t = Token::Type::Unknown;
					int pr = -1;            // приоритет
					bool ra = false;        // rightAssociative
					switch (c) {
					default:                                    break;
					case '(':   t = Token::Type::LeftParen;     break;
					case ')':   t = Token::Type::RightParen;    break;
					case '^':   t = Token::Type::Operator;      pr = 4; ra = true;  break;
					case '*':   t = Token::Type::Operator;      pr = 3; break;
					case '/':   t = Token::Type::Operator;      pr = 3; break;
					case '+':   t = Token::Type::Operator;      pr = 2; break;
					case '-':   t = Token::Type::Operator;      pr = 2; break;
					}
					// const auto s = string(1, c);
					Token T = Token{ t, c, index++ , pr, ra };
					return T;
				}

		}
		Token T;
		return T;
	}
	else // Случай одного отрицательного числа.
	{
		deque<Token> fs;
		fs = exprToTokens(expr , index);
		Tokenize_u_minus(fs);
		Token T = fs.front();
		fs.pop_front();
		return T;
	}
}

Token _SetToken(const string& expr)
{
	int index;
	Token token = _SetToken(expr, index);
	return token;
}

Token _SetToken(const char c, int& index)
{
	string s = string(1, c);
	Token token = _SetToken(s, index);
	return token;
}

Token _SetToken(const char c)
{
	int index = 0;
	Token token = _SetToken(c, index);
	return token;
}

Token _SetToken(const Token::Function f_able)
{
	int index = 0;
	Token token = Token(Token::Type::Function, f_able, index);
	return token;
}

Token _SetToken(const Token::Function f_able, int& index)
{
	Token token = Token(Token::Type::Function, f_able, index);
	return token;
}

Token SetToken(const variant<string, char, int, double, Token::Function> value)
{
	if (holds_alternative<string>(value)) {
		string f = get<string>(value);
		Token T = _SetToken(f);
		return T;
	}
	else if (holds_alternative<int>(value)) {
		int m = get<int>(value);
		Token T = _SetToken(m);
		return T;
	}
	else if (holds_alternative<double>(value)) {
		double m = get<double>(value);
		Token T = _SetToken(m);
		return T;
	}
	else if (holds_alternative<char>(value))
	{
		char c = get<char>(value);
		Token T = _SetToken(c);
		return T;
	}
	else if (holds_alternative<Token::Function>(value))
	{
		Token::Function f_able = get<Token::Function>(value);
		Token T = _SetToken(f_able);
		return T;
	}
}

Token SetToken(const variant<string, char, int, double, Token::Function> value, int& index)
{
	if (holds_alternative<string>(value)) {
		string f = get<string>(value);
		Token T = _SetToken(f, index);
		return T;
	}
	else if (holds_alternative<int>(value)) {
		int m = get<int>(value);
		Token T = _SetToken(m , index);
		return T;
	}
	else if (holds_alternative<double>(value)) {
		double m = get<double>(value);
		Token T = _SetToken(m, index);
		return T;
	}
	else if (holds_alternative<char>(value))
	{
		char c = get<char>(value);
		Token T = _SetToken(c, index);
		return T;
	}
	else if (holds_alternative<Token::Function>(value))
	{
		Token::Function f_able = get<Token::Function>(value);
		Token T = _SetToken(f_able, index);
		return T;
	}
}

bool operator == (Token& C, Token& S)
{
	if (C.value == S.value) return true;
	else return false;
}

void Tokenize_u_minus(deque<Token>& fh) {
	const bool LOCAL_DEBUG = false;
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
				if (get<char>(T_1.value) == '-') entries.push_back(i);
		iter[0] = iter[1];
		iter[1]++;
		i++;
	}
	while (0); // Для точки останова.

	if (n >= 4) // Ищем (-a) и заменяем на результат (-1)*a , где а - число.
	{
		string f, r;
		if (DEBUG) f = TokensToStr(fh);
		reverse(entries.begin(), entries.end()); // Начинаем с последнего , чтобы не корректировать индексы при удалении.
		for (int p : entries)
		{
			Token& T_0 = fh[p + 3];
			Token& T_1 = fh[p + 2];
			if (T_0.type == Token::Type::RightParen)
			{
				if (T_1.type == Token::Type::Number || T_1.type == Token::Type::Integer || T_1.type == Token::Type::Real)
				{
					double q = -1;
					if (T_1.type == Token::Type::Integer)
					{
						int q = get<int>(T_1.value);
						q = (-1) * q;
					}
					else if (T_1.type == Token::Type::Real)
					{
						double q = get<double>(T_1.value);
						q = (-1) * q;
					}
					const deque<Token>::iterator start = fh.begin();
					Token T_2 = SetToken(q);
					if (LOCAL_DEBUG) r = TokensToStr(fh);
					f = r;
					if (LOCAL_DEBUG) {
						const Token T_3 = *(start + p);
						const Token T_4 = *(start + p + 4);
						deque<Token> eh = fh;
						while (0); // Для точки останова.
					}
					if (LOCAL_DEBUG)
					{
						deque<Token> ls;
						copy(fh.begin(), fh.end(), back_inserter(ls));
						deque<Token>::iterator iter;
						int i, j;
						int m = fh.size();
						for (iter = fh.begin(), i = 0; iter != fh.end(); iter++, i++) { cout << i << ":" << *(iter) << endl; }
						r = TokensToStr(fh);
						tie(i, j) = make_pair(16, 19); // Данные для настройки.
						Token T_5 = *(start + i);
						Token T_6 = *(start + j);
						ls.erase(start + i, start + j); // Функция странно удаляет
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
					fh.erase(start + p, start + p + 4); // Функция странно удаляет
					if (LOCAL_DEBUG) r = TokensToStr(fh);
					f = r;
					fh.insert(fh.begin() + p, T_2); // fh.insert(start + p, T_2);
					if (LOCAL_DEBUG) r = TokensToStr(fh);
					f = r;
				}
				else if (T_1.type == Token::Type::Algebra)
				{
					const deque<Token>::iterator start = fh.begin();
					if (LOCAL_DEBUG) {
						const Token T_3 = *(start + p);
						const Token T_4 = *(start + p + 4);
						deque<Token> eh = fh;
						while (0); // Для точки останова.
					}
					fh.erase(start + p - 1, start + p + 4 - 1);
					if (LOCAL_DEBUG) r = TokensToStr(fh);
					f = r;
					deque<Token> es = exprToTokens("(-1)*a");
					es.pop_back();
					es.push_back(T_1);
					fh.insert(fh.begin() + p, T_1);
					if (LOCAL_DEBUG) r = TokensToStr(fh);
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
					if (T_1.type == Token::Type::Integer)
					{
						m = get<int>(T_1.value);
					}
					else if (T_1.type == Token::Type::Real)
					{
						m = get<double>(T_1.value);
					}
					m = (-1) * m;
					Token T_2 = SetToken(m);
					fh.insert(fh.begin(), T_2); // Добавление вперед очереди.
					if (LOCAL_DEBUG) r = TokensToStr(fh);
					f = r;
				}
				else if (T_1.type == Token::Type::Algebra)
				{
					fh.pop_front();
					deque<Token> es = exprToTokens("(-1)*a");
					es.pop_back();
					es.push_back(T_1); // Замена символа a вставка в начало.
					fh.insert(fh.begin(), T_1);
					if (LOCAL_DEBUG) r = TokensToStr(fh);
					f = r;
				}
			}
		}
	}
}




string TokensToStr(deque<Token> fh)
{
	string s = "";
	for (Token token : fh)
	{
		if (token.type == Token::Type::Algebra ) {
			string f = get<string>(token.value);
			s = s + f;
		}
		else if (token.type == Token::Type::Integer ) {
			int m = get<int>(token.value);
			s = s + to_string(m);
		}
		else if (token.type == Token::Type::Real ) {
			double m = get<double>(token.value);
			s = s + to_string(m);
		}
		else if (token.type == Token::Type::Operator ) {
			char c = get<char>(token.value);
			s = s + c;
		}
		else if (token.type == Token::Type::Function )
		{
			Token::Function p = get<Token::Function>(token.value);
			string f = rfunc_name[p];
			s = s + f;
		}
	}
	return s;
}