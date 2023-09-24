#include "Shanting_yard.h"
#include <iostream>
#include <vector>
#include <stack>


deque<Token> shuntingYard(const deque<Token>& tokens) {
	deque<Token> queue;
	vector<Token> stack;

	// ���� ���� ������ ��� ������:
	for (auto token : tokens) {
		// ������ �����
		switch (token.type) {
		case Token::Type::Number:
			// ���� ����� ������������ ����� �����, �� �������� ��� � ������� ������
			queue.push_back(token);
			break;
		case Token::Type::Algebra:
			queue.push_back(token);
			break;

		case Token::Type::Operator:
		{
			// ���� ����� �������� ����������, o1, ��:
			const auto o1 = token;
			// ���� ���� ����� ���������,
			while (!stack.empty()) {

				// o2, � ������� ����� �����, �
				const auto o2 = stack.back();

				// ���� o1 �������� �����������������, � ��� ��������� �����
				// *������ ��� �����* �������� o2,
			   // ��� o1, ���� ������������ ������, � ����� ���������

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

double PolishCalculation(deque<Token> es) {
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