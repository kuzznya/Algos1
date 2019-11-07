#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void qsort(vector<int> &a, int left, int right) {
	//int key = a[(left + right) / 2];
	int key = a[left + rand() % (right - left)];
	int i = left;
	int j = right;
	int buf;

	do {
		while (a[i] < key) i++;
		while (a[j] > key) j--;
		if (i <= j) {
			buf = a[i];
			a[i] = a[j];
			a[j] = buf;
			i++;
			j--;
		}
	} while (i <= j);

	if (j > left) qsort(a, left, j);
	if (i < right) qsort(a, i, right);
}


int main() {
	ifstream inputf("sort.in");
	int n;
	inputf >> n;
	vector<int> array(n, 0);

	for (int i = 0; i < n; i++) inputf >> array[i];

	inputf.close();

	qsort(array, 0, n - 1);

	ofstream outputf("sort.out");
	for (int i = 0; i < array.size(); i++) {
		if (i != 0) outputf << " ";
		outputf << array[i];
	}
	outputf.close();
	return 0;
}
