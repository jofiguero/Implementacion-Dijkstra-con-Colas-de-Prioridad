#include <stdio.h>
#include <iostream>
#include "h_class.cpp"
using namespace std;

// To heapify a subtree rooted with node i which is
// an index in arr[]. N is size of heap

void heapify(int arr[], int N, int i){
    int min = i; // Initialize minimo as root
    int izq = 2 * i + 1; // left = 2*i + 1
    int der = 2 * i + 2; // right = 2*i + 2

    if (izq < N && arr[izq] > arr[min])
        min = izq;

    if (der < N && arr[der] > arr[min])
        min = der;

    if (min != i) {
        swap(arr[i], arr[min]);
        // Recursively heapify the affected sub-tree
        heapify(arr, N, min);
    }
}
 
// Function to build a Max-Heap from the given array

void buildHeap(int arr[], int N){
    int nodo_interno = (N / 2) - 1;     // indice del ultimo nodo interno
    for (int i = nodo_interno; i >= 0; i--) {
        heapify(arr, N, i);
    }
}