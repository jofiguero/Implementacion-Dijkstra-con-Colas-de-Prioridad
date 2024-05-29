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

    F_Node(double value,int i) : key(value), degree(0), marked(false), pair(new Par(i,value)){}

    bool operator==(const F_Node& other) const {
        if (key != other.key) return false;
        return true;
    }

    void addChild(F_Node *child){
        children.push_back(child);
        degree++;
        child->parent = this;
    }
    
    void eraseChild(F_Node *child){
        auto it = find(children.begin(), children.end(), child);
        children.erase(it);
        degree--;
        child->parent = nullptr; 
    }
};

class FibonacciHeap{
    public:
    F_Node *minRoot;
    vector<F_Node*> rootList;

    FibonacciHeap(): minRoot(nullptr) {}

    double getMin(){
        return minRoot->key;
    }
    bool isEmpty(){
        if(rootList.size() == 0){
            return true;
        }
        return false;
    }

    void eraseRoot(F_Node *nodo){
        auto it = find(rootList.begin(), rootList.end(), nodo);
        rootList.erase(it);
    }

    void cutOut(F_Node *nodo){
        rootList.push_back(nodo);
        F_Node *parent = nodo->parent;
        nodo->parent = nullptr;
        nodo->marked = false;
        parent->eraseChild(nodo);
        if(!parent->marked){
            parent->marked = true;
        }else{
            if(nodo->parent != nullptr){
                cutOut(parent);
            }
        }
    }

    void setMinimum(){
        double max =  DBL_MAX;
        for(F_Node *nodo: rootList){
            if(nodo->key<=max){
                max = nodo->key;
                minRoot = nodo;
            }
        }
    }

    void insert(F_Node *nodo){
        if(rootList.size() == 0){
            rootList.push_back(nodo);
            minRoot = nodo;
        }else{
            rootList.push_back(nodo);
            if (nodo->key < minRoot->key){
                minRoot = nodo;
            }
        }
    }

    void DecreaseKey(F_Node *nodo, double newkey){
        nodo->key = newkey;
        nodo->pair->distance = newkey;
        if(nodo->parent != nullptr){
            if(nodo->parent->key > newkey){
                cutOut(nodo);
            }
        }

        setMinimum();
    }
    F_Node *ExtractMin(){
        //Seleccionamos el antiguo minimo
        F_Node* oldMin = minRoot;

        if (rootList.size() == 1){
            eraseRoot(oldMin);
            minRoot = nullptr;
            return oldMin;
        }
        
        //Agregamos sus hijos a la root list
        for (F_Node* child : oldMin->children) {
            child->parent = nullptr; 
            insert(child);  
        }

        //eliminamos los hijos del minimo de su lista de hijos
        oldMin->children.clear();

        //Eliminamos la raiz de la lista de raices
        eraseRoot(oldMin);

        vector<vector<F_Node*>*> mergeList;
        for(F_Node *raiz: rootList){
            while(raiz->degree >= mergeList.size()){
                /*Creamos un nuevo vector de nodos y lo agregamos a mergeList*/
                mergeList.push_back(new vector<F_Node*>);
            }
            /*lo agregamos al vector <grado+1>de la mergeList*/
            mergeList[raiz->degree]->push_back(raiz);
        }
        for(vector<F_Node*> *vec: mergeList){
            while(vec->size() > 1){
                /*tomo las dos primeras raices*/
                F_Node *n1 = (*vec)[0];
                F_Node *n2 = (*vec)[1];
                if(n1->key < n2->key){
                    n1->addChild(n2);
                    eraseRoot(n2);
                    /*eliminamos tambien n2 y n1 de vec*/
                    auto it1 = find(vec->begin(), vec->end(), n1);
                    auto it2 = find(vec->begin(), vec->end(), n2);
                    vec->erase(it1);
                    vec->erase(it2);

                    if(mergeList.size()<=n1->degree){
                        /*Agregar un nuevo vector a la mergeList*/
                        mergeList.push_back(new vector<F_Node*>);
                    }
                    /*Agregar n1 al siguiente vector de la mergeList*/
                    mergeList[n1->degree]->push_back(n1);
                }else{
                    n2->addChild(n1);
                    eraseRoot(n1);
                    /*eliminamos tambien n2 y n1 de vec*/
                    auto it1 = find(vec->begin(), vec->end(), n1);
                    auto it2 = find(vec->begin(), vec->end(), n2);
                    vec->erase(it1);
                    vec->erase(it2);
                    if(mergeList.size()<=n2->degree){
                        /*Agregar un nuevo vector a la mergeList*/
                        mergeList.push_back(new vector<F_Node*>);
                    }
                    /*Agregar n2 al siguiente vector de la mergeList*/
                    mergeList[n2->degree]->push_back(n2);
                }
                
            }
        }
        setMinimum();
        return oldMin;
    }
    int countNodes(F_Node *nodo){
        int count = 1; // contar el nodo actual
        for(F_Node* child : nodo->children){
            count += countNodes(child); // contar los nodos en los subárboles
        }
        return count;
    }

    int Nnodes(){
        int totalNodes = 0;
        for(F_Node *root : rootList){
            totalNodes += countNodes(root);
        }
        return totalNodes;
    }
};

#endif