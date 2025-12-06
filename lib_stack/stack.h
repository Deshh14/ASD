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