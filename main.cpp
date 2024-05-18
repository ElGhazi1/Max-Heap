#include <iostream>
#include "maxHeap.hpp"

int main() {
    MaxHeap heap(10);

    // Test insertion
    heap.insert(3);
    heap.insert(2);
    heap.insert(15);
    heap.insert(5);
    heap.insert(4);
    heap.insert(45);

    // Test getMax

    // Test deleteMax
    heap.deleteMax();

    // Test heapSort
    heap.heapSort();
    std::cout << "Sorted array: ";
    for (int i = 0; i < 5; ++i)
    std::cout << std::endl;

    return 0;
}
