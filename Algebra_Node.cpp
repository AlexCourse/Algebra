#include "algebra_node.h"
#include <string>
#include <queue>
#include <unordered_set>
#define DEBUG 1

using namespace std;

Algebra_Node::Algebra_Node(const Token& data, Algebra_Node* left, Algebra_Node* right)
    : data(data), left(left), right(right) {}

Algebra_Node::Algebra_Node()
{
    Token T = SetToken("0");
    this->left = nullptr;
    this->right = nullptr;
}

Algebra_Node::~Algebra_Node() {
    delete left;
    delete right;
}

string Algebra_Node::toString() {
    return get<string>(data.value);
}

void Algebra_Node::addLeftNode(Algebra_Node* Q) {
    this->left = Q;
}

void Algebra_Node::addRightNode(Algebra_Node* Q) {
    this->right = Q;
}


void Print_Tree_R(Algebra_Node const* node, string const& prefix = " ", bool root = true, bool last = true) {
    cout << prefix << (root ? "" : (last ? ch_udia_hor : ch_ver_hor));
    cout << (node ? ToString(node->data.value) : "") << endl;
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

        cout << cur_prefix << get<string>(node ? node->data.value : "") << endl;

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
    stack<Algebra_Node*> st;
    Algebra_Node* T = nullptr;
    while (!fs.empty()) {
        T = fs.back();
        fs.pop_back();
        if (f_arg(T->data)) {
            st.push(T);
        }
        else if (f_opr_two(T->data)) {
            Algebra_Node* p = st.top();
            st.pop();
            Algebra_Node* q = st.top();
            st.pop();
            T->addRightNode(p);
            T->addLeftNode(q);
            st.push(T);
        }
        else if (f_opr_one(T->data)) {
            Algebra_Node* q = st.top();
            st.pop();
            T = new Algebra_Node(T->data);
            T->addLeftNode(q);
            st.push(T);
        }
    }
    return T;
}

// =======================================================================================================================
// Поместить в файл vector_cl.cpp
template <typename T>
void _ReverseVector(vector<T>& fh)
{
    int start = 0;
    int end = fh.size() - 1;

    while (start < end) {
        swap(fh[start], fh[end]);
        start++;
        end--;
    }
}
template <typename T>
vector<T> ReverseVector(vector<T>& fh) {
    vector<T> kh;
    typename vector<T>::reverse_iterator iter; // Use reverse_iterator instead of iterator

    for (iter = fh.rbegin(); iter != fh.rend(); ++iter) { // Use rbegin() and rend() for reverse iteration
        T elem = *iter;
        kh.push_back(elem);
    }

    return kh;
}

template <typename T>
deque<T> ReverseVector(deque<T>& fh) {
    deque<T> kh;
    typename deque<T>::reverse_iterator iter; // Use reverse_iterator instead of iterator

    for (iter = fh.rbegin(); iter != fh.rend(); ++iter) { // Use rbegin() and rend() for reverse iteration
        T elem = *iter;
        kh.push_back(elem);
    }
    return kh;
}
// ========================================================================================================================

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

void BypassTreeW(Algebra_Node* root) { // Обход дерева в ширину без рекурсии.
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
    // Первая переменная - корень дерева. с - искомое значение, paths - все найденные пути для этого значения.
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

        if (CE(currentNode->data.value, c))
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


void FindValueW(Algebra_Node* root, string c, vector<vector<char>>& paths) { // 
    // Первая переменная - корень дерева. с - искомое значение, paths - все найденные пути для этого значения.
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

        if (CE(currentNode->data.value, c))
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


// ===========================================================================================================================
Algebra_Node* TreeExprReplaceR(Algebra_Node* root, const string c, const variant<int, double, string> value) {
    // Возвращает копию дерева с замененными значениями.
    if (root == nullptr) {
        return nullptr;
    }

    Algebra_Node* newNode = new Algebra_Node();

    if (CE(root->data.value, c)) {
        Token token = SetToken(value);
        newNode = new Algebra_Node(token);
        while (0); // For breakpoint.
    }
    else {
        newNode = new Algebra_Node(root->data);
    }

    newNode->left = TreeExprReplaceR(root->left, c, value);
    newNode->right = TreeExprReplaceR(root->right, c, value);

    return newNode;
}

// =================================================================================================================================


Algebra_Node* TreeExprReplaceD(Algebra_Node* root, const string c, const variant<int, double, string> s) {
    // Возвращение копии дерева с заменой.
    if (root == nullptr) {
        return nullptr;
    }

    stack<Algebra_Node*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Algebra_Node* currentNode = nodeStack.top();
        nodeStack.pop();

        if (CE(currentNode->data.value, c)) {
            Token T = SetToken(s);
            currentNode = new Algebra_Node(T);
        }

        if (currentNode->right != nullptr) {
            nodeStack.push(currentNode->right);
        }

        if (currentNode->left != nullptr) {
            nodeStack.push(currentNode->left);
        }
    }

    return root;
}

Algebra_Node* TreeExprReplaceW(Algebra_Node* root, const string c, const variant<int, double, string> value) {
    if (root == nullptr) {
        return nullptr;
    }

    queue<Algebra_Node*> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        Algebra_Node* currentNode = nodeQueue.front();
        nodeQueue.pop();

        if (CE(currentNode->data.value, c)) {
            Token T = SetToken(value);
            currentNode = new Algebra_Node(T);
        }

        if (currentNode->left != nullptr) {
            nodeQueue.push(currentNode->left);
        }

        if (currentNode->right != nullptr) {
            nodeQueue.push(currentNode->right);
        }
    }

    return root;
}
// Отделение области перегруженных функций.
// ============================================================================================================================================================
Algebra_Tree& Algebra_Tree::TreeExprReplaceD_T(const string c, const variant<int, double, string> value)
{
    const int MODE = 1;
    Algebra_Node* first_root = this->root;
    Algebra_Node* second_root;
    if (MODE == 0) second_root = TreeExprReplaceD(first_root, c, value); // Замена нерабочей функции
    if (MODE == 1) second_root = TreeExprReplaceR(first_root, c, value);
    Algebra_Tree t = Algebra_Tree(second_root);
    return t;
}

Algebra_Tree& Algebra_Tree::TreeExprReplaceW_T(const string c, const variant<int, double, string> value)
{
    const int MODE = 1;
    Algebra_Node* first_root = this->root;
    Algebra_Node* second_root;
    if (MODE == 0) second_root = TreeExprReplaceW(first_root, c, value); // Замена нерабочей функции
    if (MODE == 1) second_root = TreeExprReplaceR(first_root, c, value);
    Algebra_Tree t = Algebra_Tree(second_root);
    return t;
}

// =============================================================================================================================================================
Algebra_Node* TreeRExprReplaceOnSubTreeD(Algebra_Node* first, const string c, Algebra_Node* second)
{
    if (first == nullptr)
        return nullptr;

    stack<Algebra_Node*> st;
    stack<char> lr_st;
    stack<Algebra_Node*> parents;
    st.push(first);
    lr_st.push('0');
    parents.push(second);

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        Algebra_Node* parent = parents.top();
        char p = lr_st.top();
        st.pop();
        lr_st.pop();
        parents.pop();

        if (CE(currentNode->data.value, c))
        {
            Algebra_Node& Q = *parent;
            if (!(parent == second)) // Если является корнем.
            {
                switch (p)
                {
                case 'L': { Q.addLeftNode(second); break; }
                case 'R': { Q.addRightNode(second); break; }
                }
                while (0);
            }
            else first = second; // Становится в корень.
        }

        if (currentNode->left != nullptr)
        {
            lr_st.push('L');
            parents.push(currentNode);
            st.push(currentNode->left);
        }
        if (currentNode->right != nullptr)
        {
            lr_st.push('R');
            parents.push(currentNode);
            st.push(currentNode->right);
        }
    }
    if (DEBUG)
    {
        first = first;
        while (0); // Для точки останова.
    }
    return first;
}

Algebra_Node* TreeRExprReplaceOnSubTreeW(Algebra_Node* first, const string c, Algebra_Node* second)
{
    if (first == nullptr) {
        return nullptr;
    }

    queue<Algebra_Node*> fs;
    queue<char> lr_fs;
    queue<Algebra_Node*> parents;
    fs.push(first);
    lr_fs.push('0');
    parents.push(first);

    while (!fs.empty()) {
        Algebra_Node* currentNode = fs.front();
        Algebra_Node* parent = parents.front();
        char p = lr_fs.back();
        fs.pop();
        lr_fs.pop();
        parents.pop();

        if (CE(currentNode->data.value, c))
        {
            Algebra_Node& Q = *parent;
            if (!(parent == second))
            {
                switch (p)
                {
                case 'L': { Q.addLeftNode(second); break; }
                case 'R': { Q.addRightNode(second); break; }
                }
            }
            else first = second;
        }


        if (currentNode->left != nullptr)
        {
            lr_fs.push('L');
            parents.push(currentNode);
            fs.push(currentNode->left);
        }

        if (currentNode->right != nullptr)
        {
            lr_fs.push('R');
            parents.push(currentNode);
            fs.push(currentNode->right);
        }
    }
    return first;
}

bool CompareTrees(Algebra_Node* root1, Algebra_Node* root2) {
    // Если оба дерева пусты, то они равны
    if (root1 == nullptr && root2 == nullptr) {
        return true;
    }
    // Если только одно из деревьев пусто, то они не равны
    if (root1 == nullptr || root2 == nullptr) {
        return false;
    }
    // Сравниваем значения узлов и рекурсивно сравниваем их поддеревья
    return (root1->data.value == root2->data.value) && CompareTrees(root1->left, root2->left) && CompareTrees(root1->right, root2->right);
}

Algebra_Node* GetOperand(Algebra_Node* root, LR lr)
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
{ // Добавление поддерева к выбранному узлу:
  // Параметры - node выбранный узел. lr - какого направления потомок заменяется поддеревом.
  // Добавляемое поддерево содержится в текущем классе.
    Algebra_Tree& second_tree = CopyTree();
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

Algebra_Tree& Algebra_Tree::CopyTree() {
    Algebra_Node* node = this->root;
    Algebra_Tree* clonedTree = new Algebra_Tree();
    clonedTree->root = CloneTree(node);
    return *clonedTree;
}

void Algebra_Tree::Print_Tree_T()
{
    Algebra_Node* node = this->root;
    Print_Tree_R(node);
}


string PostfixToInfix(vector<Token>& fs)
{ // В первом параметре выражение в формате Обратной Польской нотации.
  // Результат возвращается во втором параметре в форме Инфиксной Записи.
    string p, q, s, t;
    reverse(fs.begin(), fs.end());
    stack<string> st;
    stack<int> st_opr; // Здесь сохраняются приоритеты операторов.
    int m, n;
    while (!fs.empty())
    {
        Token T = fs.back();
        fs.pop_back();
        // st_opr.push(0); // Для балансировки стека.
        if (T.type == Token::Type::Algebra)
        {
            s = T.ToString();
            st.push(s);
        }
        else if (T.type == Token::Type::Integer)
        {
            s = T.ToString();
            st.push(s);
        }
        else if (T.type == Token::Type::Real)
        {
            s = T.ToString();
            st.push(s);
        }
        else if (f_opr_two(T))
        {
            string f = T.ToString();
            q = st.top();
            st.pop();
            p = st.top();
            st.pop();
            m = T.precedence;
            bool ra = T.rightAssociative;
            for (int i = 0; i < 2; i++)
            {
                if (st_opr.empty()) break;
                n = st_opr.top();
                st_opr.pop();
                bool B = false;
                if (n < m && ra) B = true;
                if (n <= m && !ra) B = true;
                if (B)
                {
                    if (i == 0) p = "(" + p + ")";
                    if (i == 1) p = "(" + q + ")";
                }
            }
            s = p + f + q;
            st.push(s);
            st_opr.push(m);

        }
        else if (f_opr_one(T))
        {
            string f = T.ToString();
            p = st.top();
            st.pop();
            s = f + "(" + p + ")";
            st.push(s);
        }

    }

    s = st.top();
    st.pop();
    return s;
}

string PostfixToInfix(deque<Token>& fs)
{ // В первом параметре выражение в формате Обратной Польской нотации.
  // Результат возвращается во втором параметре в форме Инфиксной Записи.
    string p, q, s, t;
    // reverse(fs.begin(), fs.end());
    stack<string> st;
    stack<int> st_opr; // Здесь сохраняются приоритеты операторов.
    int m, n;
    while (!fs.empty())
    {
        Token T = fs.front();
        fs.pop_front();
        st_opr.push(0); // Для балансировки стека.
        if (T.type == Token::Type::Algebra)
        {
            s = T.ToString();
            st.push(s);
        }
        else if (T.type == Token::Type::Integer || T.type == Token::Type::Real || T.type == Token::Type::Number)
        {
            s = T.ToString();
            st.push(s);
        }
        else if (f_opr_two(T))
        {
            string f = T.ToString();
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

void TreeToPolish(Algebra_Node* root, vector<Token>& kh)
{ // На вход подается корень дерева , возвращается значение во втором параметре в формате Обратной Польской Нотации.
    kh.clear();
    if (root == nullptr)
        return;

    stack<Algebra_Node*> st;
    st.push(root);

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        st.pop();

        kh.push_back(currentNode->data);

        if (currentNode->left)
            st.push(currentNode->left);
        if (currentNode->right)
            st.push(currentNode->right);
    }
    kh = ReverseVector(kh);
    while (0); // Для точки останова. 
}

void TreeToPolish(Algebra_Node* root, deque<Token>& kh)
{ // На вход подается корень дерева , возвращается значение во втором параметре в формате Обратной Польской Нотации.
    kh.clear();
    if (root == nullptr)
        return;

    stack<Algebra_Node*> st;
    st.push(root);

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        st.pop();

        kh.push_back(currentNode->data);

        if (currentNode->left)
            st.push(currentNode->left);
        if (currentNode->right)
            st.push(currentNode->right);
    }
    kh = ReverseVector(kh);
    while (0); // Для точки останова. 

}

void Algebra_Tree::TreeToPolish_T()
{
    Algebra_Node* node = this->root;
    vector<Token> kh = this->polish;
    TreeToPolish(root, kh);
    this->polish = kh;
}



bool Algebra_Tree::Is_Numeric() // Реализовать с использованием итератора по дереву.
{
    return true;
}

bool Algebra_Tree::Is_Algebric() // Реализовать с использованием итератора по дереву.
{
    return true;
}

Algebra_Node* SetNode(const string s)
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

Algebra_Tree& SetAlgebricTree(const string s)
{ // Функция на вход получаем выражение в инфиксной записи, а на выходе деренво алгебраического выражения.
    deque<Token> fh, eh;
    fh = exprToTokens(s);
    Tokenize_u_minus(fh);
    eh = shuntingYard(fh);
    Algebra_Node* root = PolishToTree(eh);
    Algebra_Tree* tree = new Algebra_Tree(root);
    Algebra_Tree& T = *tree;
    return T;
}

Algebra_Node* SetOperatorTree(const string s)
{
    deque<Token> fh, eh;
    fh = exprToTokens(s);
    Tokenize_u_minus(fh);
    eh = shuntingYard(fh);
    Algebra_Node* root = PolishToTree(eh);
    return root;
}

void Algebra_Tree::TreeRExprReplaceOnSubTreeW_T(const string c, Algebra_Node* second)
{
    Algebra_Node* root = this->root;
    TreeRExprReplaceOnSubTreeW(root, c, second);
}

void Algebra_Tree::TreeRExprReplaceOnSubTreeD_T(const string c, Algebra_Node* second)
{
    Algebra_Node* root = this->root;
    TreeRExprReplaceOnSubTreeD(root, c, second);
}

double FunctionValue(Algebra_Node* root, double value, string symbol)
{ // Подстановка в функцию заданную деревом.
    const bool LOCAL_DEBUG = false;
    if (LOCAL_DEBUG)
    {
        for (int i = 0; i < 1; i++) cout << endl;
        cout << "FunctionValue() : DEBUG : BEFORE" << endl;
        Print_Tree_R(root);
        for (int i = 0; i < 43; i++) cout << "=";
        for (int i = 0; i < 2; i++) cout << endl;
    }
    Algebra_Node* second_root = TreeExprReplaceR(root, symbol, value);
    if (LOCAL_DEBUG)
    {
        cout << "FunctionValue() : DEBUG : AFTER" << endl;
        Print_Tree_R(second_root);
    }
    deque<Token> kh;
    TreeToPolish(second_root, kh);
    if (LOCAL_DEBUG)
    {
        cout << endl;
        for (Token token : kh) cout << token << " ";
    }
    double r = PolishCalculation(kh);
    return r;
}

double Algebra_Tree::FunctionValue_T(double value, string symbol)
{
    Algebra_Node* root = this->root;
    double r = FunctionValue(root, value, symbol);
    return r;
}


double FunctionValueM(string expr, map<string, double>& ds)
{ // Вычислить значение функции заданной строкой с параметрами заданными в словаре где ключ - имя переменной, а значение - ее значение.
    Algebra_Node* root = SetOperatorTree(expr);

    map<string, double>::iterator iter;
    for (iter = ds.begin(); iter != ds.end(); iter++)
    {
        string p = iter->first;
        root = TreeExprReplaceR(root, p, ds[p]);
    }
    Algebra_Tree* T = new Algebra_Tree(root);
    Algebra_Tree& tree = *T;
    if (DEBUG)
    {
        cout << "FunctionValueM() : AFTER" << endl;
        tree.Print_Tree_T();
    }
    if (tree.Is_Numeric())
    {
        vector<Token> kh, ks;
        TreeToPolish(root, kh);
        double r = PolishCalculation(kh);
        return r;
    }
    else
    {
        cout << "error" << endl;
        return 0;
    }

}

string TreeToInfix(Algebra_Node* root)
{
    vector<Token> fh , eh;
    TreeToPolish(root, fh);
    vector<Token> kh(fh.rbegin(), fh.rend());
    // reverse(fh.begin(), fh.end());
    string s = PostfixToInfix(kh);
    return s;
}

string Algebra_Tree::TreeToInfix_T()
{
    Algebra_Node* root = this->root;
    string s = TreeToInfix(root);
    return s;
}

void deleteBinaryTree(Algebra_Node* node) {
    if (node == nullptr) {
        return;
    }
    // Рекурсивно удаляем левое и правое поддерево
    if ( node->left != nullptr) deleteBinaryTree(node->left);
    if ( node->right != nullptr) deleteBinaryTree(node->right);
    // Удаляем текущий узел
    delete node;
}

void RecursiveDestructor(Algebra_Node* root)
{
    deleteBinaryTree(root);
}

