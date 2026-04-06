#include <gtest/gtest.h>
#include "OrderedTableOnBST.h"
#include <string>

// Тест 1: Вставка и поиск
TEST(OrderedTableOnBSTTest, InsertAndFind) {
    OrderedTableOnBST<int, std::string> table;

    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(2, "two");
    table.insert(4, "four");

    EXPECT_EQ("five", table.find(5));
    EXPECT_EQ("one", table.find(1));
    EXPECT_EQ("three", table.find(3));
    EXPECT_EQ("seven", table.find(7));
    EXPECT_EQ("two", table.find(2));
    EXPECT_EQ("four", table.find(4));

    EXPECT_THROW(table.find(10), std::runtime_error);
}

// Тест 2: Проверка дубликатов
TEST(OrderedTableOnBSTTest, DuplicateInsert) {
    OrderedTableOnBST<int, std::string> table;

    table.insert(5, "five");
    EXPECT_THROW(table.insert(5, "FIVE"), std::runtime_error);
}

// Тест 3: Удаление листа
TEST(OrderedTableOnBSTTest, EraseLeaf) {
    OrderedTableOnBST<int, std::string> table;

    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(1, "one");
    table.insert(4, "four");

    EXPECT_TRUE(table.consist(4));
    table.erase(4);
    EXPECT_FALSE(table.consist(4));
    EXPECT_TRUE(table.consist(5));
    EXPECT_TRUE(table.consist(3));
    EXPECT_TRUE(table.consist(7));
    EXPECT_TRUE(table.consist(1));
}

// Тест 4: Удаление узла с одним ребенком
TEST(OrderedTableOnBSTTest, EraseNodeWithOneChild) {
    OrderedTableOnBST<int, std::string> table;

    // Удаление узла с левым ребенком
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(1, "one");

    EXPECT_TRUE(table.consist(3));
    table.erase(3);
    EXPECT_FALSE(table.consist(3));
    EXPECT_TRUE(table.consist(5));
    EXPECT_TRUE(table.consist(1));

    // Удаление узла с правым ребенком
    OrderedTableOnBST<int, std::string> table2;
    table2.insert(11, "eleven");
    table2.insert(5, "five");
    table2.insert(13, "thirteen");
    table2.insert(7, "seven");
    table2.insert(6, "six");
    table2.insert(10, "ten");

    EXPECT_TRUE(table2.consist(5));
    table2.erase(5);
    EXPECT_FALSE(table2.consist(5));
}

// Тест 5: Удаление узла с двумя детьми
TEST(OrderedTableOnBSTTest, EraseNodeWithTwoChildren) {
    OrderedTableOnBST<int, std::string> table;

    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(1, "one");
    table.insert(4, "four");
    table.insert(6, "six");
    table.insert(8, "eight");

    EXPECT_TRUE(table.consist(5));
    table.erase(5);
    EXPECT_FALSE(table.consist(5));
    EXPECT_TRUE(table.consist(3));
    EXPECT_TRUE(table.consist(7));
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(4));
    EXPECT_TRUE(table.consist(6));
    EXPECT_TRUE(table.consist(8));
}

// Тест 6: Удаление корня
TEST(OrderedTableOnBSTTest, EraseRoot) {
    OrderedTableOnBST<int, std::string> table;

    table.insert(5, "five");
    EXPECT_TRUE(table.consist(5));
    table.erase(5);
    EXPECT_FALSE(table.consist(5));
    EXPECT_TRUE(table.is_empty());

    OrderedTableOnBST<int, std::string> table2;
    table2.insert(5, "five");
    table2.insert(3, "three");
    table2.insert(7, "seven");

    table2.erase(5);
    EXPECT_FALSE(table2.consist(5));
    EXPECT_EQ(2, table2.size());
}

// Тест 7: Замена значений
TEST(OrderedTableOnBSTTest, Replace) {
    OrderedTableOnBST<int, std::string> table;

    table.insert(5, "five");
    table.insert(3, "three");

    table.replace(5, "FIVE");
    EXPECT_EQ("FIVE", table.find(5));
    EXPECT_EQ("three", table.find(3));

    EXPECT_THROW(table.replace(10, "ten"), std::runtime_error);
}

// Тест 8: Упорядоченность вывода
TEST(OrderedTableOnBSTTest, OrderedOutput) {
    OrderedTableOnBST<int, std::string> table;

    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(2, "two");
    table.insert(4, "four");

    std::ostringstream oss;
    table.print(oss);
    std::string output = oss.str();

    // Проверяем, что вывод содержит элементы в порядке возрастания
    size_t pos1 = output.find("1:one");
    size_t pos2 = output.find("2:two");
    size_t pos3 = output.find("3:three");
    size_t pos4 = output.find("4:four");
    size_t pos5 = output.find("5:five");
    size_t pos6 = output.find("7:seven");

    EXPECT_LT(pos1, pos2);
    EXPECT_LT(pos2, pos3);
    EXPECT_LT(pos3, pos4);
    EXPECT_LT(pos4, pos5);
    EXPECT_LT(pos5, pos6);
}

// Тест 9: Комплексный сценарий
TEST(OrderedTableOnBSTTest, ComplexScenario) {
    OrderedTableOnBST<std::string, int> table;

    table.insert("five", 5);
    table.insert("one", 1);
    table.insert("three", 3);
    table.insert("seven", 7);
    table.insert("two", 2);
    table.insert("four", 4);

    EXPECT_EQ(5, table.find("five"));
    EXPECT_EQ(1, table.find("one"));

    table.replace("three", 33);
    EXPECT_EQ(33, table.find("three"));

    table.erase("five");
    EXPECT_FALSE(table.consist("five"));

    table.insert("six", 6);
    EXPECT_EQ(6, table.find("six"));

    EXPECT_TRUE(table.consist("one"));
    EXPECT_TRUE(table.consist("two"));
    EXPECT_TRUE(table.consist("three"));
    EXPECT_TRUE(table.consist("four"));
    EXPECT_TRUE(table.consist("six"));
    EXPECT_TRUE(table.consist("seven"));
}