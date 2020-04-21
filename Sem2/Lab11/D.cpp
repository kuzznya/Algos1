#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <limits>

using namespace std;

typedef long long ll;

const ll INF = 8e18;

struct Edge {
    int from;
    int to;
    ll weight;

    Edge() = default;

    Edge(int from, int to, ll weight)
    : from(from)
    , to(to)
    , weight(weight) {}
};

void DFS(const vector<Edge>& G, vector<bool>& used, int v) {
    used[v] = true;
    for (const Edge& e : G) {
        if (!used[e.to] && e.from == v)
            DFS(G, used, e.to);
    }
}

void markReachable(const vector<Edge>& G, vector<ll>& distances, int v) {
    vector<bool> used(distances.size(), false);
    DFS(G, used, v);
    for (int i = 0; i < distances.size(); i++) {
        if (used[i])
            distances[i] = -INF;
    }
}

vector<ll> findDistancesFord(const vector<Edge>& G, int n, int v) {
    vector<ll> distances(n, INF);
    vector<int> parents(n, -1);
    distances[v] = 0;

    int lastChangedVertex = -1;
    for (int i = 0; i < n; i++) {
        lastChangedVertex = -1;
        for (const Edge& e : G) {
            if (distances[e.from] < INF && distances[e.to] > distances[e.from] + e.weight) {
                distances[e.to] = max(distances[e.from] + e.weight, -INF);
                parents[e.to] = e.from;
                lastChangedVertex = e.to;
            }
        }
    }

    if (lastChangedVertex != -1) {
        for (int i = 0; i < n; i++)
            lastChangedVertex = parents[lastChangedVertex];
        markReachable(G, distances, lastChangedVertex);
    }

    return distances;
}

int main() {
    ifstream input("path.in");
    int n, m, s;
    input >> n >> m >> s;
    s--;

    vector<Edge> G(m);

    int from, to;
    ll weight;
    for (int i = 0; i < m; i++) {
        input >> from >> to >> weight;
        from--, to--;
        G[i] = {from, to, weight};
    }
    input.close();

    vector<ll> distances = findDistancesFord(G, n, s);

    ofstream output ("path.out");
    for (ll d : distances) {
        switch (d) {
            case INF:
                output << "*";
                break;
            case -INF:
                output << "-";
                break;
            default:
                output << d;
        }
        output << endl;
    }

    output.close();

    return 0;
}