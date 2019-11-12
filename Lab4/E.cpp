#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class PriorityQueue {
private:

    vector<int> array;
    unsigned curSize = 0;

    void siftUp(unsigned current) {
        if (current > 0 && array[current] < array[(current - 1) / 2]) {
            swap(array[current], array[(current - 1) / 2]);
            siftUp((current - 1) / 2);
        }
    }

    void siftDown(unsigned current) {
        unsigned l = 2 * current + 1;
        unsigned r = 2 * current + 2;
        unsigned indexToSwap = current;
        if (l < curSize && array[current] > array[l])
            indexToSwap = l;
        if (r < curSize && array[indexToSwap] > array[r])
            indexToSwap = r;
        if (indexToSwap != current) {
            swap(array[current], array[indexToSwap]);
            siftDown(indexToSwap);
        }
    }

    int findByKey(int key) {
        for (int i = 0; i < curSize; i++) {
            if (array[i] == key)
                return i;
        }
        return -1;
    }

public:
    PriorityQueue() {
        array.resize(1000000);
    }

    void push(int key) {
        array[curSize] = key;
        siftUp(curSize++);
    }

    int extractMin() {
        if (curSize > 0) {
            int returnValue = array[0];
            array[0] = array[--curSize];
            siftDown(0);
            return returnValue;
        }
        else
            return -1000000001;
    }

    void decreaseKey(int oldKey, int newKey) {
        int index = findByKey(oldKey);
        array[index] = newKey;
        siftUp(index);
    }

};

int main() {
    ifstream inputf("IOfiles/priorityqueue.in");
    ofstream outputf("IOfiles/priorityqueue.out");

    PriorityQueue pq;

    vector<int> keys(1000000);

    string cmd;
    int x, y;
    int counter = 0;
    while (!inputf.eof()) {
        cmd = "";
        inputf >> cmd;
        if (cmd == "push") {
            inputf >> x;
            pq.push(x);
            keys[counter] = x;
        }
        else if (cmd == "extract-min") {
            int min = pq.extractMin();
            if (min > -1000000001)
                outputf << min << endl;
            else
                outputf << '*' << endl;
        }
        else if (cmd == "decrease-key") {
            inputf >> x >> y;
            pq.decreaseKey(keys[x - 1], y);
            keys[x - 1] = y;
        }
        counter++;
    }
    inputf.close();
    outputf.close();
    return 0;
}