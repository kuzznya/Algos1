#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int k;

void kth(vector<int> &a, int left, int right) {
	if (left < right) {
		int key = a[left + (rand() % (right - left))];

		int i = left;
		int j = right;

		while (i <= j) {
			while (a[i] < key) i++;
			while (a[j] > key) j--;
			if (i > j) break;
			swap(a[i], a[j]);
			i++;
			j--;
		}

		if (k <= j) kth(a, left, j);
		else kth(a, i, right);
	}
}

int main()
{
	ifstream inputf("kth.in");
	int n;
	inputf >> n >> k;
	k--;
	int A, B, C;
	vector<int> a(n, 0);
	inputf >> A >> B >> C >> a[0] >> a[1];
	inputf.close();
	for (int i = 2; i < n; i++) {
		a[i] = A * a[i - 2] + B * a[i - 1] + C;
	}
	kth(a, 0, a.size() - 1);
	ofstream outputf("kth.out");
	outputf << a[k];
	outputf.close();
	return 0;
}