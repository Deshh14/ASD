#pragma once
#include "ITable.h"
#include "BinarySearchTree.h"
#include <iostream>
#include <utility>
#include <stdexcept>
#include <sstream>

template<typename TKey, typename TVal>
class OrderedTableOnBST : public ITable<TKey, TVal> {
private:
    struct Pair {
        TKey key;
        TVal value;

        Pair(const TKey& k, const TVal& v) : key(k), value(v) {}

        bool operator<(const Pair& other) const {
            return key < other.key;
        }

        bool operator>(const Pair& other) const {
            return key > other.key;
        }

        bool operator==(const Pair& other) const {
            return key == other.key;
        }

        bool operator!=(const Pair& other) const {
            return key != other.key;
        }

        friend std::ostream& operator<<(std::ostream& out, const Pair& p) {
            out << p.key << ":" << p.value;
            return out;
        }
    };

    BinarySearchTree<Pair> tree;

public:
    OrderedTableOnBST() = default;
    ~OrderedTableOnBST() = default;

    OrderedTableOnBST(const OrderedTableOnBST&) = delete;
    OrderedTableOnBST& operator=(const OrderedTableOnBST&) = delete;

    void insert(const TKey& key, const TVal& val) override {
        if (contains(key)) {
            throw std::runtime_error("Key already exists");
        }
        tree.insert(Pair(key, val));
    }

    TVal find(const TKey& key) const override {
        Pair result = tree.find(Pair(key, TVal()));
        return result.value;
    }

    void erase(const TKey& key) override {
        if (!tree.erase(Pair(key, TVal()))) {
            throw std::runtime_error("Key not found");
        }
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        out << "\n=== Ordered Table on BST ===\n";
        out << "Size: " << tree.size() << "\n\n";

        out << "Inorder traversal (sorted order): ";
        tree.print_inorder(out);
        out << "\n";

        out << "Preorder traversal: ";
        tree.print_preorder(out);
        out << "\n";

        out << "Postorder traversal: ";
        tree.print_postorder(out);
        out << "\n";

        out << "Level order traversal: ";
        tree.print_levelorder(out);
        out << "\n";

        out << "\nTree structure:\n";
        tree.print_tree(out);
        out << "\n";

        return out;
    }

    bool is_empty() const noexcept override {
        return tree.empty();
    }

    bool consist(const TKey& key) const noexcept override {
        return contains(key);
    }

    bool contains(const TKey& key) const {
        return tree.contains(Pair(key, TVal()));
    }

    int size(const TKey& key) const noexcept override {
        return contains(key) ? 1 : 0;
    }

    int size() const noexcept {
        return static_cast<int>(tree.size());
    }

    void replace(const TKey& key, const TVal& val) override {
        erase(key);
        insert(key, val);
    }

    void printTreeOnly(std::ostream& out) const {
        tree.print_tree(out);
    }
};