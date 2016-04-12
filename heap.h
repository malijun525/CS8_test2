#ifndef HEAP
#define HEAP

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include "node_heap.h"

using namespace std;

enum HEAP_ERRORS {HEAP_EMPTY};

#define leftChild(n) (2*n)
#define rightChild(n) (2*n+1)
#define parent(n) (n/2)

template<typename T>
class heap
{
    public:
        heap();
        heap(const node<T> &n);
        ~heap();
        heap(const heap<T> &other);
        heap<T>& operator=(const heap<T> &other);

        bool empty();
        size_t size();
        void clear();

        heap<T>& operator<<(const node<T> &n);
        heap<T>& operator>>(node<T> &n);

        template<typename U>
        friend
        ostream& operator<<(ostream& out, const heap<U> &h);

        template<typename U>
        friend
        istream& operator>>(istream& in, heap<U> &h);

    private:
        vector<node<T> > list;
        size_t lastEntered;

        void copy(const heap<T>& other);
        void reserve();
        void reheapifyUp();
        void reheapifyDown();
};

#endif // HEAP

