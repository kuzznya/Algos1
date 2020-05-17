#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

vector<int> prefix(const string& s) {
    vector<int> p(s.size(), 0);
    for (int i = 1; i < s.size(); i++) {
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k])
            k = p[k - 1];
        if (s[i] == s[k])
            k++;
        p[i] = k;

    }
    return p;
}

int main() {
    ifstream inputf("prefix.in");
    string input;
    inputf >> input;
    inputf.close();
    vector<int> result = prefix(input);
    ofstream outputf("prefix.out");
    for (int value : result)
        outputf << value << " ";
    outputf.close();
}