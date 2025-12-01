#ifndef LQUEUE_H
#define LQUEUE_H

#include <stdexcept>
#include "List.h"

template<typename T>
class LQueue {
private:
    List<T> list;  

public:
    LQueue() {}
    LQueue(const LQueue& other) : list(other.list) {}
    LQueue& operator=(const LQueue& other);
    ~LQueue() {}

    void push(const T& value);
    void pop();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    bool empty() const;
    size_t size() const;
    size_t getCapacity() const;

    void swap(LQueue& other);
    void clear();
};


template<typename T>
LQueue<T>& LQueue<T>::operator=(const LQueue& other) {
    if (this != &other) {
        list = other.list;
    }
    return *this;
}

template<typename T>
void LQueue<T>::push(const T& value) {
    list.push_back(value);
}

template<typename T>
void LQueue<T>::pop() {
    if (empty()) {
        throw std::runtime_error("LQueue is empty");
    }
    list.pop_front();
}

template<typename T>
T& LQueue<T>::front() {
    if (empty()) {
        throw std::runtime_error("LQueue is empty");
    }
    return list.front();
}

template<typename T>
const T& LQueue<T>::front() const {
    if (empty()) {
        throw std::runtime_error("LQueue is empty");
    }
    return list.front();
}

template<typename T>
T& LQueue<T>::back() {
    if (empty()) {
        throw std::runtime_error("LQueue is empty");
    }
    return list.back();
}

template<typename T>
const T& LQueue<T>::back() const {
    if (empty()) {
        throw std::runtime_error("LQueue is empty");
    }
    return list.back();
}

template<typename T>
bool LQueue<T>::empty() const {
    return list.empty();
}

template<typename T>
size_t LQueue<T>::size() const {
    return list.size();
}

template<typename T>
size_t LQueue<T>::getCapacity() const {
    return list.size();
}

template<typename T>
void LQueue<T>::swap(LQueue& other) {
    list.swap(other.list);
}

template<typename T>
void LQueue<T>::clear() {
    list.clear();
}

#endif 