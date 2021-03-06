#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<double> getHeights(int bulbsCount, double h1, double h2) {
    vector<double> bulbsHeights(bulbsCount, 0);
    bulbsHeights[0] = h1;
    bulbsHeights[1] = h2;
    for (int i = 2; i < bulbsCount; i++) {
        bulbsHeights[i] = 2 * bulbsHeights[i - 1] - bulbsHeights[i - 2] + 2;
    }
    return bulbsHeights;
}

bool isCorrect(const vector<double>& heights) {
    for (float h : heights) {
        if (h < 0)
            return false;
    }
    return true;
}

double binsearch(int bulbsCount, double h1) {
    double left = 0, right = h1;
    double mid;
    vector<double> bulbsHeights;

    while (right - left > 0.000001) {
        mid = (right + left) / 2;
        bulbsHeights = getHeights(bulbsCount, h1, mid);
        if (isCorrect(bulbsHeights))
            right = mid;
        else
            left = mid;
    }
    return bulbsHeights[bulbsHeights.size() - 1];
}

int main()
{
    ifstream inputf("IOfiles/garland.in");
    int n;
    double A;
    inputf >> n >> A;
    inputf.close();

    ofstream outputf("IOfiles/garland.out");
    outputf << fixed;
    outputf.precision(2);
    outputf << binsearch(n, A) << endl;
    outputf.close();
}
