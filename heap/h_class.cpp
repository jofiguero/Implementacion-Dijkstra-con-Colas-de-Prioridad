#ifndef HEAP_F_CPP
#define HEAP_F_CPP

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class h_Par{
    public:
    double distancia;
    int nodo;
    int pos;    //indice dentro del heap

    h_Par(double d, int nodo): distancia(d), nodo(nodo), pos(nodo) {}
};

class Heap{
    public:
    vector<h_Par*> h;
    int n;

    Heap (): n(0){}


    bool isEmpty(){
        if (h.size() == 0){
            return true;
        }
        return false;
    }
    //hunde el nodo en la posicion i hasta su nivel correcto
    void hundir(int i){ 
        //mientras tenga hijos
        while(2*i+1 < n){
            int hijo = 2*i+1;   //vemos el hijo izquierdo
            //si tiene hijo derecho y el hijo derecho tiene mejor prioridad que el izquierdo
            if(hijo+1<n && h[hijo+1]->distancia < h[hijo]->distancia){  
                hijo++; //vemos el hijo derecho
            }
            //si el nodo tiene mejor o igual prioridad que su hijo
            if(h[i]->distancia <= h[hijo]->distancia){
                break;
            }
            h_Par *temp = h[i];    //los intercambia
            h[i] = h[hijo];
            h[hijo] = temp;

            h[i]->pos = i;       //actualiza las posiciones de los pares
            h[hijo]->pos = hijo;

            i=hijo; //ahora el nodo a hundir se encuentra en la posicion de su hijo
        }
    }

    //sube un nodo en la posicion i hasta su nivel correcto
    void subir(int i){
        int padre = (i-1)/2;
        //mientras no se quiera subir la raiz, y el nodo tenga mejor prioridad que su padre
        while(i>=1 && h[i]->distancia < h[padre]->distancia){
            h_Par *temp = h[i];    //los intercambia
            h[i] = h[padre];
            h[padre] = temp;

            h[i]->pos = i;       //actualiza las posiciones de los pares
            h[padre]->pos = padre;

            i = padre;          //ahora el nodo está en el lugar de su padre
            padre = (i-1)/2;
        }
    }

    //obtener la raiz del heap(con menor distancia)
    h_Par getMin(){   
        return *h[0];
    }

    //entrega la raiz del heap(con menor distancia)
    h_Par *extractMin(){   
        h_Par *min = h[0];
        h[0] = h[n-1];
        h[0]->pos = 0;
        h.pop_back();
        n-=1;
        hundir(0);
        return min;
    }

    //inserta un elemento en el heap, siguiendo las reglas del heap
    void insertarHeap(h_Par *p){
        p->pos = n;
        h.push_back(p);
        n++;
        subir(n-1);
    }

    //inserta un elemento en el heap, sin seguir las reglas del heap
    void insertar(h_Par *p){
        p->pos = n;
        h.push_back(p);
        n++;
    }

    void decreaseKey(h_Par *p, double d){
        //p->distancia = d;
        h[p->pos]->distancia = d;
        subir(p->pos);
    }

    void heapify(){
        int nodo_interno = (n / 2) - 1;     // indice del ultimo nodo interno
        for (int i = nodo_interno; i >= 0; i--) {
            hundir(i);
        }
    }
};

#endif