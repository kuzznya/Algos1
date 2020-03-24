#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Point {
    int x;
    int y;
};

int distanceSqr(Point A, Point B) {
    return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y);
}

double getPrimMSTCost(const vector<Point> points) {
    int n = points.size();
    vector<bool> used(n, false);
    vector<int> min_cost_edge(n, INF);
    min_cost_edge[0] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int w = 0; w < n; w++) {
            if (!used[w] && (v == -1 || min_cost_edge[w] < min_cost_edge[v]))
                v = w;
        }
        used[v] = true;
        for (int to = 0; to < n; to++) {
            if (!used[to] && to != v && distanceSqr(points[v], points[to]) < min_cost_edge[to])
                min_cost_edge[to] = distanceSqr(points[v], points[to]);
        }
    }
    double totalCost = 0;
    for (int dist2 : min_cost_edge)
        totalCost += sqrt(dist2);
    return totalCost;
}

int main() {
    ifstream input("spantree.in");
    int n;
    input >> n;
    vector<Point> points(n);
    int x, y;
    for (int i = 0; i < n; i++) {
        input >> x >> y;
        points[i] = {x, y};
    }
    input.close();
    ofstream output("spantree.out");
    output.precision(10);
    output << getPrimMSTCost(points) << endl;
    output.close();
    return 0;
}