#include "simplify.h"
#define DEBUG 1


bool func_1(Algebra_Node* currentNode , Algebra_Node* parent , char p , Algebra_Node*& root)
{ // ['*']
    Algebra_Node& C = *currentNode;
    Algebra_Node* P[2];
    P[0] = currentNode->left;
    P[1] = currentNode->right;
    bool B = false;
    bool match = false;
    int k = -1;

    for (int i = 0; i < 2; i++)
    {
        if (CE(P[i]->data.value, 0)) B = true; // Если один из множителй равен нулю.
        else if (CE(P[i]->data.value, 1)) k = i; // Сохраняем номер единичного операнда.
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
                Print_Tree_R_ColoredSelectNode(root, currentNode,  "", false, false);
            }
            switch (p)
            {
                case 'L': { K.addLeftNode(W); break; }
                case 'R': { K.addRightNode(W); break; }
            }
            if (DEBUG)
            {
                std::cout << "func_1 : AFTER" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode , "", false, false);
            }
            while (0);
        }
        else root = W;
        // RecursiveDestructor(currentNode);
    }
    else if (!(k == -1))
    {
        Algebra_Node* R = currentNode;
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
        delete P[k]; // Удаление одного узла нулевого слагаемого.
        free(R);
        while (0);
    }
    return match;
}

bool func_2(Algebra_Node* currentNode, Algebra_Node* parent, char p , Algebra_Node*& root)
{ // ['^']
    Algebra_Node& C = *currentNode;
    Algebra_Node* P[2];
    P[0] = currentNode->left;
    P[1] = currentNode->right;
    if (DEBUG) root = root;
    bool match = false;

    if (CE(P[1]->data.value, 0)) // Сокращение нулевой степени.
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
    }
    else if (CE(P[1]->data.value, 1)) // Сокращение первой степени.
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
        free(prev_node);
        delete P[1]; // Удаление одного узла -показатель первой степени.
        while (0);
    }
    if (CE(P[0]->data.value, 1)) // Единица в любой степени.
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
        // RecursiveDestructor(currentNode);
    }
    else if (CE(P[0]->data.value, 0)) // Ноль в любой положительной степени.
    {
        if (P[1]->data.type == Token::Type::Integer || P[1]->data.type == Token::Type::Real || P[1]->data.type == Token::Type::Number)
        {
            double m;
            std::variant<std::string, int, double> Q = P[1]->data.GetValue();
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
                // RecursiveDestructor(currentNode);
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

bool func_3(Algebra_Node* currentNode, Algebra_Node* parent, char p, Algebra_Node*& root) {
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
        // RecursiveDestructor(currentNode);
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
            delete P[1]; // Удаление одного узла - единичного делителя.
            if (DEBUG)
            {
                std::cout << "func_3 : AFTER" << std::endl;
                Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
            }
        }
        else {
            root = P[0];
        }
        free(R);
    }
    return match;
}

bool func_4(Algebra_Node* currentNode, Algebra_Node* parent, char p, Algebra_Node*& root) {
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
        delete P[k];
        free(R);
    }

    return match;
}

bool func_5(Algebra_Node* currentNode, Algebra_Node* parent, char p, Algebra_Node*& root)
{
    Algebra_Node& C = *currentNode;
    Algebra_Node* P[2];
    P[0] = currentNode->left;
    P[1] = currentNode->right;
    if (DEBUG) root = root;
    bool match = false;
    bool B = true;
    if (C.data.type == Token::Type::Number || C.data.type == Token::Type::Integer || C.data.type == Token::Type::Real) return false;
    for (int i = 0; i < 2; i++)
    {
        if (!(P[i]->data.type == Token::Type::Number || P[i]->data.type == Token::Type::Integer || P[i]->data.type == Token::Type::Real)) B = false;
    }
    if (B)
    {
        match = true;
        Token& T = C.data;
        double m = 0;
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
        // RecursiveDestructor(currentNode);
    }
    return match;
}


Algebra_Node* simplify_F(Algebra_Node* root)
{
    /*
    *  Функция сокращения:
     1) Умножение на ноль
     2) Возведения в первую и нулевую степень.
     3) Деления на единицу
     4) Умножение на единицу
     5) Сложение с нулем и вычитание нуля.
     6) Деление нуля на любое число кроме нуля.
     7) Возведение единицы в любую степень
     8) Возведение нуля в любую степень m > 0.
    * */
    if ( root == nullptr)
        return nullptr;

    std::stack<Algebra_Node*> st;
    std::stack<char> lr_st;
    std::stack<Algebra_Node*> parents;
    st.push(root);
    lr_st.push('0'); // root
    parents.push(root);
    int j = 0;
    Algebra_Node* const r = root;
    bool match = false;

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        if (currentNode == nullptr) continue;
        if (parents.empty()) parents.push(root);
        Algebra_Node* parent = parents.top();
        char p;
        if (lr_st.empty()) p = 'L'; // Заглушка для символа в корне.
        else p = lr_st.top();
        st.pop();
        if(!lr_st.empty()) lr_st.pop();
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
            std::cout << "simplify_F : BEFORE : " << j << std::endl;
            Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
        }
        if (CE(currentNode->data.value, "*")) match = match || func_1(currentNode, parent, p, root); // Правила 1 , 4.
        if (CE(currentNode->data.value, "^")) match = match || func_2(currentNode, parent, p, root); // Правила 2 , 7 , 8.
        if (CE(currentNode->data.value, "/")) match = match || func_3(currentNode, parent, p, root); // Правило 3 , 6.
        if (CE(currentNode->data.value, "+") || CE(currentNode->data.value, "-")) match = match || func_4(currentNode, parent, p, root); // Правило 5.
        if (match)
        {   
            currentNode = parent;
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
            std::cout << "simplify_F : AFTER : " << j << std::endl;
            Print_Tree_R_ColoredSelectNode(root, currentNode, "", false, false);
        }
        j++;
    }

    Algebra_Node* Q = SetNode("0"); // Заглушка.
    return Q;
}

Algebra_Node* simplify_D(Algebra_Node* root)
{
    /*
    *  Функция сокращения:
     1) Умножение на ноль
     2) Возведения в первую и нулевую степень.
     3) Деления на единицу
     4) Умножение на единицу
     5) Сложение с нулем и вычитание нуля.
     6) Деление нуля на любое число кроме нуля.
     7) Возведение единицы в любую степень
     8) Возведение нуля в любую степень m > 0.
    * */
    if (root == nullptr)
        return nullptr;

    std::stack<Algebra_Node*> st;
    std::stack<char> lr_st;
    std::stack<Algebra_Node*> parents;
    st.push(root);
    lr_st.push('0'); // root
    parents.push(root);
    int j = 0;
    Algebra_Node* const r = root;
    bool match = false;

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        if (currentNode == nullptr) continue;
        if (parents.empty()) parents.push(root);
        Algebra_Node* parent = parents.top();
        char p;
        if (lr_st.empty()) p = 'L'; // Заглушка для символа в корне.
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
        match = match || func_5(currentNode, parent, p, root);
        if (match)
        {
            currentNode = parent;
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

    Algebra_Node* Q = SetNode("0"); // Заглушка.
    return Q;
}

Algebra_Node* simplify_E(Algebra_Node* root)
{
    Algebra_Node* first_root = simplify_F(root);
    Algebra_Node* second_node = simplify_D(first_root);
    return second_node;
}