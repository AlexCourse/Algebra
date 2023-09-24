#pragma once

#pragma once
#include <vector>
#include <stack>


struct Cane
{

	std::vector<std::vector<char>> paths;
};


void Print_paths(const std::vector<std::vector<char>>& paths) {
	for (const auto& path : paths) {
		for (const auto& ch : path) {
			std::cout << ch;
		}
		std::cout << std::endl;
	}
}
