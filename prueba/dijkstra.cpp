#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <cfloat>
#include "fibonacci-heap.cpp"
#include "aux-clases.cpp"

Retorno* Dijkstra(int raiz, double **edges, int N) {
    double *distancias = new double[N];
    int *previos = new int[N];

    FibonacciHeap heap;
    F_Node *punteros[N];

    distancias[raiz] = 0;
    previos[raiz] = -1;
    F_Node* n1 = new F_Node(0, raiz);
    punteros[raiz] = n1;
    heap.insert(n1);

    for (int v = 0; v < N; v++) {
        if (v != raiz) {
            distancias[v] = DBL_MAX;
            previos[v] = -1;
            F_Node* n = new F_Node(DBL_MAX, v);
            heap.insert(n);
            punteros[v] = n;
        }
    }

    while (!heap.isEmpty()) {
        F_Node *minimo = heap.ExtractMin();
        int nodo = minimo->pair->node;
        printf("El nodo que estoy mirando es %d\n", nodo);

        for (int v = 0; v < N; v++) {
            if (edges[nodo][v] != 0) {
                double peso = edges[nodo][v];
                printf("Tiene de vecino a %d con peso %f\n", v, peso);

                if (distancias[nodo] != DBL_MAX && distancias[v] > distancias[nodo] + peso) {
                    distancias[v] = distancias[nodo] + peso;
                    previos[v] = nodo;
                    heap.DecreaseKey(punteros[v], distancias[v]);
                    printf("Actualizando distancia de %d a %f y previo a %d\n", v, distancias[v], nodo);
                }
            }
        }
        
        printf("Distancias actuales:\n");
        for (int i = 0; i < N; i++) {
            printf("Distancia al nodo %d: %f\n", i, distancias[i]);
        }
        printf("Previos actuales:\n");
        for (int i = 0; i < N; i++) {
            printf("Nodo previo a %d: %d\n", i, previos[i]);
        }
    }  

    Retorno *ret = new Retorno(distancias, previos);
    return ret;
}
