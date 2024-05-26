#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include "aux-clases.cpp"
using namespace std; 

void link(Node *n1, Node *n2){
    n1->addNeighbor(n2);
    n2->addNeighbor(n1);
}