#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class Nodo{
    Par *par;
};

class Par{
    public:
    int distancia;
    Nodo nodo;
};

class Heap{
    public:
    vector<Par> h;
    int n;

    //hunde el nodo en la posicion i hasta su nivel correcto
    void hundir(int i){ 
        //mientras tenga hijos
        while(2*i+1 < n){
            int hijo = 2*i+1;   //vemos el hijo izquierdo
            //si tiene hijo derecho y el hijo derecho tiene mejor prioridad que el izquierdo
            if(hijo+1<n && h[hijo+1].distancia < h[hijo].distancia){  
                hijo++; //vemos el hijo derecho
            }
            //si el nodo tiene mejor o igual prioridad que su hijo
            if(h[i].distancia <= h[hijo].distancia){
                Par temp = h[i];    //los intercambia
                h[i] = h[hijo];
                h[hijo] = temp;
            }
            i=hijo; //ahora el nodo a hundir se encuentra en la posicion de su hijo
        }
    }

    //sube un nodo en la posicion i hasta su nivel correcto
    void subir(int i){
        int padre = (i-1)/2;
        //mientras no se quiera subir la raiz, y el nodo tenga mejor prioridad que su padre
        while(i>=1 && h[i].distancia < h[padre].distancia){
            Par temp = h[i];    //los intercambia
            h[i] = h[padre];
            h[padre] = temp;
            i = padre;          //ahora el nodo está en el lugar de su padre
            padre = (i-1)/2;
        }
    }

    //obtener la raiz del heap(con menor distancia)
    Par getMin(){   
        return h[0];
    }

    //entrega la raiz del heap(con menor distancia)
    Par extractMin(){   
        Par min = h[0];
        h[0] = h[n-1];
        n-=1;
        hundir(0);
        return min;
    }

    //inserta un elemento en el heap
    void insertar(Par p){
        h[n] = p;
        subir(n);
        n++;
    }

};