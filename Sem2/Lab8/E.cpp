#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

vector<int> BFSmod(vector<vector<int>>& G, int source) {
    vector<int> d(G.size(), -1);
    d[source] = 0;
    queue<int> q;
    q.push(source);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : G[u]) {
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d;
}

int main() {
    ifstream input("pathbge1.in");
    int n, m;
    input >> n >> m;

    vector<vector<int>> G(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int a, b;
        input >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    input.close();

    vector<int> dest = BFSmod(G, 0);

    ofstream output("pathbge1.out");
    for (int d : dest)
        output << d << " ";
    output << endl;
    output.close();
    return 0;
}