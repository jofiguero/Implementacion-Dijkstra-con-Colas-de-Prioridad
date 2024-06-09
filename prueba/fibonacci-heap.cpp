#ifndef FIB_CPP
#define FIB_CPP

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cfloat>
using namespace std;

class Par{
    public:
    int node;
    double distance;

    Par(int node, double distance): node(node), distance(distance) {}
};

class F_Node{
    public:
    double key;
    Par *pair;
    bool marked;
    int degree;
    F_Node *parent;
    vector<F_Node*> children;

    F_Node(double value,int i) : key(value), degree(0), marked(false), pair(new Par(i,value)), parent(nullptr) {}

    bool operator==(const F_Node& other) const {
        return key == other.key && pair->node == other.pair->node;
    }

    void addChild(F_Node *child){
        children.push_back(child);
        degree++;
        child->parent = this;
    }
    
    void eraseChild(F_Node *child){
        auto it = find(children.begin(), children.end(), child);
        if (it != children.end()) {
            children.erase(it);
            degree--;
            child->parent = nullptr;
        }
    }
};

class FibonacciHeap{
    public:
    F_Node *minRoot;
    vector<F_Node*> rootList;

    FibonacciHeap() : minRoot(nullptr) {}

    double getMin(){
        return minRoot->key;
    }
    bool isEmpty(){
        return rootList.empty();
    }

    void eraseRoot(F_Node *nodo){
        auto it = find(rootList.begin(), rootList.end(), nodo);
        if (it != rootList.end()) {
            rootList.erase(it);
        }
    }

    void cutOut(F_Node *nodo){
        if(nodo->parent != nullptr) {
            nodo->parent->eraseChild(nodo);
            nodo->parent = nullptr;
        }
        rootList.push_back(nodo);
        nodo->marked = false;
    }

    void setMinimum(){
        minRoot = nullptr;
        double min = DBL_MAX;
        for(F_Node *nodo: rootList){
            if(nodo->key < min){
                min = nodo->key;
                minRoot = nodo;
            }
        }
    }

    void insert(F_Node *nodo){
        rootList.push_back(nodo);
        if (minRoot == nullptr || nodo->key < minRoot->key){
            minRoot = nodo;
        }
    }

    void DecreaseKey(F_Node *nodo, double newkey){
        nodo->key = newkey;
        if(nodo->parent && nodo->parent->key > newkey){
            cutOut(nodo);
            nodo->parent = nullptr;
        }
        if(minRoot == nullptr || newkey < minRoot->key) {
            minRoot = nodo;
        }
    }

    F_Node *ExtractMin(){
        F_Node* oldMin = minRoot;

        if (rootList.size() == 1){
            rootList.clear();
            minRoot = nullptr;
            return oldMin;
        }
        
        for (F_Node* child : oldMin->children) {
            child->parent = nullptr;
            rootList.push_back(child);
        }

        oldMin->children.clear();
        eraseRoot(oldMin);

        vector<vector<F_Node*>*> mergeList;
        for(F_Node *raiz: rootList){
            while(raiz->degree >= mergeList.size()){
                mergeList.push_back(new vector<F_Node*>);
            }
            mergeList[raiz->degree]->push_back(raiz);
        }
        rootList.clear();
        for(vector<F_Node*> *vec: mergeList){
            while(vec->size() > 1){
                F_Node *n1 = (*vec)[0];
                F_Node *n2 = (*vec)[1];
                vec->erase(vec->begin());
                vec->erase(vec->begin());
                if(n1->key < n2->key){
                    n1->addChild(n2);
                    while(n1->degree >= mergeList.size()){
                        mergeList.push_back(new vector<F_Node*>);
                    }
                    mergeList[n1->degree]->push_back(n1);
                } else {
                    n2->addChild(n1);
                    while(n2->degree >= mergeList.size()){
                        mergeList.push_back(new vector<F_Node*>);
                    }
                    mergeList[n2->degree]->push_back(n2);
                }
            }
            if(!vec->empty()){
                rootList.push_back(vec->front());
            }
        }
        setMinimum();
        return oldMin;
    }
};

#endif
