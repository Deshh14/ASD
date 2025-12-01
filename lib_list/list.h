#ifndef LIST_H
#define LIST_H

#include <stdexcept>
#include <algorithm>

template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t list_size;

public:
    List();
    List(const List& other);
    List(List&& other) noexcept;
    ~List();

    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node);
        T& operator*();
        T* operator->();  // Добавлен оператор ->
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin();
    Iterator end();

    bool empty() const;
    size_t size() const;

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    Iterator insert(Iterator position, const T& value);
    Iterator erase(Iterator position);
    void clear();
    void swap(List& other);

    void reverse();
    void unique();
    void sort();
};


template<typename T>
List<T>::List() : head(nullptr), tail(nullptr), list_size(0) {}

template<typename T>
List<T>::List(const List& other) : head(nullptr), tail(nullptr), list_size(0) {
    for (Node* current = other.head; current != nullptr; current = current->next) {
        push_back(current->data);
    }
}

template<typename T>
List<T>::List(List&& other) noexcept
    : head(other.head), tail(other.tail), list_size(other.list_size) {
    other.head = nullptr;
    other.tail = nullptr;
    other.list_size = 0;
}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        for (Node* current = other.head; current != nullptr; current = current->next) {
            push_back(current->data);
        }
    }
    return *this;
}

template<typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
    if (this != &other) {
        clear();
        head = other.head;
        tail = other.tail;
        list_size = other.list_size;
        other.head = nullptr;
        other.tail = nullptr;
        other.list_size = 0;
    }
    return *this;
}

template<typename T>
T& List<T>::front() {
    if (empty()) throw std::runtime_error("List is empty");
    return head->data;
}

template<typename T>
const T& List<T>::front() const {
    if (empty()) throw std::runtime_error("List is empty");
    return head->data;
}

template<typename T>
T& List<T>::back() {
    if (empty()) throw std::runtime_error("List is empty");
    return tail->data;
}

template<typename T>
const T& List<T>::back() const {
    if (empty()) throw std::runtime_error("List is empty");
    return tail->data;
}

template<typename T>
List<T>::Iterator::Iterator(Node* node) : current(node) {}

template<typename T>
T& List<T>::Iterator::operator*() {
    if (!current) throw std::runtime_error("Dereferencing end iterator");
    return current->data;
}

template<typename T>
T* List<T>::Iterator::operator->() {
    if (!current) throw std::runtime_error("Accessing member of end iterator");
    return &(current->data);
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    if (current) current = current->next;
    return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

template<typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

template<typename T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(head);
}

template<typename T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(nullptr);
}

template<typename T>
bool List<T>::empty() const {
    return list_size == 0;
}

template<typename T>
size_t List<T>::size() const {
    return list_size;
}

template<typename T>
void List<T>::push_front(const T& value) {
    Node* new_node = new Node(value);
    if (empty()) {
        head = tail = new_node;
    }
    else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    ++list_size;
}

template<typename T>
void List<T>::push_back(const T& value) {
    Node* new_node = new Node(value);
    if (empty()) {
        head = tail = new_node;
    }
    else {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    ++list_size;
}

template<typename T>
void List<T>::pop_front() {
    if (empty()) return;

    Node* temp = head;
    if (head == tail) {
        head = tail = nullptr;
    }
    else {
        head = head->next;
        head->prev = nullptr;
    }
    delete temp;
    --list_size;
}

template<typename T>
void List<T>::pop_back() {
    if (empty()) return;

    Node* temp = tail;
    if (head == tail) {
        head = tail = nullptr;
    }
    else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    --list_size;
}

template<typename T>
typename List<T>::Iterator List<T>::insert(Iterator position, const T& value) {
    if (position == end()) {
        push_back(value);
        return Iterator(tail);
    }

    if (position == begin()) {
        push_front(value);
        return begin();
    }

    Node* current = position.current;
    Node* new_node = new Node(value);

    new_node->prev = current->prev;
    new_node->next = current;
    current->prev->next = new_node;
    current->prev = new_node;

    ++list_size;
    return Iterator(new_node);
}

template<typename T>
typename List<T>::Iterator List<T>::erase(Iterator position) {
    if (position == end()) return end();

    Node* current = position.current;
    Node* next_node = current->next;

    if (current == head) {
        pop_front();
    }
    else if (current == tail) {
        pop_back();
    }
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        --list_size;
    }

    return Iterator(next_node);
}

template<typename T>
void List<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void List<T>::swap(List& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(list_size, other.list_size);
}

template<typename T>
void List<T>::reverse() {
    if (size() <= 1) return;

    Node* current = head;
    while (current != nullptr) {
        std::swap(current->prev, current->next);
        current = current->prev;
    }
    std::swap(head, tail);
}

template<typename T>
void List<T>::unique() {
    if (size() <= 1) return;

    Node* current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->data == current->next->data) {
            Node* to_delete = current->next;
            current->next = to_delete->next;
            if (to_delete->next) {
                to_delete->next->prev = current;
            }
            else {
                tail = current;
            }
            delete to_delete;
            --list_size;
        }
        else {
            current = current->next;
        }
    }
}

template<typename T>
void List<T>::sort() {
    if (size() <= 1) return;

    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        while (current->next != nullptr) {
            if (current->data > current->next->data) {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

#endif