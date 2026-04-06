#pragma once
#include "ITable.h"
#include "Tvector.h"
#include <iostream>
#include <utility>
#include <stdexcept>

template<typename TKey, typename TVal>
class UnsortedTableOnVec : public ITable<TKey, TVal> {
    Tvector<std::pair<TKey, TVal>> _rows;

    int find_index(const TKey& key) const noexcept;

public:
    UnsortedTableOnVec() = default;
    ~UnsortedTableOnVec() = default;

    void insert(const TKey& key, const TVal& val) override;
    TVal find(const TKey& key) const override;
    void erase(const TKey& key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& key) const noexcept override;  
    int size(const TKey& key) const noexcept override;     
    void replace(const TKey& key, const TVal& val) override; 
};

template<typename TKey, typename TVal>
int UnsortedTableOnVec<TKey, TVal>::find_index(const TKey& key) const noexcept {
    for (int i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == key) {
            return i;
        }
    }
    return -1;
}

template<typename TKey, typename TVal>
void UnsortedTableOnVec<TKey, TVal>::insert(const TKey& key, const TVal& val) {
    if (find_index(key) != -1) {
        throw std::runtime_error("Key already exists");
    }
    _rows.push_back(std::make_pair(key, val));
}

template<typename TKey, typename TVal>
TVal UnsortedTableOnVec<TKey, TVal>::find(const TKey& key) const {
    int index = find_index(key);
    if (index == -1) {
        throw std::runtime_error("Key not found");
    }
    return _rows[index].second;
}

template<typename TKey, typename TVal>
void UnsortedTableOnVec<TKey, TVal>::erase(const TKey& key) {
    int index = find_index(key);
    if (index == -1) {
        throw std::runtime_error("Key not found");
    }

    _rows.erase(index);

}

template<typename TKey, typename TVal>
std::ostream& UnsortedTableOnVec<TKey, TVal>::print(std::ostream& out) const noexcept {
    out << "Unsorted Table Contents:\n";
    for (int i = 0; i < _rows.size(); ++i) {
        out << "Key: " << _rows[i].first << ", Value: " << _rows[i].second << "\n";
    }
    return out;
}

template<typename TKey, typename TVal>
bool UnsortedTableOnVec<TKey, TVal>::is_empty() const noexcept {
    return _rows.empty();
}

template<typename TKey, typename TVal>
bool UnsortedTableOnVec<TKey, TVal>::consist(const TKey& key) const noexcept {
    return find_index(key) != -1;
}

template<typename TKey, typename TVal>
int UnsortedTableOnVec<TKey, TVal>::size(const TKey& key) const noexcept {
    return find_index(key) != -1 ? _rows.size() : 0;
}

template<typename TKey, typename TVal>
void UnsortedTableOnVec<TKey, TVal>::replace(const TKey& key, const TVal& val) {
    int index = find_index(key);
    if (index == -1) {
        throw std::runtime_error("Key not found");
    }
    _rows[index].second = val;
}