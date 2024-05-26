#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
using namespace std; 

class Node{
    public:
    int id;
    vector<Node*> neighbors;

    void addNeighbor(Node* neighbor) {
        neighbors.push_back(neighbor);
    }

    Node(int id) : id(id) {}
};
