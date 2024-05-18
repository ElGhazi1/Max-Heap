#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

#include <vector>

class MaxHeap {
private:
    std::vector<int> heap;
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
