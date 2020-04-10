#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <limits>

using namespace std;

typedef long long ll;

const ll INF = numeric_limits<ll>::max();

struct Edge {
    int to;
    ll weight;

    Edge() = default;

    Edge(int to, ll weight)
            : to(to)
            , weight(weight) {}

    bool operator < (const Edge& other) const {
        return weight < other.weight;
    }

};

vector<ll> dijkstra(const vector<list<Edge>>& G, int from) {
    int n = G.size();
    vector<ll> distances(n, INF);
    set<pair<ll, int>> queue;

    distances[from] = 0;
    queue.insert({0, from});

    while(!queue.empty()) {
        auto cur = *queue.begin();
        queue.erase(queue.begin());

        for (Edge e : G[cur.second]) {
            if (distances[e.to] > cur.first + e.weight) {
                queue.erase({distances[e.to], e.to});
                queue.insert({cur.first + e.weight, e.to});
                distances[e.to] = cur.first + e.weight;
            }
        }
    }

    return distances;
}

int main() {
    ifstream input("pathbgep.in");
    int n, m;
    input >> n >> m;

    vector<list<Edge>> G(n);
    int from, to;
    ll weight;
    for (int i = 0; i < m; i++) {
        input >> from >> to >> weight;
        from--, to--;
        G[from].push_back({to, weight});
        G[to].push_back({from, weight});
    }
    input.close();

    vector<ll> distances = dijkstra(G, 0);

    ofstream output("pathbgep.out");
    for (ll d : distances) {
        output << d << " ";
    }
    output.close();

    return 0;
}