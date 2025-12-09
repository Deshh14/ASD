#include "list.h"

template<typename T>
bool checkListCycleTurtleAndRabbit(const typename List<T>::Iterator& start) {
    if (start == typename List<T>::Iterator(nullptr)) {
        return false;
    }

    auto turtle = start;
    auto rabbit = start;

    while (rabbit != typename List<T>::Iterator(nullptr)) {
        auto turtle_next = turtle;
        ++turtle_next;

        auto rabbit_next = rabbit;
        ++rabbit_next;
        if (rabbit_next == typename List<T>::Iterator(nullptr)) {
            return false;
        }
        ++rabbit_next;

        turtle = turtle_next;
        rabbit = rabbit_next;

        if (turtle == rabbit) {
            return true;
        }
    }

    return false;
}
/*
template <typename T>
bool checkListCyclePointer(Node<T>* head) {
    if (head == nullptr || head->_next == nullptr) {
        return false;
    }

    Node<T>* current = head;    
    Node<T>* prev = nullptr;      
    Node<T>* next = nullptr;      
    Node<T>* first = head;        
    bool has_cycle = false;       

    while (current != nullptr) {
        next = current->_next;

        current->_next = prev;

        if (next == first) {
            has_cycle = true;
            break;
        }

        prev = current;
        current = next;
    }


    if (has_cycle) {
        // current указывает на узел перед началом цикла
        // prev указывает на последний обработанный узел

        // Восстанавливаем от prev до начала
        Node<T>* restore_curr = prev;
        Node<T>* restore_prev = nullptr;

        while (restore_curr != nullptr && restore_curr != current) {
            Node<T>* temp = restore_curr->_next;
            restore_curr->_next = restore_prev;
            restore_prev = restore_curr;
            restore_curr = temp;
        }

        // Восстанавливаем связь с current
        if (current != nullptr) {
            current->_next = restore_prev;
        }
    }
    // Если цикла не было - полностью развернули список, нужно восстановить
    else {
        // prev теперь указывает на последний узел развернутого списка
        current = prev;
        prev = nullptr;

        // Разворачиваем список обратно
        while (current != nullptr) {
            next = current->_next;
            current->_next = prev;
            prev = current;
            current = next;
        }
    }

    return has_cycle;
}
*/
template<typename T>
typename List<T>::Iterator FindProblemNode(const typename List<T>::Iterator& start) {

    auto turtle = start;
    auto rabbit = start;
    bool has_cycle = false;

    while (rabbit != typename List<T>::Iterator(nullptr)) {
        auto turtle_next = turtle;
        ++turtle_next;

        auto rabbit_next = rabbit;
        ++rabbit_next;
        if (rabbit_next == typename List<T>::Iterator(nullptr)) {
            break;
        }
        ++rabbit_next;

        turtle = turtle_next;
        rabbit = rabbit_next;

        if (turtle == rabbit) {
            has_cycle = true;
            break;
        }
    }

    if (!has_cycle) {
        return typename List<T>::Iterator(nullptr);
    }

    turtle = start;

    while (turtle != rabbit) {
        auto turtle_next = turtle;
        ++turtle_next;

        auto rabbit_next = rabbit;
        ++rabbit_next;

        turtle = turtle_next;
        rabbit = rabbit_next;
    }


    return turtle;
}