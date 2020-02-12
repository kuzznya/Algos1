#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void markNodeAndAllNeighbors(vector<vector<int>>& G,
                             int nodeNumber,
                             vector<int>& nodesComponents,
                             int componentNumber) {
    nodesComponents[nodeNumber] = componentNumber;
    for (int i = 0; i < G[nodeNumber].size(); i++) {
        if (nodesComponents[G[nodeNumber][i]] == 0) {
            markNodeAndAllNeighbors(G, G[nodeNumber][i], nodesComponents, componentNumber);
        }
    }
}

int main() {
    ifstream input("components.in");
    int n, m;
    input >> n >> m;


    vector<vector<int>> G(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int a, b;
        input >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    input.close();

    vector<int> nodesComponents(n, 0);
    int componentNumber = 0;
    for (int i = 0; i < n; i++) {
        if (nodesComponents[i] == 0) {
            markNodeAndAllNeighbors(G, i, nodesComponents, ++componentNumber);
        }
    }

    ofstream output("components.out");
    output << componentNumber << endl;
    for (int i = 0; i < n; i++) {
        output << nodesComponents[i] << " ";
    }
    output << endl;
    output.close();

    return 0;
}