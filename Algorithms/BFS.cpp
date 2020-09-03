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

// `cost` is a matrix of costs of max size, but `m` and `n` are read to know
// up to what dimensions to read data and traverse it.
int cost[1001][1001];
// `x` is a queue of pairs, containing the coordinates of a node.
queue <pair <int,int> > x;
// `n` is the width of the costs matrix.
int n;
// `m` is the height of the costs matrix.
int m;
// `MAXN` is a very large number, 2^30, 'infinite' for practical purposes.
int MAXN = 1<<30;

void BFS() {

    // While there's something in the queue.
    while (x.size()) {
        // Take the element at the front.
        pair <int, int> y = x.front();
        x.pop();
        int a = y.first;
        int b = y.second;

        // If it's still possible to move left, and the left value is higher
        // than the value in the current node plus 1...
        if (a > 0 && cost[a - 1][b] > cost[a][b] + 1) {
            // Put the value of the current node plus one in the left node.
            cost[a - 1][b] = cost[a][b] + 1;
            // Put the left node in the queue for the BFS.
            x.push(make_pair(y.first - 1, y.second)); 
        }
        // If in this node there was a value lower than the current node,
        // we arrived through a shorter path than through current node.

        // Do the same if it's possible to move upwards.
        if (b > 0 && cost[a][b - 1] > cost[a][b] + 1) {
            cost[a][b - 1] = cost[a][b] + 1;
            x.push(make_pair(y.first, y.second - 1));
        }

        // Do the same if it's possible to move to the right.
        if (a + 1 < n && cost[a + 1][b] > cost[a][b] + 1) {
            cost[a + 1][b] = cost[a][b] + 1;
            x.push(make_pair(y.first + 1, y.second));
        }

        // Do the same if it's possible to move downwards.
        if (b + 1 < m && cost[a][b + 1] > cost[a][b] + 1) {    
            cost[a][b + 1] = cost[a][b] + 1;
            x.push(make_pair(y.first,y.second + 1));
        }
    }

}

int main() {

    // `c` is the number of cases.
    int c;
    // `f` is the value to read.
    int f;
    scanf("%d",&c);

    while (c--) {

        scanf("%d%d",&n,&m);
        getchar();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // Read a value, substract '0' to get actual number.
                f = getchar() - '0';
                // If it's 0 (black)...
                if (!f) {
                    // Put 'infinite' in the costs table.
                    cost[i][j] = MAXN;
                }
                else {
                    // Otherwise, it's a 1 (white) and the cost to it is 0.
                    cost[i][j] = 0;
                    // Put it in the queue for the BFS.
                    x.push(make_pair(i,j));
                }
            }
            getchar();
        }

        BFS();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // Print the costs matrix.
                printf("%d ", cost[i][j]);
            }
            puts("");
        }
    }
    return 0;
}
