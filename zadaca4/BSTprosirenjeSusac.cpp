#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unordered_set>

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

    void inorder(Node *node, vector<int>& nodes)
    {
        if (node == nullptr)
            return;
        inorder(node->left, nodes);
        nodes.push_back(node->key);
        inorder(node->right, nodes);
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

    bool nodesEqual(Node *node1, Node *node2) {
        if (node1 == nullptr && node2 == nullptr)
            return true;

        if (node1 != nullptr && node2 != nullptr) {
            return (nodesEqual(node1->left, node2->left) && nodesEqual(node1->right, node2->right));
        }

        return false;
    }

    void nthPower(Node *node, int n) {
        if (node == nullptr)
            return;
        nthPower(node->left, n);
        node->key = pow(node->key, n);
        nthPower(node->right, n);
    }

    void NodeAdd(Node *node1, Node *node2) {
        if (node1 == nullptr || node2 == nullptr) {
            return;
        }
        NodeAdd(node1->left, node2->left);
        node1->key += node2->key;
        NodeAdd(node1->right, node2->right);
    }

    Node* buildTree(vector<int>& nodes, int start, int end, Node* parent) {
        if (start > end)
            return nullptr;
        int mid = (start + end) / 2;
        Node* node = new Node{nodes[mid], nullptr, nullptr, nullptr};
        node->parent = parent;
        node->left = buildTree(nodes, start, mid - 1, node);
        node->right = buildTree(nodes, mid + 1, end, node);
        return node;
    }

public:
    BST() : root(NULL) {}

    BST(const BST &T) : BST{} {
        vector<int> copy {};
        inorder(T.root, copy);
        for (int i : copy)
            insert(i);
    }

    void print()
    {
        vector<int> temp{};
        inorder(root, temp);
        for (int key : temp)
            cout << key << " ";
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

    bool structurallyEqual(BST T1, BST T2) {
        return nodesEqual(T1.root, T2.root);
    }

    BST nthPowerBST(BST T, int n) {
        nthPower(T.root, n);
        return T;
    }

    BST BSTbuilder(vector<int> nodes) {
        Node *root = buildTree(nodes, 0, nodes.size() - 1, nullptr);
        BST T;
        T.root = root;
        return T;
    }

    BST BSTadd(BST T1, BST T2) {
        if (structurallyEqual(T1, T2)) {
            BST T3(T1);
            NodeAdd(T3.root, T2.root);
            return T3;
        }
        vector<int> nodes;
        inorder(T1.root, nodes);
        inorder(T2.root, nodes);

        unordered_set<int> s(nodes.begin(), nodes.end());
        nodes.assign(s.begin(), s.end());

        sort(nodes.begin(), nodes.end());
        return BSTbuilder(nodes);
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

    BST bst2;
    bst2.insert(6);
    bst2.insert(11);
    bst2.insert(5);
    bst2.insert(9);
    bst2.insert(10);
    bst2.insert(2);
    bst2.insert(12);
    bst2.insert(16);
    bst2.insert(4);

    bst2.print();

    cout << endl;

    cout << bst2.structurallyEqual(bst, bst2) << endl;

    bst.BSTadd(bst, bst2).print();

    cout << endl;

    bst.print();
}