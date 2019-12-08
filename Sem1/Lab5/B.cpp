#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class Map {
private:
    struct Element {
        string key;
        string value;
    };

    vector<list<Element>> hashTable;

    unsigned hash(string key) {
        unsigned hash = 0;
        int charCode;
        const int k = 199;
        for (char i : key) {
            charCode = tolower(i) - 'a';
            hash = (hash * k + charCode) % hashTable.size();
        }
        return hash;
    }

public:

    Map() : Map(100003) {}

    Map(unsigned size) {
        hashTable.resize(size);
    }

    void put(string key, string value) {
        unsigned index = hash(key);
        for (Element& i : hashTable[index]) {
            if (i.key == key) {
                i.value = value;
                return;
            }
        }
        Element newEl;
        newEl.key = key;
        newEl.value = value;
        hashTable[index].push_back(newEl);
    }

    string get(string key) {
        unsigned index = hash(key);
        for (Element i : hashTable[index]) {
            if (i.key == key) {
                return i.value;
            }
        }
        return "none";
    }

    void remove(string key) {
        unsigned index = hash(key);
        for (auto i = hashTable[index].begin(); i != hashTable[index].end(); i++) {
            if (i->key == key) {
                hashTable[index].erase(i);
                return;
            }
        }
    }
};

int main() {
    Map map(100003);
    ifstream inputf("map.in");
    ofstream outputf("map.out");
    string command, x, y;
    while (!inputf.eof()) {
        command = "";
        inputf >> command >> x;
        if (command == "put") {
            inputf >> y;
            map.put(x, y);
        }
        else if (command == "get") {
            outputf << map.get(x) << '\n';
        }
        else if (command == "delete") {
            map.remove(x);
        }
    }
    inputf.close();
    outputf.close();
}