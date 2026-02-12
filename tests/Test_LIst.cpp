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
// Тест 1: Чтение из пустого списка
TEST(ListIteratorTest, EmptyListIteration) {
    List<int> list;

    EXPECT_EQ(list.begin(), list.end());

    auto it = list.end();
    EXPECT_THROW(*it, std::runtime_error);
    EXPECT_THROW(it.operator->(), std::runtime_error);

    auto it2 = list.end();
    ++it2;
    EXPECT_EQ(it2, list.end());

    auto it3 = list.end();
    it3++;
    EXPECT_EQ(it3, list.end());
}

// Тест 2: Запись через итератор в непустом списке
TEST(ListIteratorTest, WriteThroughIterator) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    *it = 10;
    EXPECT_EQ(list.front(), 10);

    auto last_it = list.begin();
    ++last_it; ++last_it;
    *last_it = 30;
    EXPECT_EQ(list.back(), 30);

    auto mid_it = list.begin();
    ++mid_it;
    *mid_it = 20;

    auto check_it = list.begin();
    EXPECT_EQ(*check_it, 10);
    ++check_it;
    EXPECT_EQ(*check_it, 20);
    ++check_it;
    EXPECT_EQ(*check_it, 30);
}


// Тест 3: Обратный ход итератора (декремент)
TEST(ListIteratorTest, ReverseIteration) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    ++it;
    EXPECT_EQ(*it, 2);

    --it;
    EXPECT_EQ(*it, 1);

    ++it; ++it; 
    EXPECT_EQ(*it, 3);

    --it;
    EXPECT_EQ(*it, 2);

    auto it2 = list.begin();
    --it2;
    EXPECT_EQ(it2, list.end());

    auto it3 = list.end();
    ++it3;
    EXPECT_EQ(it3, list.end());
}

TEST(ListIteratorTest, RbeginRend) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    int i = 4;
    for (auto it = list.rbegin(); it != list.rend(); --it) {
        
        EXPECT_EQ(*it, i);
        --i;
    }
}