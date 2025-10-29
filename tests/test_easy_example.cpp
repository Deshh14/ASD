// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_easy_example/easy_example.h"

#define EPSILON 0.000001

TEST(TestEasyExampleLib, can_div) {
  // Arrange
  int x = 10;
  int y = 2;

  // Act & Assert
  ASSERT_NO_THROW(division(x, y));
}

TEST(TestEasyExampleLib, can_div_correctly) {
    // Arrange
    int x = 6;
    int y = 2;

    // Act
    int actual_result = division(x, y);

    // Assert
    int expected_result = 3;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestEasyExampleLib, can_div_correctly_with_remainder) {
    // Arrange
    int x = 5;
    int y = 4;

    // Act
    float actual_result = division(x, y);

    // Assert
    float expected_result = 1.25;
    EXPECT_NEAR(expected_result, actual_result, EPSILON);
}

TEST(TestEasyExampleLib, throw_when_try_div_by_zero) {
  // Arrange
  int x = 10;
  int y = 0;

  // Act & Assert
  ASSERT_ANY_THROW(division(x, y));
}



#include <gtest/gtest.h>
#include "queue.h" 
#include <string>

TEST(QueueTest, DefaultConstructor) {
    Queue<int> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_GE(queue.getCapacity(), 10);
}

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

TEST(QueueTest, FrontAndBack) {
    Queue<int> queue;

    queue.push(10);
    queue.push(20);
    queue.push(30);

    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 30);

    const Queue<int>& const_queue = queue;
    EXPECT_EQ(const_queue.front(), 10);
    EXPECT_EQ(const_queue.back(), 30);
}

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

TEST(QueueTest, EmptyQueueExceptions) {
    Queue<int> queue;

    EXPECT_THROW(queue.front(), std::runtime_error);
    EXPECT_THROW(queue.back(), std::runtime_error);
    EXPECT_THROW(queue.pop(), std::runtime_error);

    const Queue<int> const_queue;
    EXPECT_THROW(const_queue.front(), std::runtime_error);
    EXPECT_THROW(const_queue.back(), std::runtime_error);
}

TEST(QueueTest, CopyConstructor) {
    Queue<int> original;
    original.push(1);
    original.push(2);
    original.push(3);

    Queue<int> copy(original);

    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy.front(), original.front());
    EXPECT_EQ(copy.back(), original.back());

    original.pop();
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(original.size(), 2);
}

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

    assigned = assigned;
    EXPECT_EQ(assigned.size(), 3);
    EXPECT_EQ(assigned.front(), 1);
}

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

TEST(QueueTest, Resize) {
    Queue<int> queue;
    size_t initial_capacity = queue.getCapacity();

    for (int i = 0; i < 20; ++i) {
        queue.push(i);
    }

    EXPECT_GT(queue.getCapacity(), initial_capacity);
    EXPECT_EQ(queue.size(), 20);
    EXPECT_EQ(queue.front(), 0);
    EXPECT_EQ(queue.back(), 19);
}

TEST(QueueTest, DifferentDataTypes) {
    Queue<int> int_queue;
    int_queue.push(42);
    EXPECT_EQ(int_queue.front(), 42);

    Queue<double> double_queue;
    double_queue.push(3.14);
    EXPECT_DOUBLE_EQ(double_queue.front(), 3.14);

    Queue<std::string> string_queue;
    string_queue.push("hello");
    string_queue.push("world");
    EXPECT_EQ(string_queue.front(), "hello");
    EXPECT_EQ(string_queue.back(), "world");

    Queue<char> char_queue;
    char_queue.push('A');
    char_queue.push('B');
    EXPECT_EQ(char_queue.front(), 'A');
    EXPECT_EQ(char_queue.back(), 'B');
}

TEST(QueueTest, CircularBuffer) {
    Queue<int> queue;

    for (int i = 0; i < 5; ++i) {
        queue.push(i);
    }

    queue.pop();
    queue.pop();

    queue.push(5);
    queue.push(6);

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