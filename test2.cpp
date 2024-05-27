#include <stdio.h>
#include <iostream>
#include <vector>

#include "fibonacci-heap.cpp"

using namespace std;

/*Testeando ExtractMin*/
int main(){

    F_Node *n1 = new F_Node(1);
    F_Node *n2 = new F_Node(2);
    F_Node *n3 = new F_Node(3);
    F_Node *n4 = new F_Node(4);
    F_Node *n5 = new F_Node(5);
    F_Node *n6 = new F_Node(6);
    F_Node *n7 = new F_Node(7);
    F_Node *n8 = new F_Node(8);
    F_Node *n9 = new F_Node(9);
    F_Node *n10 = new F_Node(10);
    F_Node *n11 = new F_Node(11);
    F_Node *n12 = new F_Node(12);
    F_Node *n13 = new F_Node(13);
    F_Node *n14 = new F_Node(14);
    F_Node *n15 = new F_Node(15);
    F_Node *n16 = new F_Node(16);
    F_Node *n17 = new F_Node(17);
    F_Node *n18 = new F_Node(18);
    F_Node *n19 = new F_Node(19);


    n4->addChild(n5);
    n5->addChild(n6);

    n7->addChild(n8);

    n9->addChild(n10);
    n9->addChild(n11);
    n9->addChild(n12);
    n11->addChild(n13);
    n11->addChild(n17);
    n13->addChild(n18);
    n13->addChild(n19);

    n14->addChild(n15);
    n14->addChild(n16);

    FibonacciHeap *fh = new FibonacciHeap(n1);
    
    fh->insert(n2);
    fh->insert(n3);
    fh->insert(n4);
    fh->insert(n7);
    fh->insert(n9);
    fh->insert(n14);

    printf("Hay %d raices en rootList\n",fh->rootList.size());
    fh->DecreaseKey(n19,3.5);
    printf("Hay %d raices en rootList\n",fh->rootList.size());
    fh->DecreaseKey(n17,3.4);
    printf("Hay %d raices en rootList\n",fh->rootList.size());
    fh->DecreaseKey(n18,3.3);
    printf("Hay %d raices en rootList\n",fh->rootList.size());


    printf("Llegue al final del programa!!");
    return 0;
}