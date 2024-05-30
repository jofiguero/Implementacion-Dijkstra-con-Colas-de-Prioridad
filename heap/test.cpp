#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <stdio.h>
#include <cfloat>
#include "dijkstra.cpp"

void imprimirMatriz(double **matriz, int N) {
    std::cout << "[\n";
    for (int i = 0; i < N; ++i) {
        std::cout << "[";
        for (int j = 0; j < N; ++j) {
            std::cout << matriz[i][j];
            if (j < N - 1) std::cout << ",";
        }
        std::cout << "]\n";
        if (i < N - 1) std::cout << ",";
    }
    std::cout << "]" << std::endl;
}

int main(){
    int rows = 7; 
    int cols = 7;    

    double** matriz = (double**)malloc(rows * sizeof(double*));  
    for(int i = 0; i < rows; ++i) {
        matriz[i] = (double*)malloc(cols * sizeof(double));
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matriz[i][j] =0;  // Asignar valores a la matriz
        }
    }

    matriz[0][1] = matriz[1][0] = 3;
    matriz[0][2] = matriz[2][0] = 2;
    matriz[1][2] = matriz[2][1] = 2;
    matriz[1][3] = matriz[3][1] = 1;
    matriz[1][4] = matriz[4][1] = 4;
    matriz[2][3] = matriz[3][2] = 3;
    matriz[2][5] = matriz[5][2] = 6;
    matriz[2][6] = matriz[6][2] = 5;
    matriz[3][5] = matriz[5][3] = 2;
    matriz[4][5] = matriz[5][4] = 1;
    matriz[5][6] = matriz[6][5] = 2;

    imprimirMatriz(matriz,7);

    Retorno * ret = Dijkstra(6,matriz,7);

    printf("Llegue al final del programa!!\n");
    printf("Previos:\n");
    for(int i = 0; i<7; i++){
        printf("Para llegar a nodo %d, el previo es %d,\n",i+1,ret->Lprevios[i]+1);
    }
    printf("Distancias:\n");
    for(int i = 0; i<7; i++){
        printf("Para llegar a nodo %d, la distancia total es %f,\n",i+1,ret->Ldistancias[i]);
    }

    return 0;
}