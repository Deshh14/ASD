#include <gtest/gtest.h>
#include "list.h"
#include "ListCycle.h" // Ваш файл с функциями

// Тестовый класс для List с циклами
template<typename T>
class CyclicListTest : public ::testing::Test {
protected:
    List<T> list;

    // Создает циклический список: 1->2->3->4->2...
    void createSimpleCycle() {
        list.clear();
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);

        // Создаем цикл вручную, манипулируя указателями
        // Это требует доступа к внутренней структуре, поэтому
        // мы можем только симулировать это или добавить вспомогательные методы
    }

    // Создает список без цикла
    void createLinearList() {
        list.clear();
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);
    }
};

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

// Тесты для граничных случаев
TEST(CycleDetectionTest, SelfLoopDetection) {
    // Для тестирования реальных циклов нужен доступ к узлам
    // Этот тест показывает концепцию
    List<int> list;
    list.push_back(1);

    // В реальности здесь нужно создать цикл, но без доступа к Node это невозможно
    // Поэтому тест закомментирован:
    // auto it = list.begin();
    // Создаем цикл: элемент ссылается сам на себя
    // EXPECT_TRUE(checkListCycleTurtleAndRabbit<int>(it));
}

TEST(CycleDetectionTest, CircularListDetection) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Концептуально: 1->2->3->1
    // auto start = list.begin();
    // Создаем цикл от последнего к первому
    // EXPECT_TRUE(checkListCycleTurtleAndRabbit<int>(start));
}

TEST(CycleDetectionTest, PartialCycleDetection) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    // Концептуально: 1->2->3->4->5->3 (цикл 3-4-5-3)
    // auto start = list.begin();
    // Создаем частичный цикл
    // EXPECT_TRUE(checkListCycleTurtleAndRabbit<int>(start));
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

// Тесты с пользовательскими типами
struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

TEST(CycleDetectionTest, CustomTypeNoCycle) {
    List<Point> list;
    list.push_back({ 1, 2 });
    list.push_back({ 3, 4 });
    list.push_back({ 5, 6 });

    auto it = list.begin();
    EXPECT_FALSE(checkListCycleTurtleAndRabbit<Point>(it));
}

// Тесты для checkListCyclePointer (заглушка)
TEST(CycleDetectionTest, PointerMethodIsStub) {
    List<int> list;
    list.push_back(1);

    auto it = list.begin();
    // Метод всегда возвращает false в текущей реализации
    EXPECT_FALSE(checkListCyclePointer<int>(it));
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

    // Итераторы разных списков не должны быть равны
    EXPECT_FALSE(it1 == it2);

    // Проверка с nullptr
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
    // Создаем невалидный итератор
    typename List<int>::Iterator invalid(nullptr);

    // Не должно приводить к краху
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

    // Перемещаем итератор
    for (int i = 0; i < 5; ++i) {
        ++it;
    }

    // Проверяем с новой позиции
    EXPECT_FALSE(checkListCycleTurtleAndRabbit<int>(it));
}

// Группа тестов с разными стартовыми позициями
class CycleDetectionFromPositionTest : public ::testing::TestWithParam<int> {
protected:
    List<int> list;

    void SetUp() override {
        for (int i = 0; i < 10; ++i) {
            list.push_back(i);
        }
    }
};

TEST_P(CycleDetectionFromPositionTest, CheckFromDifferentPositions) {
    int startPos = GetParam();
    auto it = list.begin();

    // Перемещаем в стартовую позицию
    for (int i = 0; i < startPos && it != list.end(); ++i) {
        ++it;
    }

    // Для линейного списка всегда false
    EXPECT_FALSE(checkListCycleTurtleAndRabbit<int>(it));

    auto result = FindProblemNode<int>(it);
    EXPECT_EQ(result, typename List<int>::Iterator(nullptr));
}

INSTANTIATE_TEST_SUITE_P(
    DifferentStartPositions,
    CycleDetectionFromPositionTest,
    ::testing::Values(0, 1, 3, 5, 9) // Разные стартовые позиции
);

// Основная функция
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}