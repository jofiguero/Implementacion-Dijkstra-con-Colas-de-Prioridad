#include <stdio.h>
#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <random>
#include "h_class.cpp"
#include "dijkstra.cpp"
using namespace std;

typedef vector<vector<double>> matrix;

int random_int(int min, int max){
   return min + rand() % (max + 1 - min);
}

double random_peso(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);
    double peso = dis(gen);
    if(peso == 0){
        peso = random_peso();
    }
    return peso;
}

//Creamos una función que inicialize la matriz con n nodos.
matrix crear_matriz_ceros(int n){
    matrix M;
    for(int f = 0; f < n; f++){
        vector<double> fila;
        for(int c = 0; c < n; c++){
            fila.push_back(0);
        }
        M.push_back(fila);
    }
    return M;
}

int generar_arbol_cobertor(matrix &M, int v){
    int aristas = 0;
    int f = 1;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    while(aristas < v-1){
        int c = random_int(0,f-1);   // entero entre 0 y v
        double peso = random_peso();
        M[f][c] = peso;
        M[c][f] = peso;
        f++;
        aristas++;
    }

    return aristas;
}


int add_aristas(matrix &M, int v, int e){
    int aristas = 0;
    while(aristas < e-(v-1)){
        int f = random_int(1,v-1);
        int c = random_int(0,f-1);
        if(M[f][c] == 0){
            double peso = random_peso();
            M[f][c] = peso;
            M[c][f] = peso;
            aristas++;
        }  
    }
    return aristas;
}

void imprimirMatriz(matrix M){
   for(int i = 0; i < M.size(); i++){
      for(int j = 0; j < M[i].size(); j++){
         if(M[i][j]!=0){
             cout <<1<< " ";  
         }
         else{
            cout <<0<< " ";  
         }
        //cout<<M[i][j]<<" ";
         
      }
      cout<<endl;
   }
}

matrix genera_grafo(int v, int e){
    matrix M = crear_matriz_ceros(v);
    cout<<"se puede crear la matriz"<<endl;
    generar_arbol_cobertor(M,v);
    add_aristas(M,v,e);
    return M;
}

int main(){
    int v; // Cantidad de nodos del grafo
    int e;
    cout << "Ingrese la cantidad de nodos 2^";
    cin >> v;
    cout << "Ingrese la cantidad de aristas 2^";
    cin >> e;
    matrix M = genera_grafo(pow(2,v),pow(2,e));

    cout<<"SI SE PUDO"<<endl;

    Retorno *ret = Dijkstra(0,M,pow(2,v));

    cout<<"termine"<<endl;

    printf("Distancias:\n");
    for(int i = 0; i<pow(2,v); i++){
        printf("Para llegar a nodo %d, la distancia total es %f,\n",i+1,ret->Ldistancias[i]);
    }
    cout<<"LLegue al final del programa!!"<<endl;

    //imprimirMatriz(M);
}