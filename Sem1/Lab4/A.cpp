#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

struct ListElement {
    shared_ptr<ListElement> next;
    int value = 0;
};

shared_ptr<ListElement> createElement(int value) {
    shared_ptr<ListElement> newElement(new ListElement);
    newElement->value = value;
    newElement->next = NULL;
    return newElement;
}

class Stack {
private:
    shared_ptr<ListElement> head = NULL;
public:

    void push(int value) {
        shared_ptr<ListElement> newElement = createElement(value);
        newElement->next = head;
        head = newElement;
    }

    int pop() {
        if (head != NULL) {
            shared_ptr<ListElement> elementToPop = head;
            head = head->next;
            int returnValue = elementToPop->value;
            return returnValue;
        }
        else throw exception();
    }

    void clear() {
        while (head != NULL) {
            pop();
        }
    }

};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ifstream inputf("stack.in");
    ofstream outputf("stack.out");

    int m;
    inputf >> m;

    Stack stack;

    char operation;
    int value;
    for (int i = 0; i < m; i++) {
        inputf >> operation;
        if (operation == '+') {
            inputf >> value;
            stack.push(value);
        }
        else if (operation == '-') {
            outputf << stack.pop() << '\n';
        }
    }

    stack.clear();
    inputf.close();
    outputf.close();
    return 0;
}
