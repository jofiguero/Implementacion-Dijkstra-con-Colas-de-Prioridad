#include <stdio.h>
#include <iostream>
#include "h_class.cpp"
using namespace std;

void imprimir_heap(Heap heap){
    for(int i=0; i<heap.n; i++){
        cout << heap.h[i].distancia << " ";
    }
    cout << endl;
}

void test_heap(){
    Heap *heap = new Heap();

    heap->insertar(Par(4.5,0));
    imprimir_heap(*heap);
    heap->insertar(Par(1.2,1));
    imprimir_heap(*heap);
    heap->insertar(Par(3.0,2));
    imprimir_heap(*heap);
    heap->insertar(Par(1.2,3));
    imprimir_heap(*heap);
    //cout <<"la minima distancia en el heap es "<< heap->getMin().distancia << endl;
    imprimir_heap(*heap);
    //heap->extractMin();
    imprimir_heap(*heap);
    heap->insertar(Par(1.6,4));
    imprimir_heap(*heap);
    heap->insertar(Par(4.7,5));
    imprimir_heap(*heap);
    heap->insertar(Par(3.0,6));
    imprimir_heap(*heap);
    heap->insertar(Par(1.00,7));
    imprimir_heap(*heap);
    //cout <<"la minima distancia en el heap es "<< heap->getMin().distancia << endl;
    imprimir_heap(*heap);
    //heap->extractMin();
    imprimir_heap(*heap);
    //cout <<"la minima distancia en el heap es "<< heap->extractMin().distancia << endl;
    imprimir_heap(*heap);
    //cout <<"la minima distancia en el heap es "<< heap->extractMin().distancia << endl;
    imprimir_heap(*heap);
    cout <<"la minima distancia en el heap es "<< heap->getMin().distancia << endl;
    imprimir_heap(*heap);
    cout << "hacemos heapify"<<endl;
    heap->heapify();
    imprimir_heap(*heap);
    cout <<"la minima distancia en el heap es "<< heap->getMin().distancia << endl;
    imprimir_heap(*heap);
    cout <<"la minima distancia en el heap es "<< heap->extractMin().distancia << endl;
    imprimir_heap(*heap);
    cout <<"la minima distancia en el heap es "<< heap->extractMin().distancia << endl;
    imprimir_heap(*heap);
    cout <<"la minima distancia en el heap es "<< heap->extractMin().distancia << endl;
    imprimir_heap(*heap);
    cout <<"la minima distancia en el heap es "<< heap->extractMin().distancia << endl;
    imprimir_heap(*heap);
    cout <<"la minima distancia en el heap es "<< heap->extractMin().distancia << endl;
    imprimir_heap(*heap);
    cout <<"la minima distancia en el heap es "<< heap->extractMin().distancia << endl;
    imprimir_heap(*heap);
}

int main(){
    test_heap();
    return 0;
}