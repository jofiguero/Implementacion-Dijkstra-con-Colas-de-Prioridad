#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std; 

class F_Node{
    public:
    int key;
    F_Node *parent;
    vector<F_Node*> children;

    F_Node(int value) : key(value) {}
};

class FibonacciHeap{
    public:
    F_Node *minRoot;
    vector<F_Node*> rootList;

    FibonacciHeap(F_Node *nodo) : minRoot(nodo) {
        rootList.push_back(nodo);
    }

    int getMinKey(){
        return minRoot->key;
    }
};

