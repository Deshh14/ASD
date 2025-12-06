#pragma once
#include <stdexcept>

template<typename T>
class Queue {
private:
    T* data;
    size_t capacity;
    size_t frontIndex;
    size_t backIndex;
    size_t queueSize;

    

public:
    Queue();
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);
    ~Queue();

    void push(const T& value);
    void pop();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    bool isFull() const;
    bool empty() const;
    size_t size() const;
    size_t getCapacity() const;
    void swap(Queue& other);
    void clear();
};

template<typename T>
Queue<T>::Queue()
    : capacity(100),  frontIndex(0), backIndex(0), queueSize(0) {
    data = new T[capacity];
}

template<typename T>
Queue<T>::Queue(const Queue& other)
    : capacity(other.capacity),
    frontIndex(0),
    backIndex(0),
    queueSize(0) {
    data = new T[capacity];

    for (size_t i = 0; i < other.queueSize; ++i) {
        push(other.data[(other.frontIndex + i) % other.capacity]);
    }
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        delete[] data;

        capacity = other.capacity;
        frontIndex = 0;
        backIndex = 0;
        queueSize = 0;

        data = new T[capacity];

        for (size_t i = 0; i < other.queueSize; ++i) {
            push(other.data[(other.frontIndex + i) % other.capacity]);
        }
    }
    return *this;
}

template<typename T>
Queue<T>::~Queue() {
    delete[] data;
}


template<typename T>
bool Queue<T>::isFull() const {
    return queueSize == capacity;
}



template<typename T>
void Queue<T>::push(const T& value) {
    if (isFull()) {
        throw std::overflow_error("Queue overflow");
    }

    data[backIndex] = value;
    backIndex = (backIndex + 1) % capacity;
    queueSize++;
}

template<typename T>
void Queue<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }

    frontIndex = (frontIndex + 1) % capacity;
    queueSize--;
}

template<typename T>
T& Queue<T>::front() {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data[frontIndex];
}

template<typename T>
const T& Queue<T>::front() const {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data[frontIndex];
}

template<typename T>
T& Queue<T>::back() {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data[(backIndex == 0) ? capacity - 1 : backIndex - 1];
}

template<typename T>
const T& Queue<T>::back() const {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data[(backIndex == 0) ? capacity - 1 : backIndex - 1];
}

template<typename T>
bool Queue<T>::empty() const {
    return queueSize == 0;
}

template<typename T>
size_t Queue<T>::size() const {
    return queueSize;
}

template<typename T>
size_t Queue<T>::getCapacity() const {
    return capacity;
}

template<typename T>
void Queue<T>::swap(Queue& other) {
    std::swap(data, other.data);
    std::swap(capacity, other.capacity);
    std::swap(frontIndex, other.frontIndex);
    std::swap(backIndex, other.backIndex);
    std::swap(queueSize, other.queueSize);
}

template<typename T>
void Queue<T>::clear() {
    frontIndex = 0;
    backIndex = 0;
    queueSize = 0;
}

template class Queue<int>;
template class Queue<double>;
template class Queue<std::string>;
template class Queue<char>;