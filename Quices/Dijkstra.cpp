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

using namespace std;

int MAXN = 1<<30;                                    //MAXN es un numero muy grande, o 'infinito'

struct Nodo{
  int d;                                             //nombre de un nodo 
  int t;                                             //costo para llegar a este nodo, a partir de un padre (que es el numero de la posicion de un arreglo de vectores
                                                     //de nodos llamado graph, con el mayor numero de nodos posibles, aqui se meteran los nodos con los que esta 
                                                     //posicion se relaciona
  bool operator < (const Nodo &that) const {
    return t > that.t;                               //sobrecarga del operador, puesto que una cola de prioridad como la que utilizamos, por default pone el valor
                                                     //'mayor' en la parte de arriba
  }
};

vector < Nodo > graph [100021];                      //un arreglo de vectores de nodos, cada posicion es un nodo base, y lo que contenga el vector en esta posicion
                                                     //son los nodos a los que se puede llegar desde esta posicion, y la distancia para llegar a estos
int costo[100021]; 

int dijkstra(int i, int n, int f){
  priority_queue < Nodo > q;                         //cola de prioridad, con la sobrecarga del operador de menor, se pone el menor encima de la cola
  for(int z=1; z<=n; ++z){
    costo[z] = MAXN;                                 //costo de llegar a todos los nodos es infinito
  }
  costo[i] = 0;                                      //costo del inicial es cero
  Nodo base;                                         //se declara un nodo base
  base.d = i;                                        //este tiene de nombre el del nodo inicial 
  base.t = 0;                                        //y el costo de llegar a este es cero
  q.push(base);                                      //cola de prioridad empezando con el nodo original
  while(!q.empty()){                                 //mientras que la cola de prioridad no este vacia
    base = q.top();                                  //se mira el nodo en la parte de arriba de esta cola
    int destination = base.d;                        //destination es a lo que llega este nodo
    int timeless = base.t;                           //timeless es el tiempo que le cuesta llegar
    q.pop();
    if(timeless <= costo[destination]){              //si el tiempo para llegar a un nodo es menor que el tiempo que el nodo ya tiene
       if(destination == f){                         //y se llego al nodo deseado
          return timeless;                           //de una ves retornar el tiempo
       }
       for(int k=1;k<=graph[destination].size();++k){//para todos los subnodos del nodo actual en la cola de prioridad
          int llega = graph[destination][k-1].d;     //ver a que puede llegar este nodo
          int peso = graph[destination][k-1].t;      //y lo que cuesta llegar a estos nodos
          if(timeless + peso < costo[llega]){        //si el costo de llegar al nodo padre (que es acumulado) mas el costo de avanzar a algun nodo hijo
                                                     //es menor que el costo que tiene ese nodo hijo registrado
               costo[llega] = timeless + peso;       //el nuevo costo de ese subnodo es la suma del padre por el que venimos, mas lo que le cuesta al padre
                                                     //llegar a el hijo
               Nodo nuevo;                           //se crea un nodo nuevo
               nuevo.d = llega;                      //la destinacion es el nombre del subhijo que hallamos arriba
               nuevo.t = costo[llega];               //y el tiempo para llegar a este, es el nuevo tiempo (que es la acumulacion del padre mas lo que le toma
                                                     //llegar al hijo)
               q.push(nuevo);                        //finalmente este nodo se mete a la cola de prioridades
                                                     //de esta manera se meteran muchos nodos, mientras que la distancia de un padre hasta estos mas la distancia
                                                     //acumulada hasta dicho padre sea menor que la distancia que ya tuvieran estos nodos registrada, pero el que
                                                     //mas importa en la siguiente iteracion del algoritmo sera el nodo mas cercano entre todos los ingresados
          }
       }
    }
  }
  return MAXN;                                       //si se vacio la cola de prioridades, y nunca se llego al nodo esperado, es que es inalcanzable, retorna infinito
}

int main(){
    int c,n,m,i,f;
    //c = casos
    //n = numero de ciudades
    //m = numero de autopistas
    //i = ciudad inicial
    //j = ciudad final
    int a,b,t;
    //a = ciudad inicial autopista
    //b = ciudad final autopista
    //t = tiempo entre ambas autopistas
    Nodo nodoy, nodoz;
    scanf("%d",&c);
    while(c--){
        scanf("%d%d%d%d",&n,&m,&i,&f);
        while(m--){
            scanf("%d%d%d",&a,&b,&t);
            nodoz.t = nodoy.t = t;      //tiempo de nodoy a nodoz es el mismo que de nodoz a nodoa
            nodoy.d = a;                //nodoy tiene conexion con a
            nodoz.d = b;                //nodoz tiene conexion con b
                                        //porque es un grafo no dirigido
            graph[a].push_back(nodoz);  //se agregan ambas relaciones
            graph[b].push_back(nodoy);  //en las posiciones correspondientes
        }
         int res = dijkstra(i,n,f);
        if(res == MAXN){                //si lo retornado por el algoritmo es un numero 'infinito'
            printf("NONE\n");           //se imprime que no es posible
        }
        else{
            printf("%d\n",res);         //de otro modo se imprime lo que retorno, o lo que halla en costos[f]
        }
    }
}
