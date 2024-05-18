#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

#include <iostream>
#include <vector>

using namespace std;

template<typename Key, typename Value>
class MaxHeap {
private:
    struct Node {
        Key key;
        Value value;
    };

    vector<Node> heap;
    int capacity;
    int heapSize;

    void upHeap(int index);
    void downHeap(int index);

public:
    MaxHeap(int capacity);
    void insert(const Key& key, const Value& value);
    void deleteMax();
    void heapSort();
    bool isEmpty() const;
    Node getMax() const;
    void show() const;
};

template<typename Key, typename Value>
MaxHeap<Key, Value>::MaxHeap(int capacity) : capacity(capacity), heapSize(0) {
    heap.resize(capacity);
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::upHeap(int index) {
    while (index != 0 && heap[(index - 1) / 2].key < heap[index].key) {
        swap(heap[index], heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::downHeap(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heapSize && heap[left].key > heap[largest].key)
        largest = left;

    if (right < heapSize && heap[right].key > heap[largest].key)
        largest = right;

    if (largest != index) {
        swap(heap[index], heap[largest]);
        downHeap(largest);
    }
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::insert(const Key& key, const Value& value) {
    if (heapSize == capacity) {
        // Heap is full
        return;
    }

    int currentIndex = heapSize;
    heap[heapSize++] = {key, value};

    // Up-heap (bubble-up)
    upHeap(currentIndex);
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::deleteMax() {
    if (heapSize == 0) {
        // Heap is empty
        return;
    }

    heap[0] = heap[--heapSize];
    downHeap(0);
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::heapSort() {
    int originalSize = heapSize;
    for (int i = heapSize / 2 - 1; i >= 0; i--)
        downHeap(i);

    for (int i = heapSize - 1; i > 0; i--) {
        swap(heap[0], heap[i]);
        heapSize--;
        downHeap(0);
    }

    heapSize = originalSize;
}

template<typename Key, typename Value>
bool MaxHeap<Key, Value>::isEmpty() const {
    return heapSize == 0;
}

template<typename Key, typename Value>
typename MaxHeap<Key, Value>::Node MaxHeap<Key, Value>::getMax() const {
    if (heapSize == 0) {
        throw runtime_error("Heap is empty");
    }
    return heap[0];
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::show() const {
    for (int i = 0; i < heapSize; i++) {
        cout << heap[i].key << " (" << heap[i].value << ") ";
    }
    cout <<endl;
}

// ------------ Test ------------

int main() {
    MaxHeap<int, string> heap(10);

    // Test insertion
    heap.insert(3, "Three");
    heap.insert(2, "Two");
    heap.insert(15, "Fifteen");
    heap.insert(5, "Five");
    heap.insert(4, "Four");
    heap.insert(45, "Forty-five");

    // Show the heap
    cout << "Current heap: "<<endl;
    heap.show();

    // Test getMax
    cout << "Max value in the heap: " << heap.getMax().key << " (" << heap.getMax().value << ")" << endl;

    // Test deleteMax
    heap.deleteMax();
    cout << "Heap after deleting max: "<<endl;
    heap.show();

    // Test heapSort
    heap.heapSort();
    cout << "Heap after sorting: "<<endl;
    heap.show();

    return 0;
}


#endif
