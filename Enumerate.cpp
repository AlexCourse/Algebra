#include "Enumerate.h"
#include <set>

using namespace std;

set<int> CountIndex(deque<Token> fs)
{
	deque<Token>::iterator iter;
	set<int> f_box;
	for (iter = fs.begin(); iter != fs.end(); iter++)
	{
		Token token = *iter;
		int index = token.index;
		f_box.insert(index);
	}
	return f_box;
}

set<int> CountIndex(vector<Token> fs)
{
	vector<Token>::iterator iter;
	set<int> f_box;
	for (iter = fs.begin(); iter != fs.end(); iter++)
	{
		Token token = *iter;
		int index = token.index;
		f_box.insert(index);
	}
	return f_box;
}