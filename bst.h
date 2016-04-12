#ifndef BST
#define BST

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include "node_bst.h"

using namespace std;

enum BST_TRAVERSAL_TYPES {IN_ORDER, PRE_ORDER, POST_ORDER};
enum BST_ERROR_TYPES {TREE_EMPTY};

#define leftChild(n) (2*n+1)
#define rightChild(n) (2*n+2)
#define parent(n) ((n-1)/2)

template<typename T>
class bst
{
    public:
        typedef void (bst<T>::*fptr)(int,ostream &) const;
        bst(BST_TRAVERSAL_TYPES  t = IN_ORDER);
        bst(const T &d, int c = 1, int l = 0, int p = 0, BST_TRAVERSAL_TYPES t = IN_ORDER);
        bst(const bst<T> &other);
        ~bst();
        bst<T>& operator=(const bst<T> &other);

        void insert(const T &d, int c = 1, int l = 0, int p = 0);
        bst<T>& operator<<(const T &d);
        int find(const T &d, int& index);
        void clear();
        bool remove(const T &d, int c = 1);
        bool removeAll(const T &d);
        void moveUp(int pos);
        int totalData();
        int totalNodes(int root);
        int depth();
        const int leftMost(int index) const;
        const int rightMost(int index) const;
        bool empty() const;
        bool balanced();
        void rebalance();
        void setTraversal(BST_TRAVERSAL_TYPES t);
        BST_TRAVERSAL_TYPES currentTraversal();
        ostream& print(ostream &out = cout) const;


        template<typename U>
        friend
        ostream& operator<<(ostream& out, const bst<U> &other);

        template<typename U>
        friend
        istream& operator>>(istream& in, bst<U> &other);

    private:
        vector<node<T> > tree;
        BST_TRAVERSAL_TYPES  traverse;
        fptr whatToDo[3];
        int maxIndex;
        node<T> null;

        void addLayer();
        void copy(const bst<T> &other);
        void nukem();
        void addLineOrPara(vector<int>& v, const int& number);
        void inOrder(int currIndex, ostream &out) const;
        void preOrder(int currIndex, ostream &out) const;
        void postOrder(int currIndex, ostream &out) const;
        void printNode(const node<T>& word, ostream &out) const;
        bool balanced(int root);
        int depth(int index);
        int subtreeHeight(int root);
        int findParent(int i, const T& d);
        int totalDataCount(int root);
        void initialize(BST_TRAVERSAL_TYPES  t );
        void createSortedTree(vector<node<T> >& sortedTree, int index);
        void balanceSortedTree(const vector<node<T> >& sortedTree, int start, int end, int currIndex);
};

#endif // BST

