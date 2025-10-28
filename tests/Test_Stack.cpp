#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "Stack.h"

TEST(ArrayStackTest, DefaultConstructor) {
    ArrayStack<int> stack;
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);
    EXPECT_FALSE(stack.isFull());
}

TEST(ArrayStackTest, InitializerListConstructor) {
    ArrayStack<int> stack = { 1, 2, 3, 4, 5 };
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 5);
    EXPECT_EQ(stack.top(), 5);
}


TEST(ArrayStackTest, InitializerListConstructorExactCapacity) {
    ArrayStack<int, 3> stack = { 1, 2, 3 };
    EXPECT_NO_THROW(stack);

    EXPECT_EQ(stack.size(), 3);
    EXPECT_TRUE(stack.isFull());
}

TEST(ArrayStackTest, CopyConstructor) {
    ArrayStack<int> original = { 1, 2, 3 };
    ArrayStack<int> copy(original);

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.top(), copy.top());
    EXPECT_TRUE(original == copy);
}

TEST(ArrayStackTest, AssignmentOperator) {
    ArrayStack<int> original = { 1, 2, 3 };
    ArrayStack<int> copy;
    copy = original;

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.top(), copy.top());
    EXPECT_TRUE(original == copy);
}

TEST(ArrayStackTest, SelfAssignment) {
    ArrayStack<int> stack = { 1, 2, 3 };
    stack = stack;

    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top(), 3);
}


TEST(ArrayStackTest, PushAndPop) {
    ArrayStack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top(), 3);

    EXPECT_EQ(stack.pop(), 3);
    EXPECT_EQ(stack.pop(), 2);
    EXPECT_EQ(stack.pop(), 1);
    EXPECT_TRUE(stack.isEmpty());
}

TEST(ArrayStackTest, PushRvalue) {
    ArrayStack<std::string> stack;

    stack.push(std::string("hello"));
    stack.push(std::string("world"));

    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), "world");
}

TEST(ArrayStackTest, PopThrowsWhenEmpty) {
    ArrayStack<int> stack;
    EXPECT_THROW(stack.pop(), std::underflow_error);
}

TEST(ArrayStackTest, TopThrowsWhenEmpty) {
    ArrayStack<int> stack;
    EXPECT_THROW(stack.top(), std::underflow_error);
}

TEST(ArrayStackTest, PushThrowsWhenFull) {
    ArrayStack<int, 2> stack;

    stack.push(1);
    stack.push(2);

    EXPECT_THROW(stack.push(3), std::overflow_error);
}


TEST(ArrayStackTest, AtMethod) {
    ArrayStack<int> stack = { 10, 20, 30 };

    EXPECT_EQ(stack.at(0), 30);
    EXPECT_EQ(stack.at(1), 20);
    EXPECT_EQ(stack.at(2), 10);
}

TEST(ArrayStackTest, AtMethodThrowsWhenOutOfRange) {
    ArrayStack<int> stack = { 1, 2, 3 };

    EXPECT_THROW(stack.at(-1), std::out_of_range);
    EXPECT_THROW(stack.at(3), std::out_of_range);
}

TEST(ArrayStackTest, OperatorBrackets) {
    ArrayStack<int> stack = { 10, 20, 30 };

    EXPECT_EQ(stack[0], 30);
    EXPECT_EQ(stack[1], 20);
    EXPECT_EQ(stack[2], 10);
}

TEST(ArrayStackTest, ConstAtMethod) {
    const ArrayStack<int> stack = { 1, 2, 3 };

    EXPECT_EQ(stack.at(0), 3);
    EXPECT_EQ(stack.at(1), 2);
    EXPECT_EQ(stack.at(2), 1);
}


TEST(ArrayStackTest, IsEmptyAndIsFull) {
    ArrayStack<int, 3> stack;

    EXPECT_TRUE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());

    stack.push(1);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());

    stack.push(2);
    stack.push(3);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_TRUE(stack.isFull());
}

TEST(ArrayStackTest, SizeAndCapacity) {
    ArrayStack<int, 5> stack;

    EXPECT_EQ(stack.size(), 0);
    EXPECT_EQ(stack.capacity(), 5);

    stack.push(1);
    stack.push(2);

    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.capacity(), 5);
}

TEST(ArrayStackTest, Clear) {
    ArrayStack<int> stack = { 1, 2, 3, 4, 5 };

    EXPECT_FALSE(stack.isEmpty());
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(ArrayStackTest, Find) {
    ArrayStack<int> stack = { 1, 2, 3, 2, 1 };

    EXPECT_EQ(stack.find(3), 2);
    EXPECT_EQ(stack.find(2), 1);
    EXPECT_EQ(stack.find(1), 0);
    EXPECT_EQ(stack.find(5), -1);
}


TEST(ArrayStackTest, MinElement) {
    ArrayStack<int> stack = { 5, 2, 8, 1, 9 };

    EXPECT_EQ(stack.minElement(), 1);
}

TEST(ArrayStackTest, MaxElement) {
    ArrayStack<int> stack = { 5, 2, 8, 1, 9 };

    EXPECT_EQ(stack.maxElement(), 9);
}

TEST(ArrayStackTest, MinElementThrowsWhenEmpty) {
    ArrayStack<int> stack;
    EXPECT_THROW(stack.minElement(), std::underflow_error);
}

TEST(ArrayStackTest, MaxElementThrowsWhenEmpty) {
    ArrayStack<int> stack;
    EXPECT_THROW(stack.maxElement(), std::underflow_error);
}

TEST(ArrayStackTest, MinMaxWithStrings) {
    ArrayStack<std::string> stack = { "banana", "apple", "cherry" };

    EXPECT_EQ(stack.minElement(), "apple");
    EXPECT_EQ(stack.maxElement(), "cherry");
}

TEST(ArrayStackTest, EqualityOperator) {
    ArrayStack<int> stack1 = { 1, 2, 3 };
    ArrayStack<int> stack2 = { 1, 2, 3 };
    ArrayStack<int> stack3 = { 1, 2, 4 };
    ArrayStack<int> stack4 = { 1, 2 };

    EXPECT_TRUE(stack1 == stack2);
    EXPECT_FALSE(stack1 == stack3);
    EXPECT_FALSE(stack1 == stack4);
}

TEST(ArrayStackTest, InequalityOperator) {
    ArrayStack<int> stack1 = { 1, 2, 3 };
    ArrayStack<int> stack2 = { 1, 2, 3 };
    ArrayStack<int> stack3 = { 1, 2, 4 };

    EXPECT_FALSE(stack1 != stack2);
    EXPECT_TRUE(stack1 != stack3);
}

TEST(ArrayStackTest, OutputStreamOperator) {
    ArrayStack<int> stack = { 1, 2, 3 };
    std::ostringstream oss;

    oss << stack;

    std::string result = oss.str();
    EXPECT_TRUE(result.find("3 <- 2 <- 1") != std::string::npos);
}

TEST(ArrayStackTest, OutputStreamOperatorEmpty) {
    ArrayStack<int> stack;
    std::ostringstream oss;

    oss << stack;

    std::string result = oss.str();
    EXPECT_TRUE(result.find("empty") != std::string::npos);
}

TEST(ArrayStackTest, BoundaryConditions) {
    ArrayStack<int, 1> stack;

    EXPECT_TRUE(stack.isEmpty());
    stack.push(42);
    EXPECT_TRUE(stack.isFull());
    EXPECT_EQ(stack.top(), 42);
    EXPECT_THROW(stack.push(43), std::overflow_error);

    EXPECT_EQ(stack.pop(), 42);
    EXPECT_TRUE(stack.isEmpty());
}

TEST(ArrayStackTest, LargeNumberOfElements) {
    ArrayStack<int, 1000> stack;

    for (int i = 0; i < 1000; ++i) {
        stack.push(i);
    }

    EXPECT_TRUE(stack.isFull());
    EXPECT_EQ(stack.size(), 1000);
    EXPECT_EQ(stack.top(), 999);

    for (int i = 999; i >= 0; --i) {
        EXPECT_EQ(stack.pop(), i);
    }

    EXPECT_TRUE(stack.isEmpty());
}

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

TEST(ArrayStackTest, CustomType) {
    ArrayStack<Point> stack;

    stack.push({ 1, 2 });
    stack.push({ 3, 4 });
    stack.push({ 5, 6 });

    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top(), (Point{ 5, 6 }));
    EXPECT_EQ(stack.minElement(), (Point{ 1, 2 }));
}

TEST(ArrayStackTest, MoveSemantics) {
    ArrayStack<std::string> stack;
    std::string str = "test";

    stack.push(std::move(str));

    EXPECT_TRUE(str.empty());
    EXPECT_EQ(stack.top(), "test");
}
