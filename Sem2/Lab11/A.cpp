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

ll dijkstra(const vector<list<Edge>>& G, int from, int to) {
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

    return distances[to] != INF ? distances[to] : -1;
}

int main() {
    ifstream input("IOfiles/pathmgep.in");
    int n, s, f;
    input >> n >> s >> f;
    s--, f--;

    vector<list<Edge>> G(n);
    ll weight;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input >> weight;
            if (weight != -1 && i != j)
                G[i].push_back({j, weight});
        }
    }
    input.close();

    ofstream output("IOfiles/pathmgep.out");
    output << dijkstra(G, s, f) << endl;
    output.close();

    return 0;
}