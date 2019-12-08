#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream inputf("height.in");
    ofstream outputf("height.out");
    int n;
    inputf >> n;
    vector<int> nodes(n, 1);
    for (int i = 0; i < n; i++) {
        int value, l, r;
        inputf >> value >> l >> r;
        if (l != 0)
            nodes[l - 1] = nodes[i] + 1;
        if (r != 0)
            nodes[r - 1] = nodes[i] + 1;
    }
    inputf.close();

    int height = 0;
    for (int i = 0; i < n; i++) {
        if (nodes[i] > height)
            height = nodes[i];
    }
    outputf << height;
    outputf.close();
    return 0;
}