#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <iomanip>

template<typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node* parent;

        Node(const T& value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;
    int node_count;

    //симметричный лево корень право
    void preorder_recursive(Node* node, std::ostream& out) const {
        if (!node) return;
        out << node->data << " ";
        preorder_recursive(node->left, out);
        preorder_recursive(node->right, out);
    }
    //прямой корень лево право
    void inorder_recursive(Node* node, std::ostream& out) const {
        if (!node) return;
        inorder_recursive(node->left, out);
        out << node->data << " ";
        inorder_recursive(node->right, out);
    }
    //обратный лево право корень
    void postorder_recursive(Node* node, std::ostream& out) const {
        if (!node) return;
        postorder_recursive(node->left, out);
        postorder_recursive(node->right, out);
        out << node->data << " ";
    }

    Node* find_last_node() {
        if (!root) return nullptr;

        std::queue<Node*> q;
        q.push(root);
        Node* last = nullptr;

        while (!q.empty()) {
            last = q.front();
            q.pop();
            if (last->left) q.push(last->left);
            if (last->right) q.push(last->right);
        }
        return last;
    }

    Node* find_node(const T& value) {
        if (!root) return nullptr;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            if (current->data == value) return current;
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        return nullptr;
    }

    void delete_node(Node* node) {
        if (!node) return;

        Node* parent = node->parent;

        if (parent) {
            if (parent->left == node) parent->left = nullptr;
            else parent->right = nullptr;
        }
        else {
            root = nullptr;
        }

        delete node;
        node_count--;
    }

    void print_tree(Node* node, int space, int indent, std::ostream& out) const {
        if (!node) return;

        space += indent;
        print_tree(node->right, space, indent, out);

        out << std::endl;
        for (int i = indent; i < space; i++) out << " ";
        out << node->data << "\n";

        print_tree(node->left, space, indent, out);
    }

public:
    BinaryTree() : root(nullptr), node_count(0) {}
    ~BinaryTree() { clear(); }

    void insert(const T& value) {
        Node* new_node = new Node(value);

        if (!root) {
            root = new_node;
            node_count++;
            return;
        }

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (!current->left) {
                current->left = new_node;
                new_node->parent = current;
                node_count++;
                return;
            }
            q.push(current->left);

            if (!current->right) {
                current->right = new_node;
                new_node->parent = current;
                node_count++;
                return;
            }
            q.push(current->right);
        }
    }

    bool contains(const T& value) const {
        if (!root) return false;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            if (current->data == value) return true;
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        return false;
    }

    bool erase(const T& value) {
        Node* to_delete = find_node(value);
        if (!to_delete) return false;

        Node* last_node = find_last_node();

        if (to_delete == last_node) {
            delete_node(to_delete);
            return true;
        }

        to_delete->data = last_node->data;
        delete_node(last_node);

        return true;
    }

    //корень, левое, правое
    void print_preorder(std::ostream& out) const {
        preorder_recursive(root, out);
    }

    //левое, корень, правое
    void print_inorder(std::ostream& out) const {
        inorder_recursive(root, out);
    }

    //левое, правое, корень
    void print_postorder(std::ostream& out) const {
        postorder_recursive(root, out);
    }

    //в ширину
    void print_levelorder(std::ostream& out) const {
        if (!root) return;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            out << current->data << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

    void print_tree(std::ostream& out) const {
        if (!root) {
            out << "(empty tree)\n";
            return;
        }
        print_tree(root, 0, 4, out);
    }

    int size() const { return node_count; }
    bool empty() const { return node_count == 0; }

    void clear() {
        if (!root) return;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
            delete current;
        }

        root = nullptr;
        node_count = 0;
    }

    T find(const T& value) const {
        if (!root) throw std::runtime_error("Not found");

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            if (current->data == value) return current->data;
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        throw std::runtime_error("Not found");
    }
};