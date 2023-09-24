#include "token.h"
#include <regex>

#define DEBUG 0

using namespace std;

Token::Token() : type(Type::Unknown), value(""), index(0), start_pos(0), last_pos(0), precedence(-1), rightAssociative(false) {}

Token::Token(const Type t, const string& s, const int prec, bool ra) : type(t), value(s), precedence(prec), rightAssociative(ra), index(0), start_pos(0), last_pos(0) {}

Token::Token(const Type t, const int m) : type(t), value(m), index(0), start_pos(0), last_pos(0), precedence(-1), rightAssociative(false) {}

Token::Token(const Type t, const double m) : type(t), value(m), index(0), start_pos(0), last_pos(0), precedence(-1), rightAssociative(false) {}

Token::Token(const Type t, const Token::Function m) : type(t), value(m), index(0), start_pos(0), last_pos(0), precedence(1), rightAssociative(false) {}

Token::Token(const Type t, const char c, const int prec, bool ra) : type(t), value(c), index(0), start_pos(0), last_pos(0), precedence(prec), rightAssociative(ra) {}

Token::Token(const Token& other) : type(other.type), value(other.value), index(other.index), start_pos(other.start_pos), last_pos(other.last_pos), precedence(other.precedence), rightAssociative(other.rightAssociative) {}


// string
Token::Token(const Type t, const string& s, const int index, const int start_pos, const int last_pos, const int prec , const bool ra) : type(t), value(s),
index(index), start_pos(start_pos), last_pos(last_pos), precedence(prec), rightAssociative(ra) {}

Token::Token(const Type t, const string& s, const int index, const int start_pos, const int last_pos) : type(t), value(s), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(-1), rightAssociative(false) {}
// char
Token::Token(const Type t, const char c, const int index,  const int start_pos, const int last_pos, const int prec , const bool ra) : type(t), value(c), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(prec), rightAssociative(ra) {}

Token::Token(const Type t , const char c , const int index , int prec , bool ra) : type(t), value(c), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(prec), rightAssociative(ra) {}

// int
Token::Token(const Type t, const int m, const int index, const int start_pos, const int last_pos) : type(t), value(m), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(-1), rightAssociative(false) {}
// double
Token::Token(const Type t, const double m, const int index, const int start_pos, const int last_pos) : type(t), value(m), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(-1), rightAssociative(false) {}

Token::Token(const Token& other, const int index, const int start_pos, const int last_pos) : type(other.type), value(other.value), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(other.precedence), rightAssociative(other.rightAssociative) {}


Token::Token(const Type t, const Token::Function m, const int index, const int start_pos, const int last_pos) : type(t), value(m), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(1), rightAssociative(false) {}

void Token::SetValue(const variant<string, char, int, double, Token::Function>& newValue) {
	this->value = newValue;
}


variant<string, char, int, double, Token::Function> Token::GetValue() const {
	return this->value;
}

map< string, Token::Function>  func_name =
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
	{ "arcsh"     , Token::Function::ARCSH } ,
	{ "arcch"     , Token::Function::ARCCH } ,
	{ "arcth"     , Token::Function::ARCTH } ,
	{ "arccth"    , Token::Function::ARCCTH } ,
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
	  { Token::Function::ARCSH  , "arcsh"} ,
	  { Token::Function::ARCCH  , "arcch"} ,
	  { Token::Function::ARCTH  , "arcth"} ,
	  { Token::Function::ARCCTH , "arccth" } ,
	  { Token::Function::ABS , "abs"} ,
	  { Token::Function::LOG , "log"} ,
	  { Token::Function::POW , "pow"}
};

map<Token::Type, string > type_token = { { Token::Type::Unknown , "Unknown"} ,
										 { Token::Type::Number , "Number"} ,
										 { Token::Type::Integer , "Integer" } ,
										 { Token::Type::Real , "Real"} ,
										 { Token::Type::LongArithmetic , "LongArithmetic"} ,
										 { Token::Type::Operator , "Operator" } ,
										 { Token::Type::LeftParen , "LeftParen" } ,
										 { Token::Type::RightParen , "RightParen" } ,
										 { Token::Type::Algebra , "Algebra" } ,
										 { Token::Type::Ration, "Ration" } ,
										 { Token::Type::ComplexNumber , "ComplexNumber"},
										 { Token::Type::Function , "Function" },
										 { Token::Type::Comma , "Comma" }
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

ostream& operator<<(ostream& os, const Token::Type p)
{
	string s = type_token[p];
	os << s;
	return os;
}

unordered_set<string> operator_info_two = { "+" , "-", "/", "*", "^" };
unordered_set<string> operator_info_one = { "!" };
unordered_set<string> func_info_one = { "sin", "cos", "tg", "ctg", "ln", "exp", "sec", "cosec", "arcsin", "arccos", "arctg", "arcctg",
"sqrt", "sh", "ch", "th", "cth", "arcsh", "arcch", "arcth", "arccth", "abs", "factorial" };
unordered_set<string> func_info_two = { "log" , "pow" , "S" , "Integral" };
unordered_set<string> func_info_free = { "D" , "Z" , "P" , "Derivate" };
unordered_set<string> func_info = { "sin", "cos", "tg", "ctg", "ln", "exp", "sec", "cosec", "arcsin", "arccos", "arctg", "arcctg",
"sqrt", "sh", "ch", "th", "cth", "arcsh", "arcch", "arcth", "arccth", "abs", "factorial" , "log" , "pow" };

struct Operator {
	int precedence;
	char associativity;
};

map<char, Operator> operator_info = { { '+' , { 2, 'L'}} ,
										{'-' , { 2, 'L'}},
										{'/' , { 3, 'L'}},
										{'*' , { 3, 'L'}},
										{'^' , { 4, 'R'}},
};


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
	if (T.type == Token::Type::Algebra || T.type == Token::Type::Number || T.type == Token::Type::Integer ||
		T.type == Token::Type::Real || T.type == Token::Type::Ration || T.type == Token::Type::LongArithmetic ||
		T.type == Token::Type::ComplexNumber)
		return true;
	else
		return false;
}

bool f_opr_two(const Token& T) {
	Token token = T;
	bool B = false;
	if (T.type == Token::Type::Operator)
		B = true;
	else if (T.type == Token::Type::Function)
	{
		Token::Function p = get<Token::Function>(T.value);
		switch (p)
		{
		case Token::Function::LOG: { B = true; break; }
		case Token::Function::POW: { B = true; break; }
		}
	}
	else return false;
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
	else return false;
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

template <typename T>
T sign(T x)
{
	if (x > 0) return 1;
	else if (x == 0) return 0;
	else if (x < 0) return -1;
}

int CompareString(string s, string f)
{
	int m, n, r;
	n = s.size();
	m = f.size();
	if (n != m) return sign(m - n);
	else
	{
		for (int i = 0; i < n; i++)
		{
			int t = int(s[i]) - int(f[i]);
			if (t == 0) continue;
			else if (t < 0) return -1;
			else if (t > 0) return 1;
		}
		return 0;
	}
}

deque<Token> exprToTokens(const string& expr, int& index, BW& C, string q = "DEFAULT") {
	// q принимает 2 значения - DEFAULT и ORDERING.
	// Ошибки генерируемые функцией - слишком большое целое или вещественное число.
	deque<Token> tokens;
	deque<tuple<int, int>> positions;
	deque<tuple<int, int>> ks;
	if (q == "DEFAULT") index = 0;
	if (expr.empty()) return tokens;
	const char* const c_begin = expr.c_str();
	const char* b = &expr[0];
	int i = 0, j = 0; // Заменители индексов.
	for (const char* p = expr.c_str(); *p; ++p, i++) {
		char c = *p;
		if (isblank(c)) {
			// do nothing
		}
		else if (isdigit(c))
		{
			if (c == '.')
			{
				int pr = -1;
				// tokens.push_back(Token{ Token::Type::Unknown, string(p, p), index++ , int(b-c_begin) , int(p-c_begin) , pr , false });
				tokens.push_back(Token{ Token::Type::Unknown, string(p, p), index++ , j , i , pr , false });
				positions.push_back(make_tuple(j, i));
				cout << "Неверная запись десятичного числа" << endl;
			}
			Token::Type t = Token::Type::Integer;
			b = p;
			j = i;
			while (isdigit(c) || c == '.') {
				if (c == '.') t = Token::Type::Real;
				++p;
				++i;
				c = *p;
			}
			const string s = string(b, p);
			if (t == Token::Type::Integer)
			{
				// tokens.push_back(Token{ t, m , index++ , int(b - c_begin) , int(p - c_begin) });
				string f = to_string(INT_MAX);
				int r = CompareString(s, f);
				if (r >= 0)
				{
					int m = stoi(s);
					tokens.push_back(Token{ t, m , index++ , j , i });
					positions.push_back(make_tuple(j, i));
				}
				else // Ошибка слишком длинное число , нужна длинная арифметика.
				{
					ks.push_back(make_tuple(j, i));
					break;
				}
			}
			else if (t == Token::Type::Real)
			{
				if (s.size() <= 308)
				{
					double m = stod(s);
					// tokens.push_back(Token{ t, m , index++ , int(b - c_begin) , int(p - c_begin) });
					tokens.push_back(Token{ t, m , index++ , j , i });
					positions.push_back(make_tuple(j, i));
				}
				else // Ошибка слишком длинное число , нужна длинная арифметика.
				{
					ks.push_back(make_tuple(j, i));
					break;
				}
			}
			--p;
			--i;
		}
		else
			if (isliter(c))
			{
				b = p;
				j = i;
				while (isliter(c)) {
					++p;
					++i;
					c = *p;
				}
				const string s = string(b, p);
				int u_start = b - c_begin;
				int u_last = p - c_begin;
				if (func_info.count(s))
				{
					// tokens.push_back(Token{ Token::Type::Function, func_name[s] , index++ , u_start , u_last });
					tokens.push_back(Token{ Token::Type::Function, func_name[s] , index++ , j , i });
					positions.push_back(make_tuple(j, i));
				}
				else
				{
					// tokens.push_back(Token{ Token::Type::Algebra, s , index++ , u_start , u_last , -1 , false });
					tokens.push_back(Token{ Token::Type::Algebra, s , index++ , j , i , -1 , false });
					positions.push_back(make_tuple(j, i));
				}
				p--;
				i--;
				continue;

			}
			else if (c == ',')
			{
				string s = string(p, p + 1);
				// tokens.push_back(Token{ Token::Type::Comma , c , index++ , int(p - c_begin) , int(p - c_begin + 1) , -1 , false });
				tokens.push_back(Token{ Token::Type::Comma , c , index++ , i , i + 1, -1 , false });
				positions.push_back(make_tuple(i, i + 1));
			}
			else {
				Token::Type t = Token::Type::Unknown;
				int pr = -1;            // приоритет
				bool ra = false;        // rightAssociative
				bool is_operator = false;
				switch (c) {
				default:                                    break;
				case '(':   t = Token::Type::LeftParen;     break;
				case ')':   t = Token::Type::RightParen;    break;
				case '^':   is_operator = true;   break;
				case '*':   is_operator = true;    break;
				case '/':   is_operator = true;    break;
				case '+':   is_operator = true;    break;
				case '-':   is_operator = true;    break;
				}
				if (is_operator)
				{
					t = Token::Type::Operator;
					pr = operator_info[c].precedence;
					ra = !(operator_info[c].associativity == 'L');
				}
				// tokens.push_back(Token{ t, c, index++ ,  u_start , u_last , pr, ra });
				tokens.push_back(Token{ t, c, index++ , i , i + 1, pr , ra });
				positions.push_back(make_tuple(i, i + 1));
				while (0); // Для точки останова.
			}
	}
	C.position = positions;
	C.broken_pos = ks;
	if (!ks.empty()) return {};
	else return tokens;
}

deque<Token> exprToTokens(const string& expr, int& index, string q)
{
	BW C = BW();
	deque<Token> fh = exprToTokens(expr, index, C, q);
	return fh;
}


deque<Token> exprToTokens(const string& expr, BW& C)
{
	int index = 0;
	deque<Token> fs = exprToTokens(expr, index, C, "DEFAULT");
	return fs;
}

deque<Token> exprToTokens(const string& expr)
{
	int index = 0;
	BW C = BW();
	deque<Token> fs = exprToTokens(expr, index, C, "DEFAULT");
	return fs;
}

Token _SetToken(const int m)
{
	Token T = Token{ Token::Type::Integer, m };
	return T;
}

Token _SetToken(const double m)
{
	Token T = Token{ Token::Type::Real, m };
	return T;
}

Token _SetToken(const int m, int& index)
{
	Token T = Token{ Token::Type::Integer, m , index++ , 0 , 1 };
	return T;
}

Token _SetToken(const double m, int& index)
{
	Token T = Token{ Token::Type::Real, m , index++ , 0 , 1 };
	return T;
}


Token _SetToken(const string& expr, int& index) // фунция возвращает первый токен , если их несколько.
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
					Token T = Token{ Token::Type::Unknown, string(p, p), index++ , 0 , 1 ,pr,  false };
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
					Token T = Token{ t, m , index++ , 0 , 1 };
					return T;
				}
				else if (t == Token::Type::Real)
				{
					double m = stod(s);
					Token T = Token{ t, m ,index++ , 0 , 1 };
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
						Token T = Token{ Token::Type::Function, func_name[s] , index++ , 0 , 1 };
						return T;
					}
					else
					{
						Token T = Token{ Token::Type::Algebra, s , index++ , 0 , 1 , -1 , false };
						return T;
					}
				}
				else {
					Token::Type t = Token::Type::Unknown;
					int pr = -1;            // приоритет
					bool ra = false;        // rightAssociative
					bool is_operator = false;
					switch (c) {
					default:                                    break;
					case '(':   t = Token::Type::LeftParen;     break;
					case ')':   t = Token::Type::RightParen;    break;
					case '^':   is_operator = true;   break;
					case '*':   is_operator = true;   break;
					case '/':   is_operator = true;   break;
					case '+':   is_operator = true;   break;
					case '-':   is_operator = true;   break;
					}
					if (is_operator)
					{
						t = Token::Type::Operator;
						pr = operator_info[c].precedence;
						ra = !(operator_info[c].associativity == 'L');
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
		fs = exprToTokens(expr, index, "ORDERING");
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
	Token token = Token(Token::Type::Function, f_able, index, 0, 1);
	return token;
}

Token _SetToken(const Token::Function f_able, int& index)
{
	Token token = Token(Token::Type::Function, f_able, index, 0, 1);
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
		Token T = _SetToken(m, index);
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
						q = (double)get<int>(T_1.value);
						q = (-1) * q;
					}
					else if (T_1.type == Token::Type::Real)
					{
						q = get<double>(T_1.value);
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
			if (get<char>(T_0.value) == '-')  // Этот случай не пересекается с предыдущим случаем.
			{   // Случай когда унарный минус стоит в начале строки.
				string f, r;
				if (T_1.type == Token::Type::Number || T_1.type == Token::Type::Integer || T_1.type == Token::Type::Real)
				{
					fh.pop_front();
					fh.pop_front();
					double m = -1;
					if (T_1.type == Token::Type::Integer)
					{
						m = (double)get<int>(T_1.value);
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




string TokensToStr(const deque<Token> fh)
{
	string s = "";
	for (Token token : fh)
	{
		if (token.type == Token::Type::Algebra) {
			string f = get<string>(token.value);
			s = s + f;
		}
		else if (token.type == Token::Type::Integer) {
			int m = get<int>(token.value);
			s = s + to_string(m);
		}
		else if (token.type == Token::Type::Real) {
			double m = get<double>(token.value);
			s = s + to_string(m);
		}
		else if (token.type == Token::Type::Operator) {
			char c = get<char>(token.value);
			s = s + c;
		}
		else if (token.type == Token::Type::Function)
		{
			Token::Function p = get<Token::Function>(token.value);
			string f = rfunc_name[p];
			s = s + f;
		}
	}
	return s;
}