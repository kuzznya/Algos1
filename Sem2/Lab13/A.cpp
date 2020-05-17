#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

vector<int>* findAll(const string& input1, const string& input2) {
    string s = input1 + "l" + input2;
    vector<int> p(s.size(), 0);
    vector<int>* result = new vector<int>();
    for (int i = 1; i < s.size(); i++) {
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k])
            k = p[k - 1];
        if (s[i] == s[k])
            k++;
        if (k == input1.size())
            result->push_back(i - 2 * input1.size() + 1);
        p[i] = k;

    }
    return result;
}

int main() {
    ifstream inputf("search1.in");
    string input1, input2;
    inputf >> input1 >> input2;
    inputf.close();

    vector<int> result = *findAll(input1, input2);
    ofstream outputf("search1.out");
    outputf << result.size() << endl;
    for (int value : result)
        outputf << value << " ";
    outputf.close();
}