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

    EXPECT_EQ(table.find("key"), 50);
}

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
