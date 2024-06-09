#ifndef FIB_CPP
#define FIB_CPP

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cfloat>
using namespace std; 

/*
Clase f_par
La clase que representa un par, que será posteriormente almacenado en una cola de fibonacci siendo
contenido en un F_Node.
Contiene dos atributos:
1) node: es el nodo del grafo al que pertenece este par.
2) distance: es la distancia a la que se encuentra este nodo de el nodo raiz según las mediciones 
actuales.
*/
class f_Par{
    public:
    int node;
    double distance;

    f_Par(int node, double distance): node(node), distance(distance) {}
};

/*
Clase F_Node
La clase que representa un nodo de la cola de fibonacci.
Contiene 6 atributos:
1) key: es la distancia registrada actualmente entre el nodo al que representa este nodo (que está
en el par almacenado) y el nodo raíz. Además, es representa la prioridad del nodo dentro de la cola
de fibonacci.
2) pair: es un puntero al f_par del nodo.
3) marked: Bool que responde a si a este F_Node se le ha podado un hijo o no.
4) degree: número de hijos del nodo
5) parent: puntero al F_Node padre del nodo
6) children: vector de punteros hacia todos los F_Node's hijos
*/
class F_Node{
    public:
    double key;
    f_Par *pair;
    bool marked;
    int degree;
    F_Node *parent;
    vector<F_Node*> children;

    F_Node(double value,int i) : key(value), degree(0), marked(false), pair(new f_Par(i,value)){}

    /*
    Operador de igualdad, dos F_Nodes son iguales si es que los pares son iguales
    */
    bool operator==(const F_Node& other) const {
        if (pair->node != other.pair->node) return false;
        return true;
    }

    /*
    Agrega al hijo child a la lista de hijos children
    */
    void addChild(F_Node *child){
        children.push_back(child);
        degree++;
        child->parent = this;
    }

    /*
    Cuenta los nodos que hay en el subarbol representado por el nodo actual.
    Cumple funciones de depuración
    */
    int countNodes(F_Node *nodo){
        int count = 1; 
        for(F_Node* child : nodo->children){
            count += countNodes(child);
        }
        return count;
    }
    
    /*
    Elimina un hijo de la lista de hijos del nodo
    */
    void eraseChild(F_Node *child){
        auto it = find(children.begin(), children.end(), child);
        children.erase(it);
        degree--;
        child->parent = nullptr; 
    }
};

/*
Clase FibonacciHeap
El FibonacciHeap es una vector de punteros a F_Nodes que representan la lista de raices de la cola de
fibonacci.
Contiene 2 atributos:
1) minRoot: Puntero a el F_Node con la key mas baja actualmente
2) rootList: Vector de F_Node's que representa la lista de raices de la cola de fibonacci.
*/
class FibonacciHeap{
    public:
    F_Node *minRoot;
    vector<F_Node*> rootList;

    FibonacciHeap(): minRoot(nullptr) {}

    /*
    Obtiene la llave minima actual del heap
    */
    double getMin(){
        return minRoot->key;
    }
    /*
    Retorna verdadero si el heap está vacio, falso si no lo está
    */
    bool isEmpty(){
        if(rootList.size() == 0){
            return true;
        }
        return false;
    }

    /*
    elimina una raíz de la lista de raices del heap
    */
    void eraseRoot(F_Node *nodo){
        auto it = find(rootList.begin(), rootList.end(), nodo);
        int i = 1;
        if (it != rootList.end()) {
            rootList.erase(it);
        }
    }
    /*
    Inserta una raiz a la lista de raices del heap
    */
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
        
    /*
    Poda un nodo de un arbol y lo inserta en la lista de raices del heap
    */
    void cutOut(F_Node *nodo){
        if(nodo->parent == nullptr){
            nodo->marked = false;
        }else{
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

    }
    /*
    Establece el atributo minRoot de entre todas las raices de la rootList
    */

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

    /*
    Imprime la lista de raices
    Cumple propositos de depuración
    */
    void printRooList(){
        printf("[");
        for(F_Node *nodo: rootList){
            printf("%d,",nodo->pair->node);
        }
        printf("]\n");

    }

    /*
    Verifica si la raíz ya existe en la rootList
    */
    bool raizYaExistente(F_Node *elemento) {
        return std::find(rootList.begin(), rootList.end(), elemento) != rootList.end();
    }


    /*
    Decrementa el registro de distancia hacia el nodo raíz y reordena el heap luego de esto
    */
    void DecreaseKey(F_Node *nodo, double newkey){
        nodo->key = newkey;
        nodo->pair->distance = newkey;
        if(nodo->parent != nullptr){
            if(nodo->parent->pair->distance > newkey){
                cutOut(nodo);
            }
        }
    }

    /*
    Cuenta todos los nodos de un arbol de raíz $nodo
    Cumple funciones de depuración
    */
    int countNodes(F_Node *nodo){
        int count = 1; // contar el nodo actual
        for(F_Node* child : nodo->children){
            count += countNodes(child); // contar los nodos en los subárboles
        }
        return count;
    }

    /*
    Cuenta todos los nodos de un heap
    Cumple funciones de depuración
    */
    int Nnodes(){
        int totalNodes = 0;
        for(F_Node *root : rootList){
            totalNodes += countNodes(root);
        }
        return totalNodes;
    }

    /*
    Extrae el nodo con la prioridad minima (el más prioritario) y luego reacomoda toda la estructura
    de manera de reducir la cantidad total de arboles en el heap.
    */
    F_Node *ExtractMin(){
        //Seleccionamos el antiguo minimo
        F_Node* oldMin = minRoot;

        //Agregamos los hijos a la rootList
        for (F_Node* child : oldMin->children) {
            child->parent = nullptr;
            insert(child);
        }
        //oldMin->children.clear();
        if (rootList.size() == 1){
            eraseRoot(oldMin);
            minRoot = nullptr;
            return oldMin;
        }
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
        for(size_t i = 0; i < mergeList.size(); ++i){
            while(mergeList[i]->size() > 1){
                /*tomo las dos primeras raices*/
                F_Node *n1 = (*mergeList[i])[0];
                F_Node *n2 = (*mergeList[i])[1];

                auto it1 = find(mergeList[i]->begin(), mergeList[i]->end(), n1);
                mergeList[i]->erase(it1);
                auto it2 = find(mergeList[i]->begin(), mergeList[i]->end(), n2);
                mergeList[i]->erase(it2);

                if(raizYaExistente(n1) && raizYaExistente(n2)){
                    if(n1->key < n2->key){
                        n1->addChild(n2);

                        if(mergeList.size()<=n1->degree){
                            /*Agregar un nuevo vector a la mergeList*/
                            mergeList.push_back(new vector<F_Node*>);
                        }
                        /*Agregar n1 al siguiente vector de la mergeList*/
                        mergeList[n1->degree]->push_back(n1);
                    }else{
                        n2->addChild(n1);
                        if(mergeList.size()<=n2->degree){
                            /*Agregar un nuevo vector a la mergeList*/
                            mergeList.push_back(new vector<F_Node*>);
                        }
                        /*Agregar n2 al siguiente vector de la mergeList*/
                        mergeList[n2->degree]->push_back(n2);
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
                rootList.clear();
                for(vector<F_Node*> *vec: mergeList){
                    for(F_Node *nodo: *vec){
                        insert(nodo);
                    }
                }
            }
        }
        
        for(vector<F_Node*> *vec: mergeList){
            delete vec;
        }
        
        setMinimum();
        return oldMin;
    }

};

#endif