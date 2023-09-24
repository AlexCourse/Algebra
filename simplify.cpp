#include "simplify.h"
#define DEBUG 1


void func_1(Algebra_Node* currentNode , Algebra_Node* parent , char p , Algebra_Node* root)
{ // ['*']
    Algebra_Node& C = *currentNode;
    Algebra_Node* P[2];
    P[0] = currentNode->left;
    P[1] = currentNode->right;
    bool B = false;
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
        if (!(currentNode == root))
        {
            if (DEBUG)
            {
                cout << "func_1 : DEFORE" << endl;
                Print_Tree_R(root, "", false, false);
            }
            switch (p)
            {
                case 'L': { K.addLeftNode(W); break; }
                case 'R': { K.addRightNode(W); break; }
            }
            if (DEBUG)
            {
                cout << "func_1 : AFTER" << endl;
                Print_Tree_R(root, "", false, false);
            }
            while (0);
        }
        else root = W;
        // RecursiveDestructor(currentNode);
        currentNode = parent;

    }
    else if (!(k == -1))
    {
        delete currentNode;
        currentNode = parent;
        Algebra_Node& K = *parent;
        if (!(currentNode == root))
        {
            switch (p)
            {
                if (DEBUG)
                {
                    cout << "func_1 : BEFORE" << endl;
                    Print_Tree_Selected_R(root, currentNode, "", false, false);
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
                    cout << "func_1 : AFTER" << endl;
                    Print_Tree_Selected_R(root, currentNode, "", false, false);
                }
            }
        }
        else root = P[k];
        k = (k + 1) % 2; // 1-> 0 , 0 -> 1
        delete P[k]; // Удаление одного узла нулевого слагаемого.
        while (0);
    }
}

void func_2(Algebra_Node* currentNode, Algebra_Node* parent, char p , Algebra_Node* root)
{ // ['^']
    Algebra_Node& C = *currentNode;
    Algebra_Node* P[2];
    P[0] = currentNode->left;
    P[1] = currentNode->right;

    if (CE(P[1]->data.value, 0)) // Сокращение нулевой степени.
    {
        Algebra_Node* W = SetNode(1);
        Algebra_Node& K = *parent;
        if (!(currentNode == root))
        {
            if (DEBUG)
            {
                cout << "func_2 : BEFORE" << endl;
                Print_Tree_Selected_R(root, currentNode, "", false, false);
            }
            switch (p)
            {
                case 'L': { K.addLeftNode(W); break; }
                case 'R': { K.addRightNode(W); break; }
            }
            if (DEBUG)
            {
                cout << "func_2 : AFTER" << endl;
                Print_Tree_Selected_R(root, currentNode, "", false, false);
            }
            while (0);
        }
        else root = W;
        // RecursiveDestructor(currentNode);
        currentNode = parent;
    }
    else if (CE(P[1]->data.value, 1)) // Сокращение первой степени.
    {
        delete currentNode;
        currentNode = parent;
        Algebra_Node& K = *parent;
        if (DEBUG)
        {
            cout << "func_2 : BEFORE" << endl;
            Print_Tree_Selected_R(root, currentNode, "", false, false);
        }
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
        if (DEBUG)
        {
            cout << "func_2 : AFTER" << endl;
            Print_Tree_Selected_R(root, currentNode, "", false, false);
        }
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
                cout << "func_2 : BEFORE" << endl;
                Print_Tree_Selected_R(root, currentNode, "", false, false);
            }
            switch (p)
            {
                case 'L': { K.addLeftNode(W); break; }
                case 'R': { K.addRightNode(W); break; }
            }
            while (0);
            if (DEBUG)
            {
                cout << "func_2 : AFTER" << endl;
                Print_Tree_Selected_R(root, currentNode, "", false, false);
            }
        }
        else root = W;
        // RecursiveDestructor(currentNode);
        currentNode = parent;
    }
    else if (CE(P[0]->data.value, 0)) // Ноль в любой положительной степени.
    {
        if (P[1]->data.type == Token::Type::Integer || P[1]->data.type == Token::Type::Real || P[1]->data.type == Token::Type::Number)
        {
            double m;
            variant<string, int, double> Q = P[1]->data.GetValue();
            if (holds_alternative<int>(Q)) m = get<int>(Q);
            else if (holds_alternative<double>(Q)) m = get<double>(Q);
            if (m > 0)
            {
                Algebra_Node* W = SetNode(0);
                Algebra_Node& K = *parent;
                if (DEBUG)
                {
                    cout << "func_2 : BEFORE" << endl;
                    Print_Tree_Selected_R(root, currentNode, "", false, false);
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
                currentNode = parent;
                if (DEBUG)
                {
                    cout << "func_2 : AFTER" << endl;
                    Print_Tree_Selected_R(root, currentNode, "", false, false);
                }
            }

        }
    }
}

void func_3(Algebra_Node* currentNode, Algebra_Node* parent, char p, Algebra_Node* root) {
    // ['/']
    Algebra_Node& C = *currentNode;
    Algebra_Node* P[2];
    P[0] = currentNode->left;
    P[1] = currentNode->right;

    if (CE(P[0]->data.value, 0)) {
        Algebra_Node* W = SetNode(0);
        Algebra_Node& K = *parent;

        if (!(currentNode == root)) {
            if (DEBUG)
            {
                cout << "func_3 : BEFORE" << endl;
                Print_Tree_Selected_R(root, currentNode, "", false, false);
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
                cout << "func_3 : AFTER" << endl;
                Print_Tree_Selected_R(root, currentNode, "", false, false);
            }
        }
        else {
            root = W;
        }
        RecursiveDestructor(currentNode);
        currentNode = parent;
    }
    else if (CE(P[1]->data.value, 1)) {
        delete currentNode;
        currentNode = parent;
        Algebra_Node& K = *parent;

        if (!(currentNode == root)) {
            if (DEBUG)
            {
                cout << "func_3 : BEFORE" << endl;
                Print_Tree_Selected_R(root, currentNode, "", false, false);
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
                cout << "func_3 : AFTER" << endl;
                Print_Tree_Selected_R(root, currentNode, "", false, false);
            }
        }
        else {
            root = P[0];
        }
    }
}

void func_4(Algebra_Node* currentNode, Algebra_Node* parent, char p, Algebra_Node* root)
{ // ['+' , '-' ]
    Algebra_Node& C = *currentNode;
    Algebra_Node* P[2];
    P[0] = currentNode->left;
    P[1] = currentNode->right;
    bool B = false;
    int k = -1;

    for (int i = 0; i < 2; i++)
    {
        if (CE(P[i]->data.value, 0)) k = i;  // Если одно из слагаемых равно нулю , сохраняем номер этого слагаемого.
    }
    if (!(k==-1))
    {
        delete currentNode;
        currentNode = parent;
        delete P[k]; // Удалаение одного узла - нулевого слагаемого.
        k = (k + 1) % 2; // 1 -> 0 , 0 -> 1.
        Algebra_Node& K = *parent;
        if (!(currentNode == root))
        {
            if (DEBUG)
            {
                cout << "func_4 : BEFORE" << endl;
                Print_Tree_Selected_R(root, currentNode, "", false, false);
            }
            switch (p)
            {
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
            }
            if (DEBUG)
            {
                cout << "func_4 : AFTER" << endl;
                Print_Tree_Selected_R(root, currentNode, "", false, false);
            }
        }
        else root = P[k];
    }

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

    stack<Algebra_Node*> st;
    stack<char> lr_st;
    stack<Algebra_Node*> parents;
    st.push(root);
    lr_st.push('0');
    parents.push(root);
    int j = 0;
    Algebra_Node* const r = root;

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        Algebra_Node* parent = parents.top();
        char p = lr_st.top();
        st.pop();
        lr_st.pop();
        parents.pop();

        Algebra_Node* R = root;
        if (DEBUG)
        {
            cout << "simplify_F : BEFORE : " << j <<  endl;
            Print_Tree_Selected_R(root , currentNode, "" , false , false);
        }
        if (CE(currentNode->data.value, "*")) func_1(currentNode, parent, p , R); // Правила 1 , 4.
        if (CE(currentNode->data.value, "^")) func_2(currentNode, parent, p , R); // Правила 2 , 7 , 8.
        if (CE(currentNode->data.value, "/")) func_3(currentNode, parent, p , R); // Правило 3 , 6.
        if (CE(currentNode->data.value, "+") || CE(currentNode->data.value, "-")) func_4(currentNode, parent, p , R); // Правило 5.
        if (DEBUG)
        {
            cout << "simplify_F : AFTER : " << j << endl;
            Print_Tree_Selected_R(root, currentNode, "", false, false);
        }
        j++;
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

    Algebra_Node* Q = SetNode("0"); // Заглушка.
    return Q;
}