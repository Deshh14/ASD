#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "UnsortedTableOnVec.h"

TEST(UnsortedTableOnVecTest, BasicOperations) {
    UnsortedTableOnVec<std::string, int> table;

    EXPECT_TRUE(table.is_empty());

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);

    EXPECT_FALSE(table.is_empty());

    EXPECT_TRUE(table.consist("one"));
    EXPECT_TRUE(table.consist("two"));
    EXPECT_TRUE(table.consist("three"));
    EXPECT_FALSE(table.consist("four"));

    EXPECT_EQ(table.find("one"), 1);
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_EQ(table.find("three"), 3);

    EXPECT_EQ(table.size("one"), 3);
    EXPECT_EQ(table.size("four"), 0);
}

TEST(UnsortedTableOnVecTest, ReplaceAndErase) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("a", 10);
    table.insert("b", 20);
    table.insert("c", 30);

    EXPECT_EQ(table.find("b"), 20);

    table.replace("b", 200);
    EXPECT_EQ(table.find("b"), 200);

    table.erase("b");
    EXPECT_FALSE(table.consist("b"));
    EXPECT_TRUE(table.consist("a"));
    EXPECT_TRUE(table.consist("c"));

    // Проверка size после удаления
    EXPECT_EQ(table.size("a"), 2);
    EXPECT_EQ(table.size("b"), 0);
}

TEST(UnsortedTableOnVecTest, ExceptionHandling) {
    UnsortedTableOnVec<std::string, int> table;

    EXPECT_THROW(table.find("nonexistent"), std::runtime_error);

    EXPECT_THROW(table.erase("nonexistent"), std::runtime_error);

    EXPECT_THROW(table.replace("nonexistent", 100), std::runtime_error);

    table.insert("key", 50);

    EXPECT_THROW(table.insert("key", 100), std::runtime_error);

    // Проверка, что значение не изменилось
    EXPECT_EQ(table.find("key"), 50);
}

// Тест 4: Проверка print
TEST(UnsortedTableOnVecTest, PrintMethod) {
    UnsortedTableOnVec<std::string, int> table;
    table.insert("x", 10);
    table.insert("y", 20);

    std::stringstream ss;
    table.print(ss);

    std::string output = ss.str();
    EXPECT_NE(output.find("Unsorted Table Contents:"), std::string::npos);
    EXPECT_NE(output.find("Key: x, Value: 10"), std::string::npos);
    EXPECT_NE(output.find("Key: y, Value: 20"), std::string::npos);
}

// Тест 5: Проверка работы с разными типами
TEST(UnsortedTableOnVecTest, DifferentTypes) {
    // int ключи, string значения
    UnsortedTableOnVec<int, std::string> table1;
    table1.insert(1, "one");
    table1.insert(2, "two");

    EXPECT_EQ(table1.find(1), "one");
    EXPECT_EQ(table1.find(2), "two");
    EXPECT_TRUE(table1.consist(1));
    EXPECT_EQ(table1.size(1), 1);

    // string ключи, double значения
    UnsortedTableOnVec<std::string, double> table2;
    table2.insert("pi", 3.14159);
    table2.insert("e", 2.71828);

    EXPECT_DOUBLE_EQ(table2.find("pi"), 3.14159);
    EXPECT_DOUBLE_EQ(table2.find("e"), 2.71828);
}