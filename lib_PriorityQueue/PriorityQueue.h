#pragma once
#include "Heap.h"
#include <string>
#include <iostream>

template<typename T>
struct PriorityNode {

public:
    T name;
    int priority;
    int orderNumber;
    static int globalOrderCounter;
    PriorityNode();
    PriorityNode(const T& n, int p);

    T getName() const;
    int getPriority() const;
    int getOrderNumber() const;

    bool operator<(const PriorityNode& other) const;
    bool operator>(const PriorityNode& other) const;
    bool operator<=(const PriorityNode& other) const;
    bool operator>=(const PriorityNode& other) const;
    bool operator==(const PriorityNode& other) const;

    friend std::ostream& operator<<(std::ostream& os, const PriorityNode<T>& node) {
        os << node.name << "(" << node.priority << "," << node.orderNumber << ")";
        return os;
    }
};

template<typename T>
class PriorityQueue {
private:
    Heap<PriorityNode<T>> heap;

public:
    void push(const T& value,int p);
    T extractTop();
    T top() const;
    bool isEmpty() const;
    size_t size() const;
    void print() const;
};

template<typename T>
int PriorityNode<T>::globalOrderCounter = 0;

template<typename T>
PriorityNode<T>::PriorityNode(const T& n, int p)
    : name(n), priority(p) {
    orderNumber = ++globalOrderCounter;
}
template<typename T>
T PriorityNode<T>::getName() const {
    return name;
}
template<typename T>
int PriorityNode<T>::getPriority() const {
    return priority;
}
template<typename T>
int PriorityNode<T>::getOrderNumber() const {
    return orderNumber;
}
template<typename T>
bool PriorityNode<T>::operator<(const PriorityNode<T>& other) const {
    if (priority != other.priority) {
        return priority < other.priority;
    }
    return orderNumber < other.orderNumber;
}
template<typename T>
bool PriorityNode<T>::operator>(const PriorityNode<T>& other) const {
    return other < *this;
}
template<typename T>
bool PriorityNode<T>::operator<=(const PriorityNode<T>& other) const {
    return !(*this > other);
}
template<typename T>
bool PriorityNode<T>::operator>=(const PriorityNode<T>& other) const {
    return !(*this < other);
}
template<typename T>
bool PriorityNode<T>::operator==(const PriorityNode<T>& other) const {
    return name == other.name && priority == other.priority && orderNumber == other.orderNumber;
}


template<typename T>
PriorityNode<T>::PriorityNode() : name(T()), priority(0), orderNumber(0) {}

template<typename T>
void PriorityQueue<T>::push(const T& value, int p) {
    heap.insert(PriorityNode(value, p));
}

template<typename T>
T PriorityQueue<T>::extractTop() {
    if (isEmpty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    return heap.extractMin().name;
}

template<typename T>
T PriorityQueue<T>::top() const {
    if (isEmpty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    return heap.top();
}

template<typename T>
bool PriorityQueue<T>::isEmpty() const {
    return heap.isEmpty();
}

template<typename T>
size_t PriorityQueue<T>::size() const {
    return heap.size();
}

template<typename T>
void PriorityQueue<T>::print() const {
    heap.print();
}