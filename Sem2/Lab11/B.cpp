#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

typedef long long ll;

const ll INF = numeric_limits<ll>::max();

vector<vector<ll>> floyd(vector<vector<ll>> d) {
    int n = d.size();

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    return d;
}

int main() {
    ifstream input("pathsg.in");
    int n, m;
    input >> n >> m;

    vector<vector<ll>> G(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++)
        G[i][i] = 0;

    int from, to;
    ll weight;
    for (int i = 0; i < m; i++) {
        input >> from >> to >> weight;
        from--, to--;
        G[from][to] = weight;
    }

    vector<vector<ll>> d = floyd(G);

    ofstream output("pathsg.out");
    for (vector<ll>& line : d) {
        for (ll val : line) {
            output << val << " ";
        }
        output << endl;
    }
    output.close();
}
