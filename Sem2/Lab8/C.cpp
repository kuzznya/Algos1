#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n, m;
    input >> n >> m;

    set<pair<int, int>> edges;
    int a, b;
    for (int i = 0; i < m; i++) {
        input >> a >> b;
        if (edges.find(make_pair(a, b)) == edges.end() &&
        edges.find(make_pair(b, a)) == edges.end())
            edges.insert(make_pair(a, b));
        else {
            output << "YES" << endl;
            output.close();
            input.close();
            return 0;
        }
    }
    output << "NO" << endl;
    output.close();
    input.close();
    return 0;
}