#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <iomanip>
#include <stdexcept>

template<typename T>
class BinarySearchTree {
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

    void inorder_recursive(Node* node, std::ostream& out) const {
        if (!node) return;
        inorder_recursive(node->left, out);
        out << node->data << " ";
        inorder_recursive(node->right, out);
    }

    void preorder_recursive(Node* node, std::ostream& out) const {
        if (!node) return;
        out << node->data << " ";
        preorder_recursive(node->left, out);
        preorder_recursive(node->right, out);
    }

    void postorder_recursive(Node* node, std::ostream& out) const {
        if (!node) return;
        postorder_recursive(node->left, out);
        postorder_recursive(node->right, out);
        out << node->data << " ";
    }

    Node* find_node(const T& value) const {
        Node* current = root;
        while (current) {
            if (value < current->data) {
                current = current->left;
            }
            else if (value > current->data) {
                current = current->right;
            }
            else {
                return current;
            }
        }
        return nullptr;
    }

    Node* find_max(Node* node) const {
        while (node && node->right) {
            node = node->right;
        }
        return node;
    }

    Node* find_min(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
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

    void clear_recursive(Node* node) {
        if (!node) return;
        clear_recursive(node->left);
        clear_recursive(node->right);
        delete node;
    }

    void remove_node(Node* node) {
        if (!node) return;

        if (!node->left && !node->right) {
            if (node->parent) {
                if (node->parent->left == node) {
                    node->parent->left = nullptr;
                }
                else {
                    node->parent->right = nullptr;
                }
            }
            else {
                root = nullptr;
            }
            delete node;
        }
        else if (!node->left && node->right) {
            if (node->parent) {
                if (node->parent->left == node) {
                    node->parent->left = node->right;
                }
                else {
                    node->parent->right = node->right;
                }
                node->right->parent = node->parent;
            }
            else {
                root = node->right;
                root->parent = nullptr;
            }
            delete node;
        }

        else if (node->left && !node->right) {
            if (node->parent) {
                if (node->parent->left == node) {
                    node->parent->left = node->left;
                }
                else {
                    node->parent->right = node->left;
                }
                node->left->parent = node->parent;
            }
            else {
                root = node->left;
                root->parent = nullptr;
            }
            delete node;
        }
        else {
            Node* max_left = find_max(node->left);
            node->data = max_left->data;
            remove_node(max_left);
            return;
        }
        node_count--;
    }

public:
    BinarySearchTree() : root(nullptr), node_count(0) {}

    ~BinarySearchTree() {
        clear_recursive(root);
    }

    void insert(const T& value) {
        Node* new_node = new Node(value);

        if (!root) {
            root = new_node;
            node_count++;
            return;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current) {
            parent = current;
            if (value < current->data) {
                current = current->left;
            }
            else if (value > current->data) {
                current = current->right;
            }
            else {
                delete new_node;
                throw std::runtime_error("Duplicate value");
            }
        }

        new_node->parent = parent;
        if (value < parent->data) {
            parent->left = new_node;
        }
        else {
            parent->right = new_node;
        }
        node_count++;
    }

    bool contains(const T& value) const {
        return find_node(value) != nullptr;
    }

    T find(const T& value) const {
        Node* node = find_node(value);
        if (!node) {
            throw std::runtime_error("Value not found");
        }
        return node->data;
    }

    bool erase(const T& value) {
        Node* to_delete = find_node(value);
        if (!to_delete) return false;

        remove_node(to_delete);
        return true;
    }

    //в симметричном порядке
    void print_inorder(std::ostream& out) const {
        inorder_recursive(root, out);
    }

    //в прямом порядке
    void print_preorder(std::ostream& out) const {
        preorder_recursive(root, out);
    }

    //в обратном порядке
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

    // Красивый вывод дерева
    void print_tree(std::ostream& out) const {
        if (!root) {
            out << "(empty tree)\n";
            return;
        }
        print_tree(root, 0, 4, out);
    }

    int size() const { return node_count; }
    bool empty() const { return node_count == 0; }
};