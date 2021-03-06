#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void radixsort(vector<string>& arr, int m, int k) {

    for (int i = m - 1; i >= m - k; i--) {

        vector<int> counters(26, 0);
        for (int j = 0; j < arr.size(); j++) {
            counters[arr[j][i] - 'a']++;
        }

        int temp, count = 0;
        for (int j = 0; j < counters.size(); j++) {
            temp = counters[j];
            counters[j] = count;
            count += temp;
        }

        vector<string> result(arr.size(), "");
        for (int j = 0; j < arr.size(); j++) {
            result[ counters[arr[j][i] - 'a'] ] = arr[j];
            counters[arr[j][i] - 'a']++;
        }
        arr = result;
        counters.clear();
        result.clear();
    }
}

int main()
{
    ifstream inputf("IOfiles/radixsort.in");
    int n, m, k;
    inputf >> n >> m >> k;
    vector<string> a(n, "");
    for (int i = 0; i < n; i++) {
        inputf >> a[i];
    }
    inputf.close();

    radixsort(a, m, k);

    ofstream outputf("IOfiles/radixsort.out");
    for (int i = 0; i < n; i++) {
        outputf << a[i] << endl;
    }
    outputf.close();
}
