#include "Shanting_yard.h"
#include <iostream>
#include <vector>
#include <stack>
#define DEBUG 1


deque<Token> shuntingYard(const deque<Token>& tokens) {
	deque<Token> queue;
	vector<Token> stack;

	// ѕока есть токены дл€ чтени€:
	for (auto T : tokens) {
		// „итать токен
		switch (T.type) {
		case Token::Type::Number:
			// ≈сли токен представл€ет собой число, то добавьте его в очередь вывода
			queue.push_back(T);
			break;
		case Token::Type::Integer:
			// ≈сли токен представл€ет собой число, то добавьте его в очередь вывода
			queue.push_back(T);
			break;
		case Token::Type::Real:
			// ≈сли токен представл€ет собой число, то добавьте его в очередь вывода
			queue.push_back(T);
			break;
		case Token::Type::Algebra:
			queue.push_back(T);
			break;

		case Token::Type::Operator:
		{
			// ≈сли токен €вл€етс€ оператором, o1, то:
			const auto o1 = T;
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
			stack.push_back(T);
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
				printf("RightParen error (%s)\n", get<string>(T.value));
				return {};
			}
		}
		break;

		default:
			printf("error (%s)\n", get<string>(T.value));
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

double PolishCalculation(deque<Token> es) 
{
	vector<double> stack;
	vector<string> cst;

	while (!es.empty()) {
		string op;

		const auto T = es.front();
		es.pop_front();
		switch (T.type) {
		case Token::Type::Integer:
			stack.push_back(get<int>(T.value));
			if (DEBUG) op = "Push " + get<string>(T.value);
			break;
		case Token::Type::Real:
			stack.push_back(get<double>(T.value));
			if (DEBUG) op = "Push " + get<string>(T.value);
			break;
		case Token::Type::Algebra:
		{
			cst.push_back(get<string>(T.value));
			if (DEBUG) op = "Push" + get<string>(T.value);

		}
		case Token::Type::Operator:
		{
			if (f_opr_two(T))
			{
				const auto rhs = stack.back();
				stack.pop_back();
				const auto lhs = stack.back();
				stack.pop_back();
				switch (get<string>(T.value)[0]) {
				default:
					printf("Operator error [%s]\n", get<string>(T.value));
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

				op = "Push " + to_string(lhs) + " " + get<string>(T.value) + " " + to_string(rhs);
				break;
			}
			else if (f_opr_one(T))
			{
				const auto x = stack.back();
				stack.pop_back();
				string c = get<string>(T.value);
				if (c == "exp") { stack.push_back(exp(x)); }
				if (c == "ln") { stack.push_back(log1p(x)); }
				if (c == "sin") { stack.push_back(sin(x)); }
				if (c == "cos") { stack.push_back(cos(x)); }
				if (c == "tg") { stack.push_back(tan(x)); }
				if (c == "ctg") { stack.push_back(1 / tan(x)); }
				if (c == "arcsin") { stack.push_back(asin(x)); }
				if (c == "arccos") { stack.push_back(acos(x)); }
				if (c == "arctg") { stack.push_back(atan(x)); }
				if (c == "arcctg") { stack.push_back(atan(1 / x)); }
				if (c == "sh") { stack.push_back(sinh(x)); }
				if (c == "ch") { stack.push_back(cosh(x)); }
				if (c == "th") { stack.push_back(tanh(x)); }
				if (c == "cth") { stack.push_back(1 / tanh(x)); }
				if (c == "arsh") { stack.push_back(asinh(x)); }
				if (c == "arch") { stack.push_back(acosh(x)); }
				if (c == "arth") { stack.push_back(atanh(x)); }
				if (c == "arcth") { stack.push_back(atanh(1 / x)); }

			}
		}
		case Token::Type::Function:
		{
			if (f_opr_one(T))
			{
				const auto x = stack.back();
				stack.pop_back();
				string c = get<string>(T.value);
				if (c == "exp") { stack.push_back(exp(x)); }
				if (c == "ln") { stack.push_back(log1p(x)); }
				if (c == "sin") { stack.push_back(sin(x)); }
				if (c == "cos") { stack.push_back(cos(x)); }
				if (c == "tg") { stack.push_back(tan(x)); }
				if (c == "ctg") { stack.push_back(1 / tan(x)); }
				if (c == "arcsin") { stack.push_back(asin(x)); }
				if (c == "arccos") { stack.push_back(acos(x)); }
				if (c == "arctg") { stack.push_back(atan(x)); }
				if (c == "arcctg") { stack.push_back(atan(1 / x)); }
				if (c == "sh") { stack.push_back(sinh(x)); }
				if (c == "ch") { stack.push_back(cosh(x)); }
				if (c == "th") { stack.push_back(tanh(x)); }
				if (c == "cth") { stack.push_back(1 / tanh(x)); }
				if (c == "arsh") { stack.push_back(asinh(x)); }
				if (c == "arch") { stack.push_back(acosh(x)); }
				if (c == "arth") { stack.push_back(atanh(x)); }
				if (c == "arcth") { stack.push_back(atanh(1 / x)); }
			}
		}

		default:
			printf("Token error\n");
			exit(0);
		}
	}
	return stack.back();

}

