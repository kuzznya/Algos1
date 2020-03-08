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

bool findCycleDFS(const vector<list<int>>& G, vector<color>& colors, list<int>& cycle, int v) {
    colors[v] = grey;
    for (int u : G[v]) {
        if (colors[u] == white) {
            if (findCycleDFS(G, colors, cycle, u)) {
                colors[v] = black;
                cycle.push_back(v);
                return true;
            }
        }
        else if (colors[u] == grey) {
            colors[v] = black;
            cycle.push_back(u);
            cycle.push_back(v);
            return true;
        }
    }
    colors[v] = black;
    cycle.clear();
    return false;
}

list<int> getCycle(const vector<list<int>>& G) {
    vector<color> colors(G.size(), white);
    for (int i = 0; i < G.size(); i++) {
        if (colors[i] == white) {
            list<int> cycle;
            if (findCycleDFS(G, colors, cycle, i)) {
                cycle.reverse();
                while (cycle.front() != cycle.back())
                    cycle.pop_front();
                cycle.pop_back();
                return cycle;
            }
        }
    }
    return list<int>(0);
}

int main() {
    ifstream input("cycle.in");

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

    list<int> cycle = getCycle(G);

    ofstream output("cycle.out");
    if (cycle.empty())
        output << "NO" << endl;
    else {
        output << "YES" << endl;
        for (int v : cycle)
            output << v + 1 << " ";
    }
    output.close();
}