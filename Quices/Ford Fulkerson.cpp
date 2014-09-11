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

const int MAXN = 1000;
vector < int > g[MAXN];
long long c[MAXN][MAXN];

bool visited[MAXN];
int anterior[MAXN];

int bombear(long long extra, char b){
    int u = (int)b;
    while(anterior[u] != -1){
        c[anterior[u]][u] -= extra; //de un 'padre' a su extremo o hijo correspondiente, se actualiza el flujo al restarle
                                    //el valor minimo hallado en todo el camino del extremo original al extremo destino
                                    //puesto que ahora va a caber menos flujo por este tubo
        c[u][anterior[u]] += extra; //en sentido contrario, se indica este flujo como positivo
        u = anterior[u];
    }
    return extra; //se retorna la capacidad minima otra vez para acumularla en el flujo total
}

long long exxtra(char b){
    long long extra = 1<<30; //se inicializa extra como un numero muy grande, o 2^30
    int u = (int)b;
    while(anterior[u] != -1){
         extra = min(extra, c[anterior[u]][u]); //se esta buscando cual es la capacidad minima de una de
                                               //las aristas en el recorrido
         u = anterior[u];
    }
    return extra;  //se retorna esta capacidad minima
}

bool buscarCamino(char a, char b){
    int s = (int)a;
    int t = (int)b;
    memset(visited,0,sizeof(visited));   //inicializa en ceros el arreglo de visitados
    memset(anterior,0,sizeof(anterior)); //inicializa en ceros el arreglo de anteriores
    queue <int> q;     //declara una cola q
    visited[s] = true; //marca el original (A) como visitado
    anterior[s] = -1;  //y dice que el padre o extremo anterior a A es -1, un valor que
                       //ningun otro extremo puede tener, siendo la limitacion extremos
                       //de tubos llamados entre a-z y A-Z
    q.push(s);         //esto es como un recorrido por amplitud, mete el primer extremo a la cola
    while(q.size()){   //mientras haya algo en la cola
        long long u = q.front(); //asignar el valor del frente de la cola a una variable u
        q.pop();       //y eliminar este elemento de la cola
                       //de aqui en adelante llamaremos a lo que sacamos de la cola como el extremo original
        if(u==t)return true; //si u es el nodo destino, de una vez retornar true, indicando que se
                             //pudo armar un camino
        for(long long i=0; i < g[u].size(); ++i){
            //para todos los vecinos de u, tomaremos sus nombres
            long long vecino = g[u][i];
            //y verificaremos que estos extremos no hayan sido visitados, y que ademas aun tengan espacio
            //por donde pueda fluir algo, un valor dado por que la capacidad actual de la arista sea mayor a 0
            if(!visited[vecino] && c[u][vecino]>0){
                visited[vecino] = true; //si un extremo vecino al original cumple esta condicion, se marca como visitado
                anterior[vecino] = u;   //se indica que el original es el padre de este extremo
                q.push(vecino);         //y este nuevo extremo se mete a la cola
            }
        }
    }
    return false; //al terminar de viajar por las aristas formadas por los extremos vecinos entre si, no se hallo el nodo
    //que se deseaba hallar, se retorna false, indicando que ya no es posible armar nuevos caminos
}

long long FordFulkerson(){
    long long total = 0;   //variable total que tendra el flujo total
    while(buscarCamino('A','Z')){ 
        //buscarCamino es una funcion que revisa si es posible llegar de A a Z,
        //ademas el camino encontrado lo guarda para un posterior uso, conectando
        //los extremos al guardar quien es su padre, lo que permite reconstruir el
        //camino desde Z hasta A.
        total += bombear(exxtra('Z'),'Z');
        //la funcion exxtra halla cual es la capacidad minima de algun tubo desde Z
        //hasta el ultimo padre posible, osea A. Ademas, esta capacidad minima, la 
        //manda a una funcion bombear, que le suma a los flujos de todos los tubos
        //del recorrido esta cantidad.
        //bombear retorna finalmente el extra originalmente hallado, el cual acumularemos
        //para hallar el flujo total del sistema
    }
    return total;
}

int main(){
    long long aris,flow; //aris es numero de aristas
                         //flow es un contenedor para un flujo que se lee
    char n1,n2;             //n1 y n2 seran los dos extremos del tubo que se leeran
                         //a los cuales les corresponde una capacidad de flujo
    scanf("%lld",&aris); //se lee la cantidad de aristas
    for(long long i=0; i<aris; ++i){
        getchar();
        n1 = getchar(); //se lee el primer caracter
        getchar();
        n2 = getchar(); //se lee el segundo caracter
        getchar();
        scanf("%lld",&flow);
        c[(int)n1][(int)n2] += flow;    //agrega la capacidad de n1 a n2
        //c[(int)n2][(int)n1] += flow;  //agrega la capacidad de n2 a n1
                                        //posiblemente para un grafo direccionado
                                        //el unico cambio a realizar seria eliminar
                                        //la segunda linea

        g[(int)n1].push_back((int)n2);   //se agrega n2 como vecino de n1 en el grafo
        //g[(int)n2].push_back((int)n1); //se agrega n1 como vecino de n2 en el grafo
                                         //esta linea tambien se eliminaria para direccionado
    }
    printf("%lld\n",FordFulkerson());
    return 0;
}