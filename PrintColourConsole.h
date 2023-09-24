#pragma once
#include <windows.h>
#include "Algebra_Node.h"

void Print_Tree_R_ColoredSelectNode(Algebra_Node const* node, Algebra_Node* const selectedNode, std::string const& prefix, bool root, bool last);
