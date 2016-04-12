#ifndef NODE_HEAP
#define NODE_HEAP


#include <vector>

using namespace std;

template<typename T>
struct node
{
    T data;
    int count;
    vector<int> lines;
    vector<int> paras;

    node(const T &d = T(), int l = 0, int p = 0)
    {
        data = d;
        lines.push_back(l);
        paras.push_back(p);
    }

    ~node()
    {
        data = T();
        lines.clear();
        paras.clear();
        lines.shrink_to_fit();
        paras.shrink_to_fit();
    }

    template<typename U>
    friend
    bool operator==(const node<U>& x, const node<U> &y)
    {
         return x.data == y.data &&
                x.lines == y.lines && x.paras == y.lines;
    }

    template<typename U>
    friend
    bool operator!=(const node<U>& x, const node<U> &y)
    {
         return x.data != y.data ||
                x.lines != y.lines || x.paras != y.lines;
    }
};

#endif // NODE_HEAP

