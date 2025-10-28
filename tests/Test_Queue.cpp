#include <gtest/gtest.h>
#include "queue.h" // предполагая, что ваш класс находится в queue.h
#include <string>

// Тест конструктора по умолчанию
TEST(QueueTest, DefaultConstructor) {
    Queue<int> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_GE(queue.getCapacity(), 10);
}

// Тест push и size
TEST(QueueTest, PushAndSize) {
    Queue<int> queue;

    queue.push(1);
    EXPECT_EQ(queue.size(), 1);
    EXPECT_FALSE(queue.empty());

    queue.push(2);
    EXPECT_EQ(queue.size(), 2);

    queue.push(3);
    EXPECT_EQ(queue.size(), 3);
}

// Тест front и back
TEST(QueueTest, FrontAndBack) {
    Queue<int> queue;

    queue.push(10);
    queue.push(20);
    queue.push(30);

    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 30);

    // Проверка константных версий
    const Queue<int>& const_queue = queue;
    EXPECT_EQ(const_queue.front(), 10);
    EXPECT_EQ(const_queue.back(), 30);
}

// Тест pop
TEST(QueueTest, Pop) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    queue.pop();
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.size(), 2);

    queue.pop();
    EXPECT_EQ(queue.front(), 3);
    EXPECT_EQ(queue.size(), 1);

    queue.pop();
    EXPECT_TRUE(queue.empty());
}

// Тест исключений при пустой очереди
TEST(QueueTest, EmptyQueueExceptions) {
    Queue<int> queue;

    EXPECT_THROW(queue.front(), std::runtime_error);
    EXPECT_THROW(queue.back(), std::runtime_error);
    EXPECT_THROW(queue.pop(), std::runtime_error);

    const Queue<int> const_queue;
    EXPECT_THROW(const_queue.front(), std::runtime_error);
    EXPECT_THROW(const_queue.back(), std::runtime_error);
}

// Тест копирующего конструктора
TEST(QueueTest, CopyConstructor) {
    Queue<int> original;
    original.push(1);
    original.push(2);
    original.push(3);

    Queue<int> copy(original);

    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy.front(), original.front());
    EXPECT_EQ(copy.back(), original.back());

    // Изменение оригинала не должно влиять на копию
    original.pop();
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(original.size(), 2);
}

// Тест оператора присваивания
TEST(QueueTest, AssignmentOperator) {
    Queue<int> original;
    original.push(1);
    original.push(2);
    original.push(3);

    Queue<int> assigned;
    assigned.push(10);
    assigned = original;

    EXPECT_EQ(assigned.size(), original.size());
    EXPECT_EQ(assigned.front(), original.front());
    EXPECT_EQ(assigned.back(), original.back());

    // Самоприсваивание
    assigned = assigned;
    EXPECT_EQ(assigned.size(), 3);
    EXPECT_EQ(assigned.front(), 1);
}

// Тест очистки
TEST(QueueTest, Clear) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_FALSE(queue.empty());
    queue.clear();
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

// Тест обмена
TEST(QueueTest, Swap) {
    Queue<int> queue1;
    queue1.push(1);
    queue1.push(2);

    Queue<int> queue2;
    queue2.push(10);
    queue2.push(20);
    queue2.push(30);

    size_t size1 = queue1.size();
    size_t size2 = queue2.size();

    queue1.swap(queue2);

    EXPECT_EQ(queue1.size(), size2);
    EXPECT_EQ(queue2.size(), size1);
    EXPECT_EQ(queue1.front(), 10);
    EXPECT_EQ(queue2.front(), 1);
}

// Тест автоматического расширения
TEST(QueueTest, Resize) {
    Queue<int> queue;
    size_t initial_capacity = queue.getCapacity();

    // Добавляем больше элементов, чем начальная емкость
    for (int i = 0; i < 20; ++i) {
        queue.push(i);
    }

    EXPECT_GT(queue.getCapacity(), initial_capacity);
    EXPECT_EQ(queue.size(), 20);
    EXPECT_EQ(queue.front(), 0);
    EXPECT_EQ(queue.back(), 19);
}

// Тест с различными типами данных
TEST(QueueTest, DifferentDataTypes) {
    // Тест с int
    Queue<int> int_queue;
    int_queue.push(42);
    EXPECT_EQ(int_queue.front(), 42);

    // Тест с double
    Queue<double> double_queue;
    double_queue.push(3.14);
    EXPECT_DOUBLE_EQ(double_queue.front(), 3.14);

    // Тест с string
    Queue<std::string> string_queue;
    string_queue.push("hello");
    string_queue.push("world");
    EXPECT_EQ(string_queue.front(), "hello");
    EXPECT_EQ(string_queue.back(), "world");

    // Тест с char
    Queue<char> char_queue;
    char_queue.push('A');
    char_queue.push('B');
    EXPECT_EQ(char_queue.front(), 'A');
    EXPECT_EQ(char_queue.back(), 'B');
}

// Тест циклического буфера
TEST(QueueTest, CircularBuffer) {
    Queue<int> queue;

    // Заполняем очередь
    for (int i = 0; i < 5; ++i) {
        queue.push(i);
    }

    // Удаляем несколько элементов
    queue.pop(); // удаляем 0
    queue.pop(); // удаляем 1

    // Добавляем новые элементы - они должны использовать освободившееся место
    queue.push(5);
    queue.push(6);

    // Проверяем порядок элементов
    EXPECT_EQ(queue.front(), 2);
    queue.pop();
    EXPECT_EQ(queue.front(), 3);
    queue.pop();
    EXPECT_EQ(queue.front(), 4);
    queue.pop();
    EXPECT_EQ(queue.front(), 5);
    queue.pop();
    EXPECT_EQ(queue.front(), 6);
}

// Стресс-тест
TEST(QueueTest, StressTest) {
    Queue<int> queue;
    const int NUM_ELEMENTS = 1000;

    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        queue.push(i);
    }

    EXPECT_EQ(queue.size(), NUM_ELEMENTS);

    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        EXPECT_EQ(queue.front(), i);
        queue.pop();
    }

    EXPECT_TRUE(queue.empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}