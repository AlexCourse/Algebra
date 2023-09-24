#ifndef ALGEBRA_NODE_H
#define ALGEBRA_NODE_H
#include <deque>
#include <vector>
#include <stack>
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

        Algebra_Node(const Token& data, Algebra_Node* left = nullptr, Algebra_Node* right = nullptr);
        string toString();
        void addLeftNode(Algebra_Node* Q);
        void addRightNode(Algebra_Node* Q);

};

class Algebra_Tree {
    Algebra_Node* root;
public:
    Algebra_Tree(Algebra_Node* node);
    Algebra_Tree& operator + (Algebra_Tree& other);
    Algebra_Tree& operator - (Algebra_Tree& other);
    Algebra_Tree& operator * (Algebra_Tree& other);
    
};


bool f_arg(const Token& T);
bool f_opr_two(const Token& T);
bool f_opr_one(const Token& T);

void Print_Tree_R(Algebra_Node const* node, string const& prefix, bool root, bool last);
void Print_Tree(Algebra_Node const* node, string const& prefix, bool root, bool last);
void ByPassTreeW(Algebra_Node* root);
void ByPassTreeD(Algebra_Node* root);
void TreeExprReplaceW(Algebra_Node* root, const string c, const string s);
void TreeExprReplaceD(Algebra_Node* root, const string c, const string s);
Algebra_Node* GetOperand(Algebra_Node* root, LR lr);

Algebra_Node* PolishToTree(deque<Token> fh);

#endif
