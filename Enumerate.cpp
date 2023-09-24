#include "Enumerate.h"
#include <set>

using namespace std;

vector<int> CountIndex(deque<Token> fs)
{
	deque<Token>::iterator iter;
	vector<int> kh;
	for (iter = fs.begin(); iter != fs.end(); iter++)
	{
		Token token = *iter;
		int index = token.index;
		kh.push_back(index);
	}
	return kh;
}

vector<int> CountIndex(vector<Token> fs)
{
	vector<Token>::iterator iter;
	vector<int> kh;
	for (iter = fs.begin(); iter != fs.end(); iter++)
	{
		Token token = *iter;
		int index = token.index;
		kh.push_back(index);
	}
	return kh;
}