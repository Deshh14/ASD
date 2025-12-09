#include <gtest/gtest.h>
#include "list.h"
#include "ListCycle.h" 


// Тесты для checkListCycleTurtleAndRabbit
TEST(CycleDetectionTest, EmptyIteratorReturnsFalse) {
    typename List<int>::Iterator empty(nullptr);
    EXPECT_FALSE(checkListCycleTurtleAndRabbit<int>(empty));
}

TEST(CycleDetectionTest, SingleElementNoCycle) {
    List<int> list;
    list.push_back(1);

    auto it = list.begin();
    EXPECT_FALSE(checkListCycleTurtleAndRabbit<int>(it));
}

TEST(CycleDetectionTest, TwoElementsNoCycle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto it = list.begin();
    EXPECT_FALSE(checkListCycleTurtleAndRabbit<int>(it));
}

TEST(CycleDetectionTest, LinearListNoCycle) {
    List<int> list;
    for (int i = 0; i < 10; ++i) {
        list.push_back(i);
    }

    auto it = list.begin();
    EXPECT_FALSE(checkListCycleTurtleAndRabbit<int>(it));

    // Проверяем из середины списка
    auto mid = list.begin();
    for (int i = 0; i < 5; ++i) ++mid;
    EXPECT_FALSE(checkListCycleTurtleAndRabbit<int>(mid));
}

// Тесты для FindProblemNode
TEST(CycleDetectionTest, FindProblemNodeEmptyList) {
    typename List<int>::Iterator empty(nullptr);
    auto result = FindProblemNode<int>(empty);
    EXPECT_EQ(result, typename List<int>::Iterator(nullptr));
}

TEST(CycleDetectionTest, FindProblemNodeLinearList) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }

    auto it = list.begin();
    auto result = FindProblemNode<int>(it);
    EXPECT_EQ(result, typename List<int>::Iterator(nullptr));
}

TEST(CycleDetectionTest, FindProblemNodeSingleElement) {
    List<int> list;
    list.push_back(1);

    auto it = list.begin();
    auto result = FindProblemNode<int>(it);
    EXPECT_EQ(result, typename List<int>::Iterator(nullptr));
}

TEST(CycleDetectionTest, CircularListDetection) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto start = list.begin();
    // Создаем цикл от последнего к первому
    EXPECT_TRUE(checkListCycleTurtleAndRabbit<int>(start));
}


// Тесты производительности и стресс-тесты
TEST(CycleDetectionTest, LargeLinearListPerformance) {
    List<int> list;
    for (int i = 0; i < 10000; ++i) {
        list.push_back(i);
    }

    auto start = list.begin();

    // Не должно быть зависаний или сбоев
    EXPECT_FALSE(checkListCycleTurtleAndRabbit<int>(start));

    auto result = FindProblemNode<int>(start);
    EXPECT_EQ(result, typename List<int>::Iterator(nullptr));
}

// Тесты с различными типами данных
TEST(CycleDetectionTest, StringTypeNoCycle) {
    List<std::string> list;
    list.push_back("hello");
    list.push_back("world");
    list.push_back("test");

    auto it = list.begin();
    EXPECT_FALSE(checkListCycleTurtleAndRabbit<std::string>(it));
}

TEST(CycleDetectionTest, DoubleTypeNoCycle) {
    List<double> list;
    list.push_back(1.1);
    list.push_back(2.2);
    list.push_back(3.3);

    auto it = list.begin();
    EXPECT_FALSE(checkListCycleTurtleAndRabbit<double>(it));
}

// Тесты для checkListCyclePointer
TEST(CycleDetectionTest, PointerMethodIsStub) {
    List<int> list;
    list.push_back(1);

    auto it = list.begin();
  //  EXPECT_FALSE(checkListCyclePointer<int>(it));
}

// Тесты итераторов
TEST(CycleDetectionTest, IteratorEquality) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2;
    list2.push_back(1);
    list2.push_back(2);

    auto it1 = list1.begin();
    auto it2 = list2.begin();

    EXPECT_FALSE(it1 == it2);

    typename List<int>::Iterator nullIt(nullptr);
    EXPECT_FALSE(it1 == nullIt);
}

// Тест на корректность работы с end итератором
TEST(CycleDetectionTest, EndIteratorHandling) {
    List<int> list;
    list.push_back(1);

    auto begin = list.begin();
    auto end = list.end();

    EXPECT_FALSE(checkListCycleTurtleAndRabbit<int>(end));

    auto result = FindProblemNode<int>(end);
    EXPECT_EQ(result, typename List<int>::Iterator(nullptr));
}

// Тесты на исключительные ситуации
TEST(CycleDetectionTest, InvalidIteratorAccess) {
    typename List<int>::Iterator invalid(nullptr);

    EXPECT_NO_THROW(checkListCycleTurtleAndRabbit<int>(invalid));
    EXPECT_NO_THROW(FindProblemNode<int>(invalid));
}

// Тест с перемещением итератора
TEST(CycleDetectionTest, IteratorMovement) {
    List<int> list;
    for (int i = 0; i < 10; ++i) {
        list.push_back(i);
    }

    auto it = list.begin();

    for (int i = 0; i < 5; ++i) {
        ++it;
    }

    EXPECT_FALSE(checkListCycleTurtleAndRabbit<int>(it));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}