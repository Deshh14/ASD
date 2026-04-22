#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <functional>

template<typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    size_t _size;

    int height(Node* node) const {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    Node* rotateRight(Node* y) {
        if (!y || !y->left) return y;

        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        if (!x || !x->right) return x;

        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* node) {
        if (!node) return nullptr;

        updateHeight(node);
        int bf = balanceFactor(node);

        // Левое поддерево тяжелее (bf < -1)
        if (bf < -1) {
            if (balanceFactor(node->left) <= 0) {
                return rotateRight(node);
            }
            else {
                if (node->left) {
                    node->left = rotateLeft(node->left);
                }
                return rotateRight(node);
            }
        }

        // Правое поддерево тяжелее (bf > 1)
        if (bf > 1) {
            if (balanceFactor(node->right) >= 0) {
                return rotateLeft(node);
            }
            else {
                if (node->right) {
                    node->right = rotateRight(node->right);
                }
                return rotateLeft(node);
            }
        }

        return node;
    }

    Node* insertNode(Node* node, const T& value) {
        if (!node) {
            _size++;
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertNode(node->right, value);
        }
        else {
            return node;  // Дубликат
        }

        return balance(node);
    }

    Node* findMin(Node* node) const {
        if (!node) return nullptr;
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    Node* removeNode(Node* node, const T& value) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = removeNode(node->left, value);
        }
        else if (value > node->data) {
            node->right = removeNode(node->right, value);
        }
        else {
            // Нашли узел для удаления

            // Случай 1: нет левого потомка
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                _size--;
                return balance(temp);
            }
            // Случай 2: нет правого потомка
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                _size--;
                return balance(temp);
            }
            // Случай 3: есть оба потомка
            else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = removeNode(node->right, temp->data);
            }
        }

        return balance(node);
    }

    Node* findNode(Node* node, const T& value) const {
        if (!node) return nullptr;

        if (value < node->data) {
            return findNode(node->left, value);
        }
        else if (value > node->data) {
            return findNode(node->right, value);
        }
        else {
            return node;
        }
    }

    void inorderTraversal(Node* node, std::ostream& out) const {
        if (!node) return;
        inorderTraversal(node->left, out);
        out << node->data << " ";
        inorderTraversal(node->right, out);
    }

    void preorderTraversal(Node* node, std::ostream& out) const {
        if (!node) return;
        out << node->data << " ";
        preorderTraversal(node->left, out);
        preorderTraversal(node->right, out);
    }

    void printTree(Node* node, int space, int indent, std::ostream& out) const {
        if (!node) return;

        space += indent;
        printTree(node->right, space, indent, out);

        out << std::endl;
        for (int i = indent; i < space; i++) out << " ";
        out << node->data << "(" << balanceFactor(node) << ")\n";

        printTree(node->left, space, indent, out);
    }

    void clearTree(Node* node) {
        if (!node) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

    Node* copyTree(Node* node) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        newNode->height = node->height;
        return newNode;
    }

public:
    AVLTree() : root(nullptr), _size(0) {}

    AVLTree(const AVLTree& other) : root(nullptr), _size(0) {
        root = copyTree(other.root);
        _size = other._size;
    }

    ~AVLTree() {
        clear();
    }

    AVLTree& operator=(const AVLTree& other) {
        if (this != &other) {
            clear();
            root = copyTree(other.root);
            _size = other._size;
        }
        return *this;
    }

    void insert(const T& value) {
        root = insertNode(root, value);
    }

    void erase(const T& value) {
        if (!contains(value)) {
            throw std::runtime_error("Value not found");
        }
        root = removeNode(root, value);
    }

    bool contains(const T& value) const {
        return findNode(root, value) != nullptr;
    }

    T find(const T& value) const {
        Node* node = findNode(root, value);
        if (!node) {
            throw std::runtime_error("Value not found");
        }
        return node->data;
    }

    T min() const {
        Node* node = findMin(root);
        if (!node) {
            throw std::runtime_error("Tree is empty");
        }
        return node->data;
    }

    T max() const {
        if (!root) {
            throw std::runtime_error("Tree is empty");
        }
        Node* node = root;
        while (node->right) {
            node = node->right;
        }
        return node->data;
    }

    size_t size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    int getHeight() const {
        return height(root);
    }

    void clear() {
        clearTree(root);
        root = nullptr;
        _size = 0;
    }

    void printInorder(std::ostream& out = std::cout) const {
        inorderTraversal(root, out);
    }

    void printPreorder(std::ostream& out = std::cout) const {
        preorderTraversal(root, out);
    }

    void printTree(std::ostream& out = std::cout) const {
        if (!root) {
            out << "Empty tree\n";
            return;
        }
        printTree(root, 0, 4, out);
    }

    void forEach(std::function<void(const T&)> func) const {
        std::function<void(Node*)> inorder = [&](Node* node) {
            if (!node) return;
            inorder(node->left);
            func(node->data);
            inorder(node->right);
            };
        inorder(root);
    }
};