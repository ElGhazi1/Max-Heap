#include "maxHeap-tests.hpp"


int MaxHeap::parentIndex(int i){
    return (i+1)/2 ;
}

int MaxHeap::leftChildIndex(int i){
    return (2*i+1)/2 ;
}

int MaxHeap::rightChildIndex(int i){
    return (2*i+2)/2 ;
}

