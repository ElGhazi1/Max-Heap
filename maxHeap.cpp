#include "maxHeap.hpp"

MaxHeap::MaxHeap(int capacity) : capacity(capacity), heapSize(0) {
    heap.resize(capacity);
}

void MaxHeap::heapify(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heapSize && heap[left] > heap[largest])
        largest = left;

    if (right < heapSize && heap[right] > heap[largest])
        largest = right;

    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapify(largest);
    }
}

void MaxHeap::insert(int value) {
    if (heapSize == capacity) {
        // Heap is full
        return;
    }

    int currentIndex = heapSize;
    heap[heapSize++] = value;

    while (currentIndex != 0 && heap[(currentIndex - 1) / 2] < heap[currentIndex]) {
        std::swap(heap[currentIndex], heap[(currentIndex - 1) / 2]);
        currentIndex = (currentIndex - 1) / 2;
    }
}



void MaxHeap::deleteMax() {
    if (heapSize == 0) {
        // Heap is empty
        return;
    }

    heap[0] = heap[--heapSize];
    heapify(0);
}

void MaxHeap::heapSort() {
    for (int i = heapSize / 2 - 1; i >= 0; i--)
        heapify(i);

    for (int i = heapSize - 1; i > 0; i--) {
        std::swap(heap[0], heap[i]);
        heapify(0);
    }
}
