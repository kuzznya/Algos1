#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream inputf("antiqs.in");

	int n;
	inputf >> n;
	inputf.close();

	vector<int> array(n, 0);

	for (int i = 0; i < n; i++) array[i] = i + 1;
	for (int i = 0; i < n; i++) {
		swap(array[i], array[i / 2]);
	}

	ofstream outputf("antiqs.out");
	for (int i = 0; i < array.size(); i++) {
		if (i != 0) outputf << " ";
		outputf << array[i];

		if (i != 0) cout << " ";
		cout << array[i];
	}
	outputf.close();
	return 0;
}
