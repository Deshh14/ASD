#include "LQueue.h"
#include <gtest/gtest.h>
#include <string>

// Тест 1: Конструктор по умолчанию и empty
TEST(LQueueTest, DefaultConstructor) {
    LQueue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

// Тест 2: Push и front/back
TEST(LQueueTest, PushAndAccess) {
    LQueue<int> q;
    q.push(10);
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 10);

    q.push(20);
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.front(), 10);  // Первый элемент остается
    EXPECT_EQ(q.back(), 20);   // Последний элемент обновился
}

// Тест 3: Pop
TEST(LQueueTest, Pop) {
    LQueue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    EXPECT_EQ(q.front(), 10);
    q.pop();
    EXPECT_EQ(q.front(), 20);
    EXPECT_EQ(q.size(), 2);

    q.pop();
    EXPECT_EQ(q.front(), 30);
    EXPECT_EQ(q.size(), 1);

    q.pop();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

// Тест 4: Pop из пустой очереди
TEST(LQueueTest, PopEmptyLQueue) {
    LQueue<int> q;
    EXPECT_THROW(q.pop(), std::runtime_error);
}

// Тест 5: Front/back на пустой очереди
TEST(LQueueTest, AccessEmptyLQueue) {
    LQueue<int> q;
    EXPECT_THROW(q.front(), std::runtime_error);
    EXPECT_THROW(q.back(), std::runtime_error);

    const LQueue<int>& const_q = q;
    EXPECT_THROW(const_q.front(), std::runtime_error);
    EXPECT_THROW(const_q.back(), std::runtime_error);
}

// Тест 6: Конструктор копирования
TEST(LQueueTest, CopyConstructor) {
    LQueue<int> q1;
    q1.push(10);
    q1.push(20);
    q1.push(30);

    LQueue<int> q2 = q1;  // Конструктор копирования
    EXPECT_EQ(q1.size(), 3);
    EXPECT_EQ(q2.size(), 3);

    // Проверяем, что это глубокие копии
    q1.pop();
    EXPECT_EQ(q1.size(), 2);
    EXPECT_EQ(q2.size(), 3);  // q2 не изменилась

    EXPECT_EQ(q2.front(), 10);
    q2.pop();
    EXPECT_EQ(q2.front(), 20);
}

// Тест 7: Оператор присваивания
TEST(LQueueTest, AssignmentOperator) {
    LQueue<int> q1;
    q1.push(100);
    q1.push(200);

    LQueue<int> q2;
    q2.push(300);

    q2 = q1;  // Оператор присваивания

    EXPECT_EQ(q1.size(), 2);
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), 100);

    // Проверяем глубокое копирование
    q1.pop();
    EXPECT_EQ(q1.front(), 200);
    EXPECT_EQ(q2.front(), 100);  // q2 не изменилась

    // Самоприсваивание
    q2 = q2;
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), 100);
}

// Тест 8: Swap
TEST(LQueueTest, Swap) {
    LQueue<int> q1;
    q1.push(1);
    q1.push(2);

    LQueue<int> q2;
    q2.push(3);
    q2.push(4);
    q2.push(5);

    q1.swap(q2);

    EXPECT_EQ(q1.size(), 3);
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q1.front(), 3);
    EXPECT_EQ(q2.front(), 1);
}

// Тест 9: Clear
TEST(LQueueTest, Clear) {
    LQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.size(), 3);
    q.clear();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);

    // Можно снова использовать после clear
    q.push(4);
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 4);
}

// Тест 10: GetCapacity
TEST(LQueueTest, GetCapacity) {
    LQueue<int> q;
    EXPECT_EQ(q.getCapacity(), 0);

    q.push(1);
    EXPECT_EQ(q.getCapacity(), 1);  // Для списка capacity = size

    q.push(2);
    q.push(3);
    EXPECT_EQ(q.getCapacity(), 3);

    q.pop();
    EXPECT_EQ(q.getCapacity(), 2);
}

// Тест 11: Строки
TEST(LQueueTest, StringLQueue) {
    LQueue<std::string> q;

    q.push("hello");
    q.push("world");
    q.push("test");

    EXPECT_EQ(q.front(), "hello");
    EXPECT_EQ(q.back(), "test");
    EXPECT_EQ(q.size(), 3);

    q.pop();
    EXPECT_EQ(q.front(), "world");
    EXPECT_EQ(q.size(), 2);
}

// Тест 12: Много элементов
TEST(LQueueTest, ManyElements) {
    LQueue<int> q;
    const int N = 1000;

    for (int i = 0; i < N; ++i) {
        q.push(i);
        EXPECT_EQ(q.back(), i);
        EXPECT_EQ(q.size(), i + 1);
    }

    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(q.front(), i);
        q.pop();
        EXPECT_EQ(q.size(), N - i - 1);
    }

    EXPECT_TRUE(q.empty());
}

// Тест 13: Константная очередь
TEST(LQueueTest, ConstLQueue) {
    LQueue<int> q;
    q.push(42);
    q.push(84);

    const LQueue<int>& const_q = q;

    EXPECT_FALSE(const_q.empty());
    EXPECT_EQ(const_q.size(), 2);
    EXPECT_EQ(const_q.front(), 42);
    EXPECT_EQ(const_q.back(), 84);
}
