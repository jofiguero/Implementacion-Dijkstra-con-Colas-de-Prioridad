#include <iostream>
#include <stdio.h>
#include <initializer_list>
#include <set>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <random>
#include "grafo_maker.cpp"


using namespace std;

double exp(int v, int e){
    matrix M = genera_grafo(pow(2,v), pow(2,e));
    unsigned inicio, final;
    inicio = clock();

    f_Retorno *ret = f_Dijkstra(0,M,pow(2,v));

    final = clock();
    free(ret->Ldistancias);
    free(ret->Lprevios);
    delete ret;
    double tiempo = (double(final-inicio)/CLOCKS_PER_SEC);
    return tiempo;
}

void exp_50(int v, int e){
    cout<<"50 experimentos con 2^"<<v<<" nodos y 2^"<<e<<" aristas arroja los tiempos:"<<endl;
    for(int i=0; i<50; i++){
        double t = exp(v,e);
        cout<<t<<" | ";
    }
    cout<<endl;
}

void experimento(){
    for(int v=10; v<=14; v+=2){
        for(int e=16; e<=22; e++){
            if(v*2-2 >= e){
                exp_50(v,e);
            }
        }
    }
}

int main(){
    cout<<"Comienza el experimento para Dijkstra con colas de Fibonacci"<<endl;
    experimento();
}