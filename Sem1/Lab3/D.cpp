#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void siftDown(vector<int>& a, int n, int i) {
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int ind = i;
	if (l < n && a[i] < a[l])
		ind = l;
	if (r < n && a[ind] < a[r])
		ind = r;
	if (ind != i) {
		swap(a[i], a[ind]);
		siftDown(a, n, ind);
	}
}

void buildHeap(vector<int>& a) {
	for (int i = a.size() / 2; i >= 0; i--) {
		siftDown(a, a.size(), i);
	}
}

void heapSort(vector<int>& a) {
	buildHeap(a);
	int size = a.size();
	for (int i = 0; i < a.size() - 1; i++) {
		swap(a[0], a[a.size() - 1 - i]);
		size--;
		siftDown(a, size, 0);
	}
}

int main()
{
	ifstream inputf("sort.in");
	int n;
	inputf >> n;
	vector<int> a(n, 0);
	for (int i = 0; i < n; i++) {
		inputf >> a[i];
	}
	inputf.close();
	heapSort(a);
	ofstream outputf("sort.out");
	for (int i = 0; i < a.size(); i++) {
		outputf << a[i] << " ";
	}
	outputf.close();

}
