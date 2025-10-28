#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>

template<typename T, size_t MAX_SIZE = 100>
class ArrayStack {
private:
    T data[MAX_SIZE];
    int topIndex;

public:
    ArrayStack() : topIndex(-1) {}

    ArrayStack(std::initializer_list<T> initList) : topIndex(-1) {
        if (initList.size() > MAX_SIZE) {
            throw std::overflow_error("Initializer list exceeds stack capacity");
        }
        for (const auto& item : initList) {
            push(item);
        }
    }

    ArrayStack(const ArrayStack& other) : topIndex(other.topIndex) {
        for (int i = 0; i <= topIndex; ++i) {
            data[i] = other.data[i];
        }
    }

    ArrayStack& operator=(const ArrayStack& other) {
        if (this != &other) {
            topIndex = other.topIndex;
            for (int i = 0; i <= topIndex; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void push(const T& value) {
        if (isFull()) {
            throw std::overflow_error("Stack overflow");
        }
        data[++topIndex] = value;
    }

    void push(T&& value) {
        if (isFull()) {
            throw std::overflow_error("Stack overflow");
        }
        data[++topIndex] = std::move(value);
    }

    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack underflow");
        }
        return data[topIndex--];
    }

    T& top() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data[topIndex];
    }

    const T& top() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex >= static_cast<int>(MAX_SIZE) - 1;
    }

    size_t size() const {
        return topIndex + 1;
    }

    size_t capacity() const {
        return MAX_SIZE;
    }

    void clear() {
        topIndex = -1;
    }

    T& at(int index) {
        if (index < 0 || index > topIndex) {
            throw std::out_of_range("Index out of range");
        }
        return data[topIndex - index];
    }

    const T& at(int index) const {
        if (index < 0 || index > topIndex) {
            throw std::out_of_range("Index out of range");
        }
        return data[topIndex - index];
    }

    T& operator[](int index) {
        return at(index);
    }

    const T& operator[](int index) const {
        return at(index);
    }

    int find(const T& value) const {
        for (int i = topIndex; i >= 0; --i) {
            if (data[i] == value) {
                return topIndex - i;
            }
        }
        return -1;
    }

    T& minElement() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }

        T& minVal = data[0];
        for (int i = 1; i <= topIndex; ++i) {
            if (data[i] < minVal) {
                minVal = data[i];
            }
        }
        return minVal;
    }

    const T& minElement() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }

        const T& minVal = data[0];
        for (int i = 1; i <= topIndex; ++i) {
            if (data[i] < minVal) {
                minVal = data[i];
            }
        }
        return minVal;
    }

    T& maxElement() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }

        T& maxVal = data[0];
        for (int i = 1; i <= topIndex; ++i) {
            if (data[i] > maxVal) {
                maxVal = data[i];
            }
        }
        return maxVal;
    }

    const T& maxElement() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }

        const T& maxVal = data[0];
        for (int i = 1; i <= topIndex; ++i) {
            if (data[i] > maxVal) {
                maxVal = data[i];
            }
        }
        return maxVal;
    }

    bool operator==(const ArrayStack& other) const {
        if (size() != other.size()) {
            return false;
        }
        for (int i = 0; i <= topIndex; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const ArrayStack& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const ArrayStack& stack) {
        os << "Stack: ";
        if (stack.isEmpty()) {
            os << "empty";
        }
        else {
            os << "(top) ";
            for (int i = stack.topIndex; i >= 0; --i) {
                os << stack.data[i];
                if (i > 0) os << " <- ";
            }
            os << " (bottom)";
        }
        return os;
    }
};

#endif