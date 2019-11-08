#include <iostream>
#include <fstream>
#include <memory>
#include <string>


using namespace std;

struct Element {
    union value {
        int num;
        char sign;
    };

    enum Type {
        num, sign
    } type;
};

template <class T>
struct ListElement {
    shared_ptr<ListElement> next;
    T value;
};

template <class T>
class Stack {
private:
    shared_ptr<ListElement<T>> head = NULL;

    shared_ptr<ListElement<T>> createElement(T value) {
        shared_ptr<ListElement<T>> newElement(new ListElement<T>);
        newElement->value = value;
        newElement->next = NULL;
        return newElement;
    }

public:

    Stack() {}

    void push(T value) {
        shared_ptr<ListElement<T>> newElement = createElement(value);
        newElement->next = head;
        head = newElement;
    }

    T pop() {
        if (head != NULL) {
            shared_ptr<ListElement<T>> elementToPop = head;
            head = head->next;
            T returnValue = elementToPop->value;
            return returnValue;
        }
        else throw exception();
    }

    void clear() {
        while (head != NULL) {
            pop();
        }
    }

    unsigned size() {
        unsigned counter = 0;
        shared_ptr<ListElement<T>> currentElement = head;
        while (currentElement != NULL) {
            counter++;
            currentElement = currentElement->next;
        }
        return counter;
    }

    bool isEmpty() {
        if (head == NULL)
            return true;
        else
            return false;
    }

};


int main() {
    Stack<int> stack;

    ifstream inputf("IOfiles/postfix.in");

    char c;
    while (!inputf.eof()) {
        inputf >> c;
        if (inputf.eof())
            break;
        if (isdigit(c)) {
            stack.push(atoi(&c));
        }
        else {
            int val2 = stack.pop();
            int val1 = stack.pop();
            switch (c) {
                case '+':
                    stack.push(val1 + val2);
                    break;
                case '-':
                    stack.push(val1 - val2);
                    break;
                case '*':
                    stack.push(val1 * val2);
                    break;
            }
        }
    }
    inputf.close();
    ofstream outputf("IOfiles/postfix.out");
    outputf << stack.pop() << endl;
    outputf.close();
    return 0;
}