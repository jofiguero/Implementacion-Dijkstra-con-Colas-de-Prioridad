#ifndef CLASES_CPP
#define CLASES_CPP

#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include "fibonacci-heap.cpp"
using namespace std; 

class Retorno{
    public:
    double *Ldistancias;
    int *Lprevios;

    Retorno(double *distancias,int *previos): Ldistancias(distancias), Lprevios(previos){}
};
#endif