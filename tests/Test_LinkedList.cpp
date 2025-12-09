#include <gtest/gtest.h>
#include "LinkedList.h"

TEST(LinkedListTest, DefaultConstructor) {
    LinkedList<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.get_size(), 0);
}

TEST(LinkedListTest, CopyConstructor) {
    LinkedList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    LinkedList<int> list2(list1);

    EXPECT_EQ(list2.get_size(), 3);
    EXPECT_EQ(list2[0], 1);
    EXPECT_EQ(list2[1], 2);
    EXPECT_EQ(list2[2], 3);

    list1.push_back(4);
    EXPECT_EQ(list1.get_size(), 4);
    EXPECT_EQ(list2.get_size(), 3);
}

TEST(LinkedListTest, AssignmentOperator) {
    LinkedList<int> list1;
    list1.push_back(10);
    list1.push_back(20);

    LinkedList<int> list2;
    list2 = list1;

    EXPECT_EQ(list2.get_size(), 2);
    EXPECT_EQ(list2[0], 10);
    EXPECT_EQ(list2[1], 20);

    list2 = list2;
    EXPECT_EQ(list2.get_size(), 2);
    EXPECT_EQ(list2[0], 10);
}

TEST(LinkedListTest, PushBack) {
    LinkedList<int> list;

    list.push_back(1);
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list[0], 1);

    list.push_back(2);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
}

TEST(LinkedListTest, PushBackMultiple) {
    LinkedList<int> list;

    for (int i = 0; i < 100; ++i) {
        list.push_back(i);
        EXPECT_EQ(list.get_size(), i + 1);
        EXPECT_EQ(list[i], i);
    }
}

TEST(LinkedListTest, PushFront) {
    LinkedList<int> list;

    list.push_front(1);
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list[0], 1);
}

TEST(LinkedListTest, PopFront) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list[0], 2);
    EXPECT_EQ(list[1], 3);
}

TEST(LinkedListTest, PopBack) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
}

TEST(LinkedListTest, PopBackSingleElement) {
    LinkedList<int> list;
    list.push_back(42);
    list.pop_back();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.get_size(), 0);
}

TEST(LinkedListTest, Insert) {
    LinkedList<int> list;
    list.push_back(2);
    list.push_back(3);

    list.insert(0, 1);
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
}

TEST(LinkedListTest, InsertIntoEmptyList) {
    LinkedList<int> list;
    list.insert(0, 42);
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list[0], 42);
}

TEST(LinkedListTest, EraseAllElements) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(0);
    list.erase(0);
    list.erase(0);

    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.get_size(), 0);
}

TEST(LinkedListTest, AtMethod) {
    LinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    EXPECT_EQ(list.at(0), 10);
    EXPECT_EQ(list.at(1), 20);
    EXPECT_EQ(list.at(2), 30);

    list.at(1) = 25;
    EXPECT_EQ(list.at(1), 25);

    EXPECT_THROW(list.at(3), std::out_of_range);
    EXPECT_THROW(list.at(10), std::out_of_range);
}


TEST(LinkedListTest, OperatorBrackets) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);

    list[1] = 99;
    EXPECT_EQ(list[1], 99);

    list[0] = list[1] = 100;
    EXPECT_EQ(list[0], 100);
    EXPECT_EQ(list[1], 100);
}

TEST(LinkedListTest, Contains) {
    LinkedList<int> list;

    EXPECT_FALSE(list.contains(42));

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(20));
    EXPECT_TRUE(list.contains(30));
    EXPECT_FALSE(list.contains(40));
    EXPECT_FALSE(list.contains(0));

    list.push_back(20); 
    EXPECT_TRUE(list.contains(20));
}

TEST(LinkedListTest, StringType) {
    LinkedList<std::string> list;

    list.push_back("hello");
    list.push_back("world");
    list.push_back("!");

    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list[0], "hello");
    EXPECT_EQ(list[1], "world");
    EXPECT_EQ(list[2], "!");

    list[1] = "everyone";
    EXPECT_EQ(list[1], "everyone");

    EXPECT_TRUE(list.contains("hello"));
    EXPECT_FALSE(list.contains("test"));
}

TEST(LinkedListIteratorTest, IterateThroughElements) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }

    EXPECT_EQ(sum, 6); 
}

TEST(LinkedListIteratorTest, ModifyElementsThroughIterator) {
    LinkedList<int> list;
    list.push_back(5);
    list.push_back(10);

    for (auto it = list.begin(); it != list.end(); ++it) {
        *it = *it * 2;
    }

    EXPECT_EQ(list.at(0), 10); 
    EXPECT_EQ(list.at(1), 20);
}