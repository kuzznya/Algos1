#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <list>

using namespace std;

class LinkedMap {
private:
    struct Element {
        string key;
        string value;
        shared_ptr<Element> prev;
        shared_ptr<Element> next;
    };

    static shared_ptr<Element> createElement(string key, string value) {
        shared_ptr<Element> newElement = make_shared<Element>();
        newElement->key = key;
        newElement->value = value;
        newElement->prev = nullptr;
        newElement->next = nullptr;
        return newElement;
    }

    vector<list<shared_ptr<Element>>> hashTable;

    shared_ptr<Element> first;
    shared_ptr<Element> last;

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

    LinkedMap() : LinkedMap(100003) {}

    LinkedMap(unsigned size) {
        hashTable.resize(size);
    }

    void put(string key, string value) {
        unsigned index = hash(key);
        for (shared_ptr<Element>& i : hashTable[index]) {
            if (i->key == key) {
                i->value = value;
                return;
            }
        }
        shared_ptr<Element> elementToPut = createElement(key, value);
        elementToPut->prev = last;
        if (last != nullptr)
            last->next = elementToPut;
        last = elementToPut;
        if (first == nullptr)
            first = elementToPut;
        hashTable[index].push_back(elementToPut);
    }

    string get(string key) {
        unsigned index = hash(key);
        for (shared_ptr<Element> i : hashTable[index]) {
            if (i->key == key)
                return i->value;
        }
        return "none";
    }

    void remove(string key) {
        unsigned index = hash(key);
        for (shared_ptr<Element>& i : hashTable[index]) {
            if (i->key == key) {
                if (i->prev != nullptr)
                    i->prev->next = i->next;
                else
                    first = i->next;
                if (i->next != nullptr)
                    i->next->prev = i->prev;
                else
                    last = i->prev;
                hashTable[index].remove(i);
                return;
            }
        }
    }

    string prev(string key) {
        unsigned index = hash(key);
        for (shared_ptr<Element> i : hashTable[index]) {
            if (i->key == key) {
                if (i->prev != nullptr)
                    return i->prev->value;
                else
                    return "none";
            }
        }
        return "none";
    }

    string next(string key) {
        unsigned index = hash(key);
        for (shared_ptr<Element> i : hashTable[index]) {
            if (i->key == key) {
                if (i->next != nullptr)
                    return i->next->value;
                else
                    return "none";
            }
        }
        return "none";
    }

    void print() {
        cout << "===================" << endl;
        if (first != nullptr)
            cout << "FIRST KEY: " << first->key << endl;
        else
            cout << "FIRST KEY: " << "NULL" << endl;
        if (last != nullptr)
            cout << "LAST KEY: " << last->key << endl;
        else
            cout << "LAST KEY: " << "NULL" << endl;
        for (auto i : hashTable) {
            for (auto j : i) {
                cout << j->key << ":" << j->value << " ";
            }
            if (i.size() != 0)
                cout << endl;
        }
        cout << "===================" << endl << endl;
    }

};

int main() {
    LinkedMap lmap(100003);
    ifstream inputf("linkedmap.in");
    ofstream outputf("linkedmap.out");
    string command, x, y;
    while (!inputf.eof()) {
        command = "";
        inputf >> command >> x;
//        cout << "Before:\n";
//        lmap.print();
        if (command == "put") {
            inputf >> y;
            lmap.put(x, y);
        }
        else if (command == "get") {
            outputf << lmap.get(x) << '\n';
        }
        else if (command == "delete") {
            lmap.remove(x);
        }
        else if (command == "prev") {
            outputf << lmap.prev(x) << '\n';
        }
        else if (command == "next") {
            outputf << lmap.next(x) << '\n';
        }
//        cout << "After " + command + ":\n";
//        lmap.print();
    }
    inputf.close();
    outputf.close();
}