#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

struct Edge {
    int from;
    int to;
    long long cost;
};

class Compare {
public:
    bool operator() (Edge A, Edge B) {
        return A.cost > B.cost;
    }
};

long long getPrimMSTCost(const vector<list<pair<int, long long>>> G) {
    int n = G.size();
    vector<bool> visited(n, false);
    vector<Edge> mstEdges;

    priority_queue<Edge, vector<Edge>, Compare> pq;

    auto addEdges = [&](const int v) {
        visited[v] = true;
        for (pair<int, long long> w : G[v]) {
            if (!visited[w.first])
                pq.push({v, w.first, w.second});
        }
    };

    addEdges(0);

    while(!pq.empty()) {
        Edge e = pq.top();
        pq.pop();
        int w = e.to;

        if (visited[w])
            continue;

        mstEdges.push_back(e);

        addEdges(w);
    }

    long long cost = 0;
    for (Edge e : mstEdges)
        cost += e.cost;

    return cost;
}

int main() {
    ifstream input("spantree3.in");
    int n, m;
    input >> n >> m;
    vector<list<pair<int, long long>>> G(n, list<pair<int, long long>>(0));
    int from, to, cost;
    for (int i = 0; i < m; i++) {
        input >> from >> to >> cost;
        G[--from].push_back(make_pair(--to, cost));
        G[to].push_back(make_pair(from, cost));
    }
    input.close();

    ofstream output("spantree3.out");
    output << getPrimMSTCost(G) << endl;
    output.close();
    return 0;
}