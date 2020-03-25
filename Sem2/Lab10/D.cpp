#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct edge {
    int to;
    long long weight;
};

enum color {
    white,
    grey,
    black
};

void DFS(const vector<list<edge>>& G, vector<color>& colors, list<int>& topSortResult, int v) {
    colors[v] = grey;
    for (edge e : G[v]) {
        if (colors[e.to] == white) {
            DFS(G, colors, topSortResult, e.to);
        }
    }
    colors[v] = black;
    topSortResult.push_back(v);
}

list<int> topSort(const vector<list<edge>>& G) {
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

void markNodesDFS(const vector<list<edge>>& G, vector<int>& nodesComponents, int componentNumber, int v) {
    nodesComponents[v] = componentNumber;
    for (edge e : G[v]) {
        if (nodesComponents[e.to] == -1)
            markNodesDFS(G, nodesComponents, componentNumber, e.to);
    }
}

vector<list<edge>> converse(const vector<list<edge>>& G) {
    vector<list<edge>> GConversed(G.size(), list<edge>(0));
    for (int v = 0; v < G.size(); v++) {
        for (edge e : G[v]) {
            GConversed[e.to].push_back({v, 0});
        }
    }
    return GConversed;
}

int condensate(const vector<list<edge>>& G, vector<int>& nodesComponents) {
    list<int> sortedNodes = topSort(G);
    if (sortedNodes.empty())
        return 0;

    vector<list<edge>> GConversed = converse(G);

    int componentNumber = 0;
    for (int v : sortedNodes) {
        if (nodesComponents[v] == -1)
            markNodesDFS(GConversed, nodesComponents, componentNumber++, v);
    }
    return componentNumber;
}

long long findMST(const vector<list<edge>>& G, int n, int root) {
    long long result = 0;
    vector<long long> minEdge(n, INF);
    for (int i = 0; i < n; i++) {
        for (edge e : G[i])
            minEdge[e.to] = min(e.weight, minEdge[e.to]);
    }
    for (int v = 0; v < n; v++) {
        if (v != root)
            result += minEdge[v];
    }

    vector<list<edge>> zeroG(n);

    for (int v = 0; v < n; v++) {
        for (edge e : G[v]) {
            if (e.weight == minEdge[e.to]) {
                zeroG[v].push_back({e.to, 0});
            }
        }
    }

    vector<int> testNodesComponents(n, -1);
    markNodesDFS(zeroG, testNodesComponents, 1, root);
    bool allNodesMarked = true;
    for (int component : testNodesComponents) {
        if (component != 1) {
            allNodesMarked = false;
            break;
        }
    }
    if (allNodesMarked)
        return result;

    vector<int> nodesComponents(n, -1);
    int componentCount = condensate(zeroG, nodesComponents);

    vector<list<edge>> newG(componentCount);
    for (int v = 0; v < n; v++) {
        for (edge e : G[v]) {
            if (nodesComponents[v] != nodesComponents[e.to])
                newG[nodesComponents[v]].push_back({nodesComponents[e.to], e.weight - minEdge[e.to]});
        }
    }
    result += findMST(newG, componentCount, nodesComponents[root]);
    return result;
}

int main() {
    ifstream input("chinese.in");
    int n, m;
    input >> n >> m;
    vector<list<edge>> G(n);
    int from, to, weight;
    for (int i = 0; i < m; i++) {
        input >> from >> to >> weight;
        G[--from].push_back({--to, weight});
    }
    input.close();

    ofstream output("chinese.out");

    vector<int> testNodesComponents(n, -1);
    markNodesDFS(G, testNodesComponents, 1, 0);
    bool allNodesMarked = true;
    for (int component : testNodesComponents) {
        if (component != 1) {
            allNodesMarked = false;
            break;
        }
    }
    if (allNodesMarked) {
        output << "YES" << endl;
        output << findMST(G, n, 0);
    } else
        output << "NO" << endl;

    output.close();
    return 0;
}