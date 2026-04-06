#pragma once
#include "ITable.h"
#include "Tvector.h"
#include <iostream>
#include <utility>
#include <stdexcept>
#include <algorithm>

template<typename TKey, typename TVal>
class SortedTableOnVec : public ITable<TKey, TVal> {
    Tvector<std::pair<TKey, TVal>> _rows;

    int binary_search(const TKey& key) const noexcept;
    int find_insert_position(const TKey& key) const noexcept;

public:
    SortedTableOnVec() = default;
    ~SortedTableOnVec() = default;

    void insert(const TKey& key, const TVal& val) override;
    TVal find(const TKey& key) const override;
    void erase(const TKey& key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& key) const noexcept override;  
    int size(const TKey& key) const noexcept override;      
    int size() const noexcept;                               
    void replace(const TKey& key, const TVal& val) override;

    Tvector<TKey> get_keys() const;
    Tvector<TVal> get_values() const;
    TKey get_min_key() const;
    TKey get_max_key() const;
};

template<typename TKey, typename TVal>
int SortedTableOnVec<TKey, TVal>::binary_search(const TKey& key) const noexcept {
    
    int pos = find_insert_position(key);

    if(pos < _rows.size() && _rows[pos].first == key) {
        return pos;
    }

    return -1;
}

template<typename TKey, typename TVal>
int SortedTableOnVec<TKey, TVal>::find_insert_position(const TKey& key) const noexcept {
    int left = 0;
    int right = _rows.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (_rows[mid].first == key) {
            return mid;
        }
        if (_rows[mid].first < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

template<typename TKey, typename TVal>
void SortedTableOnVec<TKey, TVal>::insert(const TKey& key, const TVal& val) {
    if (binary_search(key) != -1) {
        throw std::runtime_error("Key already exists");
    }

    int pos = find_insert_position(key);
    _rows.push_back(std::make_pair(key, val));

    for (int i = _rows.size() - 1; i > pos; --i) {
        std::swap(_rows[i], _rows[i - 1]);
    }
}

template<typename TKey, typename TVal>
TVal SortedTableOnVec<TKey, TVal>::find(const TKey& key) const {
    int index = binary_search(key);
    if (index == -1) {
        throw std::runtime_error("Key not found");
    }
    return _rows[index].second;
}

template<typename TKey, typename TVal>
void SortedTableOnVec<TKey, TVal>::erase(const TKey& key) {
    int index = binary_search(key);
    if (index == -1) {
        throw std::runtime_error("Key not found");
    }

    for (int i = index; i < _rows.size() - 1; ++i) {
        _rows[i] = _rows[i + 1];
    }
    _rows.pop_back();
}

template<typename TKey, typename TVal>
std::ostream& SortedTableOnVec<TKey, TVal>::print(std::ostream& out) const noexcept {
    out << "Sorted Table Contents (size: " << _rows.size() << "):\n";
    for (int i = 0; i < _rows.size(); ++i) {
        out << "  [" << i << "] Key: " << _rows[i].first << ", Value: " << _rows[i].second << "\n";
    }
    if (_rows.size() == 0) {
        out << "  Table is empty\n";
    }
    return out;
}

template<typename TKey, typename TVal>
bool SortedTableOnVec<TKey, TVal>::is_empty() const noexcept {
    return _rows.empty();
}

template<typename TKey, typename TVal>
bool SortedTableOnVec<TKey, TVal>::consist(const TKey& key) const noexcept {
    return binary_search(key) != -1;
}

template<typename TKey, typename TVal>
int SortedTableOnVec<TKey, TVal>::size(const TKey& key) const noexcept {
    return binary_search(key) != -1 ? 1 : 0;
}

template<typename TKey, typename TVal>
int SortedTableOnVec<TKey, TVal>::size() const noexcept {
    return _rows.size();
}

template<typename TKey, typename TVal>
void SortedTableOnVec<TKey, TVal>::replace(const TKey& key, const TVal& val) {
    int index = binary_search(key);
    if (index == -1) {
        throw std::runtime_error("Key not found");
    }
    _rows[index].second = val;
}

template<typename TKey, typename TVal>
Tvector<TKey> SortedTableOnVec<TKey, TVal>::get_keys() const {
    Tvector<TKey> keys;
    for (int i = 0; i < _rows.size(); ++i) {
        keys.push_back(_rows[i].first);
    }
    return keys;
}

template<typename TKey, typename TVal>
Tvector<TVal> SortedTableOnVec<TKey, TVal>::get_values() const {
    Tvector<TVal> values;
    for (int i = 0; i < _rows.size(); ++i) {
        values.push_back(_rows[i].second);
    }
    return values;
}

template<typename TKey, typename TVal>
TKey SortedTableOnVec<TKey, TVal>::get_min_key() const {
    if (_rows.empty()) {
        throw std::runtime_error("Table is empty");
    }
    return _rows[0].first;
}

template<typename TKey, typename TVal>
TKey SortedTableOnVec<TKey, TVal>::get_max_key() const {
    if (_rows.empty()) {
        throw std::runtime_error("Table is empty");
    }
    return _rows[_rows.size() - 1].first;
}