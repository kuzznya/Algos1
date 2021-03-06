#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream inputf("isheap.in");
	int n;
	inputf >> n;
	vector<int> a(n, 0);
	bool flag = true;
	inputf >> a[0];
	for (int i = 1; i < n; i++) {
		inputf >> a[i];
		if (a[i] < a[i / 2 - (i + 1) % 2]) {
			flag = false;
		}
	}
	inputf.close();
	ofstream outputf("isheap.out");
	if (flag) {
		outputf << "YES";
	}
	else {
		outputf << "NO";
	}
	outputf.close();
}

