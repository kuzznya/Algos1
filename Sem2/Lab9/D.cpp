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

void DFS(const vector<list<int>>& G, vector<color>& colors, list<int>& topSortResult, int v) {
    colors[v] = grey;
    for (int u : G[v]) {
        if (colors[u] == white) {
            DFS(G, colors, topSortResult, u);
        }
    }
    colors[v] = black;
    topSortResult.push_back(v);
}

list<int> topSort(const vector<list<int>>& G) {
    list<int> result;
    vector<color> colors(G.size(), white);
    for (int i = 0; i < G.size(); i++) {
        if (colors[i] == white) {
            DFS(G, colors, result, i);
        }
    }
    result.reverse();
    return result;
}

void markNodesDFS(const vector<list<int>>& G, vector<int>& nodesComponents, int componentNumber, int v) {
    nodesComponents[v] = componentNumber;
    for (int u : G[v]) {
        if (nodesComponents[u] == 0)
            markNodesDFS(G, nodesComponents, componentNumber, u);
    }
}

vector<list<int>> converse(const vector<list<int>>& G) {
    vector<list<int>> GConversed(G.size(), list<int>(0));
    for (int v = 0; v < G.size(); v++) {
        for (int u : G[v]) {
            GConversed[u].push_back(v);
        }
    }
    return GConversed;
}

pair<int, vector<int>> condensate(const vector<list<int>>& G) {
    list<int> sortedNodes = topSort(G);
    if (sortedNodes.empty())
        return make_pair(0, vector<int>(0));

    vector<list<int>> GConversed = converse(G);


    vector<int> nodesComponents(G.size(), 0);
    int componentNumber = 1;
    for (int v : sortedNodes) {
        if (nodesComponents[v] == 0)
            markNodesDFS(GConversed, nodesComponents, componentNumber++, v);
    }
    return make_pair(componentNumber - 1, nodesComponents);
}

int main() {
    ifstream input("cond.in");

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

    pair<int, vector<int>> result = condensate(G);

    ofstream output("cond.out");
    output << result.first << endl;
    for (int v : result.second)
        output << v << " ";
    output.close();
}