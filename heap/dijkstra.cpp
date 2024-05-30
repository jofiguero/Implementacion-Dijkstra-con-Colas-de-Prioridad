#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <stdio.h>
#include <cfloat>
#include "h_class.cpp"

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
Retorno *Dijkstra(int raiz, double **edges, int N){
    //PASO 1
    int nodes[N];
    for (int i = 0; i<N; i++){
        nodes[i] = i;
    }
    double *distancias = (double*) malloc(N * sizeof(double));
    int *previos = (int*) malloc(N * sizeof(int));

    //PASO 2
    Heap heap; 
    Par *punteros[N];

    //PASO 3
    distancias[raiz] = 0;
    previos[raiz] = -1;
    Par *p1 = new Par(0,raiz);
    punteros[raiz] = p1;
    heap.insertar(p1);

    //PASO 4 DBL_MAX
    for (int v = 0; v < N; v++){
        if(v != raiz){
            /*Se define distancias[v] como infinita*/
            distancias[v] = DBL_MAX;
            /*Se define previos[v] como indefinido*/
            previos[v] = -1;
            /*Creamos el F_Node(infinito,v)*/
            Par *n = new Par(DBL_MAX,v);
            /*Lo agregamos a heap*/
            heap.insertar(n);
            /*Registramos el puntero*/
            punteros[v] = n;
        }
    }
    //PASO 5
    heap.heapify();
    //PASO 6
    while(!heap.isEmpty()){
        printf("\nEl minimo en el nodo es %d\n",heap.getMin().nodo);
        printf("Hay %d elementos en el heap antes del extractMin\n",heap.h.size());
        Par *minimo = heap.extractMin();
        printf("Hay %d elementos en el heap despues del extractMin\n",heap.h.size());
        for(Par *p: heap.h){
            printf("queda el nodo %d\n",p->nodo);
        }
        int nodo = minimo->nodo;
        printf("El nodo que estoy mirando es %d\n",nodo);
        for(int v = 0; v < N; v++){ //Por cada nodo
            if(edges[nodo][v] != 0){  // Si es vecino
                double peso = edges[nodo][v]; //Calculamos su distancia
                printf("Tiene de vecino a %d, que act tiene una distancia de %f\n", v, distancias[v]);
                if(distancias[v] > distancias[nodo]+peso){
                    distancias[v] = distancias[nodo]+peso;
                    printf("Le vamos a colocar como nueva distancia minima: %f\n",distancias[v]);
                    previos[v] = nodo;
                    heap.decreaseKey(punteros[v], distancias[v]);

                    printf("La nueva distancia de %d es %f\n", v, punteros[v]->distancia);
                    
                }
            }
        }
        printf("El que esta al comienzo del heap es ahora %d, cuya distancia es %f\n",heap.h[0]->nodo,heap.h[0]->distancia);
    }  
    Retorno *ret = new Retorno(distancias,previos);
    return ret;
}