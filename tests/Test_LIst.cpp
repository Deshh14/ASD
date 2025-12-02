#include <gtest/gtest.h>
#include "List.h"
#include <vector>

TEST(ListTest, DefaultConstructorCreatesEmptyList) {
    List<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, PushAndPopWorkCorrectly) {
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_front(0);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.back(), 2);

    list.pop_front();
    EXPECT_EQ(list.front(), 1);

    list.pop_back();
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list.size(), 1);
}

TEST(ListTest, CopyConstructorCreatesIndependentCopy) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2 = list1; 

    list1.push_back(3);
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list2.size(), 2); 
}

TEST(ListTest, ReverseChangesOrder) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.reverse();

    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, ClearRemovesAllElements) {
    List<int> list;

    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }

    EXPECT_EQ(list.size(), 5);
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(IteratorTest, BeginPointsToFirstElement) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    auto it = list.begin();
    EXPECT_EQ(*it, 10);
}

TEST(IteratorTest, IncrementMovesToNextElement) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    auto it = list.begin();
    ++it;
    EXPECT_EQ(*it, 20);

    it++;
    EXPECT_EQ(*it, 30);
}

TEST(IteratorTest, RangeBasedForWorks) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    int sum = 0;
    for (int val : list) {
        sum += val;
    }

    EXPECT_EQ(sum, 6); 
}

TEST(IteratorTest, InsertAndEraseWithIterators) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    auto it = list.begin();
    ++it;
    list.insert(it, 2);

    std::vector<int> expected = { 1, 2, 3 };
    std::vector<int> result;
    for (int val : list) {
        result.push_back(val);
    }
    EXPECT_EQ(result, expected);

    it = list.begin();
    ++it;
    list.erase(it); 

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}