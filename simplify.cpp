#include "simplify.h"
#define DEBUG 1

class GarbegeCollector
{
public:
    std::deque<Algebra_Node*> ExposedBranches;
    std::deque<Algebra_Node*> ExposedNodes;
};




bool func_1(Algebra_Node* currentNode, Algebra_Node* parent, char p, Algebra_Node*& root, char& c, int level, GarbegeCollector& G)
{ // ['*']
    // ��������� �������� �������� ��: ��������� ��� ������������� ������� � ����� �������� ��������� �� ������������� �� ������ �������. 'L' - ������������� , 'R' - ���������., 'Z' - �������� �����.
    // � ���� ��������� ���������� �������� ������������.
    Algebra_Node& C = *currentNode;
    Algebra_Node* P[2];
    P[0] = currentNode->left;
    P[1] = currentNode->right;
    bool B = false;
    bool match = false;
    int k = -1;

    for (int i = 0; i < 2; i++)
    {
        if (CE(P[i]->data.value, 0)) B = true; // ���� ���� �� ��������� ����� ����.
        else if (CE(P[i]->data.value, 1)) k = i; // ��������� ����� ���������� ��������.
    }
    if (B)
    {
        Algebra_Node* W = SetNode(0);
        Algebra_Node& K = *parent;
        match = true;
        if (!(currentNode == root))
        {
            if (DEBUG)
            {
                std::cout << "func_1 : DEFORE" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
            switch (p)
            {
            case 'L': { K.addLeftNode(W); break; }
            case 'R': { K.addRightNode(W); break; }
            }
            if (DEBUG)
            {
                std::cout << "func_1 : AFTER" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
            while (0);
        }
        else root = W;
        // RecursiveDestructor(currentNode);
        G.ExposedBranches.push_back(currentNode);
        c = 'Z';
    }
    else if (!(k == -1))
    {
        Algebra_Node* R = currentNode;
        match = true;
        Algebra_Node& K = *parent;
        k = (k + 1) % 2; // 1-> 0 , 0 -> 1
        if (!(currentNode == root))
        {
            switch (p)
            {
                if (DEBUG)
                {
                    std::cout << "func_1 : BEFORE" << std::endl;
                    Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
                }
            case 'L':
            {
                K.addLeftNode(P[k]);
                break;
            }
            case 'R':
            {
                K.addRightNode(P[k]);
                break;
            }
            if (DEBUG)
            {
                std::cout << "func_1 : AFTER" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
            }
        }
        else root = P[k];
        k = (k + 1) % 2; // 1-> 0 , 0 -> 1
        // delete P[k]; // �������� ������ ���� �������� ����������.
        G.ExposedBranches.push_back(P[k]);
        G.ExposedNodes.push_back(R);
        while (0);
        switch (k)
        {
        case 0: { c = 'L'; break; }
        case 1: { c = 'R'; break; }
        }
    }
    return match;
}

bool func_2(Algebra_Node* currentNode, Algebra_Node* parent, char p, Algebra_Node*& root, char& c, int level, GarbegeCollector& G)
{ // ['^']
    Algebra_Node& C = *currentNode;
    Algebra_Node* P[2];
    P[0] = currentNode->left;
    P[1] = currentNode->right;
    if (DEBUG) root = root;
    bool match = false;

    if (CE(P[1]->data.value, 0)) // ���������� ������� �������.
    {
        Algebra_Node* W = SetNode(1);
        Algebra_Node& K = *parent;
        match = true;
        if (!(currentNode == root))
        {
            if (DEBUG)
            {
                std::cout << "func_2 : BEFORE" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
            switch (p)
            {
            case 'L': { K.addLeftNode(W); break; }
            case 'R': { K.addRightNode(W); break; }
            }
            if (DEBUG)
            {
                std::cout << "func_2 : AFTER" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
            while (0);
        }
        else root = W;
        // RecursiveDestructor(currentNode);
        G.ExposedBranches.push_back(currentNode);
        c = 'Z';
    }
    else if (CE(P[1]->data.value, 1)) // ���������� ������ �������.
    {
        Algebra_Node* prev_node = currentNode;
        currentNode = parent;
        Algebra_Node& K = *parent;
        if (DEBUG)
        {
            std::cout << "func_2 : BEFORE" << std::endl;
            Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
        }
        if (!(currentNode == root))
        {
            switch (p)
            {
            case 'L':
            {
                K.addLeftNode(P[0]);
                break;
            }
            case 'R':
            {
                K.addRightNode(P[0]);
                break;
            }
            }
        }
        else root = P[0];
        if (DEBUG)
        {
            std::cout << "func_2 : AFTER" << std::endl;
            Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
        }
        G.ExposedNodes.push_back(prev_node);
        // �������� ������ ���� -���������� ������ �������.
        G.ExposedBranches.push_back(P[1]);
        match = true;
        c = 'R';
        while (0);
    }
    if (CE(P[0]->data.value, 1)) // ������� � ����� �������.
    {
        Algebra_Node* W = SetNode(1);
        Algebra_Node& K = *parent;
        if (!(currentNode == root))
        {
            if (DEBUG)
            {
                std::cout << "func_2 : BEFORE" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
            switch (p)
            {
            case 'L': { K.addLeftNode(W); break; }
            case 'R': { K.addRightNode(W); break; }
            }
            while (0);
            if (DEBUG)
            {
                std::cout << "func_2 : AFTER" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
        }
        else root = W;
        match = true;
        c = 'Z';
        // RecursiveDestructor(currentNode);
        G.ExposedBranches.push_back(currentNode);
    }
    else if (CE(P[0]->data.value, 0)) // ���� � ����� ������������� �������.
    {
        if (P[1]->data.type == Token::Type::Integer || P[1]->data.type == Token::Type::Real || P[1]->data.type == Token::Type::Number)
        {
            double m;
            std::variant<std::string, char, int, double, Token::Function> Q = P[1]->data.GetValue();
            if (holds_alternative<int>(Q)) m = get<int>(Q);
            else if (holds_alternative<double>(Q)) m = get<double>(Q);
            if (m > 0)
            {
                Algebra_Node* W = SetNode(0);
                Algebra_Node& K = *parent;
                if (DEBUG)
                {
                    std::cout << "func_2 : BEFORE" << std::endl;
                    Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
                }
                if (!(currentNode == root))
                {
                    switch (p)
                    {
                    case 'L': { K.addLeftNode(W); break; }
                    case 'R': { K.addRightNode(W); break; }
                    }
                    while (0);
                }
                else root = W;
                c = 'Z';
                match = true;
                // RecursiveDestructor(currentNode);
                G.ExposedBranches.push_back(currentNode);
                if (DEBUG)
                {
                    std::cout << "func_2 : AFTER" << std::endl;
                    Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
                }
            }

        }
    }
    return match;
}

bool func_3(Algebra_Node* currentNode, Algebra_Node* parent, char p, Algebra_Node*& root, char& c, int level, GarbegeCollector& G) {
    // ['/']
    Algebra_Node& C = *currentNode;
    Algebra_Node* P[2];
    P[0] = currentNode->left;
    P[1] = currentNode->right;
    bool match = false;

    if (CE(P[0]->data.value, 0)) {
        match = true;
        Algebra_Node* W = SetNode(0);
        Algebra_Node& K = *parent;

        if (!(currentNode == root)) {
            if (DEBUG)
            {
                std::cout << "func_3 : BEFORE" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
            switch (p) {
            case 'L': {
                K.addLeftNode(W);
                break;
            }
            case 'R': {
                K.addRightNode(W);
                break;
            }
            }
            if (DEBUG)
            {
                std::cout << "func_3 : AFTER" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
        }
        else {
            root = W;
        }
        c = 'Z';
        G.ExposedBranches.push_back(currentNode);
    }
    else if (CE(P[1]->data.value, 1)) {
        Algebra_Node* R = currentNode;
        Algebra_Node& K = *parent;

        if (!(currentNode == root)) {
            if (DEBUG)
            {
                std::cout << "func_3 : BEFORE" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
            switch (p) {
            case 'L': {
                K.addLeftNode(P[0]);
                break;
            }
            case 'R': {
                K.addRightNode(P[0]);
                break;
            }
            }
            // delete P[1]; // �������� ������ ���� - ���������� ��������.
            G.ExposedBranches.push_back(P[1]);
            c = 'R';
            if (DEBUG)
            {
                std::cout << "func_3 : AFTER" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
        }
        else {
            root = P[0];
        }
        match = true;
        G.ExposedNodes.push_back(R);
        R = nullptr;
    }
    return match;
}

bool func_4(Algebra_Node* currentNode, Algebra_Node* parent, char p, Algebra_Node*& root, char& c, int level, GarbegeCollector& G) {
    // ['+']
    Algebra_Node& C = *currentNode;
    Algebra_Node* P[2];
    P[0] = currentNode->left;
    P[1] = currentNode->right;
    bool B = false;
    bool match = false;
    int k = -1;

    for (int i = 0; i < 2; i++) {
        if (CE(P[i]->data.value, 0))
            k = i;
    }

    if (!(k == -1)) {
        Algebra_Node* R = currentNode;
        k = (k + 1) % 2;
        Algebra_Node& K = *parent;
        match = true;

        if (!(currentNode == root)) {
            if (DEBUG) {
                std::cout << "func_4 : BEFORE" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }

            switch (p) {
            case 'L': {
                K.addLeftNode(P[k]);
                break;
            }
            case 'R': {
                K.addRightNode(P[k]);
                break;
            }
            }

            if (DEBUG) {
                std::cout << "func_4 : AFTER" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
        }
        else {
            root = P[k];
        }
        k = (k + 1) % 2;
        // delete P[k];
        G.ExposedBranches.push_back(P[k]);
        switch (k)
        {
        case 0: { c = 'L'; break; }
        case 1: { c = 'R'; break; }
        }
        G.ExposedNodes.push_back(R);
        R = nullptr;
    }

    return match;
}

bool func_5(Algebra_Node* currentNode, Algebra_Node* parent, char p, Algebra_Node*& root, char& c, int level, GarbegeCollector& G)
{
    Algebra_Node& C = *currentNode;
    Algebra_Node* P[2];
    P[0] = currentNode->left;
    P[1] = currentNode->right;
    if (DEBUG) root = root;
    bool match = false;
    bool B = true;
    if (C.data.type == Token::Type::Operator || C.data.type == Token::Type::Function)
    {
        for (int i = 0; i < 2; i++)
        {
            if (!(P[i]->data.type == Token::Type::Number || P[i]->data.type == Token::Type::Integer || P[i]->data.type == Token::Type::Real)) B = false;
        }
        if (B)
        {
            match = true;
            Token& T = C.data;
            double m = 0;
            c = 'Z';
            std::deque<Token> fs;
            if (f_opr_two(T))
            {
                fs.push_back(P[0]->data);
                fs.push_back(P[1]->data);
                fs.push_back(T);
            }
            if (f_opr_one(T))
            {
                fs.push_back(P[0]->data);
                fs.push_back(T);
            }
            m = PolishCalculation(fs);
            Algebra_Node* W = SetNode(m);
            Algebra_Node& K = *parent;

            if (!(currentNode == root)) {
                if (DEBUG)
                {
                    std::cout << "func_5 : BEFORE" << std::endl;
                    Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
                }
                switch (p) {
                case 'L': {
                    K.addLeftNode(W);
                    break;
                }
                case 'R': {
                    K.addRightNode(W);
                    break;
                }
                }
                if (DEBUG)
                {
                    std::cout << "func_5 : AFTER" << std::endl;
                    Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
                }
            }
            else {
                root = W;
            }
            G.ExposedBranches.push_back(currentNode);
        }
    }
    return match;
}

void GoDown(std::stack<Algebra_Node*> st, std::stack<Algebra_Node*> parents, Algebra_Node* currentNode, Algebra_Node* parent, char p, Algebra_Node*& root, char& c, int level, GarbegeCollector& G)
{

    switch (c)
    {
    case 'L': { Algebra_Node* topNode = st.top(); st.pop(); st.pop(); st.push(topNode); break; } // �������� �������������� �������� �� �����.
    case 'R': { st.pop();  break;  } // ������-��� ����� ���������� ���������� ���� , ��� ����� � ������� ������ ������.
    case 'Z': { st.pop(); st.pop(); }
    }
    if (level)
    {
        st.push(parent);
        if (f_opr_two(parent->data))
        {
            parents.pop();
            parents.pop();
        }
        else if (f_opr_one(parent->data)) parents.pop();
    }
    else
    {
        while (!st.empty()) st.pop();
        while (!parents.empty()) parents.pop();
        st.push(root);
        parents.push(root);
    }
}


void simplify_F(Algebra_Node*& root)
{
    /*
    *  ������� ����������:
     1) ��������� �� ����
     2) ���������� � ������ � ������� �������.
     3) ������� �� �������
     4) ��������� �� �������
     5) �������� � ����� � ��������� ����.
     6) ������� ���� �� ����� ����� ����� ����.
     7) ���������� ������� � ����� �������
     8) ���������� ���� � ����� ������� m > 0.
    * */
    if (root == nullptr)
        return;

    std::stack<Algebra_Node*> st;
    std::stack<char> lr_st;
    std::stack<Algebra_Node*> parents;
    st.push(root);
    lr_st.push('0'); // root
    parents.push(root);
    int j = 0;
    Algebra_Node* const r = root;
    bool match = false;
    std::stack<int> st_depth;
    st_depth.push(0);
    int level = 0;
    GarbegeCollector G = GarbegeCollector();

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        if (currentNode == nullptr) continue;
        if (parents.empty()) parents.push(root);
        Algebra_Node* parent = parents.top();
        char p;
        if (lr_st.empty()) p = 'L'; // �������� ��� ������� � �����.
        else p = lr_st.top();
        st.pop();
        if (!lr_st.empty()) lr_st.pop();
        parents.pop();
        level = st_depth.top();
        st_depth.pop();
        match = false;

        Algebra_Node* R = root;
        if (currentNode->left != nullptr)
        {
            lr_st.push('L');
            parents.push(currentNode);
            st.push(currentNode->left);
            st_depth.push(level + 1);
        }
        if (currentNode->right != nullptr)
        {
            lr_st.push('R');
            parents.push(currentNode);
            st.push(currentNode->right);
            st_depth.push(level + 1);
        }
        if (DEBUG)
        {
            std::cout << "simplify_F : BEFORE : " << j << std::endl;
            Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
        }
        char c = '0';
        if (CE(currentNode->data.value, '*')) match = match || func_1(currentNode, parent, p, root, c, level, G); // ������� 1 , 4.
        if (CE(currentNode->data.value, '^')) match = match || func_2(currentNode, parent, p, root, c, level, G); // ������� 2 , 7 , 8.
        if (CE(currentNode->data.value, '/')) match = match || func_3(currentNode, parent, p, root, c, level, G); // ������� 3 , 6.
        if (CE(currentNode->data.value, '+') || CE(currentNode->data.value, '-')) match = match || func_4(currentNode, parent, p, root, c, level, G); // ������� 5.
        if (match)
        {
            GoDown(st, parents, currentNode, parent, p, root, c, level, G);
        }
        if (DEBUG)
        {
            std::cout << "simplify_F : AFTER : " << j << std::endl;
            Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
        }
        j++;
    }
    for (Algebra_Node* D : G.ExposedBranches)
    {
        RecursiveDestructor(D);
    }
    for (Algebra_Node* D : G.ExposedNodes) delete D;
}

void simplify_D(Algebra_Node*& root)
{
    /*
    *  ������� ����������:
     1) ��������� �� ����
     2) ���������� � ������ � ������� �������.
     3) ������� �� �������
     4) ��������� �� �������
     5) �������� � ����� � ��������� ����.
     6) ������� ���� �� ����� ����� ����� ����.
     7) ���������� ������� � ����� �������
     8) ���������� ���� � ����� ������� m > 0.
    * */
    if (root == nullptr)
        return;

    std::stack<Algebra_Node*> st;
    std::stack<char> lr_st;
    std::stack<Algebra_Node*> parents;
    st.push(root);
    lr_st.push('0'); // root
    parents.push(root);
    int j = 0;
    Algebra_Node* const r = root;
    bool match = false;
    GarbegeCollector G = GarbegeCollector();

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        if (currentNode == nullptr) continue;
        if (parents.empty()) parents.push(root);
        Algebra_Node* parent = parents.top();
        char p;
        if (lr_st.empty()) p = 'L'; // �������� ��� ������� � �����.
        else p = lr_st.top();
        st.pop();
        if (!lr_st.empty()) lr_st.pop();
        parents.pop();
        match = false;

        Algebra_Node* R = root;
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
        if (DEBUG)
        {
            std::cout << "simplify_D : BEFORE : " << j << std::endl;
            Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
        }
        char c = '0';
        match = match || func_5(currentNode, parent, p, root, c, 0 ,G);
        if (match)
        {
            if (c == 'Z')
            {
                if (f_opr_two(currentNode->data)) { st.pop(); st.pop(); }
                else if (f_opr_one(currentNode->data)) { st.pop(); }
            }
            currentNode = parent;
            if (st.empty()) break;
            if (currentNode == parent) st.push(root);
            else if (currentNode != root)
            {
                st.push(parent);
                if (f_opr_two(parent->data))
                {
                    parents.pop();
                    parents.pop();
                }
                else if (f_opr_one(parent->data)) parents.pop();
            }
        }
        if (DEBUG)
        {
            std::cout << "simplify_D : AFTER : " << j << std::endl;
            Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
        }
        j++;
    }

    for (Algebra_Node* D : G.ExposedBranches )
    {
        RecursiveDestructor(D);
    }
    for (Algebra_Node* D : G.ExposedNodes) delete D;

}

void simplify_E(Algebra_Node*& root)
{
    simplify_F(root);
    simplify_D(root);
}