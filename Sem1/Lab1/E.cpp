#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream input("sortland.in");
    int n;
    input >> n;
    float* a = new float[n];
    int* b = new int[n];
    for (int i = 0; i < n; i++) {
        input >> a[i];
        b[i] = i + 1;
    }
    input.close();

    float key;
    int keyB;

    int i;

    for (int j = 1; j < n; j++) {
        key = a[j];
        keyB = b[j];
        i = j - 1;
        while ((i >= 0) && (a[i] > key)) {
            a[i + 1] = a[i];
            b[i + 1] = b[i];
            i--;
        }
        a[i + 1] = key;
        b[i + 1] = keyB;
    }

    ofstream output("sortland.out");
    output << b[0] << " " << b[n / 2] << " " << b[n - 1];
    output.close();
    return 0;
}
