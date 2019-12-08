#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

struct ListElement {
    shared_ptr<ListElement> prev;
    shared_ptr<ListElement> next;
    int value = 0;
};

shared_ptr<ListElement> createElement(int value) {
    shared_ptr<ListElement> newElement(new ListElement);
    newElement->value = value;
    newElement->next = nullptr;
    return newElement;
}

class Queue {
private:
    shared_ptr<ListElement> head = nullptr;
public:
    void push(int value) {
        shared_ptr<ListElement> newElement = createElement(value);
        if (head != nullptr) {
            newElement->prev = head->prev;
            newElement->next = head;
            head->prev->next = newElement;
            head->prev = newElement;
        }
        else {
            head = newElement;
            head->prev = head;
            head->next = head;
        }
    }

    int pop() {
        if (head == nullptr)
            throw exception();
        if (head->prev == head->next && head->prev == head) {
            int returnValue = head->value;
            head = nullptr;
            return returnValue;
        }
        head->prev->next = head->next;
        head->next->prev = head->prev;
        int returnValue = head->value;
        head = head->next;
        return returnValue;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ifstream inputf("IOfiles/queue.in");
    ofstream outputf("IOfiles/queue.out");

    int m;
    inputf >> m;

    Queue queue;

    char operation;
    int value;
    for (int i = 0; i < m; i++) {
        inputf >> operation;
        if (operation == '+') {
            inputf >> value;
            queue.push(value);
        }
        else if (operation == '-') {
            outputf << queue.pop() << '\n';
        }
    }

    inputf.close();
    outputf.close();
    return 0;
}
