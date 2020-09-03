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

// `MAXN` is a very large number, 2^30, 'infinite' for practical purposes.
int MAXN = 1<<30;

struct Node {
    // `d` is the "name" of key of a node. 
    int d;
    // `t` is the time/cost to reach this node, starting from a father.
    int t;

    // Overload the comparison operator to be able to compare nodes directly
    // when using a priority queue, but in reverse order so that we get the
    // "bigger" element first.
    bool operator < (const Node &that) const {
        return t > that.t;
    }
};

// An array of vectors of nodes. Each position is a base node, and the
// vector at this position are the nodes that can be reached from this,
// together with the distance required to reach them.
vector < Node > graph [100021];

int cost[100021]; 

int dijkstra(int i, int n, int f) {

    // Priority queue of Node, which has the '<' operator overloaded.
    priority_queue < Node > q;

    // Initialize the cost of reaching all nodes as 'infinite'.
    for(int z = 1; z <= n; ++z) {
      cost[z] = MAXN;
    }

    // But set the cost of reaching the current node as 0.
    cost[i] = 0;
    // Declare the base node.
    Node base;
    // Give it the name and cost of the current node.
    base.d = i;
    base.t = 0;
    // Initialize the priority queue with the current node.
    q.push(base);

    // Loop while the priority queue still has elements in it.
    while(!q.empty()){
        // Look at the node at the top of the priority queue.
        base = q.top();
        int destination = base.d;
        int node_time = base.t;
        // Remove the node from the priority queue.
        q.pop();

        // If the time to reach the node is lower than the currently
        // "known" time (which by default is infinite)...
        if(node_time <= cost[destination]){
            // And we reached the node we were looking for,
            // just return the time it took.
            if(destination == f) {
                return node_time;
            }
            // If the new node (destination) is not the node we were
            // looking for, then start looking amongst its neighbors.
            for(int k = 1; k <= graph[destination].size(); ++k) {
                // Get the "id" of every node that can be reached.
                int id = graph[destination][k-1].d;
                // And get the "weight" it takes to reach this node.
                int weight = graph[destination][k-1].t;
                // If the time up to this node plus the weight it takes
                // to reach the new node is less than the previously known
                // "lowest" time it takes to reach new node, then update
                // the new route we found to it.
                if(node_time + weight < cost[id]) {
                     cost[id] = node_time + weight;       
                     Node newNode;
                     newNode.d = id;
                     newNode.t = cost[id];
                     q.push(newNode);
              }
           }
        }
    }
    // If the priority queue was emptied, and we never found the desired
    // node, then it means it's unreachable, so we have to return an
    // "infinite" distance.
    return MAXN;
}

int main() {

    // `c` = cases.
    // `n` = number of cities.
    // `m` = number of highways.
    // `i` = initial city.
    // `j` = final city.
    int c, n, m, i, f;
    
    int a, b, t;
    // `a` = starting city highway.
    // `b` = ending city highway.
    // `t` = time between both highways.
    Node nodeY, nodeZ;

    // Read the number of cases.
    scanf("%d",&c);

    while(c--){

        // Read the values for cities, highways, initial and final cities.
        scanf("%d%d%d%d",&n, &m, &i, &f);

        while(m--) {
            scanf("%d%d%d", &a, &b, &t);
            nodeZ.t = nodeY.t = t;
            nodeY.d = a;
            nodeZ.d = b;
            // Because this is an undirected graph, create bidirectional
            // relations between cities, and the cost of reaching one from
            // the other should be the same in both directions.
            graph[a].push_back(nodeZ);
            graph[b].push_back(nodeY);
        }

        int res = dijkstra(i, n, f);

        // If the algorithm returned the "infinite" value, it means
        // there's no way from the initial city to reach the final
        // city, so print "NONE". 
        if(res == MAXN) {
            printf("NONE\n");
        }
        else {
            // Print the cost[f] value, or the cost of reaching the final city.
            printf("%d\n",res);
        }
    }

}
