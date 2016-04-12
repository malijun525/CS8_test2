#include "bst.h"


template<typename T>
bst<T>::bst(BST_TRAVERSAL_TYPES  t )
{
    initialize(t);
}

template<typename T>
bst<T>::bst(const T &d, int c, int l, int p, BST_TRAVERSAL_TYPES t)
{
    initialize(t);
    addLayer();
    tree[0] = node<T>(d, c, l, p);
    ++maxIndex;
}

template<typename T>
bst<T>::bst(const bst<T> &other)
{
    copy(other);
}


template<typename T>
bst<T>::~bst()
{
    nukem();
}

template<typename T>
bst<T>& bst<T>::operator=(const bst<T> &other)
{
    if(this != &other)
        copy(other);
    return *this;
}


template<typename T>
void bst<T>::insert(const T &d, int c, int l, int p)
{
    if(empty()){
        addLayer();
        tree[0] = node<T>(d, c, l, p);
        ++maxIndex;
    }
    else{
        int i = 0;
        bool notDone = true;
        while(notDone){

            if(d == tree[i].data){
                tree[i].count += c;
                addLineOrPara(tree[i].lines, l);
                addLineOrPara(tree[i].paras, p);
                notDone = false;
            }
            else{
                int child;
                child = d < tree[i].data ? leftChild(i) : rightChild(i);
                if(depth(child) > depth())
                    addLayer();
                if(tree[child] == null){
                    tree[child] = node<T>(d, c, l, p);
                    if(child > maxIndex)
                        maxIndex = child;
                    notDone = false;
                }
                else
                    i = child;
            }
        }
        if(!balanced())
            rebalance();
    }
}

template<typename T>
void bst<T>::addLineOrPara(vector<int>& v, const int& number)
{
    if(v[v.size()-1] != number){
        v.reserve(v.size() + 1);
        v.push_back(number);
    }
}

template<typename T>
bst<T>& bst<T>::operator<<(const T &d)
{
    insert(d, 1, 0, 0);
    return *this;
}

template<typename T>
int bst<T>::find(const T& d, int& index)
{
    if(empty()){
        index = -1;
        return 0;
    }
    int i = 0;
    while(depth(i) <= depth()){
        if(tree[i] == null){
            index = -1;
            return 0;
        }
        else{
            if(tree[i].data == d){
                index = i;
                return tree[i].count;
            }
            else
                i = d < tree[i].data ? leftChild(i) : rightChild(i);
        }
    }
    index = -1;
    return 0;
}

template<typename T>
void bst<T>::clear()
{
    tree.clear();
    maxIndex = -1;
}

template<typename T>
bool bst<T>::remove(const T &d, int c)
{
    if(empty())
        return false;

    int count, i;
    count = find(d, i);
    if(i == -1)
        return false;

    if(c < count)
        tree[i].count -= c;
    else{
        tree[i] = null;

        //if remove node is not at bottom
        if(depth(i) < depth()){
            int base = 1;

            //if only has left child
            if(tree[leftChild(i)] != null && tree[rightChild(i)] == null){
                int theMost = rightMost(leftChild(i));
                if(theMost != leftChild(i)){
                    tree[i] = tree[theMost];
                    tree[theMost] = null;
                    i = theMost;
                }
                while(depth(i) < depth()){
                    for(int n = 0; n < base; ++n)
                        tree[i+n] = tree[leftChild(i)+n];
                    i = leftChild(i);
                    base *= 2;
                }
                for(int n = 0; n < base/2; ++n)
                    tree[i+n] = null;
            }

            //if right child exists
            else{
                int theMost = leftMost(rightChild(i));
                if(theMost != rightChild(i)){
                    tree[i] = tree[theMost];
                    tree[theMost] = null;
                    i = theMost;
                }
                else{
                    //if both children exist
                    if(tree[rightChild(i)] != null){
                        tree[i] = tree[rightChild(i)];
                        tree[rightChild(i)] = null;
                        i = rightChild(i);
                    }
                }
                while(depth(i) < depth()){
                    for(int n = 0; n < base; ++n)
                        tree[i-n] = tree[rightChild(i)-n];
                    i = rightChild(i);
                    base *= 2;
                }
                for(int n = 0; n < base/2; ++n)
                    tree[i-n] = null;
            }
        }
    }

    if(tree[maxIndex] == null){
        for(; tree[i] == null && i >= 0; --i);
        maxIndex = i;
    }
    if(empty()){
        tree.clear();
        tree.shrink_to_fit();
    }
    else{
        tree.resize(pow(2, depth()) - 1);
        tree.shrink_to_fit();
    }

    if(!balanced())
        rebalance();
    return true;
}

template<typename T>
bool bst<T>::removeAll(const T &d)
{
    return remove(d,UINT_MAX);
}

template<typename T>
int bst<T>::totalData()
{
    return totalDataCount(0);
}

template<typename T>
int bst<T>::totalDataCount(int root)
{
    return root <= maxIndex && tree[root] != null ? tree[root].count + totalDataCount(leftChild(root)) + totalDataCount(rightChild(root)) : 0;
}

template<typename T>
int bst<T>::totalNodes(int root)
{
    return root <= maxIndex && tree[root] != null ? 1 + totalNodes(leftChild(root)) + totalNodes(rightChild(root)) : 0;
}

template<typename T>
int bst<T>::depth()
{
    return depth(maxIndex);
}

template<typename T>
int bst<T>::depth(int index)
{
    return index == -1 ? 0 : (int)(log2(index+1)+1);
}

template<typename T>
const int bst<T>::leftMost(int index) const
{
    if(empty())
        throw TREE_EMPTY;
    for(; leftChild(index) <= maxIndex && tree[leftChild(index)] != null; index = leftChild(index));
    return index;
}

template<typename T>
const int bst<T>::rightMost(int index) const
{
    if(empty())
        throw TREE_EMPTY;
    for(; rightChild(index) <= maxIndex && tree[rightChild(index)] != null; index = rightChild(index));
    return index;
}

template<typename T>
bool bst<T>::empty() const
{
    return maxIndex == -1;
}

template<typename T>
bool bst<T>::balanced()
{
   return balanced(0);
}

template<typename T>
void bst<T>::setTraversal(BST_TRAVERSAL_TYPES t)
{
    traverse = t;
}

template<typename T>
BST_TRAVERSAL_TYPES bst<T>::currentTraversal()
{
    return traverse;
}

template<typename T>
void  bst<T>::addLayer()
{
    int capacity = pow(2, depth() + 1) - 1;
    tree.reserve(capacity);
    tree.resize(capacity, null);
}

template<typename T>
void bst<T>::copy(const bst<T> &other)
{
    nukem();
    tree.reserve(other.tree.capacity());
    // vector::operator=
    // copies all the elements from x into the container
    // (with x preserving its contents).
    tree = other.tree;
    maxIndex = other.maxIndex;
    traverse = other.traverse;
}

template<typename T>
void bst<T>::nukem()
{
    if(!tree.capacity())
        return;
    clear();
    tree.shrink_to_fit();
}


template<typename T>
void bst<T>::inOrder(int currIndex, ostream &out) const
{
    if(currIndex > maxIndex || tree[currIndex].count == 0)
        return;
    inOrder(leftChild(currIndex),out);
    printNode(tree[currIndex], out);
    inOrder(rightChild(currIndex),out);
}

template<typename T>
void bst<T>::preOrder(int currIndex, ostream &out) const
{
    if(currIndex > maxIndex || tree[currIndex].count == 0)
        return;
    printNode(tree[currIndex], out);
    preOrder(leftChild(currIndex),out);
    preOrder(rightChild(currIndex),out);
}

template<typename T>
void bst<T>::postOrder(int currIndex, ostream &out) const
{
    if(currIndex > maxIndex || tree[currIndex].count == 0)
        return;
    postOrder(leftChild(currIndex),out);
    postOrder(rightChild(currIndex),out);
    printNode(tree[currIndex], out);
}

template<typename T>
void bst<T>::printNode(const node<T>& word, ostream &out) const
{
    out << word.data << endl;
    out << "----------------" <<endl;
    out << "count:" << word.count << endl;
    out << "lines No.:" << endl;
    for(int i = 0; i < word.lines.size(); ++i)
        out << word.lines[i] << ", ";
    out << endl;
    out << "paragraphs No.:" << endl;
    for(int i = 0; i < word.paras.size(); ++i)
        out << word.paras[i] << ", ";
    out << endl;
}

template<typename T>
int bst<T>::subtreeHeight(int root)
{
    return root > maxIndex || tree[root] == null ? 0 : 1 + max(subtreeHeight(leftChild(root)), subtreeHeight(rightChild(root)));
}

template<typename T>
bool bst<T>::balanced(int root)
{
    return abs((double)subtreeHeight(leftChild(root)) - subtreeHeight(rightChild(root))) <= 1;
}

template<typename T>
void bst<T>::rebalance()
{
    if(empty())
        return;

    vector<node<T>> sortedTree;

    sortedTree.reserve(totalNodes(0));
    createSortedTree(sortedTree, 0);

    int start = 0, end = sortedTree.size()-1;
    balanceSortedTree(sortedTree, start, end, 0);
    sortedTree.clear();
    sortedTree.shrink_to_fit();

    for(end = tree.capacity()-1; tree[end] == null; --end);
    maxIndex = end;
    tree.resize(pow(2, depth()) - 1);
    tree.shrink_to_fit();
}

template<typename T>
void bst<T>::createSortedTree(vector<node<T> >& sortedTree, int index)
{
    if(empty() || index > maxIndex || tree[index] == null)
        return;
    createSortedTree(sortedTree, leftChild(index));
    sortedTree.push_back(tree[index]);
    tree[index] = null;
    createSortedTree(sortedTree, rightChild(index));
}

template<typename T>
void bst<T>::balanceSortedTree(const vector<node<T> >& sortedTree, int start, int end, int currIndex)
{
    if (start > end)
      return;

    int mid = (start + end)/2;
    tree[currIndex] = sortedTree[mid];
    balanceSortedTree(sortedTree, start, mid-1, leftChild(currIndex));
    balanceSortedTree(sortedTree, mid+1, end, rightChild(currIndex));
}

template<typename T>
int bst<T>::findParent(int i, const T& d)
{
    return   i > maxIndex || tree[i] == null?  -1 :
             (!(leftChild(i) > maxIndex || tree[leftChild(i)] == null)? tree[leftChild(i)].data == d : 0)
             ||(!(rightChild(i) > maxIndex || tree[rightChild(i)] == null)? tree[rightChild(i)].data == d : 0)
             ? i
             : findParent((d < tree[i]? leftChild(i) : rightChild(i)), d);
}

template<typename T>
void bst<T>::initialize(BST_TRAVERSAL_TYPES  t )
{
    maxIndex = -1;
    traverse = t;
    null = node<T>(0, 0);
    whatToDo[IN_ORDER] = &bst<T>::inOrder;
    whatToDo[PRE_ORDER] = &bst<T>::preOrder;
    whatToDo[POST_ORDER] = &bst<T>::postOrder;
}

template<typename T>
ostream& bst<T>::print(ostream &out) const
{
    (this->*whatToDo[traverse])(0, out);
    return out;
}

template<typename U>
ostream& operator<<(ostream& out, const bst<U> &other)
{
    return other.print(out);
}

template<typename U>
istream& operator>>(istream& in, bst<U> &other)
{
    U data;
    int count, line, para;
    char junk;
    string lineStr;
    stringstream ss;
    bool moreData = true;
    if(&in == &cin)
        while(moreData)
        {
            cout<<"Data: ";
            getline(in,lineStr);
            if(lineStr.empty())
                moreData = false;
            else
            {
                ss<<lineStr;
                ss>>data;
                ss.clear();
                cout<<"Count: ";
                cin>>count;
                cout<<"Line No.: ";
                cin>>line;
                cout<<"Para No.: ";
                cin>>para;
                other.insert(data,count,line,para);
            }
        }
    else
        while(in>>data>>junk>>count>>junk>>line>>junk>>para>>junk)
            other.insert(data,count,line,para);

    return in;
}
