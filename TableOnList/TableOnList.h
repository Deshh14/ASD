#pragma once
#include "ITable.h"
#include "SkipList.h"
#include <iostream>
#include <stdexcept>

template<typename TKey, typename TVal>
class TableOnSkipList : public ITable<TKey, TVal> {
private:
    SkipList<TKey, TVal> _skipList;

public:
    TableOnSkipList(size_t max_levels = 10) : _skipList(max_levels) {}
    ~TableOnSkipList() = default;

    void insert(const TKey& key, const TVal& val) override {
        _skipList.insert(key, val);
    }

    TVal find(const TKey& key) const override {
        return _skipList.find(key);
    }

    void erase(const TKey& key) override {
        _skipList.erase(key);
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        _skipList.print(out);
        return out;
    }

    bool is_empty() const noexcept override {
        return _skipList.is_empty();
    }

    bool contains(const TKey& key) const noexcept override {
        return _skipList.contains(key);
    }

    int size() const noexcept override {
        return _skipList.size();
    }

    void replace(const TKey& key, const TVal& val) override {
        if (!contains(key)) {
            throw std::runtime_error("Key not found");
        }
        _skipList.erase(key);
        _skipList.insert(key, val);
    }
};