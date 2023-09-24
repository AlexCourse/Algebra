#include "vector_cl.h"
using namespace std;

template <typename T>
void ReverseVector(vector<T>& fh)
{
    int start = 0;
    int end = fh.size() - 1;

    while (start < end) {
        swap(fh[start], fh[end]);
        start++;
        end--;
    }
}
