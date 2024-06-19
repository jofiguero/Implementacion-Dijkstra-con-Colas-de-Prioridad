#include <iostream>
#include <stdio.h>
#include <initializer_list>
#include <set>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <random>
#include "fibonacci/dijkstra.cpp"
#include "grafo_maker.cpp"
#include "heap/dijkstra.cpp"

using namespace std;

tuple<double, double> exp(int v, int e){
    matrix M = genera_grafo(pow(2,v), pow(2,e));
    unsigned f_inicio, f_final, h_inicio, h_final;

    f_inicio = clock();
    f_Dijkstra(0,M,pow(2,v));
    f_final = clock();

    h_inicio = clock();
    h_Dijkstra(0,M,pow(2,v));
    h_final = clock();

    double f_tiempo = (double(f_final-f_inicio)/CLOCKS_PER_SEC);
    double h_tiempo = (double(h_final-h_inicio)/CLOCKS_PER_SEC);
    
    return make_tuple(f_tiempo, h_tiempo);
}

void exp_50(int v, int e){
    cout<<"50 experimentos con 2^"<<v<<" nodos y 2^"<<e<<" aristas arroja los tiempos:"<<endl;
    for(int i=0; i<50; i++){
        tuple<double, double> resultado = exp(v,e);
        double f = get<0>(resultado);
        double h = get<1>(resultado);
        cout<<f<<"_"<<h<<" | ";
    }
    cout<<endl;
}

void experimento(){
    for(int v=10; v<=14; v+=2){
        for(int e=16; e<=22; e++){
            if(pow(2,2*v-2)-pow(2,v-1) >= pow(2,e)){
                exp_50(v,e);
            }
        }
    }
}

int main(){
    cout<<"Comienza el experimento para Dijkstra: los pares entregados son de forma (fibonacci _ heap)"<<endl;
    experimento();
}