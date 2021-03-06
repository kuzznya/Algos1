#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

long long c = 0;

void merge(vector<int>& array, vector<int>& array1, vector<int>& array2) {
	array.clear();
	int a1i = 0, a2i = 0;
	while (a1i < array1.size() && a2i < array2.size()) {
		if (array1[a1i] <= array2[a2i]) {
			array.push_back(array1[a1i]);
			a1i++;
		}
		else if (array1[a1i] > array2[a2i]) {
			array.push_back(array2.at(a2i));
			a2i++;
		}
	}

	while (a1i < array1.size()) {
		array.push_back(array1[a1i]);
		a1i++;
	}

	while (a2i < array2.size()) {
		array.push_back(array2[a2i]);
		a2i++;
	}
}


void merge_sort(vector<int>& array) {
	if (1 < array.size()) {
		vector<int> array1(array.begin(), array.begin() + array.size() / 2);
		merge_sort(array1);
		vector<int> array2(array.begin() + array.size() / 2, array.end());
		merge_sort(array2);
		
		int a1i = 0, a2i = 0;
		while (a1i < array1.size() && a2i < array2.size()) {
			if (array1[a1i] > array2[a2i]) {
				c += array1.size() - a1i;
				a2i++;
			}
			else {
				a1i++;
			}
		}

		merge(array, array1, array2);
	}
}


int main()
{
	ifstream inputf("inversions.in");
	int n;
	inputf >> n;
	vector<int> a(n, 0);
	for (int i = 0; i < n; i++) {
		inputf >> a[i];
	}
	inputf.close();
	merge_sort(a);
	ofstream outputf("inversions.out");
	outputf << c;
	outputf.close();
	return 0;
}
