#include <gtest/gtest.h>
#include "LStack.h"
#include <string>
#include <vector>

TEST(StackTest, DefaultConstructor) {
    Stack<int> stack;
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, InitializerListConstructor) {
    Stack<int> stack{ 1, 2, 3, 4, 5 };
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 5);
    EXPECT_EQ(stack.top(), 5);
}

TEST(StackTest, PushAndTop) {
    Stack<int> stack;

    stack.push(1);
    EXPECT_EQ(stack.top(), 1);
    EXPECT_EQ(stack.size(), 1);

    stack.push(2);
    EXPECT_EQ(stack.top(), 2);
    EXPECT_EQ(stack.size(), 2);

    stack.push(3);
    EXPECT_EQ(stack.top(), 3);
    EXPECT_EQ(stack.size(), 3);
}

TEST(StackTest, Pop) {
    Stack<int> stack{ 1, 2, 3 };

    EXPECT_EQ(stack.top(), 3);
    stack.pop();
    EXPECT_EQ(stack.top(), 2);
    EXPECT_EQ(stack.size(), 2);

    stack.pop();
    EXPECT_EQ(stack.top(), 1);
    EXPECT_EQ(stack.size(), 1);

    stack.pop();
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, PopEmptyStack) {
    Stack<int> stack;
    EXPECT_THROW(stack.pop(), std::underflow_error);
}

TEST(StackTest, TopEmptyStack) {
    Stack<int> stack;
    EXPECT_THROW(stack.top(), std::underflow_error);

    const Stack<int> constStack;
    EXPECT_THROW(constStack.top(), std::underflow_error);
}

TEST(StackTest, CopyConstructor) {
    Stack<int> original{ 1, 2, 3 };
    Stack<int> copy(original);

    EXPECT_EQ(original.size(), 3);
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(original.top(), 3);
    EXPECT_EQ(copy.top(), 3);

    original.push(4);
    EXPECT_EQ(original.size(), 4);
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(original.top(), 4);
    EXPECT_EQ(copy.top(), 3);
}

TEST(StackTest, CopyAssignment) {
    Stack<int> original{ 1, 2, 3 };
    Stack<int> copy;
    copy = original;

    EXPECT_EQ(original.size(), 3);
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(original.top(), 3);
    EXPECT_EQ(copy.top(), 3);

    copy = copy;
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.top(), 3);
}

TEST(StackTest, EmptyAndSize) {
    Stack<int> stack;
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);

    stack.push(1);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 1);

    stack.push(2);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 2);

    stack.pop();
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 1);

    stack.pop();
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, Clear) {
    Stack<int> stack{ 1, 2, 3, 4, 5 };
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 5);

    stack.clear();
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);

    stack.push(10);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.top(), 10);
}

TEST(StackTest, Swap) {
    Stack<int> stack1{ 1, 2, 3 };
    Stack<int> stack2{ 4, 5 };

    stack1.swap(stack2);

    EXPECT_EQ(stack1.size(), 2);
    EXPECT_EQ(stack1.top(), 5);
    EXPECT_EQ(stack2.size(), 3);
    EXPECT_EQ(stack2.top(), 3);
}

TEST(StackTest, EqualityOperator) {
    Stack<int> stack1{ 1, 2, 3 };
    Stack<int> stack2{ 1, 2, 3 };
    Stack<int> stack3{ 1, 2 };
    Stack<int> stack4{ 1, 2, 4 };

    EXPECT_TRUE(stack1 == stack2);
    EXPECT_FALSE(stack1 == stack3);
    EXPECT_FALSE(stack1 == stack4);
    EXPECT_TRUE(stack1 != stack3);
    EXPECT_TRUE(stack1 != stack4);
}

TEST(StackTest, Emplace) {
    Stack<std::string> stack;

    stack.emplace("hello");
    EXPECT_EQ(stack.top(), "hello");

    stack.emplace(5, 'a'); 
    EXPECT_EQ(stack.top(), "aaaaa");

    stack.emplace("world");
    EXPECT_EQ(stack.top(), "world");
}

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

TEST(StackTest, CustomType) {
    Stack<Point> stack;

    stack.emplace(1, 2);
    stack.emplace(3, 4);

    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), Point(3, 4));

    stack.pop();
    EXPECT_EQ(stack.top(), Point(1, 2));
}

TEST(StackTest, OutputOperator) {
    Stack<int> stack{ 1, 2, 3 };
    std::stringstream ss;
    ss << stack;

    std::string result = ss.str();
    EXPECT_TRUE(result.find("Stack (top to bottom)") != std::string::npos);
    EXPECT_TRUE(result.find("1") != std::string::npos);
    EXPECT_TRUE(result.find("2") != std::string::npos);
    EXPECT_TRUE(result.find("3") != std::string::npos);
}

TEST(StackTest, OutputOperatorEmpty) {
    Stack<int> stack;
    std::stringstream ss;
    ss << stack;

    EXPECT_TRUE(ss.str().find("empty") != std::string::npos);
}

TEST(StackTest, StressTest) {
    Stack<int> stack;
    const int COUNT = 1000;

    for (int i = 0; i < COUNT; ++i) {
        stack.push(i);
        EXPECT_EQ(stack.top(), i);
    }

    EXPECT_EQ(stack.size(), COUNT);

    for (int i = COUNT - 1; i >= 0; --i) {
        EXPECT_EQ(stack.top(), i);
        stack.pop();
    }

    EXPECT_TRUE(stack.empty());
}
