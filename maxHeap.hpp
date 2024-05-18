#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP
#include <iostream>
#include <vector>

using namespace std;

typedef int datatype;

typedef vector<datatype> tablePriority;

class MaxHeap {
private:
    tablePriority heap;
    int capacity;
    int heapSize;

    void heapify(int index);

public:
    MaxHeap(int capacity);
    void insert(int value);
    void deleteMax();
    void heapSort();
};

#endif
