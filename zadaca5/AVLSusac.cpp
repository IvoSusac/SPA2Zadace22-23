#include <iostream>

using namespace std;

struct Node
{
    int key;
    int h;
    Node *left, *right, *parent;
};

class AVL
{
    Node *root;

    int height(Node *node) {
        if (node == nullptr)
            return 0;
        return node->h;
    }

    int balanceOfNode(Node *node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node* rightRotate(Node *y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        if (T2 != nullptr)
            T2->parent = y;

        y->h = max(height(y->left), height(y->right)) + 1;
        x->h = max(height(x->left), height(x->right)) + 1;

        x->parent = y->parent;
        y->parent = x;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        if (T2 != nullptr)
            T2->parent = x;

        x->h = max(height(x->left), height(x->right)) + 1;
        y->h = max(height(y->left), height(y->right)) + 1;

        y->parent = x->parent;
        x->parent = y;

        return y;
    }

    Node* insert(Node* node, int key) {
        if (node == nullptr)
            node = new Node{key, 0, nullptr, nullptr, nullptr};
        else if (key < node->key) {
            node->left = insert(node->left, key);
            node->left->parent = node;
        }
        else if (key > node->key) {
            node->right = insert(node->right, key);
            node->right->parent = node;
        }
        else
            return node;

        node->h = 1 + max(height(node->left), height(node->right));

        int balance = balanceOfNode(node);

        // Left Left
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(Node *node) {
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << "key: " << node->key << ", height: " << node->h << ", balance: " << balanceOfNode(node) << ". ";
        inorder(node->right);
    }

public:
    AVL() : root(nullptr) {}

    void print() {
        inorder(root);
    }

    void insert(int key) {
        root = insert(root, key);
    }
};

int main()
{
    AVL avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    avl.print();

}