#include "list.h"

template<typename T>
bool checkListCycleTurtleAndRabbit(const typename List<T>::Iterator& start) {
    if (start == typename List<T>::Iterator(nullptr)) {
        return false;
    }

    auto turtle = start;
    auto rabbit = start;

    while (rabbit != typename List<T>::Iterator(nullptr)) {
        // Двигаем черепаху на 1 шаг
        auto turtle_next = turtle;
        ++turtle_next;

        // Двигаем зайца на 2 шага
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

template<typename T>
bool checkListCyclePointer(const typename List<T>::Iterator& start) {
    if (start == typename List<T>::Iterator(nullptr)) {
        return false;
    }

    // Для алгоритма с изменением указателей нам нужен доступ к узлам
    // В текущей реализации List нет публичных методов для работы с указателями на Node
    // Поэтому этот метод не может быть корректно реализован без изменения класса List

    return false; // Заглушка - требуется доработка архитектуры
}

template<typename T>
typename List<T>::Iterator FindProblemNode(const typename List<T>::Iterator& start) {
    // Проверяем есть ли цикл
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

    // Находим начало цикла
    turtle = start;

    while (turtle != rabbit) {
        auto turtle_next = turtle;
        ++turtle_next;

        auto rabbit_next = rabbit;
        ++rabbit_next;

        turtle = turtle_next;
        rabbit = rabbit_next;
    }

    // Возвращаем итератор на узел, который является началом цикла
    return turtle;
}