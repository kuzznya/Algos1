#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

enum color {
    white,
    grey,
    black
};

bool DFS(const vector<list<int>>& G, vector<color>& colors, list<int>& topSortResult, int v) {
    colors[v] = grey;
    for (int u : G[v]) {
        if (colors[u] == white) {
            if (!DFS(G, colors, topSortResult, u))
                return false;
        }
        else if (colors[u] == grey)
            return false;
    }
    colors[v] = black;
    topSortResult.push_back(v);
    return true;
}

list<int> topSort(const vector<list<int>>& G) {
    list<int> result;
    vector<color> colors(G.size(), white);
    for (int i = 0; i < G.size(); i++) {
        if (colors[i] == white) {
            if (!DFS(G, colors, result, i))
                return list<int>(0);
        }
    }
    result.reverse();
    return result;
}

int main() {
    ifstream input("topsort.in");

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

    list<int> topSortResult = topSort(G);

    ofstream output("topsort.out");
    if (topSortResult.empty())
        output << -1 << endl;
    else {
        for (int v : topSortResult)
            output << v + 1 << " ";
    }
    output.close();
}