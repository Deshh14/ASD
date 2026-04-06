#include <gtest/gtest.h>
#include "UnsortedTableOnTree.h"
#include <string>

// Тест 1: Вставка и размер
TEST(UnsortedTableOnTreeTest, InsertAndSize) {
    UnsortedTableOnTree<int, std::string> table;

    EXPECT_TRUE(table.is_empty());

    table.insert(5, "five");
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(1, table.size(5));
    EXPECT_EQ(0, table.size(1));

    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(2, "two");
    table.insert(4, "four");

    EXPECT_EQ(1, table.size(5));
    EXPECT_EQ(1, table.size(1));
    EXPECT_EQ(1, table.size(3));
    EXPECT_EQ(1, table.size(7));
    EXPECT_EQ(1, table.size(2));
    EXPECT_EQ(1, table.size(4));

    // Проверка дубликата
    EXPECT_THROW(table.insert(5, "FIVE"), std::runtime_error);
}

// Тест 2: Поиск
TEST(UnsortedTableOnTreeTest, Find) {
    UnsortedTableOnTree<int, std::string> table;

    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(7, "seven");

    EXPECT_EQ("five", table.find(5));
    EXPECT_EQ("one", table.find(1));
    EXPECT_EQ("three", table.find(3));
    EXPECT_EQ("seven", table.find(7));

    EXPECT_THROW(table.find(10), std::runtime_error);
    EXPECT_FALSE(table.consist(10));
}

// Тест 3: Удаление
TEST(UnsortedTableOnTreeTest, Erase) {
    UnsortedTableOnTree<int, std::string> table;

    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(2, "two");
    table.insert(4, "four");

    // Удаление листа
    EXPECT_NO_THROW(table.erase(7));
    EXPECT_FALSE(table.consist(7));

    // Удаление узла с детьми
    EXPECT_NO_THROW(table.erase(5));
    EXPECT_FALSE(table.consist(5));

    // Удаление несуществующего
    EXPECT_THROW(table.erase(100), std::runtime_error);
}

// Тест 4: Замена
TEST(UnsortedTableOnTreeTest, Replace) {
    UnsortedTableOnTree<int, std::string> table;

    table.insert(5, "five");
    table.insert(1, "one");

    EXPECT_NO_THROW(table.replace(5, "FIVE"));
    EXPECT_EQ("FIVE", table.find(5));
    EXPECT_EQ("one", table.find(1));

    EXPECT_THROW(table.replace(10, "ten"), std::runtime_error);
}

// Тест 5: Комплексный тест
TEST(UnsortedTableOnTreeTest, ComplexScenario) {
    UnsortedTableOnTree<std::string, int> table;

    table.insert("five", 5);
    table.insert("one", 1);
    table.insert("three", 3);
    table.insert("seven", 7);
    table.insert("two", 2);
    table.insert("four", 4);

    EXPECT_EQ(1, table.size("five"));
    EXPECT_EQ(1, table.size("one"));
    EXPECT_EQ(1, table.size("three"));

    EXPECT_EQ(5, table.find("five"));
    EXPECT_EQ(1, table.find("one"));
    EXPECT_EQ(3, table.find("three"));

    table.replace("three", 33);
    EXPECT_EQ(33, table.find("three"));

    table.erase("five");
    EXPECT_FALSE(table.consist("five"));

    table.insert("six", 6);
    EXPECT_EQ(6, table.find("six"));

    table.erase("one");
    table.erase("two");
    table.erase("three");
    table.erase("four");
    table.erase("seven");
    table.erase("six");

    EXPECT_TRUE(table.is_empty());
}

// Тест 6: Проверка всех обходов дерева
TEST(UnsortedTableOnTreeTest, TreeTraversals) {
    UnsortedTableOnTree<int, std::string> table;

    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(2, "two");
    table.insert(4, "four");

    // Просто проверяем, что вывод не вызывает ошибок
    std::ostringstream oss;
    EXPECT_NO_THROW(table.print(oss));
    EXPECT_FALSE(oss.str().empty());
}