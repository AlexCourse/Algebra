#include "Shanting_yard.h"
#include <iostream>
#include <vector>
#include <stack>
#define DEBUG 1


deque<Token> shuntingYard(const deque<Token>& tokens) {
	deque<Token> eh;
	stack<Token> st; // �������� �� stack

	// ���� ���� ������ ��� ������:
	for (auto T : tokens) {
		// ������ �����
		switch (T.type) {
		case Token::Type::Number:
			eh.push_back(T); // ���� ����� ������������ ����� �����, �� �������� ��� � ������� ������
			break;
		case Token::Type::Integer:
			eh.push_back(T); // ���� ����� ������������ ����� �����, �� �������� ��� � ������� ������
			break;
		case Token::Type::Real:
			eh.push_back(T); // ���� ����� ������������ ����� �����, �� �������� ��� � ������� ������
			break;
		case Token::Type::Algebra:
			eh.push_back(T);
			break;
		case Token::Type::Function:
			st.push(T);
		case Token::Type::Comma:
		{
			bool B = false;
			while (!st.empty())
			{
				Token T_1 = st.top();
				if (T_1.type == Token::Type::LeftParen) { B = true; break; }
				else eh.push_back(T_1);
			}

		}
		case Token::Type::Operator:
		{
			// ���� ����� �������� ����������, o1, ��:
			const auto o1 = T;
			// ���� ���� ����� ���������,
			while (!st.empty()) {

				// o2, � ������� ����� �����, �
				const auto o2 = st.top();

				// ���� o1 �������� �����������������, � ��� ��������� �����
				// *������ ��� �����* �������� o2,
			   // ��� o1, ���� ������������ ������, � ����� ���������

				if (
					(!o1.rightAssociative && o1.precedence <= o2.precedence)
					|| (o1.rightAssociative && o1.precedence < o2.precedence)
					) {
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

			st.pop();

			if (!match && st.empty()) {
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
	vector<double> stack;
	vector<string> cst;
	string s;

	while (!es.empty()) {
		string op;

		Token T = es.front();
		es.pop_front();
		switch (T.type) {
		case Token::Type::Integer:
			stack.push_back(get<int>(T.value));
			if (DEBUG) op = "Push " + T.ToString();
			break;
		case Token::Type::Real:
			stack.push_back(get<double>(T.value));
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
				const auto rhs = stack.back();
				stack.pop_back();
				const auto lhs = stack.back();
				stack.pop_back();
				switch (get<string>(T.value)[0]) {
				default:
					printf("Operator error [%s]\n", get<string>(T.value));
					// exit(0);
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
			// exit(0);
		}
		
	}
	return stack.back();

}

