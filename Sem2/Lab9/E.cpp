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

int getStartNode(const vector<list<int>>& G) {
    vector<int> degIn(G.size(), 0);
    for (int v = 0; v < G.size(); v++) {
        for (int u : G[v]) {
            degIn[u]++;
        }
    }

    int vResult = -1;

    for (int v = 0; v < degIn.size(); v++) {
        if (degIn[v] == 0) {
            if (vResult == -1)
                vResult = v;
            else
                return -1;
        }
    }

    return vResult;
}

pair<int, int> getNextNode(const vector<list<int>>& G, const vector<int>& sortedNodes, int v, int pos) {
    if (G[v].empty())
        return make_pair(-1, -1);

    for (int i = pos; i < G.size(); i++) {
        for (int u : G[v]) {
            if (sortedNodes[i] == u)
                return make_pair(u, i);
        }
    }
    return make_pair(-1, -1);
}

bool checkHamiltonianPath(const vector<list<int>>& G) {
    list<int> sortedNodesList = topSort(G);
    vector<int> sortedNodes(sortedNodesList.begin(), sortedNodesList.end());

    int v = getStartNode(G);
    if (v == -1)
        return false;

    int pathLength = 1;
    int pos = 0;
    while (true) {
        pair<int, int> VPos = getNextNode(G, sortedNodes, v, pos);
        v = VPos.first;
        pos = VPos.second;
        if (v == -1)
            break;
        pathLength++;
    }
    return pathLength == G.size();
}

int main() {
    ifstream input("hamiltonian.in");

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

    ofstream output("hamiltonian.out");
    output << (checkHamiltonianPath(G) ? "YES" : "NO") << endl;
    output.close();
}