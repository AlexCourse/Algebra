#pragma once

#ifndef ALGEBRA_NODE_H
#define ALGEBRA_NODE_H
#include <deque>
#include <vector>
#include <stack>
#include <iterator>
#include <set>
#include "token.h"
#include "Enumerate.h"
#include "Shunting_yard.h"

// #include <windows.h> // Для цветного консольного вывода.

static std::string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";

enum LR {
    LEFT, //левый потомок добавить
    RIGHT, // правый потомок добавить
    TOP,  // элемент в корне
    ONE   // оператор с одним аргументом
};

class Debug_concept
{
public:
    Debug_concept();
    Debug_concept(int index);
    int index;
    int call_order; // Уровень вызова в производной.
    std::map<int, std::set<int>> colored;
    std::set<int> red; // Узлы в которых неверно вычислена производная.
    std::set<int> orange; // Узлы нечетного уровня.
    std::set<int> white; // Узлы четного уровня.
};

class Algebra_Node {
public:
    Token data;
    Algebra_Node* left;
    Algebra_Node* right;
    Algebra_Node();
    ~Algebra_Node();
    Algebra_Node(const Token& data, Algebra_Node* left = nullptr, Algebra_Node* right = nullptr);
    Algebra_Node(const Token& data, Debug_concept& W, Algebra_Node* left = nullptr, Algebra_Node* right = nullptr);
    std::string toString();
    void addLeftNode(Algebra_Node* Q);
    void addRightNode(Algebra_Node* Q);

};

class Algebra_Tree {
private:
    Algebra_Node* root;
    Algebra_Node* CloneTree(Algebra_Node* root);
public:
    std::vector<Token> polish;
    bool Is_Algebric(); // В дереве могут присутсвовать алгебраические выражения.
    bool Is_Numeric(); // В дереве присутствуют только числа.
    Algebra_Tree() { this->root = nullptr; }
    Algebra_Tree(Algebra_Node* node);
    Algebra_Tree& const CopyTree();
    Algebra_Tree& AddSubtree(Algebra_Node* node, LR lr);
    Algebra_Tree& SetIndexTree_T();
    void FindValueD_T(std::string c, std::vector<std::vector<char>>& paths);
    void FindValueW_T(std::string c, std::vector<std::vector<char>>& paths);
    void Print_Tree_T();
    void TreeToPolish_T();
    Algebra_Tree& TreeExprReplaceD_T(const std::string c, const std::variant<std::string, char, int, double, Token::Function> s); // Дальше перегрузки заменить на шаблоны.
    Algebra_Tree& TreeExprReplaceW_T(const std::string c, const std::variant<std::string, char, int, double, Token::Function> s);
    void TreeRExprReplaceOnSubTreeD_T(const std::string c, Algebra_Node* second);
    void TreeRExprReplaceOnSubTreeW_T(const std::string c, Algebra_Node* second);
    void TreeRExprReplaceOnSubTreeD_T(const std::string c, Algebra_Node* second, Debug_concept& W);
    void TreeRExprReplaceOnSubTreeW_T(const std::string c, Algebra_Node* second, Debug_concept& W);
    double FunctionValue_T(double value, std::string symbol);
    std::string TreeToInfix_T();
    Algebra_Tree operator+(const Algebra_Tree& other);
    Algebra_Tree operator-(const Algebra_Tree& other);
    Algebra_Tree operator*(const Algebra_Tree& other);
    Algebra_Tree operator/(const Algebra_Tree& other);
    Algebra_Tree operator^(const Algebra_Tree& other);
    typedef Algebra_Tree iterator;
    ~Algebra_Tree(); 


};


void BypassTreeD(Algebra_Node* root);
void BypassTreeW(Algebra_Node* root);
void Print_Tree_R(Algebra_Node const* node, std::string const& prefix, bool root, bool last);
void Print_Tree_Selected_R(Algebra_Node const* node, Algebra_Node* const selectedNode, std::string const& prefix, bool root, bool last);
void Print_Tree(Algebra_Node const* node, std::string const& prefix, bool root, bool last);
void Print_Tree_R_ColoredSelectNode(Algebra_Node const* node, Algebra_Node* const selectedNode, std::string const& prefix, bool root, bool last);
void FindValueW(Algebra_Node* root, std::string c, std::vector<std::vector<char>>& paths);
void FindValueD(Algebra_Node* root, std::string c, std::vector<std::vector<char>>& paths);
Algebra_Node* TreeExprReplaceR(Algebra_Node* root, const std::string c, const std::variant<std::string, char, int, double, Token::Function> s);
Algebra_Node* TreeExprReplaceW(Algebra_Node* root, const std::string c, const std::variant<std::string, char, int, double, Token::Function> s);
Algebra_Node* TreeExprReplaceD(Algebra_Node* root, const std::string c, const std::variant<std::string, char, int, double, Token::Function> s);
bool CompareTrees(Algebra_Node* root1, Algebra_Node* root2);
Algebra_Node* GetOperand(Algebra_Node* root, LR lr);

Algebra_Node* PolishToTree(std::deque<Token> fh);
void TreeToPolish(Algebra_Node* root, std::vector<Token>& kh);
void TreeToPolish(Algebra_Node* root, std::deque<Token>& kh);

Algebra_Node* SetNode(const char c);
Algebra_Node* SetNode(const int m);
Algebra_Node* SetNode(const double m);
Algebra_Node* SetNode(const std::string s);
Algebra_Node* SetNode(const int m, int& index);
Algebra_Node* SetNode(const double m, int& index);
Algebra_Node* SetNode(const std::string s, int& index);


Algebra_Tree& SetAlgebricTree(const std::string s);
Algebra_Node* SetOperatorTree(const std::string s);
Algebra_Node* SetOperatorTree(const std::string s, int& index);

Algebra_Node* TreeRExprReplaceOnSubTreeD(Algebra_Node* first, const std::string c, Algebra_Node* second);
Algebra_Node* TreeRExprReplaceOnSubTreeW(Algebra_Node* first, const std::string c, Algebra_Node* second);
Algebra_Node* TreeRExprReplaceOnSubTreeD(Algebra_Node* first, const std::string c, Algebra_Node* second, Debug_concept& W);
Algebra_Node* TreeRExprReplaceOnSubTreeW(Algebra_Node* first, const std::string c, Algebra_Node* second, Debug_concept& W);

double FunctionValueM(std::string expr, std::map<std::string, double>& ds);

Algebra_Node* TreeExprReplaceR(Algebra_Node* root, const std::string c, const std::variant<std::string, char, int, double, Token::Function> s);

Algebra_Node* _CloneTree(Algebra_Node* root);
Algebra_Node* _CloneTree(Algebra_Node* root, Debug_concept& W);

template<typename T>
void _FindValueD(Algebra_Node* root, T c, std::vector<std::vector<char>>& paths);

std::string TreeToInfix(Algebra_Node* root);
void RecursiveDestructor(Algebra_Node* root);

#endif

