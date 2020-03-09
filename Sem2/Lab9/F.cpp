#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

void DFS(const vector<list<int>>& G, vector<int>& winPositions, int v) {
    for (int u : G[v]) {
        if (winPositions[u] == 0)
            DFS(G, winPositions, u);
    }

    if (G[v].empty()) {
        winPositions[v] = -1;
        return;
    }

    winPositions[v] = -1;
    for (int u : G[v]) {
        if (winPositions[u] == -1) {
            winPositions[v] = 1;
            return;
        }
    }
}

bool firstPlayerWin(const vector<list<int>>& G, int start) {
    vector<int> winPositions(G.size(), 0);
    DFS(G, winPositions, start);
    return winPositions[start] == 1;
}

int main() {
    ifstream input("game.in");

    int n, m, s;
    input >> n >> m >> s;
    s--;
    vector<list<int>> G(n, list<int>(0));
    int v, u;
    for (int i = 0; i < m; i++) {
        input >> v >> u;
        v--, u--;
        G[v].push_back(u);
    }
    input.close();

    ofstream output("game.out");
    output << (firstPlayerWin(G, s) ? "First player wins" : "Second player wins") << endl;
    output.close();
}