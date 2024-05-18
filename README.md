# Priority Queue Implementation in C++

This project implements a priority queue using a heap data structure in C++. The code provides various functionalities such as insertion, deletion, and heap sort. Below is a detailed explanation of the code, including key functions and structures.

## Code Overview

### Data Structures

#### DataType
```cpp
struct DataType {
    int key;
    int value; // other attributes or member functions can be added here
    void scan() {
        std::cout << "key: "; std::cin >> key;
        std::cout << "value: "; std::cin >> value;
    }
};
