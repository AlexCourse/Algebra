#include "algebra_node.h"
#include <string>
#include <queue>
#include <unordered_set>

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

bool f_arg(Token& T)
{
    if (T.type == Token::Type::Algebra || T.type == Token::Type::Number) return true;
    else return false;
}
bool f_opr_two(Token& T) {
    string p = T.str;
    if (operator_info_two.count(p) || func_info_two.count(p)) {
        return true;
    }
    return false;
}

bool f_opr_one(Token& T) {
    string p = T.str;
    if (operator_info_one.count(p) || func_info_one.count(p)) {
        return true;
    }
    return false;
}

bool f_opr_free(Token& T) {
    string p = T.str;
    if (func_info_free.count(p)) {
        return true;
    }
    return false;
}


void Print_Tree_R(Algebra_Node const* node, string const& prefix, bool root, bool last) {
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

void ByPassTreeD(Algebra_Node* root) {
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

void ByPassTreeW(Algebra_Node* root) { // Обход дерева в ширину без рекурсии.
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

void TreeExprReplaceD(Algebra_Node* root, const string c, const string s) {
    // c - что заменяем , s- чем заменяем.
    if (root == nullptr) {
        return;
    }

    stack<Algebra_Node*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Algebra_Node* currentNode = nodeStack.top();
        nodeStack.pop();

        if (currentNode->data.str == c) currentNode->data.str = s;

        if (currentNode->right != nullptr) {
            nodeStack.push(currentNode->right);
        }
        if (currentNode->left != nullptr) {
            nodeStack.push(currentNode->left);
        }
    }
}


void TreeExprReplaceW(Algebra_Node* root ,const string c , const string s) { // Обход дерева в ширину без рекурсии.
    // c - что заменяем , s- чем заменяем.
    if (root == nullptr) {
        return;
    }

    queue<Algebra_Node*> fs;
    fs.push(root);

    while (!fs.empty()) {
        Algebra_Node* currentNode = fs.front();
        fs.pop();

        if (currentNode->data.str == c) currentNode->data.str = s;

        if (currentNode->left != nullptr) {
            fs.push(currentNode->left);
        }

        if (currentNode->right != nullptr) {
            fs.push(currentNode->right);
        }
    }
}


Algebra_Node* GetOperand(Algebra_Node* root , LR lr)
{
    if (lr == LR::LEFT) return root->left;
    if (lr == LR::RIGHT) return root->right;
}