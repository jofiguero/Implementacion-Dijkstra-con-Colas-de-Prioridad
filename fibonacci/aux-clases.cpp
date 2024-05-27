#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include "fibonacci-heap.cpp"
using namespace std; 

class Neighbor{
    public:
    Node* node;
    double distance;

    Neighbor(Node *node, double distance): node(node), distance(distance) {}
};


class Node{
    public:
    int id;
    vector<Neighbor*> neighbors;
    F_Node *fnode;

    void addNeighbor(Node* nodo, double distance) {
        Neighbor *neighbor = new Neighbor(nodo, distance);
        neighbors.push_back(neighbor);
    }

    Node(int id) : id(id) {}
};

