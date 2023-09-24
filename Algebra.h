#pragma once
#include <vector>
#include <stack>

using namespace std;

struct Cane
{

	vector<vector<char>> paths;
};


void Print_paths(const vector<vector<char>>& paths) {
	for (const auto& path : paths) {
		for (const auto& ch : path) {
			cout << ch;
		}
		cout << endl;
	}
}