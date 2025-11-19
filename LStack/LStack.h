#pragma once

#include "list.h"
#include <stdexcept>
#include <initializer_list>

template<typename T>
class Stack {
private:
    List<T> list;

public:
    Stack() = default;

    Stack(std::initializer_list<T> initList) {
        for (const auto& item : initList) {
            push(item);
        }
    }

    Stack(const Stack& other) : list(other.list) {}

    Stack(Stack&& other) noexcept : list(std::move(other.list)) {}

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            list = std::move(other.list);
        }
        return *this;
    }

    void push(const T& value) {
        list.push_back(value);
    }

    void push(T&& value) {
        list.push_back(std::move(value));
    }

    void pop() {
        if (empty()) {
            throw std::underflow_error("Stack underflow");
        }
        list.pop_back();
    }

    T& top() {
        if (empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return list.back();
    }

    const T& top() const {
        if (empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return list.back();
    }

    bool empty() const {
        return list.empty();
    }

    size_t size() const {
        return list.size();
    }

    void clear() {
        list.clear();
    }

    void swap(Stack& other) {
        list.swap(other.list);
    }

    bool operator==(const Stack& other) const {
        if (size() != other.size()) {
            return false;
        }

        Stack<T> temp1 = *this;
        Stack<T> temp2 = other;

        while (!temp1.empty()) {
            if (temp1.top() != temp2.top()) {
                return false;
            }
            temp1.pop();
            temp2.pop();
        }
        return true;
    }

    bool operator!=(const Stack& other) const {
        return !(*this == other);
    }

    template<typename... Args>
    void emplace(Args&&... args) {
        list.push_back(T(std::forward<Args>(args)...));
    }

    const List<T>& get_list() const { return list; }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
    os << "Stack (top to bottom): ";
    if (stack.empty()) {
        os << "empty";
    }
    else {
        auto temp = stack;
        Stack<T> reverse;
        while (!temp.empty()) {
            reverse.push(temp.top());
            temp.pop();
        }

        bool first = true;
        while (!reverse.empty()) {
            if (!first) os << " <- ";
            os << reverse.top();
            reverse.pop();
            first = false;
        }
    }
    return os;
}

