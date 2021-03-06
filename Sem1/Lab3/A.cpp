#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int lbinsearch(vector<int>& array, int query) {
	int lborder = -1;
	int rborder = array.size();
	int mid;
	while (lborder < rborder - 1) {
		mid = (lborder + rborder) / 2;
		if (array[mid] < query) {
			lborder = mid;
		}
		else {
			rborder = mid;
		}
	}
	if (rborder >= array.size())
		return -2;
	else if (array[rborder] != query)
		return -2;
	return rborder;
}

int rbinsearch(vector<int>& array, int query) {
	int lborder = -1;
	int rborder = array.size();
	int mid;
	while (lborder < rborder - 1) {
		mid = (lborder + rborder) / 2;
		if (array[mid] <= query) {
			lborder = mid;
		}
		else {
			rborder = mid;
		}
	}
	if (rborder < array.size() && array[rborder] == query)
		return rborder;
	else if (lborder > -1 && array[lborder] == query)
		return lborder;
	else
		return -2;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	ifstream inputf("binsearch.in");
	ofstream outputf("binsearch.out");
	int n;
	inputf >> n;
	vector<int> array(n, 0);
	for (int i = 0; i < n; ++i) {
		inputf >> array[i];
	}
	int m;
	inputf >> m;
	int query, l, r;
	for (int i = 0; i < m; ++i) {
		inputf >> query;
		l = lbinsearch(array, query) + 1;
		r = rbinsearch(array, query) + 1;
		outputf << l << " " << r << '\n';
	}
	inputf.close();
	outputf.close();
}
