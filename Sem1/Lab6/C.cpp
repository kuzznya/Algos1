#include <iostream>
#include <fstream>
#include <memory>
#include <limits>
#include <string>

using namespace std;

class BinSearchTree {
private:
    struct Node {
        int key;
        shared_ptr<Node> leftChild;
        shared_ptr<Node> rightChild;
        Node(int key, shared_ptr<Node> leftChild, shared_ptr<Node> rightChild) {
            this->key = key;
            this->leftChild = leftChild;
            this->rightChild = rightChild;
        }
    };

    static shared_ptr<Node> createNode(int key) {
        shared_ptr<Node> newNode = make_shared<Node>(key, nullptr, nullptr);
        return newNode;
    }

    shared_ptr<Node> root = nullptr;

    static shared_ptr<Node> insertIntoTree(shared_ptr<Node> currentNode, const int key) {
        if (currentNode == nullptr)
            return createNode(key);
        if (currentNode->key > key)
            currentNode->leftChild = insertIntoTree(currentNode->leftChild, key);
        else if (currentNode->key < key)
            currentNode->rightChild = insertIntoTree(currentNode->rightChild, key);
        return currentNode;
    }

    static bool find(shared_ptr<Node> currentNode, const int key) {
        if (currentNode == nullptr)
            return false;
        if (currentNode->key == key)
            return true;
        if (currentNode->key < key)
            return find(currentNode->rightChild, key);
        else
            return find(currentNode->leftChild, key);
    }

    static shared_ptr<Node> findNode(shared_ptr<Node> currentNode, const int key) {
        if (currentNode == nullptr)
            return nullptr;
        if (currentNode->key == key)
            return currentNode;
        if (currentNode->key < key)
            return findNode(currentNode->rightChild, key);
        else
            return findNode(currentNode->leftChild, key);
    }

    static shared_ptr<Node> getNextNode(shared_ptr<Node> currentNode) {
        if (currentNode->rightChild == nullptr)
            return nullptr;
        currentNode = currentNode->rightChild;
        while (currentNode->leftChild != nullptr)
            currentNode = currentNode->leftChild;
        return currentNode;
    }

    static int getNextKey(shared_ptr<Node> currentNode, const int key) {
        if (currentNode == nullptr)
            return INT32_MAX;
        if (currentNode->key > key && currentNode->leftChild == nullptr)
            return currentNode->key;
        if (currentNode->key > key) {
            int result = getNextKey(currentNode->leftChild, key);
            if (result != INT32_MAX)
                return result;
            return currentNode->key;
        }
        else
            return getNextKey(currentNode->rightChild, key);
    }

    static shared_ptr<Node> getPrevNode(shared_ptr<Node> currentNode) {
        if (currentNode->leftChild == nullptr)
            return nullptr;
        currentNode = currentNode->leftChild;
        while (currentNode->rightChild != nullptr)
            currentNode = currentNode->rightChild;
        return currentNode;
    }

    static int getPrevKey(shared_ptr<Node> currentNode, const int key) {
        if (currentNode == nullptr)
            return INT32_MAX;
        if (currentNode->key < key && currentNode->rightChild == nullptr)
            return currentNode->key;
        if (currentNode->key < key) {
            int result = getPrevKey(currentNode->rightChild, key);
            if (result != INT32_MAX)
                return result;
            return currentNode->key;
        }
        else
            return getPrevKey(currentNode->leftChild, key);
    }

    shared_ptr<Node> del(shared_ptr<Node> node) {
        if (node->leftChild == nullptr && node->rightChild == nullptr) {
            node.reset();
            return nullptr;
        }
        if (node->rightChild == nullptr) {
            shared_ptr<Node> temp = node->leftChild;
            node.reset();
            return temp;
        }
        node->key = getNextNode(node)->key;
        node->rightChild = findAndDelete(node->rightChild, getNextNode(node)->key);
        return node;
    }

    shared_ptr<Node> findAndDelete(shared_ptr<Node> currentNode, const int key) {
        if (currentNode == nullptr)
            return nullptr;
        if (currentNode->key == key)
            return del(currentNode);
        if (currentNode->key > key)
            currentNode->leftChild = findAndDelete(currentNode->leftChild, key);
        else
            currentNode->rightChild = findAndDelete(currentNode->rightChild, key);
        return currentNode;
    }

public:
    void insert(const int key) {
        root = insertIntoTree(root, key);
    }

    void remove(const int key) {
        root = findAndDelete(root, key);
    }

    bool exists(const int key) {
        return find(root, key);
    }

    int next(const int key) {
        return getNextKey(root, key);
    }

    int prev(const int key) {
        return getPrevKey(root, key);
    }

};

int main() {
    ifstream inputf("bstsimple.in");
    ofstream outputf("bstsimple.out");
    string cmd;
    int x;
    BinSearchTree tree;
    while (!inputf.eof()) {
        cmd = "";
        inputf >> cmd >> x;
        if (cmd == "insert")
            tree.insert(x);
        else if (cmd == "delete")
            tree.remove(x);
        else if (cmd == "exists") {
            if (tree.exists(x))
                outputf << "true" << endl;
            else
                outputf << "false" << endl;
        }
        else if (cmd == "next") {
            int next = tree.next(x);
            if (next != INT32_MAX)
                outputf << next << endl;
            else
                outputf << "none" << endl;
        }
        else if (cmd == "prev") {
            int prev = tree.prev(x);
            if (prev != INT32_MAX)
                outputf << prev << endl;
            else
                outputf << "none" << endl;
        }
    }
    inputf.close();
    outputf.close();
}
