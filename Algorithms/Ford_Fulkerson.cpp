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
int previous[MAXN];

int pump(long long extra, char b) {

    int u = (int)b;

    while(previous[u] != -1) {
        // From a parent to a corresponding child, update the flow
        // by substracting the minimum value found in the whole path
        // from the original point to the target point, because now
        // the flow will be limited by this value.
        c[previous[u]][u] -= extra;
        // In the opposite direction, this flow is considered positive.
        c[u][previous[u]] += extra;
        // Keep updating `u` as if iterating a linked list.
        u = previous[u];
    }

    // Return the minimum capacity again to accumulate it in the total flow.
    return extra;

}

long long createExtra(char b) {

    // Initialize the extra flow as an 'infinite' or very large number.
    long long extra = 1<<30; //se inicializa extra como un numero muy grande, o 2^30
    int u = (int)b;
    // While we haven't reached the root node...
    while(previous[u] != -1) {
        // We are looking for the min capacity of any edge/path/pipe in the way.
        extra = min(extra, c[previous[u]][u]);
        // Keep updating `u` as if iterating a linked list.
        u = previous[u];
    }
    // Return the minimum capacity.
    return extra;

}

bool searchPath(char a, char b) {

    int s = (int)a;
    int t = (int)b;
    // Initialize with 0s the visited array.
    memset(visited,0,sizeof(visited));
    // Initialize with 0s the previous array.
    memset(previous,0,sizeof(previous));

    // Create a queue `q`
    queue <int> q;
    // Label the starting node `s` as visited.
    visited[s] = true;
    // Indicate that the parent of `s` is -1, a value that no other
    // end of a pipe/node can have.
    previous[s] = -1;
    // Put this first end of a pipe in the queue.
    q.push(s);

    // Iterate while there's something in the queue.
    while(q.size()) {
        // Take the value at the front of the queue and then remove it.
        long long u = q.front();
        q.pop();

        // Return true if this end is the end we were looking for,
        // indicating that a path could be found to `t`.
        if(u == t) {
            return true;
        }

        // Otherwise, iterate over all the neighbors of `u` in the
        // graph `g` to keep building paths.
        for(long long i = 0; i < g[u].size(); ++i){
            // Get the id/name of each neighbor of `u`...
            long long neighbor = g[u][i];
            
            // Verify both that the neighbor hasn't been visited, and that it
            // still has "capacity" through which flow can go through.
            if(!visited[neighbor] && c[u][neighbor] > 0){
                // Label this new end as visited.
                visited[neighbor] = true;
                // Indicate that the current end is the parent of that end.
                previous[neighbor] = u;
                // Put that end into the queue.
                q.push(neighbor);
            }
        }
    }
    // If at the end of all the paths formed by the ends of the pipes we
    // didn't reach the end we wanted to, then return false, indicating that
    // either it's unreachable or no new paths can be created.
    return false;

}

long long doFordFulkerson() {

    // Variable to accumulate the total flow.
    long long total = 0;
    // While there's still a way to reach 'Z' from 'A'
    while(searchPath('A','Z')) { 
        // `searchPath` is a function that returns if it's possible to go
        // from 'A' to 'Z;, also the path found is stored for next use,
        // connecting the ends storing parents, what allows to reconstruct
        // the path backwards from 'Z' to 'A'.

        // The `createExtra` function finds which is the minimum capacity
        // of any pipe from last node 'Z' to the root node, 'A'. In addition,
        // this minimum capacity is sent to a `pump` function, which is added
        // to the flows of all the pipes in the way to 'Z'. Pump finally returns
        // the same `extra` we provided, which we'll accumulate to find out the
        // total flow of the system.
        total += pump(createExtra('Z'),'Z');
    }
    return total;

}

int main(){

    // `paths` = the number of paths/pipes/edges.
    long long paths;
    // `n1`, `n2` = the ends/nodes of each pipe to read, with a flow.
    char n1, n2;
    long long flow;

    // Read the number of paths/pipes/edges.
    scanf("%lld", &paths);

    for(long long i = 0; i < paths; ++i) {
        // This I/O is a mess because of the provided input file...
        getchar();
        // Read the first character.
        n1 = getchar();
        getchar();
        // Read the second character.
        n2 = getchar();
        getchar();

        // Read the flow between both ends.
        scanf("%lld", &flow);

        // Add the flow from one node to the other.
        // For an undirected graph, keep both lines.
        c[(int)n1][(int)n2] += flow;
        // If it's a directed graph, comment the line below.
        //c[(int)n2][(int)n1] += flow;

        // Add the node as a neighborg in the graph.
        g[(int)n1].push_back((int)n2);
        //g[(int)n2].push_back((int)n1); 
    }

    printf("%lld\n", doFordFulkerson());

    return 0;

}
