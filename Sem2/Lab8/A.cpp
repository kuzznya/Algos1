#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

int main() {
    ifstream input("input.txt");
    int m, n;
    input >> n >> m;
    vector<vector<short>> matrix(n, vector<short>(n, 0));

    int a, b;
    for (int i = 0; i < m; i++) {
        input >> a >> b;
        matrix[a - 1][b - 1] = 1;
    }
    input.close();

    ofstream output("output.txt");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            output << matrix[i][j] << " ";
        }
        output << endl;
    }
    output.close();
    return 0;
}