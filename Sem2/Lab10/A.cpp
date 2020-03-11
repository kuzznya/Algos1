#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

vector<int> getDegrees(const vector<list<int>>& G) {
    vector<int> deg(G.size(), 0);
    for (int v = 0; v < G.size(); v++) {
        deg[v] += G[v].size();
        for (int u : G[v]) {
            deg[u]++;
        }
    }
    return deg;
}

int main() {
    ifstream input("input.txt");

    int n, m;
    input >> n >> m;
    vector<list<int>> G(n, list<int>(0));
    int v, u;
    for (int i = 0; i < m; i++) {
        input >> v >> u;
        v--, u--;
        G[v].push_back(u);
    }
    input.close();

    vector<int> degrees = getDegrees(G);

    ofstream output("output.txt");
    for (int deg : degrees)
        output << deg << " ";
    output << endl;
    output.close();
}