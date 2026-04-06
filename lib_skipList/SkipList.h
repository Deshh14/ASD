#pragma once
#include <iostream>
#include <utility>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include "List.h"

template<typename Tkey, typename Tval>
struct Node {
    std::pair<Tkey, Tval> data;
    size_t levels;
    Node** next;

    Node(const Tkey& key, const Tval& val, size_t lvl = 1)
        : data(key, val), levels(lvl) {
        next = new Node * [lvl];
        for (size_t i = 0; i < lvl; ++i) {
            next[i] = nullptr;
        }
    }

    ~Node() {
        delete[] next;
    }
};

template<typename Tkey, typename Tval>
class SkipList {
private:
    Node<Tkey, Tval>* head;  
    size_t lvl;
    size_t max_lvl;
    int count;

    size_t generate_level() {
        size_t level = 1;
        while (level < max_lvl && (rand() % 100) < 50) {
            level++;
        }
        return level;
    }

public:
    SkipList(size_t max_levels = 10);
    ~SkipList();

    void insert(const Tkey& key, const Tval& val);
    Tval find(const Tkey& key) const;
    void erase(const Tkey& key);
    bool contains(const Tkey& key) const;
    bool is_empty() const;
    int size() const;
    void print(std::ostream& out) const;
};

template<typename Tkey, typename Tval>
SkipList<Tkey, Tval>::SkipList(size_t max_levels)
    : lvl(max_levels), max_lvl(max_levels), count(0) {
    srand(time(nullptr));

    Tkey dummy_key = Tkey();
    Tval dummy_val = Tval();
    head = new Node<Tkey, Tval>(dummy_key, dummy_val, max_lvl);
}

template<typename Tkey, typename Tval>
SkipList<Tkey, Tval>::~SkipList() {
    Node<Tkey, Tval>* current = head->next[0];
    while (current) {
        Node<Tkey, Tval>* next = current->next[0];
        delete current;
        current = next;
    }
    delete head;
}

template<typename Tkey, typename Tval>
void SkipList<Tkey, Tval>::insert(const Tkey& key, const Tval& val) {
    if (contains(key)) {
        throw std::runtime_error("Key already exists");
    }

    Node<Tkey, Tval>** update = new Node<Tkey, Tval>* [max_lvl];
    for (size_t i = 0; i < max_lvl; ++i) {
        update[i] = nullptr;
    }

    Node<Tkey, Tval>* current = head;

    for (int i = lvl - 1; i >= 0; --i) {
        while (current->next[i] && current->next[i]->data.first < key) {
            current = current->next[i];
        }
        update[i] = current;
    }

    size_t new_lvl = generate_level();
    if (new_lvl > lvl) {
        for (size_t i = lvl; i < new_lvl; ++i) {
            update[i] = head;
        }
        lvl = new_lvl;
    }

    Node<Tkey, Tval>* new_node = new Node<Tkey, Tval>(key, val, new_lvl);

    for (size_t i = 0; i < new_lvl; ++i) {
        new_node->next[i] = update[i]->next[i];
        update[i]->next[i] = new_node;
    }

    count++;
    delete[] update;
}

template<typename Tkey, typename Tval>
Tval SkipList<Tkey, Tval>::find(const Tkey& key) const {
    Node<Tkey, Tval>* current = head;

    for (int i = lvl - 1; i >= 0; --i) {
        while (current->next[i] && current->next[i]->data.first < key) {
            current = current->next[i];
        }
    }

    current = current->next[0];

    if (current && current->data.first == key) {
        return current->data.second;
    }

    throw std::runtime_error("Key not found");
}

template<typename Tkey, typename Tval>
void SkipList<Tkey, Tval>::erase(const Tkey& key) {
    Node<Tkey, Tval>** update = new Node<Tkey, Tval>* [max_lvl];
    for (size_t i = 0; i < max_lvl; ++i) {
        update[i] = nullptr;
    }

    Node<Tkey, Tval>* current = head;

    for (int i = lvl - 1; i >= 0; --i) {
        while (current->next[i] && current->next[i]->data.first < key) {
            current = current->next[i];
        }
        update[i] = current;
    }

    current = current->next[0];

    if (current && current->data.first == key) {
        for (size_t i = 0; i < current->levels; ++i) {
            update[i]->next[i] = current->next[i];
        }

        delete current;
        count--;

        while (lvl > 1 && head->next[lvl - 1] == nullptr) {
            lvl--;
        }
    }
    else {
        delete[] update;
        throw std::runtime_error("Key not found");
    }

    delete[] update;
}

template<typename Tkey, typename Tval>
bool SkipList<Tkey, Tval>::contains(const Tkey& key) const {
    try {
        find(key);
        return true;
    }
    catch (...) {
        return false;
    }
}

template<typename Tkey, typename Tval>
bool SkipList<Tkey, Tval>::is_empty() const {
    return count == 0;
}

template<typename Tkey, typename Tval>
int SkipList<Tkey, Tval>::size() const {
    return count;
}

template<typename Tkey, typename Tval>
void SkipList<Tkey, Tval>::print(std::ostream& out) const {
    out << "SkipList Contents (size: " << count << ", levels: " << lvl << "):\n";

    Node<Tkey, Tval>* current = head->next[0];

    if (!current) {
        out << "  (empty)\n";
        return;
    }

    int index = 0;
    while (current) {
        out << "  [" << index++ << "] Key: " << current->data.first
            << ", Value: " << current->data.second
            << " (levels: " << current->levels << ")\n";
        current = current->next[0];
    }
}