#include <iostream>
#include <string>
#include <ctime>

// Déclarations des structures et fonctions
struct DataType {
    int key;
    int value; // ou tous autres attributs et/ou fonctions membres
    void scan() {
        std::cout << "key: "; std::cin >> key;
        std::cout << "value: "; std::cin >> value; // …
    }
};

typedef int (*Comparator)(const DataType&, const DataType&);

struct Node : public DataType {
    // Inherit DataType's members
};

struct PriorityQueue {
    Node **heapArray;
    int capacity, size;
    Comparator comparator;
};

void heapifyUp(PriorityQueue& queue, int index);
void heapifyDown(PriorityQueue& queue, int index);
Node* createNode(const DataType& data);
PriorityQueue* createQueue(int capacity, Comparator comparator);
PriorityQueue* createQueue(DataType* array, int size, Comparator comparator);
bool isEmpty(const PriorityQueue& queue);
bool insert(PriorityQueue& queue, const DataType& data);
DataType deleteMax(PriorityQueue& queue);
DataType peek(const PriorityQueue& queue);
void change(PriorityQueue& queue, int index, int newKey);
int dataTypeComparator(const DataType& d1, const DataType& d2);
void randomDataArray(DataType *array, int size, int minVal, int maxVal);
void heapSort(DataType* array, int size);
void displayHeap(const PriorityQueue& queue);

void heapifyUp(PriorityQueue& queue, int index) {
    int parent = (index - 1) / 2;
    Node *bottom = queue.heapArray[index];
    while (index > 0 && queue.comparator(*queue.heapArray[parent], *bottom) < 0) {
        queue.heapArray[index] = queue.heapArray[parent]; // move it down
        index = parent;
        parent = (parent - 1) / 2;
    }
    queue.heapArray[index] = bottom;
}

void heapifyDown(PriorityQueue& queue, int index) {
    int largerChild;
    Node *top = queue.heapArray[index];
    while (index < queue.size / 2) {
        int leftChild = 2 * index + 1, rightChild = leftChild + 1;
        if (rightChild < queue.size && queue.comparator(*queue.heapArray[leftChild], *queue.heapArray[rightChild]) < 0) {
            largerChild = rightChild;
        } else {
            largerChild = leftChild;
        }
        if (queue.comparator(*top, *queue.heapArray[largerChild]) >= 0) break;
        queue.heapArray[index] = queue.heapArray[largerChild];
        index = largerChild;
    }
    queue.heapArray[index] = top;
}

Node* createNode(const DataType& data) {
    Node* node = new Node;
    node->key = data.key;
    node->value = data.value;
    return node;
}

PriorityQueue* createQueue(int capacity, Comparator comparator) {
    PriorityQueue* queue = new PriorityQueue;
    queue->capacity = capacity;
    queue->size = 0;
    queue->heapArray = new Node*[capacity];
    queue->comparator = comparator;
    return queue;
}

PriorityQueue* createQueue(DataType* array, int size, Comparator comparator) {
    PriorityQueue* queue = createQueue(2 * size, comparator);
    for (int i = 0; i < size; i++) {
        queue->heapArray[i] = createNode(array[i]);
        queue->size++;
    }
    for (int i = (queue->size - 1) / 2; i >= 0; i--) heapifyDown(*queue, i);
    return queue;
}

bool isEmpty(const PriorityQueue& queue) {
    return queue.size == 0;
}

bool insert(PriorityQueue& queue, const DataType& data) {
    if (queue.size == queue.capacity)
        return false;
    queue.heapArray[queue.size] = createNode(data);
    heapifyUp(queue, queue.size++);
    return true;
}

DataType deleteMax(PriorityQueue& queue) { // pré-condition !isEmpty(queue)
    Node *root = queue.heapArray[0];
    queue.heapArray[0] = queue.heapArray[--queue.size];
    heapifyDown(queue, 0);
    DataType data = *root;
    delete root;
    return data;
}

DataType peek(const PriorityQueue& queue) { // pré-condition : !isEmpty(queue)
    return *queue.heapArray[0];
}

// pré-condition : 0<= index<queue.size
void change(PriorityQueue& queue, int index, int newKey) {
    DataType oldData = *queue.heapArray[index];
    queue.heapArray[index]->key = newKey;
    if (queue.comparator(oldData, *queue.heapArray[index]) < 0)
        heapifyUp(queue, index);
    else
        heapifyDown(queue, index);
}

int dataTypeComparator(const DataType& d1, const DataType& d2) {
    if (d1.key < d2.key) return -1;
    if (d1.key == d2.key) return 0;
    return 1;
}

void randomDataArray(DataType *array, int size, int minVal, int maxVal) {
    srand(time(NULL));
    for (int i = 0; i < size; ++i) {
        array[i] = { (rand() % (maxVal - minVal + 1)) + minVal, i + 1 };
    }
}

void heapSort(DataType* array, int size) {
    PriorityQueue* queue = createQueue(array, size, dataTypeComparator);
    std::cout << "Array to heap:\n"; displayHeap(*queue);
    for (int i = size - 1; i >= 0; i--) array[i] = deleteMax(*queue);
    delete[] queue->heapArray;
    delete queue;
}

void displayHeap(const PriorityQueue& queue) {
    std::cout << "\n..............................................................\n\n\n" << "heapArray:\n" << "\tkey values: ";
    for (int i = 0; i < queue.size; i++) std::cout << queue.heapArray[i]->key << ", ";
    std::cout << std::endl << "\tsize: " << queue.size << ",\n\tcapacity: " << queue.capacity << std::endl;
    int nBlanks = 32, itemsPerRow = 1, column = 0, j = 0;
    std::cout << "\n..............................................................\n\n" << "heapArray as a complete binary tree:\n\n";
    while (j < queue.size) {
        if (column == 0) for (int k = 0; k < nBlanks; k++) std::cout << " ";
        std::cout << queue.heapArray[j]->key;
        if (++j == queue.size) break;
        if (++column == itemsPerRow) {
            nBlanks /= 2;
            itemsPerRow *= 2;
            column = 0;
            std::cout << std::endl << std::endl << std::endl;
        } else {
            for (int k = 0; k < nBlanks * 2 - 2; k++) std::cout << " ";
        }
    }
    std::cout << "\n\n..............................................................\n\n";
}

int main() {
    PriorityQueue *theQueue = createQueue(31, dataTypeComparator); // make a Heap; max size 31
    insert(*theQueue, { 70, 1 });
    insert(*theQueue, { 40, 2 });
    insert(*theQueue, { 50, 3 });
    insert(*theQueue, { 20, 4 });
    insert(*theQueue, { 60, 5 });
    insert(*theQueue, { 100, 6 });
    insert(*theQueue, { 80, 7 });
    insert(*theQueue, { 30, 8 });
    insert(*theQueue, { 10, 9 });
    insert(*theQueue, { 90, 10 });

    while (true) {
        std::cout << "\nEnter first letter of (s)how, (i)nsert, (r)emove, (p)eek, (c)hange, s(o)rt, (q)uit: ";
        char choice; std::cin >> choice;
        switch (choice) {
            case 's':
                displayHeap(*theQueue);
                break;
            case 'i': {
                DataType data;
                std::cout << "Enter the data to insert: "; data.scan();
                if (!insert(*theQueue, data)) std::cout << "Can't insert; heap full" << std::endl;
                break;
            }
            case 'r':
                if (!isEmpty(*theQueue)) std::cout << "Max key item(" << deleteMax(*theQueue).key << ") is removed\n";
                else std::cout << "Can't remove; queue empty\n";
                break;
            case 'p':
                if (!isEmpty(*theQueue)) std::cout << "Max key: " << peek(*theQueue).key << std::endl;
                else std::cout << "Can't peek; queue empty\n";
                break;
            case 'c': {
                int index, newKey;
                std::cout << "Enter current index of item: "; std::cin >> index;
                if (index >= 0 && index < theQueue->size) {
                    std::cout << "Enter new key: "; std::cin >> newKey;
                    change(*theQueue, index, newKey);
                } else {
                    std::cout << "Invalid index" << std::endl;
                }
                break;
            }
            case 'o': {
                int size;
                std::cout << "Sorting - Array size: "; std::cin >> size;
                DataType *array = new DataType[size];
                randomDataArray(array, size, 1, 20);
                std::cout << "Array before sorting:\n";
                for (int i = 0; i < size; i++) std::cout << array[i].key << ", ";
                std::cout << std::endl;
                heapSort(array, size);
                std::cout << "Array sorted:\n";
                for (int i = 0; i < size; i++) std::cout << array[i].key << ", ";
                std::cout << std::endl;
                delete[] array;
                break;
            }
            case 'q':
                delete[] theQueue->heapArray;
                delete theQueue;
                std::quick_exit(0);
            default:
                std::cout << "Invalid entry" << std::endl;
        }
    }
}