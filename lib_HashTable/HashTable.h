//#include <iostream>
//#include <string>
//#include <vector>      
//#include <stdexcept>   
//#include "list.h"      
//#include "Tvector.h"
//#include "ITable.h"
//
//enum class MergeStrategy {
//    KEEP_FIRST,      
//    KEEP_SECOND,     
//    THROW_ON_CONFLICT, 
//    SUM_VALUES      
//};
//
//
//template<typename Tkey, typename Tval>
//class HashTableC : public ITable<Tkey, Tval> {
//    Tvector<list<std::pair<Tkey, Tval>>> _rows;
//    size_t _size; 
//
//public:
//    HashTableC(size_t size = 100) : _rows(size), _size(0) {}
//
//    void insert(const Tkey& key, const Tval& val) override;
//    Tval find(const Tkey& key) const override;
//    void erase(const Tkey& key) override;
//    std::ostream& print(std::ostream& out) const noexcept override;
//    bool is_empty() const noexcept override;
//    bool consist(const Tkey& key) const noexcept override;
//    int size(const Tkey& key) const noexcept override;
//    void replace(const Tkey& key, const Tval& val) override;
//    Tvector<std::pair<Tkey, Tval>> get_all_pairs() const {
//        std::vector<std::pair<Tkey, Tval>> all_pairs;
//        for (size_t i = 0; i < _rows.get_size(); ++i) {
//            for (const auto& pair : _rows[i]) {
//                all_pairs.push_back(pair);
//            }
//        }
//        return all_pairs;
//    }
//
//    size_t count() const noexcept {
//        return _size;
//    }
//private:
//    size_t h(const Tkey& key) const noexcept;
//};
//
//template<typename Tkey, typename Tval>
//size_t HashTableC<Tkey, Tval>::h(const Tkey& key) const noexcept {
//    size_t hash = 0;
//    for (char c : key) {
//        hash = hash * 31 + c;
//    }
//    return hash % _rows.get_size();
//}
//
//template<typename Tkey, typename Tval>
//void HashTableC<Tkey, Tval>::insert(const Tkey& key, const Tval& val) {
//    size_t index = h(key);
//
//    for (auto& pair : _rows[index]) {
//        if (pair.first == key) {
//            throw std::runtime_error("Key already exists");
//        }
//    }
//
//    _rows[index].push_back(std::make_pair(key, val));
//    ++_size;
//}
//
//template<typename Tkey, typename Tval>
//Tval HashTableC<Tkey, Tval>::find(const Tkey& key) const {
//    size_t index = h(key);
//
//    for (const auto& pair : _rows[index]) {
//        if (pair.first == key) {
//            return pair.second;
//        }
//    }
//
//    throw std::runtime_error("Key not found");
//}
//template<typename Tkey, typename Tval>
//void HashTableC<Tkey, Tval>::erase(const Tkey& key) {
//    size_t index = h(key);
//
//    for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it) {
//        if (it->first == key) {
//            _rows[index].erase(it);
//            --_size;
//            return;
//        }
//    }
//
//    throw std::runtime_error("Key not found");
//}
//
//template<typename Tkey, typename Tval>
//std::ostream& HashTableC<Tkey, Tval>::print(std::ostream& out) const noexcept {}
//
//template<typename Tkey, typename Tval>
//bool HashTableC<Tkey, Tval>::is_empty() const noexcept {
//    return _size == 0;
//}
//
//template<typename Tkey, typename Tval>
//bool HashTableC<Tkey, Tval>::consist(const Tkey& key) const noexcept {
//    size_t index = h(key);
//
//    for (const auto& pair : _rows[index]) {
//        if (pair.first == key) {
//            return true;
//        }
//    }
//
//    return false;
//}
//
//template<typename Tkey, typename Tval>
//int HashTableC<Tkey, Tval>::size(const Tkey& key) const noexcept {
//    size_t index = h(key);
//    int count = 0;
//
//    for (const auto& pair : _rows[index]) {
//        ++count;
//    }
//
//    return count;
//}
//
//template<typename Tkey, typename Tval>
//void HashTableC<Tkey, Tval>::replace(const Tkey& key, const Tval& val) {
//    size_t index = h(key);
//
//    for (auto& pair : _rows[index]) {
//        if (pair.first == key) {
//            pair.second = val;
//            return;
//        }
//    }
//
//    throw std::runtime_error("Key not found");
//}
//
//template<typename Tkey, typename Tval>
//HashTableC<Tkey, Tval> mergeTables(
//    const HashTableC<Tkey, Tval>& table1,
//    const HashTableC<Tkey, Tval>& table2,
//    MergeStrategy strategy = MergeStrategy::KEEP_FIRST) {
//
//    HashTableC<Tkey, Tval> result;
//
//    auto pairs1 = table1.get_all_pairs();
//    for (const auto& pair : pairs1) {
//        result.insert(pair.first, pair.second);
//    }
//
//    auto pairs2 = table2.get_all_pairs();
//    for (const auto& pair : pairs2) {
//        if (result.consist(pair.first)) {
//            switch (strategy) {
//            case MergeStrategy::KEEP_FIRST:
//                break;
//
//            case MergeStrategy::KEEP_SECOND:
//                result.replace(pair.first, pair.second);
//                break;
//
//            case MergeStrategy::THROW_ON_CONFLICT:
//                throw std::runtime_error("Key conflict: " + pair.first);
//
//            case MergeStrategy::SUM_VALUES:
//                Tval old_val = result.find(pair.first);
//                result.replace(pair.first, old_val + pair.second);
//                break;
//            }
//        }
//        else {
//            result.insert(pair.first, pair.second);
//        }
//    }
//
//    return result;
//}