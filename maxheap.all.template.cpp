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

    void heapify(int index);

public:
    MaxHeap(int capacity);
    void insert(const Key& key, const Value& value);
    void deleteMax();
    void heapSort();
    void show() const;
};

template<typename Key, typename Value>
MaxHeap<Key, Value>::MaxHeap(int capacity) : capacity(capacity), heapSize(0) {
    heap.resize(capacity);
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::heapify(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heapSize && heap[left].key > heap[largest].key)
        largest = left;

    if (right < heapSize && heap[right].key > heap[largest].key)
        largest = right;

    if (largest != index) {
        swap(heap[index], heap[largest]);
        heapify(largest);
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

    while (currentIndex != 0 && heap[(currentIndex - 1) / 2].key < heap[currentIndex].key) {
        swap(heap[currentIndex], heap[(currentIndex - 1) / 2]);
        currentIndex = (currentIndex - 1) / 2;
    }
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::deleteMax() {
    if (heapSize == 0) {
        // Heap is empty
        return;
    }

    heap[0] = heap[--heapSize];
    heapify(0);
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::heapSort() {
    for (int i = heapSize / 2 - 1; i >= 0; i--)
        heapify(i);

    for (int i = heapSize - 1; i > 0; i--) {
        swap(heap[0], heap[i]);
        heapify(0);
    }
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::show() const {
    for (int i = 0; i < heapSize; i++) {
        cout<<"( " << heap[i].key <<"=>" << heap[i].value << ")\t"<<endl;
    }
    cout << std::endl;
}

int main() {
    // MaxHeap<int, string> heap(10);

    // // Test insertion
    // heap.insert(3, "Three");
    // heap.insert(2, "Two");
    // heap.insert(15, "Fifteen");
    // heap.insert(5, "Five");
    // heap.insert(4, "Four");
    // heap.insert(45, "Forty-five");

    MaxHeap<int, int> heap(10);

    // Test insertion
    heap.insert(3, 3);
    heap.insert(2, 2);
    heap.insert(15, 15);
    heap.insert(5, 5);
    heap.insert(4, 4);
    heap.insert(45, 45);

    // Test d'affichage
    cout<<"Key => Value "<<endl;
    heap.show();

    // Test deleteMax
    heap.deleteMax();

    cout << "after suppression of max: "<<endl;
    cout<<"Key => Value "<<endl;
    heap.show();
    
    cout << endl;

    return 0;
}

#endif


