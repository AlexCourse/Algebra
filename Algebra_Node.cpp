#include "algebra_node.h"
#include <string>
#include <queue>
#include <unordered_set>
#define DEBUG 1

using namespace std;

Algebra_Node::Algebra_Node(const Token& data, Algebra_Node* left, Algebra_Node* right)
    : data(data), left(left), right(right) {}

string Algebra_Node::toString() {
    return data.str;
}

void Algebra_Node::addLeftNode(Algebra_Node* Q) {
    this->left = Q;
}

void Algebra_Node::addRightNode(Algebra_Node* Q) {
    this->right = Q;
}

unordered_set<string> operator_info_two = { "+" , "-", "/", "*", "^" };
unordered_set<string> operator_info_one = { "!" };
unordered_set<string> func_info_one = { "sin", "cos", "tg", "ctg", "ln", "exp", "sec", "cosec", "arcsin", "arccos", "arctg", "arcctg",
"sqrt", "sh", "ch", "th", "cth", "arsh", "arch", "arth", "arcth", "abs", "factorial" };
unordered_set<string> func_info_two = { "log" , "pow" , "S" , "Integral" };
unordered_set<string> func_info_free = { "D" , "Z" , "P" , "Derivate" };

static string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";

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


void Print_Tree_R(Algebra_Node const* node, string const& prefix = " ", bool root = true, bool last = true) {
    cout << prefix << (root ? "" : (last ? ch_udia_hor : ch_ver_hor)) << (node ? node->data.str : "") << endl;
    if (!node || (!node->left && !node->right))
        return;
    vector<Algebra_Node*> v{ node->left, node->right };
    for (size_t i = 0; i < v.size(); ++i)
        Print_Tree_R(v[i], prefix + (root ? "" : (last ? "  " : ch_ver_spa)), false, i + 1 >= v.size());
}

void Print_Tree(Algebra_Node const* node, string const& prefix = "", bool root = true, bool last = true) {
    stack<pair<Algebra_Node const*, string>> stack;
    stack.emplace(node, "");

    while (!stack.empty()) {
        auto pair = stack.top();
        stack.pop();

        node = pair.first;
        string cur_prefix = prefix + (root ? "" : (pair.second.empty() ? "" : (last ? ch_udia_hor : ch_ver_hor)));

        cout << cur_prefix << (node ? node->data.str : "") << endl;

        if (node && (node->left || node->right)) {
            vector<Algebra_Node*> v{ node->left, node->right };

            for (size_t i = 0; i < v.size(); ++i) {
                stack.emplace(v[i], cur_prefix + (root ? "" : (pair.second.empty() ? "" : (last ? "  " : ch_ver_spa))));
                last = (i + 1 >= v.size());
            }
        }
    }
}


Algebra_Node* PolishToTree(deque<Token> fh) {
    vector<Algebra_Node*> fs;
    for (Token p : fh) {
        Algebra_Node* T = new Algebra_Node(p);
        fs.push_back(T);
    }
    reverse(fs.begin(), fs.end());
    stack<Algebra_Node*> stack;
    Algebra_Node* T = nullptr;
    while (!fs.empty()) {
        T = fs.back();
        fs.pop_back();
        string c = T->data.str;
        if (f_arg(T->data)) {
            stack.push(T);
        }
        else if (f_opr_two(T->data)) {
            Algebra_Node* p = stack.top();
            stack.pop();
            Algebra_Node* q = stack.top();
            stack.pop();
            T->addRightNode(p);
            T->addLeftNode(q);
            stack.push(T);
        }
        else if (f_opr_one(T->data)) {
            Algebra_Node* q = stack.top();
            stack.pop();
            T = new Algebra_Node(T->data);
            T->addLeftNode(q);
        }
    }
    return T;
}

void BypassTreeD(Algebra_Node* root) {
    if (root == nullptr)
        return;

    stack<Algebra_Node*> st;
    st.push(root);

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        st.pop();

        cout << currentNode->data << " ";

        if (currentNode->right)
            st.push(currentNode->right);
        if (currentNode->left)
            st.push(currentNode->left);
    }
}

void BypassTreeW(Algebra_Node* root) { // ����� ������ � ������ ��� ��������.
    if (root == nullptr) {
        return;
    }

    queue<Algebra_Node*> fs;
    fs.push(root);

    while (!fs.empty()) {
        Algebra_Node* currentNode = fs.front();
        fs.pop();

        cout << currentNode->data << " ";

        if (currentNode->left != nullptr) {
            fs.push(currentNode->left);
        }

        if (currentNode->right != nullptr) {
            fs.push(currentNode->right);
        }
    }
}

void Print_stack(stack<char> st)
{
    stack<char> sq = st;
    while (sq.empty()) {
        cout << sq.top() << " ";
        sq.pop();
    }
}

void FindValueD(Algebra_Node* root, string c, vector<vector<char>>& paths) { // 
    // ������ ���������� - ������ ������. � - ������� ��������, paths - ��� ��������� ���� ��� ����� ��������.
    if (root == nullptr) {
        return;
    }

    stack<Algebra_Node*> st;
    stack<vector<char>> k_st;
    vector<char> track;
    st.push(root);
    track.push_back('0');
    Algebra_Node* currentNode = st.top();
    st.pop();

    while (true) {

        if (currentNode->data.str == c)
        {
            bool B = false;
            if (track.empty())
            {
                track.push_back('0');
                B = true;
            }
            paths.push_back(track);
            if (B)  track.pop_back();
        }
        if (currentNode->left != nullptr) {
            st.push(currentNode->left);
            track.push_back('L');
            vector<char> es;
            es.assign(track.begin(), track.end());
            k_st.push(es);
            track.pop_back();
        }
        if (currentNode->right != nullptr) {
            st.push(currentNode->right);
            track.push_back('R');
            vector<char> es;
            es.assign(track.begin(), track.end());
            k_st.push(es);
            track.pop_back();
        }
        while (0);
        if (!st.empty())
        {
            currentNode = st.top();
            st.pop();
            track = k_st.top();
            k_st.pop();
        }
        else break;
    }
}

void FindValueW(Algebra_Node* root , string c , vector<vector<char>>& paths) { // 
    // ������ ���������� - ������ ������. � - ������� ��������, paths - ��� ��������� ���� ��� ����� ��������.
    if (root == nullptr) {
        return;
    }

    queue<Algebra_Node*> fs;
    queue<vector<char>> k_queue;
    vector<char> track;
    fs.push(root);
    track.push_back('0');

    Algebra_Node* currentNode = fs.front();
    fs.pop();

    while (true) {

        if (currentNode->data.str == c)
        {
            bool B = false;
            if (track.empty())
            {
                track.push_back('0');
                B = true;
            }
            paths.push_back(track);
            if (B)  track.pop_back();
        }

        if (currentNode->left != nullptr) {
            fs.push(currentNode->left);
            track.push_back('L');
            vector<char> es;
            es.assign(track.begin(), track.end());
            k_queue.push(es);
            track.pop_back();
        }

        if (currentNode->right != nullptr) {
            fs.push(currentNode->right);
            track.push_back('R');
            vector<char> es;
            es.assign(track.begin(), track.end());
            k_queue.push(es);
            track.pop_back();
        }
        if (!fs.empty())
        {
            currentNode = fs.front();
            fs.pop();
            track = k_queue.front();
            k_queue.pop();
        }
        else break;
    }
}

void Algebra_Tree::FindValueD_T(string c, vector<vector<char>>& paths)
{
    Algebra_Node* node = this->root;
    FindValueD(node, c, paths);
}

void Algebra_Tree::FindValueW_T(string c, vector<vector<char>>& paths)
{
    Algebra_Node* node = this->root;
    FindValueD(node, c, paths);
}


void TreeExprReplaceD(Algebra_Node* root, const string c, const string s) {
    // c - ��� �������� , s- ��� ��������.
    if (root == nullptr) {
        return;
    }

    stack<Algebra_Node*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Algebra_Node* currentNode = nodeStack.top();
        nodeStack.pop();

        if (currentNode->data.str == c)
        {
            deque<Token> es = exprToTokens(s);
            if (es.size() > 1) return; // �������� �� ����� ����������.
            else
            {
                currentNode->data = es.front();
            }
        }

        if (currentNode->right != nullptr) {
            nodeStack.push(currentNode->right);
        }
        if (currentNode->left != nullptr) {
            nodeStack.push(currentNode->left);
        }
    }
}


void TreeExprReplaceW(Algebra_Node* root ,const string c , const string s) { // ����� ������ � ������ ��� ��������.
    // c - ��� �������� , s- ��� ��������.
    if (root == nullptr) {
        return;
    }

    queue<Algebra_Node*> fs;
    fs.push(root);

    while (!fs.empty()) {
        Algebra_Node* currentNode = fs.front();
        fs.pop();

        if (currentNode->data.str == c)
        {  
            deque<Token> es = exprToTokens(s);
            if (es.size() > 1) return; // �������� �� ����� ����������.
            else 
            {
                currentNode->data = es.front();
            }
        }

        if (currentNode->left != nullptr) {
            fs.push(currentNode->left);
        }

        if (currentNode->right != nullptr) {
            fs.push(currentNode->right);
        }
    }
}

bool CompareTrees(Algebra_Node* root1, Algebra_Node* root2) {
    // ���� ��� ������ �����, �� ��� �����
    if (root1 == nullptr && root2 == nullptr) {
        return true;
    }
    // ���� ������ ���� �� �������� �����, �� ��� �� �����
    if (root1 == nullptr || root2 == nullptr) {
        return false;
    }
    // ���������� �������� ����� � ���������� ���������� �� ����������
    return (root1->data.str == root2->data.str) && CompareTrees(root1->left, root2->left) && CompareTrees(root1->right, root2->right);
}

Algebra_Node* GetOperand(Algebra_Node* root , LR lr)
{
    if (lr == LR::LEFT) return root->left;
    if (lr == LR::RIGHT) return root->right;
}

Algebra_Tree::Algebra_Tree(Algebra_Node* node)
{
    this->root = node;
}


Algebra_Tree& operator+(Algebra_Tree& first_tree, Algebra_Tree& second_tree)
{
    const Token& T = Token(Token::Type::Operator, "+", 2, false);
    Algebra_Node* top_node = new Algebra_Node(T);
    first_tree = first_tree.AddSubtree(top_node, LR::LEFT);
    second_tree = second_tree.AddSubtree(top_node, LR::RIGHT);
    return second_tree;
}

Algebra_Tree& operator-(Algebra_Tree& first_tree, Algebra_Tree& second_tree)
{
    const Token& T = Token(Token::Type::Operator, "-", 2, false);
    Algebra_Node* top_node = new Algebra_Node(T);
    first_tree = first_tree.AddSubtree(top_node, LR::LEFT);
    second_tree = second_tree.AddSubtree(top_node, LR::RIGHT);
    return second_tree;
}

Algebra_Tree& operator*(Algebra_Tree& first_tree, Algebra_Tree& second_tree)
{
    const Token& T = Token(Token::Type::Operator, "*", 3, false);
    Algebra_Node* top_node = new Algebra_Node(T);
    first_tree = first_tree.AddSubtree(top_node, LR::LEFT);
    second_tree = second_tree.AddSubtree(top_node, LR::RIGHT);
    return second_tree;
}

Algebra_Tree& operator/(Algebra_Tree& first_tree, Algebra_Tree& second_tree)
{
    const Token& T = Token(Token::Type::Operator, "/", 3, false);
    Algebra_Node* top_node = new Algebra_Node(T);
    first_tree = first_tree.AddSubtree(top_node, LR::LEFT);
    second_tree = second_tree.AddSubtree(top_node, LR::RIGHT);
    return second_tree;
}

Algebra_Tree& operator^(Algebra_Tree& first_tree, Algebra_Tree& second_tree)
{
    const Token& T = Token(Token::Type::Operator, "^", 4, true);
    Algebra_Node* top_node = new Algebra_Node(T);
    first_tree = first_tree.AddSubtree(top_node, LR::LEFT);
    second_tree = second_tree.AddSubtree(top_node, LR::RIGHT);
    return second_tree;
}

Algebra_Tree& Algebra_Tree::AddSubtree(Algebra_Node* node, LR lr)
{ // ���������� ��������� � ���������� ����:
  // ��������� - node ��������� ����. lr - ������ ����������� ������� ���������� ����������.
  // ����������� ��������� ���������� � ������� ������.
    Algebra_Tree& second_tree = CopyTree(this->root);
    Algebra_Node* second = this->root;
    this->root = node;
    if (lr == LR::LEFT)
    {
        node->left = second;
    }
    if (lr == LR::RIGHT)
    {
        node->right = second;
    }
    return *this;
}


Algebra_Node* Algebra_Tree::CloneTree(Algebra_Node* root) {
    if (root == nullptr) {
        return nullptr;
    }

    Algebra_Node* newNode = new Algebra_Node(root->data);
    newNode->left = CloneTree(root->left);
    newNode->right = CloneTree(root->right);

    return newNode;
}

Algebra_Tree& Algebra_Tree::CopyTree(Algebra_Node* node) {
    Algebra_Tree* clonedTree = new Algebra_Tree();
    clonedTree->root = CloneTree(node);
    return *clonedTree;
}

void Algebra_Tree::Print_Tree_T()
{
    Algebra_Node* node = this->root;
    Print_Tree_R(node);
}

void Algebra_Tree::TreeExprReplaceD_T(const string c, const string s)
{
    Algebra_Node* node = this->root;
    TreeExprReplaceD(node , c , s);
}

string PostfixToInfix(vector<Token>& fs)
{ // � ������ ��������� ��������� � ������� �������� �������� �������.
  // ��������� ������������ �� ������ ��������� � ����� ��������� ������.
    string p, q, s , t;
    reverse(fs.begin(), fs.end());
    stack<string> st;
    stack<int> st_opr;
    int m , n;
    while (!fs.empty())
    {
        Token T = fs.back();
        string f = T.str;
        fs.pop_back();
        st_opr.push(0); // ��� ������������ �����.
        if (T.type == Token::Type::Algebra || T.type == Token::Type::Number)
        {   
            t = T.str;
            st.push(t);
        }
        else if (f_opr_two(T))
        {
            p = st.top();
            st.pop();
            q = st.top();
            st.pop();
            n = st_opr.top();
            m = T.precedence;
            bool ra = T.rightAssociative;
            st_opr.pop();
            bool B = false;
            if (n < m && ra) B = true;
            if (n <= m && !ra) B = true;
            
            if (B) s = "(" + q + f + p + ")";
            else s = q + f + p;
            st.push(s);
            st_opr.push(m);
            
        }
        else if (f_opr_one(T))
        {
            p = st.top();
            st.pop();
            s = "(" + p + ")";
            st.push(s);
        }

    }
    
    s = st.top();
    st.pop();
    return s;
}

void TreeToPolish(Algebra_Node* root , vector<Token>& kh)
{ // �� ���� �������� ������ ������ , ������������ �������� �� ������ ��������� � ������� �������� �������� �������.
    kh.clear();
    if (root == nullptr)
        return;

    stack<Algebra_Node*> st;
    st.push(root);

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        st.pop();

        kh.push_back(currentNode->data);

        if (currentNode->right)
            st.push(currentNode->right);
        if (currentNode->left)
            st.push(currentNode->left);
    }
   
}

void TreeToPolish(Algebra_Node* root, deque<Token>& kh)
{ // �� ���� �������� ������ ������ , ������������ �������� �� ������ ��������� � ������� �������� �������� �������.
    kh.clear();
    if (root == nullptr)
        return;

    stack<Algebra_Node*> st;
    st.push(root);

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        st.pop();

        kh.push_back(currentNode->data);

        if (currentNode->right)
            st.push(currentNode->right);
        if (currentNode->left)
            st.push(currentNode->left);
    }

}

void Algebra_Tree::TreeToPolish_T()
{
    Algebra_Node* node = this->root;
    vector<Token> kh = this->polish;
    TreeToPolish(root, kh);
    this->polish = kh;
}



bool Is_Numeric() // ����������� � �������������� ��������� �� ������.
{
    return true;
}

bool Is_Algebric() // ����������� � �������������� ��������� �� ������.
{
    return true;
}

Algebra_Node* SetNode(string s)
{
    Token T = SetToken(s);
    Algebra_Node* node = new Algebra_Node(T);
    return node;
}

Algebra_Node* SetNode(int m)
{
    Token T = SetToken(m);
    Algebra_Node* node = new Algebra_Node(T);
    return node;
}

Algebra_Tree& SetAlgebricTree(string s)
{ // ������� �� ���� �������� ��������� � ��������� ������, � �� ������ ������� ��������������� ���������.
    deque<Token> fh, eh;
    fh = exprToTokens(s);
    Tokenize_u_minus(fh);
    eh = shuntingYard(fh);
    Algebra_Node* root = PolishToTree(eh);
    Algebra_Tree* tree = new Algebra_Tree(root);
    Algebra_Tree& T = *tree;
    return T;
}
