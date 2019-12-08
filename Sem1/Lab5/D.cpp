#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <list>

using namespace std;

class Set {
private:
    vector<list<string>> hashTable;

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
    Set() : Set (233) {}

    Set(unsigned size) {
        hashTable.resize(size);
    }

    bool exists(string key) {
        unsigned index = hash(key);
        for (string i : hashTable[index]) {
            if (i == key)
                return true;
        }
        return false;
    }

    void insert(string key) {
        if (!exists(key))
            hashTable[hash(key)].push_back(key);
    }

    void remove(string key) {
        unsigned index = hash(key);
        for (auto i = hashTable[index].begin(); i != hashTable[index].end(); i++) {
            if (*i == key) {
                hashTable[index].erase(i);
                return;
            }
        }
    }

    vector<string> getAll() {
        vector<string> result;
        for (list<string> values : hashTable) {
            for (string value : values) {
                result.push_back(value);
            }
        }
        return result;
    }

    void reset() {
        unsigned size = hashTable.size();
        hashTable.clear();
        hashTable.resize(size);
    }

};

class MultiMap {
private:
    struct Element {
        string key;
        shared_ptr<Set> values;
    };

    vector<list<Element>> hashTable;

    unsigned valueSetSize;

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

    shared_ptr<Set> getValueSet(string key) {
        unsigned index = hash(key);
        for (Element& element : hashTable[index]) {
            if (element.key == key) {
                return element.values;
            }
        }
        return nullptr;
    }

public:
    MultiMap() : MultiMap(100003, 233) {}
    MultiMap(unsigned mapSize) : MultiMap(mapSize, 233) {}
    MultiMap(unsigned mapSize, unsigned valueSetSize) {
        hashTable.resize(mapSize);
        this->valueSetSize = valueSetSize;
    }

    void put(string key, string value) {
        shared_ptr<Set> valueSet = getValueSet(key);
        if (valueSet != nullptr)
            valueSet->insert(value);
        else {
            Element newElement;
            newElement.key = key;
            newElement.values = make_shared<Set>(valueSetSize);
            newElement.values->insert(value);
            hashTable[hash(key)].push_back(newElement);
        }
    }

    vector<string> get(string key) {
        shared_ptr<Set> valueSet = getValueSet(key);
        if (valueSet != nullptr)
            return valueSet->getAll();
        else
            return vector<string>(0);
    }

    void remove(string key, string value) {
        shared_ptr<Set> valueSet = getValueSet(key);
        if (valueSet != nullptr)
            valueSet->remove(value);
    }

    void removeAll(string key) {
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
    MultiMap multiMap(100003, 233);
    ifstream inputf("IOfiles/multimap.in");
    ofstream outputf("IOfiles/multimap.out");
    string command, x, y;
    while (!inputf.eof()) {
        command = "";
        inputf >> command >> x;
        if (command == "put") {
            inputf >> y;
            multiMap.put(x, y);
        }
        else if (command == "get") {
            vector<string> values = multiMap.get(x);
            outputf << values.size() << " ";
            for (string value : values)
                outputf << value << " ";
            outputf << '\n';
        }
        else if (command == "delete") {
            inputf >> y;
            multiMap.remove(x, y);
        }
        else if (command == "deleteall") {
            multiMap.removeAll(x);
        }
    }
    inputf.close();
    outputf.close();
}