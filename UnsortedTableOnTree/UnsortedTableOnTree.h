#pragma once
#include "ITable.h"
#include "BinaryTree.h"
#include <iostream>
#include <utility>
#include <stdexcept>
#include <sstream>

template<typename TKey, typename TVal>
class UnsortedTableOnTree : public ITable<TKey, TVal> {
private:
    struct Pair {
        TKey key;
        TVal value;

        Pair(const TKey& k, const TVal& v) : key(k), value(v) {}

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

    BinaryTree<Pair> tree;

    Pair find_pair(const TKey& key) const {
        Pair dummy(key, TVal());
        return tree.find(dummy);
    }

public:
    UnsortedTableOnTree() = default;
    ~UnsortedTableOnTree() = default;

    UnsortedTableOnTree(const UnsortedTableOnTree&) = delete;
    UnsortedTableOnTree& operator=(const UnsortedTableOnTree&) = delete;

    void insert(const TKey& key, const TVal& val) override {
        if (this->contains(key)) {
            throw std::runtime_error("Key already exists");
        }
        tree.insert(Pair(key, val));
    }

    TVal find(const TKey& key) const override {
        Pair result = find_pair(key);
        return result.value;
    }

    void erase(const TKey& key) override {
        Pair to_delete(key, TVal());
        if (!tree.erase(to_delete)) {
            throw std::runtime_error("Key not found");
        }
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        out << "\n=== Unsorted Table on Tree ===\n";
        out << "Size: " << tree.size() << "\n\n";

        out << "Preorder traversal: ";
        tree.print_preorder(out);
        out << "\n";

        out << "Inorder traversal: ";
        tree.print_inorder(out);
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
        Pair dummy(key, TVal());
        return tree.contains(dummy);
    }

    int size(const TKey& key) const noexcept override {
        return this->contains(key) ? 1 : 0;  
    }

    int size() const noexcept {
        return static_cast<int>(tree.size());
    }

    void replace(const TKey& key, const TVal& val) override {
        this->erase(key); 
        this->insert(key, val);  
    }
    \
    bool contains(const TKey& key) const {
        Pair dummy(key, TVal());
        return tree.contains(dummy);
    }

    void printTreeOnly(std::ostream& out) const {
        tree.print_tree(out);
    }
};