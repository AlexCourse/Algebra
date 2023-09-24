#ifndef ALGEBRA_NODE_H
#define ALGEBRA_NODE_H
#include <deque>
#include <vector>
#include <stack>
#include <iterator>
#include "token.h"
// #include <windows.h> // ƒл€ цветного консольного вывода.

static std::string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";

enum LR {
    LEFT, //левый потомок добавить
    RIGHT, // правый потомок добавить
    TOP,  // элемент в корне
    ONE   // оператор с одним аргументом
};


class Algebra_Node {
public:
    Token data;
    Algebra_Node* left;
    Algebra_Node* right;
    Algebra_Node();
    ~Algebra_Node();
    Algebra_Node(const Token& data, Algebra_Node* left = nullptr, Algebra_Node* right = nullptr);
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
    bool Is_Algebric(); // ¬ дереве могут присутсвовать алгебраические выражени€.
    bool Is_Numeric(); // ¬ дереве присутствуют только числа.
    Algebra_Tree() { this->root = nullptr; }
    Algebra_Tree(Algebra_Node* node);
    Algebra_Tree& CopyTree();
    Algebra_Tree& AddSubtree(Algebra_Node* node, LR lr);
    Algebra_Tree& SetIndexTree_T();
    void FindValueD_T(std::string c, std::vector<std::vector<char>>& paths);
    void FindValueW_T(std::string c, std::vector<std::vector<char>>& paths);
    void Print_Tree_T();
    void TreeToPolish_T();
    Algebra_Tree& TreeExprReplaceD_T(const std::string c, const std::variant<std::string, char, int, double, Token::Function> s); // ƒальше перегрузки заменить на шаблоны.
    Algebra_Tree& TreeExprReplaceW_T(const std::string c, const std::variant<std::string, char, int, double, Token::Function> s);
    void TreeRExprReplaceOnSubTreeD_T(const std::string c, Algebra_Node* second);
    void TreeRExprReplaceOnSubTreeW_T(const std::string c, Algebra_Node* second);
    double FunctionValue_T(double value, std::string symbol);
    std::string TreeToInfix_T();
    typedef Algebra_Tree iterator;
    // ~Algebra_Tree(); // chat 


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
std::string PostfixToInfix(std::vector<Token>& fs);
std::string PostfixToInfix(std::deque<Token>& fs);
void TreeToPolish(Algebra_Node* root, std::vector<Token>& kh);
void TreeToPolish(Algebra_Node* root, std::deque<Token>& kh);

Algebra_Node* SetNode(int m);
Algebra_Node* SetNode(double m);
Algebra_Node* SetNode(const std::string s);
Algebra_Node* SetNode(int m , int& index);
Algebra_Node* SetNode(double m , int& index);
Algebra_Node* SetNode(const std::string s , int& index);


Algebra_Tree& SetAlgebricTree(const std::string s);
Algebra_Node* SetOperatorTree(const std::string s);
Algebra_Node* SetOperatorTree(const std::string s , int& index);

Algebra_Node* TreeRExprReplaceOnSubTreeD(Algebra_Node* first, const std::string c, Algebra_Node* second);
Algebra_Node* TreeRExprReplaceOnSubTreeW(Algebra_Node* first, const std::string c, Algebra_Node* second);
double FunctionValueM(std::string expr, std::map<std::string, double>& ds);

Algebra_Node* TreeExprReplaceR(Algebra_Node* root, const std::string c, const std::variant<std::string, char, int, double, Token::Function> s);


template<typename T>
void _FindValueD(Algebra_Node* root, T c, std::vector<std::vector<char>>& paths);

std::string TreeToInfix(Algebra_Node* root);
void RecursiveDestructor(Algebra_Node* root);

#endif
