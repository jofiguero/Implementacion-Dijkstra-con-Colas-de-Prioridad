#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <stdio.h>
#include <cfloat>
#include "fibonacci-heap.cpp"
typedef vector<vector<double>> matrix;
class Retorno{
    public:
    double *Ldistancias;
    int *Lprevios;

    Retorno(double *distancias,int *previos): Ldistancias(distancias), Lprevios(previos){}
};

/*
Algoritmo Dijkstra

Recibe un nodo raiz, un arreglo de nodos, una matriz de distancias entre nodos y la cantidad de nodos
que hay, construye el arbol de caminos mas corto entre el nodo raiz y cualquier nodo del grafo y 
retorna el arreglo de distancias y de previos que lo representa.
*/
Retorno *Dijkstra(int raiz, matrix edges, int N){
    //PASO 1
    int nodes[N];
    for (int i = 0; i<N; i++){
        nodes[i] = i;
    }
    double *distancias = (double*) malloc(N * sizeof(double));
    int *previos = (int*) malloc(N * sizeof(int));

    //PASO 2
    FibonacciHeap heap; 
    F_Node *punteros[N];

    //PASO 3
    distancias[raiz] = 0;
    previos[raiz] = -1;
    F_Node *n1 = new F_Node(0,raiz);
    punteros[raiz] = n1;
    heap.insert(n1);

    //PASO 4 DBL_MAX
    for (int v = 0; v < N; v++){
        if(v != raiz){
            /*Se define distancias[v] como infinita*/
            distancias[v] = DBL_MAX;
            /*Se define previos[v] como indefinido*/
            previos[v] = -1;
            /*Creamos el F_Node(infinito,v)*/
            F_Node *n = new F_Node(DBL_MAX,v);
            /*Lo agregamos a heap*/
            heap.insert(n);
            /*Registramos el puntero*/
            punteros[v] = n;
        }
    }
    //PASO 6
    while(!heap.isEmpty()){
        printf("\nHay %d nodos en el heap antes de la extraccion\n",heap.Nnodes());
        F_Node *minimo = heap.ExtractMin();
        printf("Hay %d nodos en el heap despues de la extraccion\n\n",heap.Nnodes());
        int nodo = minimo->pair->node;

        for(int v = 0; v < N; v++){ //Por cada nodo
            if(edges[nodo][v] != 0){  // Si es vecino
                double peso = edges[nodo][v]; //Calculamos su distancia
                if(distancias[v] > distancias[nodo]+peso){
                    distancias[v] = distancias[nodo]+peso;
                    previos[v] = nodo;
                    heap.DecreaseKey(punteros[v], distancias[v]);
                }
            }
        }
    }  
    Retorno *ret = new Retorno(distancias,previos);
    return ret;
}