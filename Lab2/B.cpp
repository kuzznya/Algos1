#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>


using namespace std;

void merge(vector<tuple<string, int, string>>& array, vector<tuple<string, int, string>>& array1, vector<tuple<string, int, string>>& array2) {
	array.clear();
	int a1i = 0, a2i = 0;
	while (a1i < array1.size() && a2i < array2.size()) {
		if (array1.at(a1i) <= array2.at(a2i)) {
			array.push_back(array1.at(a1i));
			++a1i;
		}
		else if (array1.at(a1i) > array2.at(a2i)) {
			array.push_back(array2.at(a2i));
			++a2i;
		}
	}

	while (a1i < array1.size()) {
		array.push_back(array1.at(a1i));
		++a1i;
	}

	while (a2i < array2.size()) {
		array.push_back(array2.at(a2i));
		++a2i;
	}
}


void merge_sort(std::vector<tuple<string, int, string>>& array) {
	if (1 < array.size()) {
		vector<tuple<string, int, string>> array1(array.begin(), array.begin() + array.size() / 2);
		merge_sort(array1);
		vector<tuple<string, int, string>> array2(array.begin() + array.size() / 2, array.end());
		merge_sort(array2);
		merge(array, array1, array2);
	}
}

int main()
{
	ifstream inputf("race.in");
	int n;
	inputf >> n;
	//vector< pair<string, vector<string> > > list = {};
	vector < tuple<string, int, string> > list;
	string country;
	string name;

	for (int i = 0; i < n; i++) {
		inputf >> country;
		inputf >> name;

		list.push_back(make_tuple(country, i, name));
	}
	inputf.close();

	merge_sort(list);

	ofstream outputf("race.out");
	string prevcountry = "";
	int k;
	for (tuple<string, int, string> el : list) {
		tie(country, k, name) = el;
		if (country != prevcountry) {
			outputf << "=== " << country << " ===" << endl;
			prevcountry = country;
		}
		outputf << name << endl;
	}
	outputf.close();
	return 0;
}
