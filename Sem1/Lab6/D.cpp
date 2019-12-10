#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>

using namespace std;

class QuackVM {
private:

    vector<uint16_t> registers;
    queue<uint16_t> mainQueue;
    map<string, int> labels;
    vector<string> program;
    int currentPos = 0;

    void updateLabels() {
        int pos = 0;
        labels.clear();
        for (string command : program) {
            if (command[0] == ':') {
                command.erase(0, 1);
                labels.emplace(command, pos);
            }
            pos++;
        }
    }

public:
    QuackVM() {
        registers.resize(26);
    }

    QuackVM(vector<string> program) : QuackVM() {
        this->program = program;
    }

    void add() {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        uint16_t y = mainQueue.front();
        mainQueue.pop();
        mainQueue.push((x + y) % 65536);
    }

    void sub() {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        uint16_t y = mainQueue.front();
        mainQueue.pop();
        mainQueue.push((x - y) % 65536);
    }

    void mul() {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        uint16_t y = mainQueue.front();
        mainQueue.pop();
        mainQueue.push((x * y) % 65536);
    }

    void div() {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        uint16_t y = mainQueue.front();
        mainQueue.pop();
        uint16_t result = y == 0 ? 0 : x / y;
        mainQueue.push(result);
    }

    void mod() {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        uint16_t y = mainQueue.front();
        mainQueue.pop();
        uint16_t result = y == 0 ? 0 : x % y;
        mainQueue.push(result);
    }

    void setRegister(char reg) {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        registers[reg - 'a'] = x;
    }

    void getRegister(char reg) {
        uint16_t x = registers[reg - 'a'];
        mainQueue.push(x);
    }

    void print(ostream& output) {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        output << x << endl;
    }

    void printRegister(ostream& output, char reg) {
        output << registers[reg - 'a'] << endl;
    }

    void printChar(ostream& output) {
        output << (char) (mainQueue.front() % 256);
    }

    void printRegisterChar(ostream& output, char reg) {
        output << (char) (registers[reg - 'a'] % 256);
    }

    void setNewLabel(string label) {
        labels.emplace(label, currentPos);
    }

    void setNewLabel(string label, int pos) {
        labels.emplace(label, pos);
    }

    void updateLabel(string label) {
        labels.erase(label);
        labels.insert(make_pair(label, currentPos));
    }

    void jump(string label) {
        currentPos = labels[label];
    }

    void jumpIfZero(char reg, string label) {
        if (registers[reg - 'a'] == 0)
            jump(label);
    }

    void jumpIfEquals(char reg1, char reg2, string label) {
        if (registers[reg1 - 'a'] == registers[reg2 - 'a'])
            jump(label);
    }

    void jumpIfMore(char reg1, char reg2, string label) {
        if (registers[reg1 - 'a'] > registers[reg2 - 'a'])
            jump(label);
    }

    void put(uint16_t x) {
        mainQueue.push(x);
    }

    void start(ostream& output) {
        updateLabels();
        currentPos = 0;
        while (currentPos < program.size()) {
            string command = program[currentPos];
            if (command.length() == 0) {
                currentPos++;
                continue;
            }
            switch (command[0]) {
                case '+':
                    this->add();
                    break;
                case '-':
                    this->sub();
                    break;
                case '*':
                    this->mul();
                    break;
                case '/':
                    this->div();
                    break;
                case '%':
                    this->mod();
                    break;
                case '>':
                    this->setRegister(command[1]);
                    break;
                case '<':
                    this->getRegister(command[1]);
                    break;
                case 'P':
                    if (command.length() == 1)
                        this->print(output);
                    else
                        this->printRegister(output, command[1]);
                    break;
                case 'C':
                    if (command.length() == 1)
                        this->printChar(output);
                    else
                        this->printRegisterChar(output, command[1]);
                    break;
                case ':': {
                    string label = command;
                    label.erase(0, 1);
                    this->updateLabel(command);
                    break;
                }
                case 'J': {
                    string label = command;
                    label.erase(0, 1);
                    this->jump(label);
                    break;
                }
                case 'Z': {
                    char reg = command[1];
                    string label = command;
                    label.erase(0, 2);
                    this->jumpIfZero(reg, label);
                    break;
                }
                case 'E': {
                    char reg1 = command[1];
                    char reg2 = command[2];
                    string label = command;
                    label.erase(0, 3);
                    this->jumpIfEquals(reg1, reg2, label);
                    break;
                }
                case 'G': {
                    char reg1 = command[1];
                    char reg2 = command[2];
                    string label = command;
                    label.erase(0, 3);
                    this->jumpIfMore(reg1, reg2, label);
                    break;
                }
                case 'Q':
                    return;
                default: {
                    if (isdigit(command[0])) {
                        this->put(stoi(command));
                    }
                    else {
                        output << "Parsing error at line: \"" << command << "\" " << endl;
                    }
                }
            }
            currentPos++;
        }
    }

    void start(vector<string> program, ostream& output) {
        this->program = program;
        this->start(output);
    }

};

int main() {
    ifstream inputf("quack.in");
    ofstream outputf("quack.out");
    QuackVM qvm;
    vector<string> program;
    while (!inputf.eof()) {
        string line = "";
        inputf >> line;
        program.push_back(line);
    }
    qvm.start(program, outputf);
}