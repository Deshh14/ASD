#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "SortedTableOnVec.h"

TEST(SortedTableOnVecTest, BasicOperationsAndOrder) {
    SortedTableOnVec<int, std::string> table;

    EXPECT_TRUE(table.is_empty());

    table.insert(5, "five");
    table.insert(2, "two");
    table.insert(8, "eight");
    table.insert(1, "one");
    table.insert(9, "nine");

    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 5); 

    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(8));
    EXPECT_FALSE(table.consist(3));

    EXPECT_EQ(table.size(5), 1);
    EXPECT_EQ(table.size(1), 1);
    EXPECT_EQ(table.size(100), 0);

    EXPECT_EQ(table.find(5), "five");
    EXPECT_EQ(table.find(1), "one");

    auto keys = table.get_keys();
    EXPECT_EQ(keys.size(), 5);
    EXPECT_EQ(keys[0], 1);
    EXPECT_EQ(keys[1], 2);
    EXPECT_EQ(keys[2], 5);
    EXPECT_EQ(keys[3], 8);
    EXPECT_EQ(keys[4], 9);

    EXPECT_EQ(table.get_min_key(), 1);
    EXPECT_EQ(table.get_max_key(), 9);
}

TEST(SortedTableOnVecTest, ReplaceAndErase) {
    SortedTableOnVec<std::string, int> table;

    table.insert("banana", 3);
    table.insert("apple", 5);
    table.insert("cherry", 8);
    table.insert("date", 2);

    auto keys = table.get_keys();
    EXPECT_EQ(keys[0], "apple");
    EXPECT_EQ(keys[1], "banana");
    EXPECT_EQ(keys[2], "cherry");
    EXPECT_EQ(keys[3], "date");

    table.replace("banana", 30);
    EXPECT_EQ(table.find("banana"), 30);
    EXPECT_EQ(table.size("banana"), 1);

    table.erase("banana");
    EXPECT_FALSE(table.consist("banana"));
    EXPECT_EQ(table.size(), 3);
    EXPECT_EQ(table.size("banana"), 0);

    keys = table.get_keys();
    EXPECT_EQ(keys[0], "apple");
    EXPECT_EQ(keys[1], "cherry");
    EXPECT_EQ(keys[2], "date");
}
TEST(SortedTableOnVecTest, ExceptionHandling) {
    SortedTableOnVec<int, double> table;

    EXPECT_THROW(table.find(100), std::runtime_error);

    EXPECT_THROW(table.erase(100), std::runtime_error);

    EXPECT_THROW(table.replace(100, 3.14), std::runtime_error);

    EXPECT_THROW(table.get_min_key(), std::runtime_error);
    EXPECT_THROW(table.get_max_key(), std::runtime_error);

    table.insert(50, 1.5);

    EXPECT_THROW(table.insert(50, 2.5), std::runtime_error);

    EXPECT_EQ(table.find(50), 1.5);
    EXPECT_EQ(table.size(50), 1);
}

TEST(SortedTableOnVecTest, BinarySearchAndBoundaries) {
    SortedTableOnVec<int, std::string> table;

    for (int i = 0; i <= 20; i += 2) {
        table.insert(i, "value" + std::to_string(i));
    }

    EXPECT_EQ(table.size(), 11);

    for (int i = 0; i <= 20; i += 2) {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.size(i), 1);
        EXPECT_EQ(table.find(i), "value" + std::to_string(i));
    }

    for (int i = 1; i <= 19; i += 2) {
        EXPECT_FALSE(table.consist(i));
        EXPECT_EQ(table.size(i), 0);
    }

    EXPECT_EQ(table.get_min_key(), 0);
    EXPECT_EQ(table.get_max_key(), 20);
}

TEST(SortedTableOnVecTest, DifferentTypes) {
    SortedTableOnVec<std::string, double> table1;

    table1.insert("pi", 3.14159);
    table1.insert("e", 2.71828);
    table1.insert("phi", 1.61803);

    auto keys = table1.get_keys();
    EXPECT_EQ(keys[0], "e");
    EXPECT_EQ(keys[1], "phi");
    EXPECT_EQ(keys[2], "pi");

    EXPECT_DOUBLE_EQ(table1.find("pi"), 3.14159);
    EXPECT_DOUBLE_EQ(table1.find("e"), 2.71828);
    EXPECT_EQ(table1.size("phi"), 1);
}

TEST(SortedTableOnVecTest, PrintMethod) {
    SortedTableOnVec<std::string, double> table1;
    table1.insert("pi", 3.14159);
    table1.insert("e", 2.71828);
    table1.insert("phi", 1.61803);

    std::stringstream ss;
    table1.print(ss);
    std::string output = ss.str();

    EXPECT_FALSE(output.empty());

    EXPECT_NE(output.find("pi"), std::string::npos);
    EXPECT_NE(output.find("e"), std::string::npos);
    EXPECT_NE(output.find("phi"), std::string::npos);
}