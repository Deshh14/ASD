#include <iostream>
#include <stdexcept>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t size;

public:
    LinkedList();
    LinkedList(const LinkedList& other);
    ~LinkedList();

    LinkedList& operator=(const LinkedList& other);

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_front();
    void pop_back();
    void insert(size_t index, const T& value);
    void erase(size_t index);
    T& at(size_t index);
    const T& at(size_t index) const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void clear();
    bool empty() const;
    size_t get_size() const;
    void print() const;
    bool contains(const T& value) const;
};

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), size(0) {
    Node* current = other.head;
    while (current) {
        push_back(current->data);
        current = current->next;
    }
}

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();
        Node* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }
    return *this;
}

template<typename T>
void LinkedList<T>::push_back(const T& value) {
    Node* newNode = new Node(value);

    if (!head) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

template<typename T>
void LinkedList<T>::push_front(const T& value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
}

template<typename T>
void LinkedList<T>::pop_front() {
    if (!head) {
        throw std::out_of_range("List is empty");
    }

    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
}

template<typename T>
void LinkedList<T>::pop_back() {
    if (!head) {
        throw std::out_of_range("List is empty");
    }

    if (!head->next) {
        delete head;
        head = nullptr;
    }
    else {
        Node* current = head;
        while (current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    size--;
}

template<typename T>
void LinkedList<T>::insert(size_t index, const T& value) {
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }

    if (index == 0) {
        push_front(value);
    }
    else if (index == size) {
        push_back(value);
    }
    else {
        Node* newNode = new Node(value);
        Node* current = head;

        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
}

template<typename T>
void LinkedList<T>::erase(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    if (index == 0) {
        pop_front();
    }
    else {
        Node* current = head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        size--;
    }
}

template<typename T>
T& LinkedList<T>::at(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    Node* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

template<typename T>
const T& LinkedList<T>::at(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    Node* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

template<typename T>
T& LinkedList<T>::operator[](size_t index) {
    return at(index);
}

template<typename T>
const T& LinkedList<T>::operator[](size_t index) const {
    return at(index);
}

template<typename T>
void LinkedList<T>::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

template<typename T>
bool LinkedList<T>::empty() const {
    return size == 0;
}

template<typename T>
size_t LinkedList<T>::get_size() const {
    return size;
}

template<typename T>
void LinkedList<T>::print() const {
    Node* current = head;
    while (current) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

template<typename T>
bool LinkedList<T>::contains(const T& value) const {
    Node* current = head;
    while (current) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}