#ifndef ALGEBRA_NODE_H
#define ALGEBRA_NODE_H
#include <deque>
#include <vector>
#include <stack>
#include <iterator>
#include "token.h"

using namespace std;

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
        string toString();
        void addLeftNode(Algebra_Node* Q);
        void addRightNode(Algebra_Node* Q);

};

class Algebra_Tree {
    private:
        Algebra_Node* root;
        Algebra_Node* CloneTree(Algebra_Node* root);
    public:
        vector<Token> polish;
        bool Is_Algebric(); // ¬ дереве могут присутсвовать алгебраические выражени€.
        bool Is_Numeric(); // ¬ дереве присутствуют только числа.
        Algebra_Tree() { this->root = nullptr; }
        Algebra_Tree(Algebra_Node* node);
        Algebra_Tree& CopyTree();
        Algebra_Tree& AddSubtree(Algebra_Node* node, LR lr);
        void FindValueD_T(string c, vector<vector<char>>& paths);
        void FindValueW_T(string c, vector<vector<char>>& paths);
        void Print_Tree_T();
        void TreeToPolish_T();
        Algebra_Tree& TreeExprReplaceD_T(const string c, const string s);
        Algebra_Tree& TreeExprReplaceW_T(const string c, const string s);
        void TreeRExprReplaceOnSubTreeD_T(const string c, Algebra_Node* second);
        void TreeRExprReplaceOnSubTreeW_T(const string c, Algebra_Node* second);
        double FunctionValue_T(double value, string symbol);
        typedef Algebra_Tree iterator;
        // ~Algebra_Tree(); // chat 

    
};


void BypassTreeD(Algebra_Node* root);
void BypassTreeW(Algebra_Node* root);
void Print_Tree_R(Algebra_Node const* node, string const& prefix, bool root, bool last);
void Print_Tree(Algebra_Node const* node, string const& prefix, bool root, bool last);
void FindValueW(Algebra_Node* root, string c, vector<vector<char>>& paths);
void FindValueD(Algebra_Node* root, string c, vector<vector<char>>& paths);
Algebra_Node* TreeExprReplaceR(Algebra_Node* root, const string c, const string s);
Algebra_Node* TreeExprReplaceW(Algebra_Node* root, const string c, const string s);
Algebra_Node* TreeExprReplaceD(Algebra_Node* root, const string c, const string s);
bool CompareTrees(Algebra_Node* root1, Algebra_Node* root2);
Algebra_Node* GetOperand(Algebra_Node* root, LR lr);

Algebra_Node* PolishToTree(deque<Token> fh);
string PostfixToInfix(vector<Token>& fs);
void TreeToPolish(Algebra_Node* root, vector<Token>& kh);
void TreeToPolish(Algebra_Node* root, deque<Token>& kh);
Algebra_Node* SetNode(int m);
Algebra_Node* SetNode(const string s);
Algebra_Tree& SetAlgebricTree(const string s);
Algebra_Node* SetOperatorTree(const string s);
void TreeRExprReplaceOnSubTreeD(Algebra_Node* first, const string c, Algebra_Node* second);
void TreeRExprReplaceOnSubTreeW(Algebra_Node* first, const string c, Algebra_Node* second);
deque<Token> FToPolish(string expr);
double FunctionValueM(string expr, map<string, float> ds);
double FunctionValue(deque<Token> fh, double value, string symbol);
double FunctionValue(vector<Token> fh, double value, string symbol);

template<typename T> // ƒл€ типов int , double , string.
Algebra_Node* TreeExprReplaceRT(Algebra_Node* root, const string c, const T s);

#endif
