#pragma once
#include "AVLTree.h"
#include "ITable.h"
#include <string>

template<typename Tkey, typename Tval>
class AVLTable : public ITable<Tkey, Tval> {
private:
    struct KeyValue {
        Tkey key;
        mutable Tval value;

        KeyValue() : key(Tkey()), value(Tval()) {}
        KeyValue(const Tkey& k, const Tval& v) : key(k), value(v) {}

        bool operator<(const KeyValue& other) const {
            return key < other.key;
        }

        bool operator>(const KeyValue& other) const {
            return key > other.key;
        }

        bool operator==(const KeyValue& other) const {
            return key == other.key;
        }
    };

    AVLTree<KeyValue> tree;

    // Вспомогательный метод для поиска
    KeyValue makeKeyValue(const Tkey& key) const {
        return KeyValue(key, Tval());
    }

public:
    AVLTable() = default;

    void insert(const Tkey& key, const Tval& val) override {
        KeyValue kv(key, val);
        if (tree.contains(kv)) {
            throw std::runtime_error("Key already exists");
        }
        tree.insert(kv);
    }

    Tval find(const Tkey& key) const override {
        return tree.find(makeKeyValue(key)).value;
    }

    void erase(const Tkey& key) override {
        tree.erase(makeKeyValue(key));
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        out << "AVL Table (size=" << tree.size() << "):\n";
        bool first = true;
        tree.forEach([&](const KeyValue& kv) {
            if (!first) out << "\n";
            out << "  [" << kv.key << "] = " << kv.value;
            first = false;
            });
        return out;
    }

    bool is_empty() const noexcept override {
        return tree.empty();
    }

    bool consist(const Tkey& key) const noexcept override {
        return tree.contains(makeKeyValue(key));
    }

    int size(const Tkey& key) const noexcept override {
        return consist(key) ? 1 : 0;
    }

    void replace(const Tkey& key, const Tval& val) override {
        KeyValue kv(key, val);
        if (!tree.contains(makeKeyValue(key))) {
            throw std::runtime_error("Key not found");
        }
        tree.erase(makeKeyValue(key));
        tree.insert(kv);
    }

    Tkey min_key() const {
        if (tree.empty()) {
            throw std::runtime_error("Table is empty");
        }
        return tree.min().key;
    }

    Tkey max_key() const {
        if (tree.empty()) {
            throw std::runtime_error("Table is empty");
        }
        return tree.max().key;
    }

    size_t get_size() const {
        return tree.size();
    }

    int get_height() const {
        return tree.getHeight();
    }

    void print_tree(std::ostream& out = std::cout) const {
        tree.printTree(out);
    }
};