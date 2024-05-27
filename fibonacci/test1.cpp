#include <stdio.h>
#include <iostream>
#include <vector>

#include "fibonacci-heap.cpp"

using namespace std;

/*Testeando el correcto funcionamiento de addChild, eraseChild, el constructor de F_Node y de 
FibonacciHeap y la funcion getMin*/
//Pasado
int main(){

    F_Node *n1 = new F_Node(3);
    F_Node *n2 = new F_Node(5);
    F_Node *n3 = new F_Node(6);
    F_Node *n4 = new F_Node(7);
    F_Node *n5 = new F_Node(8);

    printf("n1 tiene %d hijos antes\n",n1->children.size());
    n1->addChild(n2);
    n1->addChild(n3);
    n1->addChild(n4);
    n1->addChild(n5);
    printf("n1 tiene %d hijos despues\n",n1->children.size());

    for(F_Node *nodo: n1->children){
        printf("El padre del nodo es n1? %d\n", nodo->parent == n1);
    }

    n1->eraseChild(n4);
    printf("la direccion del padre de n4 es %p\n", n4->parent);

    FibonacciHeap *fh = new FibonacciHeap(n1);

    printf("la llave del nodo minimo es %f\n", fh->getMin());

    return 0;
}

