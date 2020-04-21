#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll INF = 1e12 + 7;

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

vector<int> findNegativeCycle(const vector<Edge>& G, int n) {
    vector<ll> distances(n);
    vector<int> parents(n, -1);

    int lastChangedVertex = -1;
    for (int i = 0; i < n; i++) {
        lastChangedVertex = -1;
        for (const Edge& e : G) {
            if (distances[e.to] > distances[e.from] + e.weight) {
                distances[e.to] = max(distances[e.from] + e.weight, -INF);
                parents[e.to] = e.from;
                lastChangedVertex = e.to;
            }
        }
    }

    if (lastChangedVertex != -1) {
        int v = lastChangedVertex, u;
        for (int i = 0; i < n; i++)
            v = parents[v];

        vector<int> path;
        u = v;
        do {
            path.push_back(u);
            u = parents[u];
        } while (u != v);
        path.push_back(u);
        reverse(path.begin(), path.end());
        return path;
    }
    else {
        return vector<int>(0);
    }

}

int main() {
    ifstream input("negcycle.in");
    int n;
    input >> n;
    vector<Edge> G;
    ll weight;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input >> weight;
            if (weight != 1e9)
                G.emplace_back(i, j, weight);
        }
    }
    input.close();

    vector<int> cycle = findNegativeCycle(G, n);

    ofstream output("negcycle.out");
    if (cycle.empty())
        output << "NO" << endl;
    else {
        output << "YES" << endl;
        output << cycle.size() << endl;
        for (int v : cycle)
            output << v + 1 << " ";
        output << endl;
    }

    output.close();

    return 0;
}