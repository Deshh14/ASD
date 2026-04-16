#pragma once
#include <iostream>
#include "Tvector.h"
#include <stdexcept>

template<typename T>
class Heap {
private:
    Tvector<T> data;

    void siftUp(int index);
    void siftDown(int index);
    int _left(int index);
    int _right(int index);
    int _parent(int index);

public:
    explicit Heap(const Tvector<T>& arr);
    Heap() = default;
    void insert(const T& value);
    T extractMin();
    const T& top() const;
    bool isEmpty() const;
    size_t size() const;
    void print() const;
};

template<typename T>
Heap<T>::Heap(const Tvector<T>& arr) : data(arr) {
    for (int i = (data.size() / 2) - 1; i >= 0; --i) {
        siftDown(i);
    }
}

template<typename T>
int Heap<T>::_left(int index) {
    return 2 * index + 1;
}

template<typename T>
int Heap<T>::_right(int index) {
    return 2 * index + 2;
}

template<typename T>
int Heap<T>::_parent(int index) {
    return (index - 1) / 2;
}


template<typename T>
void Heap<T>::siftUp(int index) {
    while (index > 0) {
        int parent = _parent(index);
        if (data[index] < data[parent]) {
            std::swap(data[index], data[parent]);
            index = parent;
        }
        else {
            break;
        }
    }
}

template<typename T>
void Heap<T>::siftDown(int index) {
    int size = data.size();
    while (true) {
        int left = _left(index);
        int right = _right(index);
        int smallest = index;

        if (left < size && data[left] < data[smallest]) {
            smallest = left;
        }
        if (right < size && data[right] < data[smallest]) {
            smallest = right;
        }

        if (smallest != index) {
            std::swap(data[index], data[smallest]);
            index = smallest;
        }
        else {
            break;
        }
    }
}


template<typename T>
void Heap<T>::insert(const T& value) {
    data.push_back(value);
    siftUp(data.size() - 1);
}

template<typename T>
T Heap<T>::extractMin() {
    if (data.empty()) {
        throw std::runtime_error("Heap is empty");
    }

    T minValue = data[0];
    data[0] = data.back();
    data.pop_back();

    if (!data.empty()) {
        siftDown(0);
    }

    return minValue;
}

template<typename T>
const T& Heap<T>::top() const {
    if (data.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return data[0];
}

template<typename T>
bool Heap<T>::isEmpty() const {
    return data.empty();
}

template<typename T>
size_t Heap<T>::size() const {
    return data.size();
}

template<typename T>
void Heap<T>::print() const {
    std::cout << "Heap: ";
    for (const auto& val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}