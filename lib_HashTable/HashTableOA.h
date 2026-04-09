#include <iostream>
#include <string>
#include "Tvector.h"
#include "ITable.h"

enum class Status {
    empty,
    busy,
    deleted
};

template<typename Tval>
struct HashData {
    std::string key;
    Tval val;
    Status state;

    HashData() : key(""), val(Tval()), state(Status::empty) {}
    HashData(const std::string& k, const Tval& v) : key(k), val(v), state(Status::busy) {}
};

template<typename Tval>
class HashTableOA : public ITable<std::string, Tval> {
    size_t _size;      
    size_t _shift;    
    size_t _count;    
    Tvector<HashData<Tval>> _rows;

public:
    HashTableOA(size_t size = 101);

    void insert(const std::string& key, const Tval& val) override;
    Tval find(const std::string& key) const override;
    void erase(const std::string& key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const std::string& key) const noexcept override;
    int size(const std::string& key) const noexcept override;
    void replace(const std::string& key, const Tval& val) override;

private:
    size_t h(const std::string& key) const noexcept;
    size_t hh(size_t hash) const noexcept;
    bool is_simple(size_t a, size_t b) const noexcept;
    bool is_full() const noexcept;
    size_t find_index(const std::string& key) const;
};

template<typename Tval>
HashTableOA<Tval>::HashTableOA(size_t size) : _rows(size), _size(size), _count(0) {
    for (size_t s = 1 + std::max(size_t(1), _size / 15); s < _size; ++s) {
        if (is_simple(s, _size)) {
            _shift = s;
            break;
        }
    }
}

template<typename Tval>
bool HashTableOA<Tval>::is_simple(size_t a, size_t b) const noexcept {
    while (b != 0) {
        size_t temp = b;
        b = a % b;
        a = temp;
    }
    return a == 1;
}

template<typename Tval>
size_t HashTableOA<Tval>::h(const std::string& key) const {
    size_t hash = 0;
    for (auto sym : key) {
        hash += sym;
    }
    return hash % _size;
}

template<typename Tval>
size_t HashTableOA<Tval>::hh(size_t hash) const noexcept {
    return (hash + _shift) % _size;
}

template<typename Tval>
bool HashTableOA<Tval>::is_full() const noexcept {
    return _count >= _size;
}

template<typename Tval>
size_t HashTableOA<Tval>::find_index(const std::string& key) const {
    size_t index = h(key);
    size_t start_index = index;

    do {
        if (_rows[index].state == Status::empty) {
            throw std::runtime_error("Key not found");
        }
        if (_rows[index].state == Status::busy && _rows[index].key == key) {
            return index;
        }
        index = hh(index);
    } while (index != start_index);

    throw std::runtime_error("Key not found");
}

template<typename Tval>
void HashTableOA<Tval>::insert(const std::string& key, const Tval& val) {
    if (is_full()) {
        throw std::runtime_error("Hash table is full");
    }

    HashData<Tval> new_data(key, val);
    size_t index = h(key);
    size_t start_index = index;

    while (_rows[index].state == Status::busy) {
        if (_rows[index].key == key) {
            throw std::runtime_error("Key already exists");
        }
        index = hh(index);
        if (index == start_index) {
            throw std::runtime_error("Hash table is full");
        }
    }

    _rows[index] = new_data;
    ++_count;
}

template<typename Tval>
Tval HashTableOA<Tval>::find(const std::string& key) const {
    size_t index = find_index(key);
    return _rows[index].val;
}

template<typename Tval>
void HashTableOA<Tval>::erase(const std::string& key) {
    size_t index = find_index(key);
    _rows[index].state = Status::deleted;
    --_count;
}

template<typename Tval>
std::ostream& HashTableOA<Tval>::print(std::ostream& out) const noexcept {}

template<typename Tval>
bool HashTableOA<Tval>::is_empty() const noexcept {
    return _count == 0;
}

template<typename Tval>
bool HashTableOA<Tval>::consist(const std::string& key) const noexcept {
    try {
        find_index(key);
        return true;
    }
    catch (...) {
        return false;
    }
}

template<typename Tval>
int HashTableOA<Tval>::size(const std::string& key) const noexcept {}

template<typename Tval>
void HashTableOA<Tval>::replace(const std::string& key, const Tval& val) {
    size_t index = find_index(key);
    _rows[index].val = val;
}