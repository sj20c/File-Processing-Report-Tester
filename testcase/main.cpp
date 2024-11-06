#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    int size;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1), size(1) {}
};

int height(Node* T) {
    return T ? T->height : 0;
}

int size(Node* T) {
    return T ? T->size : 0;
}

Node* minNode(Node* T) {
    while (T && T->left) {
        T = T->left;
    }
    return T;
}

Node* maxNode(Node* T) {
    while (T && T->right) {
        T = T->right;
    }
    return T;
}

Node* insertBST(Node* T, int key) {
    Node* p = T;
    Node* q = nullptr;
    Node* stack[1000];
    int top = -1;

    while (p != nullptr) {
        if (key == p->key) {
            cerr << "i " << key << ": The key already exists" << endl;
            return nullptr;
        }
        q = p;
        stack[++top] = q;
        if (key < p->key) {
            p = p->left;
        } 
        else {
            p = p->right;
        }
    }

    Node* newNode = new Node(key);

    if (T == nullptr) {
        T = newNode;
    } 
    else if (key < q->key) {
        q->left = newNode;
    } 
    else {
        q->right = newNode;
    }

    while (top >= 0) {
        q = stack[top--];
        q->height = 1 + max(height(q->left), height(q->right));
        q->size = 1 + size(q->left) + size(q->right);
    }

    return T;
}

Node* eraseBST(Node* T, int key) {
    Node* p = T;
    Node* q = nullptr;
    Node* stack[1000];
    int top = -1;

    while (p != nullptr && key != p->key) {
        q = p;
        stack[++top] = q;
        if (key < p->key) {
            p = p->left;
        } 
        else {
            p = p->right;
        }
    }

    if (p == nullptr) {
        cerr << "d " << key << ": The key does not exist" << endl;
        return T;
    }

    if (p->left != nullptr && p->right != nullptr) {
        stack[++top] = p;
        Node* tempNode = p;

        if (height(p->left) <= height(p->right)) {
            Node* minNodeRight = minNode(p->right);
            p->key = minNodeRight->key;
            p->right = eraseBST(p->right, minNodeRight->key);
        } 
        else {
            Node* maxNodeLeft = maxNode(p->left);
            p->key = maxNodeLeft->key;
            p->left = eraseBST(p->left, maxNodeLeft->key);
        }
    } 
    else {
        Node* child = (p->left != nullptr) ? p->left : p->right;
        if (q == nullptr) {
            T = child;
        } 
        else if (q->left == p) {
            q->left = child;
        } 
        else {
            q->right = child;
        }
        delete p;
    }

    while (top >= 0) {
        q = stack[top--];
        q->height = 1 + max(height(q->left), height(q->right));
        q->size = 1 + size(q->left) + size(q->right);
    }

    return T;
}

string inorder(Node* T) {
    if (!T) return "";
    string left = inorder(T->left);
    string right = inorder(T->right);
    return "<" + left + " " + to_string(T->key) + " " + right + ">";
}

void clear(Node*& T) {
    if (!T) return;
    clear(T->left);
    clear(T->right);
    delete T;
    T = nullptr;
}

int main() {
    Node* T = nullptr;
    char cmd;
    int key;
    while (cin >> cmd >> key) {
        if (cmd == 'i') {
            Node* result = insertBST(T, key);
            if (result != nullptr) {
                T = result;
                cout << inorder(T) << endl;
            }
        } 
        else if (cmd == 'd') {
            T = eraseBST(T, key);
            cout << inorder(T) << endl;
        }
    }
    clear(T);
    return 0;
}

