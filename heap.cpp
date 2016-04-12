#include "heap.h"


template<typename T>
heap<T>::heap()
{
    lastEntered = 0;
}

template<typename T>
heap<T>::heap(const node<T> &n)
{
    reserve();
    list.push_back(n);
    lastEntered = 1;
}

template<typename T>
heap<T>::~heap()
{
    clear();
}

template<typename T>
heap<T>::heap(const heap<T> &other)
{
    copy(other);
}

template<typename T>
heap<T>& heap<T>::operator=(const heap<T> &other)
{
    if(this != &other)
    {
        clear();
        copy(other);
    }
    return *this;
}

template<typename T>
bool heap<T>::empty()
{
    return !lastEntered;
}

template<typename T>
size_t heap<T>::size()
{
    return lastEntered;
}

template<typename T>
void heap<T>::clear()
{
    node<T> n;
    while(!empty())
        *this>>n;
    lastEntered = 0;
    list.shrink_to_fit();
}

template<typename T>
heap<T>& heap<T>::operator<<(const node<T> &n)
{
    if(lastEntered == list.capacity())
        reserve();

    ++lastEntered;
    list.push_back(n);
    reheapifyUp();

    return *this;
}

template<typename T>
heap<T>& heap<T>::operator>>(node<T> &n)
{
    if(empty())
        throw HEAP_EMPTY;

    n = list[0];
    if(lastEntered == 1)
    {
        list[0].data = T();
        list.resize(0);
        lastEntered--;
        return *this;
    }

    swap(list[0], list[lastEntered-1]);
    list[lastEntered-1].data = T();
    list.erase(list.end());
    lastEntered--;

    if(list.capacity() == 2*lastEntered+1)
        list.resize(lastEntered);

    reheapifyDown();
    return *this;
}

template<typename T>
void heap<T>::copy(const heap<T>& other)
{
    if(other.lastEntered == 0)
       return;
    list.reserve(other.list.capacity());
    for(size_t i = 0; i < other.lastEntered; ++i)
        list.push_back(other.list[i]);
    lastEntered = other.lastEntered;
}

template<typename T>
void heap<T>::reserve()
{
    list.reserve(2*lastEntered+1);
}

template<typename T>
void heap<T>::reheapifyUp()
{
    bool notDone = true;
    size_t last = lastEntered;

    while(notDone && parent(last))
    {
        if(list[last-1].data > list[parent(last)-1].data)
        {
            swap(list[last-1], list[parent(last)-1]);
            last/=2;
        }
        else
          notDone = false;
    }
}

template<typename T>
void heap<T>::reheapifyDown()
{
    size_t toSwap;
    bool notDone = true;
    for(size_t i = 1; notDone && leftChild(i) <= lastEntered; i = toSwap)
    {
        toSwap = rightChild(i)>lastEntered ?
                    leftChild(i)   :
                 list[leftChild(i)-1] > list[rightChild(i)-1]
                                   ?
                 leftChild(i) : rightChild(i);
        if(list[i-1].data < list[toSwap-1].data)
           swap(list[i-1],list[toSwap-1]);
        else
           notDone = false;
    }
}

template<typename U>
ostream& operator<<(ostream& out, const heap<U> &h)
{
    heap<U> theCopy(h);
    node<U> n;
    while(!theCopy.empty())
    {
        theCopy>>n;
        out<<n;
    }
    return out;
}

template<typename U>
istream& operator>>(istream& in, heap<U> &h)
{
    node<U> n;
    while(in>>n)
        h << n;
    return in;
}
