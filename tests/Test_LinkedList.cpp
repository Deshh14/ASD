#include <gtest/gtest.h>
#include "LinkedList.h"

// Тесты для конструкторов
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

    list.push_back(3);
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list[2], 3);
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

    list.push_front(2);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list[0], 2);
    EXPECT_EQ(list[1], 1);

    list.push_front(3);
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list[0], 3);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 1);
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

    list.pop_front();
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list[0], 3);

    list.pop_front();
    EXPECT_EQ(list.get_size(), 0);
    EXPECT_TRUE(list.empty());
}

TEST(LinkedListTest, PopFrontEmpty) {
    LinkedList<int> list;
    EXPECT_THROW(list.pop_front(), std::out_of_range);
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

    list.pop_back();
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list[0], 1);

    list.pop_back();
    EXPECT_EQ(list.get_size(), 0);
    EXPECT_TRUE(list.empty());
}

TEST(LinkedListTest, PopBackEmpty) {
    LinkedList<int> list;
    EXPECT_THROW(list.pop_back(), std::out_of_range);
}

TEST(LinkedListTest, PopBackSingleElement) {
    LinkedList<int> list;
    list.push_back(42);
    list.pop_back();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.get_size(), 0);
}

TEST(LinkedListTest, InsertAtBeginning) {
    LinkedList<int> list;
    list.push_back(2);
    list.push_back(3);

    list.insert(0, 1);
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
}

TEST(LinkedListTest, InsertAtEnd) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);

    list.insert(2, 3);
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
}

TEST(LinkedListTest, InsertInMiddle) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(3);
    list.push_back(4);

    list.insert(1, 2);
    EXPECT_EQ(list.get_size(), 4);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
    EXPECT_EQ(list[3], 4);
}

TEST(LinkedListTest, InsertInvalidIndex) {
    LinkedList<int> list;
    list.push_back(1);

    EXPECT_THROW(list.insert(5, 2), std::out_of_range);
    EXPECT_THROW(list.insert(3, 2), std::out_of_range);
}

TEST(LinkedListTest, InsertIntoEmptyList) {
    LinkedList<int> list;
    list.insert(0, 42);
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list[0], 42);
}

TEST(LinkedListTest, EraseAtBeginning) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(0);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list[0], 2);
    EXPECT_EQ(list[1], 3);
}

TEST(LinkedListTest, EraseAtEnd) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(2);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
}

TEST(LinkedListTest, EraseInMiddle) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(1);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 3);
}

TEST(LinkedListTest, EraseInvalidIndex) {
    LinkedList<int> list;
    list.push_back(1);

    EXPECT_THROW(list.erase(1), std::out_of_range);
    EXPECT_THROW(list.erase(5), std::out_of_range);
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

TEST(LinkedListTest, ConstOperatorBrackets) {
    LinkedList<int> list;
    list.push_back(5);
    list.push_back(10);

    const LinkedList<int>& const_list = list;
    EXPECT_EQ(const_list[0], 5);
    EXPECT_EQ(const_list[1], 10);
}

TEST(LinkedListTest, Clear) {
    LinkedList<int> list;

    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.get_size(), 0);

    for (int i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    EXPECT_FALSE(list.empty());

    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.get_size(), 0);

    list.push_back(42);
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list[0], 42);
}

TEST(LinkedListTest, EmptyAndSize) {
    LinkedList<int> list;

    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.get_size(), 0);

    list.push_back(1);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.get_size(), 1);

    list.push_back(2);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.get_size(), 2);

    list.pop_back();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.get_size(), 1);

    list.pop_back();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.get_size(), 0);
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

// Тесты для деструктора (косвенно через RAII)
TEST(LinkedListTest, Destructor) {
    {
        LinkedList<int> list;
        for (int i = 0; i < 1000; ++i) {
            list.push_back(i);
        }
    } // Деструктор вызывается здесь

    // Если деструктор работает правильно, не должно быть утечек памяти
    // Это проверяется инструментами анализа памяти
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

// Тест на граничные случаи
TEST(LinkedListTest, BoundaryCases) {
    LinkedList<int> list;

    // Один элемент
    list.push_back(1);
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list[0], 1);
    EXPECT_NO_THROW(list.pop_front());
    EXPECT_TRUE(list.empty());

    // Два элемента
    list.push_back(1);
    list.push_back(2);
    EXPECT_EQ(list.get_size(), 2);
    list.pop_back();
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list[0], 1);

    list.clear();

    // Большое количество элементов
    for (int i = 0; i < 10000; ++i) {
        list.push_back(i);
    }
    EXPECT_EQ(list.get_size(), 10000);
    EXPECT_EQ(list[0], 0);
    EXPECT_EQ(list[9999], 9999);
}
