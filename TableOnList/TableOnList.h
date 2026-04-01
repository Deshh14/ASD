#pragma once
#include "ITable.h"
#include "List.h"
#include <iostream>
#include <utility>
#include <stdexcept>

template<typename TKey, typename TVal>
class UnsortedTableOnList : public ITable<TKey, TVal> {
private:
    List<std::pair<TKey, TVal>> _rows;

    typename List<std::pair<TKey, TVal>>::Iterator find_iterator(const TKey& key) const noexcept;

public:
    UnsortedTableOnList() = default;
    ~UnsortedTableOnList() = default;

    UnsortedTableOnList(const UnsortedTableOnList&) = delete;
    UnsortedTableOnList& operator=(const UnsortedTableOnList&) = delete;

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
typename List<std::pair<TKey, TVal>>::Iterator
UnsortedTableOnList<TKey, TVal>::find_iterator(const TKey& key) const noexcept {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if ((*it).first == key) {  
            return it;
        }
    }
    return _rows.end();
}

template<typename TKey, typename TVal>
void UnsortedTableOnList<TKey, TVal>::insert(const TKey& key, const TVal& val) {
    if (find_iterator(key) != _rows.end()) {
        throw std::runtime_error("Key already exists");
    }
    _rows.push_back(std::make_pair(key, val));
}

template<typename TKey, typename TVal>
TVal UnsortedTableOnList<TKey, TVal>::find(const TKey& key) const {
    auto it = find_iterator(key);
    if (it == _rows.end()) {
        throw std::runtime_error("Key not found");
    }
    return (*it).second;
}

template<typename TKey, typename TVal>
void UnsortedTableOnList<TKey, TVal>::erase(const TKey& key) {
    auto it = find_iterator(key);
    if (it == _rows.end()) {
        throw std::runtime_error("Key not found");
    }
    _rows.erase(it);
}

template<typename TKey, typename TVal>
std::ostream& UnsortedTableOnList<TKey, TVal>::print(std::ostream& out) const noexcept {
    out << "Unsorted List Table Contents (size: " << _rows.size() << "):\n";
    int index = 0;
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        out << "  [" << index++ << "] Key: " << (*it).first  
            << ", Value: " << (*it).second << "\n"; 
    }
    return out;
}

template<typename TKey, typename TVal>
bool UnsortedTableOnList<TKey, TVal>::is_empty() const noexcept {
    return _rows.empty();
}

template<typename TKey, typename TVal>
bool UnsortedTableOnList<TKey, TVal>::consist(const TKey& key) const noexcept {
    return find_iterator(key) != _rows.end();
}

template<typename TKey, typename TVal>
int UnsortedTableOnList<TKey, TVal>::size(const TKey& key) const noexcept {
    auto it = find_iterator(key);
    return (it != _rows.end()) ? 1 : 0;
}

template<typename TKey, typename TVal>
void UnsortedTableOnList<TKey, TVal>::replace(const TKey& key, const TVal& val) {
    auto it = find_iterator(key);
    if (it == _rows.end()) {
        throw std::runtime_error("Key not found");
    }
    (*it).second = val;  
}