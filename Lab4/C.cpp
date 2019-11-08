#include <iostream>
#include <fstream>
#include <memory>
#include <string>


using namespace std;

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
    Stack<char> stack;

    ifstream inputf("IOfiles/brackets.in");
    ofstream outputf("IOfiles/brackets.out");
    string input;

    bool isCorrect;
    while (!inputf.eof()) {
        stack.clear();

        getline(inputf, input);
        if (input.empty()) {
            break;
        }

        isCorrect = true;
        for (char c : input) {
            if (c == '(' || c == '[') {
                stack.push(c);
            }
            else {
                char prev_c;
                if (!stack.isEmpty())
                    prev_c = stack.pop();
                else {
                    isCorrect = false;
                    break;
                }
                if ((c == ')' && prev_c != '(') || (c == ']' && prev_c != '[')) {
                    isCorrect = false;
                    break;
                }
            }
        }

        if (isCorrect) {
            if (stack.isEmpty())
                outputf << "YES\n";
            else
                outputf << "NO\n";
        }
        else
            outputf << "NO\n";
    }
    stack.clear();
    inputf.close();
    outputf.close();
    return 0;
}
