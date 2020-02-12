#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");
    int n;
    input >> n;
    vector<vector<short>> matrix(n, vector<short>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input >> matrix[i][j];
        }
    }
    input.close();

    ofstream output("output.txt");

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (matrix[i][j] != matrix[j][i] || (i == j && matrix[i][j] != 0)) {
                output << "NO" << endl;
                output.close();
                return 0;
            }
        }
    }
    output << "YES" << endl;
    return 0;
}