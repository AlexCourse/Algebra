#include "token.h"
#include <regex>
#define DEBUG 1

Token::Token() : type(Type::Unknown), str(""), precedence(-1), rightAssociative(false) {}


Token::Token(Type t, const string& s, int prec, bool ra)
    : type(t), str(s), precedence(prec), rightAssociative(ra) {}

Token::Token(const Token& other)
    : type(other.type), str(other.str), precedence(other.precedence), rightAssociative(other.rightAssociative) {}

Token Token::operator=(const Token other) {
    return Token(other);
}

ostream& operator<<(ostream& os, const Token& token) {
    os << token.str;
    return os;
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



map<char, Operator> operator_info = { { '+' , { 2, "L" }} ,
										{'-' , { 2, "L" }},
										{'/' , { 3, "L" }},
										{'*' , { 3, "L" }},
										{'^' , { 4, "R" }},
};


bool f_arg(const Token& T)
{
	if (T.type == Token::Type::Algebra || T.type == Token::Type::Number) return true;
	else return false;
}
bool f_opr_two(const Token& T) {
	string p = T.str;
	if (operator_info_two.count(p) || func_info_two.count(p)) {
		return true;
	}
	return false;
}

bool f_opr_one(const Token& T) {
	string p = T.str;
	if (operator_info_one.count(p) || func_info_one.count(p)) {
		return true;
	}
	return false;
}

bool f_opr_free(const Token& T) {
	string p = T.str;
	if (func_info_free.count(p)) {
		return true;
	}
	return false;
}

bool isliter(char p)
{
	if ((p >= 'A' && p <= 'Z') || (p >= 'a' && p <= 'z'))
	{
		return true;
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
				tokens.push_back(Token{ Token::Type::Unknown, std::string(p, p), pr,  false });
				cout << "Неверная запись десятичного числа" << std::endl;
			}
			const auto* b = p;
			while (isdigit(*p) || (*p) == '.') {
				++p;
			}
			const auto s = std::string(b, p);
			tokens.push_back(Token{ Token::Type::Number, s });
			--p;
		}
		else
			if (isliter(*p))
			{
				const auto s = string(p, p + 1);
				tokens.push_back(Token{ Token::Type::Algebra, s });
				continue;
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
	Token T = Token{ Token::Type::Number, to_string(m) };
	return T;
}



Token SetToken(const string& expr) // фунция возвращает первый токен , если их несколько.
{ // Или можно передать одно отрицательное число.
	Token T;
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
				while (isdigit(*p) || (*p) == '.') {
					++p;
				}
				const auto s = std::string(b, p);
				Token T = Token{ Token::Type::Number, s };
				return T;
				--p;
			}
			else
				if (isliter(*p))
				{
					const auto s = string(p, p + 1);
					T = Token{ Token::Type::Algebra, s };
					return T;
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
	if (C.str == S.str) return true;
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
				if (T_1.str == "-") entries.push_back(i);
		iter[0] = iter[1];
		iter[1]++;
		i++;
	}
	while (0);

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
				if (T_1.type == Token::Type::Number)
				{  
					int q = stoi(T_1.str);
					q = (-1) * q;
					Token T_2 = SetToken(q);
					fh.erase(fh.begin() + p, fh.begin() + p + 4); // Функция странно удаляет
					if (DEBUG) r = TokensToStr(fh);
					f = r;
					fh.insert(fh.begin() + p, T_2);
					if (DEBUG) r = TokensToStr(fh);
					f = r;
				}
				else if (T_1.type == Token::Type::Algebra)
				{
					fh.erase(fh.begin() + p, fh.begin() + p + 4);
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
	Token& T_0 = fh.front();
	Token& T_1 = fh[1];
	if (T_0.str == "-")  // Этот случай не пересекается с предыдущим случаем.
	{   // Случай когда унарный минус стоит в начале строки.
		string f, r;
		if (T_1.type == Token::Type::Number)
		{
			fh.pop_front();
			int m = stoi(T_1.str);
			m = (-1) * m;
			T_1.str = to_string(m);
			if (DEBUG) r = TokensToStr(fh);
			f = r;
	    }
		else if (T_1.type == Token::Type::Algebra)
		{
			fh.pop_front();
			deque<Token> es = exprToTokens("(-1)*a");
			es.pop_back();
			es.push_back(T_1);
			fh.insert(fh.begin(), T_1);
			if (DEBUG) r = TokensToStr(fh);
			f = r;
		}
	}
}




string TokensToStr(deque<Token> fh)
{
	string s = "";
	for (Token T : fh)
	{
		s = s + T.str;
	}
	return s;
}