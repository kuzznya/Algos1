#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Node {
    int key;
    int leftNum = 0;
    int rightNum = 0;
};

bool checkTree(vector<Node>& nodes, int nodeNum, int lowerLimit, int upperLimit) {
    if (nodes[nodeNum].leftNum != -1 && nodes[nodeNum].key < nodes[nodes[nodeNum].leftNum].key)
        return false;
    if (nodes[nodeNum].rightNum != -1 && nodes[nodeNum].key > nodes[nodes[nodeNum].rightNum].key)
        return false;
    if (nodes[nodeNum].key <= lowerLimit || nodes[nodeNum].key >= upperLimit)
        return false;
    if (nodes[nodeNum].leftNum != -1)
        return checkTree(nodes, nodes[nodeNum].leftNum, lowerLimit, nodes[nodeNum].key);
    if (nodes[nodeNum].rightNum != -1)
        return checkTree(nodes, nodes[nodeNum].rightNum, nodes[nodeNum].key, upperLimit);
    return true;
}

int main() {
    ifstream inputf("IOfiles/check.in");
    ofstream outputf("IOfiles/check.out");
    int n = 0;
    inputf >> n;
    vector<Node> nodes(n);
    for (int i = 0; i < n; i++) {
        int k = 0, l = 0 , r = 0;
        inputf >> k >> l >> r;
        nodes[i].key = k;
        nodes[i].leftNum = l - 1;
        nodes[i].rightNum = r - 1;
    }
    inputf.close();

    if (n != 0 && !checkTree(nodes, 0, -1000000001, 1000000001))
        outputf << "NO";
    else
        outputf << "YES";
    outputf.close();
    return 0;
}