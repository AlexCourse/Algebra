#include "Shanting_yard.h"
#include <iostream>
#include <vector>
#include <stack>


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
				cout << "Ќеверна€ запись дес€тичного числа" << std::endl;
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

deque<Token> shuntingYard(const deque<Token>& tokens) {
	deque<Token> queue;
	vector<Token> stack;

	// ѕока есть токены дл€ чтени€:
	for (auto token : tokens) {
		// „итать токен
		switch (token.type) {
		case Token::Type::Number:
			// ≈сли токен представл€ет собой число, то добавьте его в очередь вывода
			queue.push_back(token);
			break;
		case Token::Type::Algebra:
			queue.push_back(token);
			break;

		case Token::Type::Operator:
		{
			// ≈сли токен €вл€етс€ оператором, o1, то:
			const auto o1 = token;
			// пока есть токен оператора,
			while (!stack.empty()) {

				// o2, в верхней части стека, и
				const auto o2 = stack.back();

				// либо o1 €вл€етс€ левоассоциативным, и его приоритет равен
				// *меньше или равно* значению o2,
			   // или o1, если ассоциативно справа, и имеет приоритет

				if (
					(!o1.rightAssociative && o1.precedence <= o2.precedence)
					|| (o1.rightAssociative && o1.precedence < o2.precedence)
					) {
					stack.pop_back();

					queue.push_back(o2);

					continue;
				}
				break;
			}
			stack.push_back(o1);
		}
		break;

		case Token::Type::LeftParen:
			stack.push_back(token);
			break;

		case Token::Type::RightParen:
		{
			bool match = false;

			while (!stack.empty() && stack.back().type != Token::Type::LeftParen) {
				queue.push_back(stack.back());
				stack.pop_back();
				match = true;
			}

			stack.pop_back();

			if (!match && stack.empty()) {
				printf("RightParen error (%s)\n", token.str.c_str());
				return {};
			}
		}
		break;

		default:
			printf("error (%s)\n", token.str.c_str());
			return {};
		}
	}
	while (!stack.empty()) {
		if (stack.back().type == Token::Type::LeftParen) {
			printf("Mismatched parentheses error\n");
			return {};
		}
		queue.push_back(std::move(stack.back()));
		stack.pop_back();
	}

	return queue;
}

double PolishCalculation(std::deque<Token> es) {
	vector<float> stack;
	vector<char> cst;

	while (!es.empty()) {
		string op;

		const auto token = es.front();
		es.pop_front();
		switch (token.type) {
		case Token::Type::Number:
			stack.push_back(stof(token.str));
			op = "Push " + token.str;
			break;
		case Token::Type::Algebra:
		{
			cst.push_back(token.str[0]);
			op = "Push" + token.str[0];

		}
		case Token::Type::Operator:
		{
			const auto rhs = stack.back();
			stack.pop_back();
			const auto lhs = stack.back();
			stack.pop_back();
			switch (token.str[0]) {
			default:
				printf("Operator error [%s]\n", token.str.c_str());
				exit(0);
				break;
			case '^':
				stack.push_back(static_cast<int>(pow(lhs, rhs)));
				break;
			case '*':
				stack.push_back(lhs * rhs);
				break;
			case '/':
				stack.push_back(lhs / rhs);
				break;
			case '+':
				stack.push_back(lhs + rhs);
				break;
			case '-':
				stack.push_back(lhs - rhs);
				break;
			}

			op = "Push " + to_string(lhs) + " " + token.str + " " + to_string(rhs);
		}
		break;

		default:
			printf("Token error\n");
			exit(0);
		}
	}
	return stack.back();

}