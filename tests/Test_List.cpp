#include <gtest/gtest.h>
#include "list.h" 
#include <string>

/*
// Тесты конструкторов
TEST(ListTest, DefaultConstructor) {
    List<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, CopyConstructor) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    List<int> copy(original);
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.front(), 1);
    EXPECT_EQ(copy.back(), 3);
}

TEST(ListTest, MoveConstructor) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);

    List<int> moved(std::move(original));
    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(moved.front(), 1);
    EXPECT_EQ(moved.back(), 2);
    EXPECT_TRUE(original.empty());
}

// Тесты операторов присваивания
TEST(ListTest, CopyAssignment) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2;
    list2 = list1;

    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 2);
}

TEST(ListTest, MoveAssignment) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2;
    list2 = std::move(list1);

    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 2);
    EXPECT_TRUE(list1.empty());
}

TEST(ListTest, SelfAssignment) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    list = list;
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
}

// Тесты доступа к элементам
TEST(ListTest, FrontAndBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);

    list.front() = 10;
    list.back() = 30;

    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 30);
}

TEST(ListTest, FrontBackConst) {
    const List<int> list = []() {
        List<int> temp;
        temp.push_back(1);
        temp.push_back(2);
        return temp;
        }();

        EXPECT_EQ(list.front(), 1);
        EXPECT_EQ(list.back(), 2);
}

// Тесты методов вместимости
TEST(ListTest, EmptyAndSize) {
    List<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);

    list.push_back(1);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 1);

    list.pop_front();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

// Тесты модификаторов - добавление элементов
TEST(ListTest, PushFront) {
    List<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, PushBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, PopFront) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);

    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 3);

    list.pop_front();
    EXPECT_TRUE(list.empty());
}

TEST(ListTest, PopBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.back(), 2);

    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 1);

    list.pop_back();
    EXPECT_TRUE(list.empty());
}

TEST(ListTest, Clear) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.size(), 3);
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);


    list.clear();
    EXPECT_TRUE(list.empty());
}

// Тесты итераторов
TEST(ListTest, IteratorBasic) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(ListTest, IteratorPostIncrement) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto it = list.begin();
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it, 2);
}

TEST(ListTest, IteratorEquality) {
    List<int> list;
    list.push_back(1);

    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);

    ++it1;
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}

TEST(ListTest, IteratorRangeBasedFor) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    int sum = 0;
    for (const auto& item : list) {
        sum += item;
    }
    EXPECT_EQ(sum, 6);
}

// Тесты вставки и удаления
TEST(ListTest, InsertAtBeginning) {
    List<int> list;
    list.push_back(2);
    list.push_back(3);

    auto it = list.insert(list.begin(), 1);
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
}

TEST(ListTest, InsertAtEnd) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto it = list.insert(list.end(), 3);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, InsertInMiddle) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    auto it = list.begin();
    ++it;
    it = list.insert(it, 2);

    EXPECT_EQ(*it, 2);
    EXPECT_EQ(list.size(), 3);

    it = list.begin();
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
}

TEST(ListTest, EraseAtBeginning) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.erase(list.begin());
    EXPECT_EQ(*it, 2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
}

TEST(ListTest, EraseAtEnd) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    ++it;
    ++it;
    it = list.erase(it);
    EXPECT_EQ(it, list.end());
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, EraseInMiddle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    ++it;
    it = list.erase(it);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(list.size(), 2);

    it = list.begin();
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 3);
}

TEST(ListTest, EraseAll) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto it = list.begin();
    while (it != list.end()) {
        it = list.erase(it);
    }

    EXPECT_TRUE(list.empty());
}

// Тесты операций со списком
TEST(ListTest, Swap) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2;
    list2.push_back(3);
    list2.push_back(4);
    list2.push_back(5);

    list1.swap(list2);

    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list1.front(), 3);
    EXPECT_EQ(list1.back(), 5);

    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 2);
}

TEST(ListTest, Reverse) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.reverse();

    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 1);

    auto it = list.begin();
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 1);
}

TEST(ListTest, Unique) {
    List<int> list;
    list.push_back(1);
    list.push_back(1);
    list.push_back(2);
    list.push_back(2);
    list.push_back(3);
    list.push_back(3);

    list.unique();

    EXPECT_EQ(list.size(), 3);
    auto it = list.begin();
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
}

TEST(ListTest, Sort) {
    List<int> list;
    list.push_back(3);
    list.push_back(1);
    list.push_back(4);
    list.push_back(2);

    list.sort();

    auto it = list.begin();
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(*it++, 4);
}

// Тесты с разными типами данных
TEST(ListTest, StringType) {
    List<std::string> list;
    list.push_back("hello");
    list.push_back("world");
    list.push_back("test");

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), "hello");
    EXPECT_EQ(list.back(), "test");

    list.sort();
    EXPECT_EQ(list.front(), "hello");
}

TEST(ListTest, DoubleType) {
    List<double> list;
    list.push_back(1.1);
    list.push_back(2.2);
    list.push_back(3.3);

    EXPECT_DOUBLE_EQ(list.front(), 1.1);
    EXPECT_DOUBLE_EQ(list.back(), 3.3);

    list.reverse();
    EXPECT_DOUBLE_EQ(list.front(), 3.3);
}


*/