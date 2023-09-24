#include "PrintColourConsole.h"

void Print_Tree_R_ColoredSelectNode(Algebra_Node const* node, Algebra_Node* const selectedNode, string const& prefix = " ", bool root = true, bool last = true) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ������� ����� �� �������
    cout << prefix << (root ? "" : (last ? ch_udia_hor : ch_ver_hor));
    if ( node == selectedNode) SetConsoleTextAttribute(hConsole, 11);
    cout << (node ? ToString(node->data.value) : "") << endl;
    if (!node || (!node->left && !node->right))
        return;
    vector<Algebra_Node*> v{ node->left, node->right };
    for (size_t i = 0; i < v.size(); ++i)
        Print_Tree_R(v[i], prefix + (root ? "" : (last ? "  " : ch_ver_spa)), false, i + 1 >= v.size());
}