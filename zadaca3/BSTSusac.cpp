#include <iostream>

using namespace std;

struct Node
{
    int key;
    Node *left, *right, *parent;
};

class BST
{
    Node *root;

    Node* insert(int key, Node *node)
    {
        if (node == nullptr)
            return new Node{key, nullptr, nullptr, nullptr};

        if (key < node->key) {
            Node *lchild = insert(key, node->left);
            node->left = lchild;
            lchild->parent = node;
        }
        else if (key > node->key) {
            Node *rchild = insert(key, node->right);
            node->right = rchild;
            rchild->parent = node;
        }

        return node;
    }

    void inorder(Node *node)
    {
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    Node* search(int key, Node *node)
    {
        if (node == nullptr || key == node->key)
            return node;
        if (key > node->key)
            search(key, node->right);
        else search(key, node->left);
    }

    Node* find_min(Node *node)
    {
        if (node == nullptr)
            return node;
        if (node->left == nullptr)
            return node;
        else
            find_min(node->left);
    }

    Node* find_max(Node *node)
    {
        if (node == nullptr)
            return node;
        if (node->right == nullptr)
            return node;
        else
            find_max(node->right);
    }

    Node* successor(Node *node)
    {
        if (node->right != nullptr)
            return find_min(node->right);

        Node* par = node->parent;
        while (par != nullptr && node == par->right) {
            node = par;
            par = par->parent;
        }

        return par;
    }

    Node* predecessor(Node *node)
    {
        if (node->left != nullptr)
            return find_max(node->left);

        Node* par = node->parent;
        while (par != nullptr && node == par->left) {
            node = par;
            par = par->parent;
        }

        return par;
    }

    Node* BSTdelete(int key, Node *node)
    {
        if (node == nullptr)
            return node;

        if (key < node->key) {
            node->left = BSTdelete(key, node->left);
            if (node->left != nullptr)
                node->left->parent = node;
        }
        else if (key > node->key) {
            node->right = BSTdelete(key, node->right);
            if (node->right != nullptr)
                node->right->parent = node;
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = find_min(node->right);

            node->key = temp->key;

            node->right = BSTdelete(temp->key, node->right);
        }

        return node;
    }

public:
    BST() : root(NULL) {}

    void print()
    {
        inorder(root);
    }

    void insert(int key)
    {
        root = insert(key, root);
    }

    bool search(int key)
    {
        return search(key, root) != nullptr;
    }

    int find_min()
    {
        return find_min(root)->key;
    }

    int find_max()
    {
        return find_max(root)->key;
    }

    int successor(int key)
    {
        Node* temp = search(key, root);
        return successor(temp)->key;
    }

    int predecessor(int key)
    {
        Node* temp = search(key, root);
        return predecessor(temp)->key;
    }

    void BSTdelete(int key)
    {
        root = BSTdelete(key, root);
    }
};

int main()
{
    BST bst;
    bst.insert(5);
    bst.insert(10);
    bst.insert(4);
    bst.insert(8);
    bst.insert(9);
    bst.insert(1);
    bst.insert(11);
    bst.insert(15);
    bst.insert(3);

    bst.print();

    cout << endl;

    cout << bst.find_min() << endl;

    cout << bst.find_max() << endl;

    cout << bst.successor(8) << endl;

    cout << bst.predecessor(10) << endl;

    bst.BSTdelete(10);

    bst.print();
}