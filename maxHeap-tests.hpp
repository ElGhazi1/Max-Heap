#include <iostream>
#include <vector>

using namespace std;
class MaxHeap {

    private:
        vector<int> heap;


    public:
        MaxHeap();

        int parentIndex(int);
        int leftChildIndex(int);
        int rightChildIndex(int);

        // Heapify Up & Down
        void HeapifyUp();
        void HeapifyDown();
        
        void insert(int);
        int getMax();
        void extractMax();
        bool isImpty();
};