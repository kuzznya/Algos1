#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

int INF = numeric_limits<int>::max();

struct Edge {
    int index;
    int from;
    int to;
    int flow;
    int maxFlow;
};

vector<vector<int>> G;
vector<Edge> edges;
vector<int> distances;
vector<int> cur;

bool bfs(int s, int t) {
    distances.assign(distances.size(), INF);
    queue<int> q;
    q.push(s);
    distances[s] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int e : G[v]) {
            if (distances[edges[e].to] == INF && edges[e].flow < edges[e].maxFlow) {
                q.push(edges[e].to);
                distances[edges[e].to] = distances[v] + 1;
            }
        }
    }
    return distances[t] != INF;
}

int dfs(int t, int flow, int v) {
    if (flow == 0)
        return 0;
    if (v == t)
        return flow;
    while (cur[v] < G[v].size()) {
        if (distances[edges[G[v][cur[v]]].to] == distances[v] + 1) {

            int result = dfs(t,
                             min(flow, edges[G[v][cur[v]]].maxFlow - edges[G[v][cur[v]]].flow),
                             edges[G[v][cur[v]]].to);

            if (result > 0) {
                edges[G[v][cur[v]]].flow += result;
                edges[G[v][cur[v]] ^ 1].flow -= result;
                return result;
            }
        }
        cur[v]++;
    }

    return 0;
}

int dinic(int s, int t) {
    distances.assign(distances.size(), INF);

    while (bfs(s, t)) {
        cur.assign(cur.size(), 0);

        int currentResult = dfs(t, INF, s);
        while (currentResult > 0) {
            currentResult = dfs(t, INF, s);
        }
    }

    return 0;
}

int findFlowDFS(vector<list<int>>& paths, int& t, int pos, int flow) {
    if (pos == t) {
        paths.emplace_back();
        return flow;
    }

    for (int e : G[pos]) {
        if (edges[e].flow > 0) {
            int resultFlow = findFlowDFS(paths, t, edges[e].to, min(edges[e].flow, flow));
            if (resultFlow > 0) {
                paths.back().push_front(edges[e].index);
                edges[e].flow -= resultFlow;
                return resultFlow;
            }
        }
    }
    return 0;
}

void decomposeFlow(int s, int t, vector<list<int>>& paths, vector<int>& flowValues) {
    dinic(s, t);
    int flow = 0;
    while (flow = findFlowDFS(paths, t, s, INF)) {
        flowValues.push_back(flow);
    }
}

int main() {
    ifstream input("decomposition.in");
    int n, m;
    input >> n >> m;
    G.resize(n);
    cur.resize(n);
    distances.resize(n);
    int from, to, maxFlow;
    for (int i = 0; i < m; i++) {
        input >> from >> to >> maxFlow;
        from--, to--;
        edges.push_back({i + 1, from, to, 0, maxFlow});
        G[from].push_back(edges.size() - 1);
        edges.push_back({i + 1, to, from, 0, 0});
        G[to].push_back(edges.size() - 1);
    }
    input.close();

    vector<list<int>> paths;
    vector<int> flowValues;
    decomposeFlow(0, n - 1, paths, flowValues);

    ofstream output("decomposition.out");
    output << paths.size() << endl;
    for (int i = 0; i < paths.size(); i++) {
        output << flowValues[i] << " " << paths[i].size() << " ";
        for (int e : paths[i])
            output << e << " ";
        output << endl;
    }
    output.close();

}