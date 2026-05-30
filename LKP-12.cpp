#include <iostream>
#include <queue>

using namespace std;

const int ORDER = 4;
const int MAX_KEYS = ORDER - 1;
const int MIN_DEGREE = 2;

struct Node {
    int key[MAX_KEYS];
    Node* child[ORDER];
    int n;
    bool isLeaf;

    Node(bool leaf = true) : n(0), isLeaf(leaf)
    {
        for (int i = 0; i < ORDER; i++) {
            child[i] = nullptr;
        }
    }
};

void splitChild(Node* parent, int childIndex)
{
    Node* fullChild = parent->child[childIndex];
    Node* newChild = new Node(fullChild->isLeaf);

    newChild->n = MIN_DEGREE - 1;

    for (int j = 0; j < MIN_DEGREE - 1; j++) {
        newChild->key[j] = fullChild->key[j + MIN_DEGREE];
    }

    if (!fullChild->isLeaf) {
        for (int j = 0; j < MIN_DEGREE; j++) {
            newChild->child[j] = fullChild->child[j + MIN_DEGREE];
        }
    }

    fullChild->n = MIN_DEGREE - 1;

    for (int j = parent->n; j >= childIndex + 1; j--) {
        parent->child[j + 1] = parent->child[j];
    }

    parent->child[childIndex + 1] = newChild;

    for (int j = parent->n - 1; j >= childIndex; j--) {
        parent->key[j + 1] = parent->key[j];
    }

    parent->key[childIndex] = fullChild->key[MIN_DEGREE - 1];
    parent->n++;
}

void insertNonFull(Node* node, int value)
{
    int i = node->n - 1;

    if (node->isLeaf) {
        while (i >= 0 && value < node->key[i]) {
            node->key[i + 1] = node->key[i];
            i--;
        }

        node->key[i + 1] = value;
        node->n++;
        return;
    }

    while (i >= 0 && value < node->key[i]) {
        i--;
    }

    i++;

    if (node->child[i]->n == MAX_KEYS) {
        splitChild(node, i);

        if (value > node->key[i]) {
            i++;
        }
    }

    insertNonFull(node->child[i], value);
}

Node* insert(Node* root, int value)
{
    if (root == nullptr) {
        root = new Node();
        root->key[0] = value;
        root->n = 1;
        return root;
    }

    if (root->n == MAX_KEYS) {
        Node* newRoot = new Node(false);
        newRoot->child[0] = root;
        splitChild(newRoot, 0);

        int childIndex = (value > newRoot->key[0]) ? 1 : 0;
        insertNonFull(newRoot->child[childIndex], value);

        return newRoot;
    }

    insertNonFull(root, value);
    return root;
}

void printKeys(const Node* node)
{
    for (int i = 0; i < node->n; i++) {
        cout << node->key[i] << " ";
    }
}

void printTree(const Node* root)
{
    if (root == nullptr) {
        cout << "Tree kosong" << endl;
        return;
    }

    queue<const Node*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        int levelSize = nodes.size();

        for (int i = 0; i < levelSize; i++) {
            const Node* current = nodes.front();
            nodes.pop();

            cout << "[ ";
            printKeys(current);
            cout << "] ";

            if (!current->isLeaf) {
                for (int j = 0; j <= current->n; j++) {
                    if (current->child[j] != nullptr) {
                        nodes.push(current->child[j]);
                    }
                }
            }
        }

        cout << endl;
    }
}

void deleteTree(Node* root)
{
    if (root == nullptr) {
        return;
    }

    if (!root->isLeaf) {
        for (int i = 0; i <= root->n; i++) {
            deleteTree(root->child[i]);
        }
    }

    delete root;
}

int main()
{
    Node* root = nullptr;
    int values[] = {6, 2, 1, 4, 8, 9, 7};

    for (int value : values) {
        root = insert(root, value);
    }

    cout << "Original Tree:" << endl;
    printTree(root);

    cout << endl;
    cout << "Setelah menambahkan 5:" << endl;
    root = insert(root, 5);
    printTree(root);

    deleteTree(root);
    return 0;
}
