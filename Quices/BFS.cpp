/*Santiago Zubieta*/
#include <iostream>
#include <numeric>
#include <fstream>
#include <climits>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <deque>
#include <vector>
#include <string>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <iterator>
#include <algorithm>

int cost[1001][1001];                              //cost es una matriz de costos de tamano maximo, pero se lee m y n para saber hasta que punto ingresarle
                                                   //datos y recorrerla
queue <pair <int,int> > x;                         //x es una cola de pairs, conteniendo las dos coordenadas de un nodo
int n;                                             //n es el ancho de la matriz de costos
int m;                                             //m es el alto de la matriz de costos
int MAXN = 1<<30;                                  //MAXN es 'infinito' o 2^30 (un numero muy grande, mayor que el mayor resultado posible)

void BFS(){
    while(x.size()){                               //mientras haya algo en la cola
        pair <int, int> y = x.front();             //se toma el elemento en la parte de arriba
        x.pop();
        int a = y.first;
        int b = y.second;
        if(a>0 && cost[a-1][b]>cost[a][b]+1){      //si aun es posible moverse para la izquierda y ademas el valor que hay en la izquierda es mayor
                                                   //que si se metiera el valor del nodo en el que estamos, mas uno
            cost[a-1][b] = cost[a][b]+1;           //se mete el valor del nodo en el que estamos, mas uno, en el nodo izquierdo
            x.push(make_pair(y.first-1,y.second)); //y se mete el nodo izquierdo a la cola para el BFS.
        }                                          //si en este nodo ya hubiera un valor menor al del nodo en el que estamos, es que a ese nodo ya se
                                                   //llego por un camino mas corto a que si se llegara a el por el nodo actual, y se deja intacto
        if(b>0 && cost[a][b-1]>cost[a][b]+1){      //se repite lo mismo si es posible moverse para arriba
            cost[a][b-1] = cost[a][b]+1;
            x.push(make_pair(y.first,y.second-1));
        }
        if(a+1<n && cost[a+1][b]>cost[a][b]+1){    //se repite lo mismo si es posible moverse para la derecha
            cost[a+1][b] = cost[a][b]+1;
            x.push(make_pair(y.first+1,y.second));
        }
        if(b+1<m && cost[a][b+1]>cost[a][b]+1){    //se repite lo mismo si es posible moverse para abajo
            cost[a][b+1] = cost[a][b]+1;
            x.push(make_pair(y.first,y.second+1));
        }
    }
}

int main(){
    int c;                                         //c es el numero de casos
    int f;                                         //f es el valor para leer
    scanf("%d",&c);
    while(c--){
        scanf("%d%d",&n,&m);
        getchar();
        for(int i=0; i<n; ++i){
            for (int j=0; j<m; ++j){
                f = getchar()-'0';                 //se lee un valor
                if(!f){                            //si es 0 (negro)..
                    cost[i][j] = MAXN;             //se pone 'infinito' en la tabla de costos
                }
                else{                              //de otro modo
                    cost[i][j] = 0;                //es que es 1 (blanco), entonces el costo a un blanco es 0
                    x.push(make_pair(i,j));        //y se mete a una cola para iniciar el BFS
                }
            }
            getchar();
        }
        BFS();                                     //se inicia el BFS
        for(int i=0; i<n; ++i){
            for (int j=0; j<m; ++j){
                printf("%d ", cost[i][j]);         //se imprime la matriz de costos
            }
            puts("");
        }
    }
    return 0;
}


