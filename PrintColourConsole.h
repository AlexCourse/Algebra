#pragma once

#pragma once
#include <windows.h>
#include "Algebra_Node.h"

void Print_Tree_R_ColoredSelectNode(Algebra_Node const* node, Algebra_Node* const selectedNode, std::string const& prefix, bool root, bool last);
void PrintColorText(std::string expr, int color);
void PrintLineWithColorRed(std::string expr, std::set<int> f_box);
