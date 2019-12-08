#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int max(int a, int b) {
    if (a >= b) return a;
    else return b;
}

int main()
{
    ifstream inputStream("turtle.in");
    int h, w;
    inputStream >> h >> w;

    vector< vector<int> > field(h, vector<int>(w, 0));

    for (int i = h-1; i >= 0; i--) {
        for (int j = 0; j < w; j++) {
            inputStream >> field[i][j];
        }
    }

    inputStream.close();

    for (int i = 1; i < h; i++) {
        field[i][0] += field[i - 1][0];
    }

    for (int j = 1; j < w; j++) {
        field[0][j] += field[0][j - 1];
    }

    for (int i = 1; i < h; i++) {
        for (int j = 1; j < w; j++) {
            field[i][j] += max(field[i - 1][j], field[i][j - 1]);
        }
    }

    ofstream outputStream("turtle.out");
    outputStream << field[h - 1][w - 1];
    cout << field[h - 1][w - 1] << endl;
}
