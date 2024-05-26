#include <stdio.h>
#include <iostream>
#include <vector>

#include "fibonacci-heap.cpp"

using namespace std;

int main(){

    F_Node *nodo = new F_Node(3);
    FibonacciHeap *fh = new FibonacciHeap(nodo);

    printf("la llave del nodo es %d\n", fh->getMinKey());

    return 0;
}

