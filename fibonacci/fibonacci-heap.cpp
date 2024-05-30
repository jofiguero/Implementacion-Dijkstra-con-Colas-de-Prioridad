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
        if (pair->node != other.pair->node) return false;
        return true;
    }

    void addChild(F_Node *child){
        children.push_back(child);
        degree++;
        child->parent = this;
    }

    int countNodes(F_Node *nodo){
        int count = 1; 
        for(F_Node* child : nodo->children){
            count += countNodes(child);
        }
        return count;
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
        int i = 1;
        if (it != rootList.end()) {
            printf("El nodo que vamos a eliminar es el %d y tiene %d nodos en su subarbol\n", (*it)->pair->node,countNodes(*it)-1);
            rootList.erase(it);
        }else{
            printf("Chuta\n");
        }
    }
    void insert(F_Node *nodo){
        if(!raizYaExistente(nodo)){
                if(rootList.size() == 0){
                rootList.push_back(nodo);
                minRoot = nodo;
            }else{
                rootList.push_back(nodo);
                if (nodo->key < minRoot->key){
                    minRoot = nodo;
                }
            }
        }else{
            printf("chuta2, el nodo que la cago es %d\n",nodo->pair->node);
        }
        
    }

    void cutOut(F_Node *nodo){
        insert(nodo);
        F_Node *parent = nodo->parent;
        nodo->parent = nullptr;
        nodo->marked = false;
        parent->eraseChild(nodo);
        if(!parent->marked){
            parent->marked = true;
        }else{
            if(parent->parent != nullptr){
                cutOut(parent);
            }
        }
    }

    void setMinimum(){
        if (rootList.empty()) {
            minRoot = nullptr;
            return;
        }
        double max =  DBL_MAX;
        minRoot = rootList[0];
        for (F_Node *nodo : rootList){
            if (nodo->key < minRoot->key){
                minRoot = nodo;
            }
        }
    }

    void printRooList(){
        printf("[");
        for(F_Node *nodo: rootList){
            printf("%d,",nodo->pair->node);
        }
        printf("]\n");

    }
    bool raizYaExistente(F_Node *elemento) {
        return std::find(rootList.begin(), rootList.end(), elemento) != rootList.end();
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
    F_Node *ExtractMin(){
        //Seleccionamos el antiguo minimo
        F_Node* oldMin = minRoot;
        printf("En este momento la rootList esta asi:");
        printRooList();

        printf("Hay %d nodos en el heap durante de la extraccion 2\n",Nnodes());
        //Agregamos los hijos a la rootList
        for (F_Node* child : oldMin->children) {
            child->parent = nullptr; 
            insert(child);
            oldMin->eraseChild(child);  
        }
        if (rootList.size() == 1){
            eraseRoot(oldMin);
            minRoot = nullptr;
            return oldMin;
        }
        printf("Hay %d nodos en el heap durante de la extraccion 1\n",Nnodes());
        //Eliminamos la raiz de la lista de raices
        eraseRoot(oldMin);
        
        printf("Hay %d nodos en el heap durante de la extraccion 4\n",Nnodes());
        vector<vector<F_Node*>*> mergeList;
        for(F_Node *raiz: rootList){
            while(raiz->degree >= mergeList.size()){
                /*Creamos un nuevo vector de nodos y lo agregamos a mergeList*/
                mergeList.push_back(new vector<F_Node*>);
            }
            /*lo agregamos al vector <grado+1>de la mergeList*/
            mergeList[raiz->degree]->push_back(raiz);
        }
        printf("Hay %d nodos en el heap durante de la extraccion 5\n",Nnodes());
        for(size_t i = 0; i < mergeList.size(); ++i){
            printf("Hay %d nodos en el heap FOR 1\n",Nnodes());
            while(mergeList[i]->size() > 1){
                printf("Hay %d nodos en el heap WHILE 1\n",Nnodes());
                /*tomo las dos primeras raices*/
                F_Node *n1 = (*mergeList[i])[0];
                F_Node *n2 = (*mergeList[i])[1];
                printf("Hay %d nodos en el heap WHILE 2\n",Nnodes());
                printf("Hay %d elementos en mergeList[i] antes de borrar\n",mergeList[i]->size());
                auto it1 = find(mergeList[i]->begin(), mergeList[i]->end(), n1);
                mergeList[i]->erase(it1);
                auto it2 = find(mergeList[i]->begin(), mergeList[i]->end(), n2);
                mergeList[i]->erase(it2);
                printf("Hay %d elementos en mergeList[i] despues de borrar\n",mergeList[i]->size());
                if(raizYaExistente(n1) && raizYaExistente(n2)){
                    if(n1->key < n2->key){
                        printf("n1 tiene %d nodos\n",countNodes(n1));
                        printf("n2 tiene %d nodos\n",countNodes(n2));
                        printf("Hay %d nodos y %d raices en el heap IF 1\n",Nnodes(),rootList.size());
                        printRooList();
                        n1->addChild(n2);
                        printf("Hay %d nodos y %d raices en el heap IF 1.5\n",Nnodes(),rootList.size());
                        eraseRoot(n2);
                        printf("Hay %d nodos en el heap IF 2\n",Nnodes());
                        printRooList();

                        if(mergeList.size()<=n1->degree){
                            /*Agregar un nuevo vector a la mergeList*/
                            mergeList.push_back(new vector<F_Node*>);
                        }
                        printf("Hay %d nodos en el heap IF 4\n",Nnodes());
                        /*Agregar n1 al siguiente vector de la mergeList*/
                        mergeList[n1->degree]->push_back(n1);
                        printf("Hay %d nodos en el heap IF 5\n",Nnodes());
                    }else{
                        printf("n1 tiene %d nodos\n",countNodes(n1));
                        printf("n2 tiene %d nodos\n",countNodes(n2));

                        printf("Hay %d nodos y %d raices en el heap ELSE 1\n",Nnodes(),rootList.size());
                        printRooList();
                        n2->addChild(n1);
                        printf("Hay %d nodos y %d raices en el heap ELSE 2\n",Nnodes(),rootList.size());
                        printf("El nodo que deberia eliminar es el %d\n",n1->pair->node);
                        eraseRoot(n1);
                        printf("Hay %d nodos y %d raices en el heap ELSE 3\n",Nnodes(),rootList.size());
                        printRooList();
                        /*eliminamos tambien n2 y n1 de vec*/

                        printf("Hay %d nodos en el heap ELSE 3\n",Nnodes());
                        if(mergeList.size()<=n2->degree){
                            /*Agregar un nuevo vector a la mergeList*/
                            mergeList.push_back(new vector<F_Node*>);
                        }
                        printf("Hay %d nodos en el heap ELSE 4\n",Nnodes());
                        /*Agregar n2 al siguiente vector de la mergeList*/
                        mergeList[n2->degree]->push_back(n2);
                        printf("Hay %d nodos en el heap ELSE 5\n",Nnodes());
                    }
                }else{
                    if(!raizYaExistente(n1)){
                        auto it1 = find(mergeList[i]->begin(), mergeList[i]->end(), n1);
                        mergeList[i]->erase(it1);
                    }else{
                        auto it2 = find(mergeList[i]->begin(), mergeList[i]->end(), n2);
                        mergeList[i]->erase(it2);
                    }
                }
            }
        }
        printf("Hay %d nodos en el heap durante de la extraccion 6\n",Nnodes());
        setMinimum();
        return oldMin;
    }

};

#endif