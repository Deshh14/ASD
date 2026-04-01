#include <gtest/gtest.h>
#include "TableOnList.h"
#include <string>

TEST(UnsortedTableOnListTest, InsertAndSize) {
    UnsortedTableOnList<int, std::string> table;

    EXPECT_TRUE(table.is_empty());

    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(1, table.size(1)); 

    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_EQ(1, table.size(1)); 
    EXPECT_EQ(1, table.size(2)); 
    EXPECT_EQ(1, table.size(3));
    EXPECT_EQ(0, table.size(4)); 

    EXPECT_THROW(table.insert(1, "duplicate"), std::runtime_error);
    EXPECT_EQ(1, table.size(1)); 
}

TEST(UnsortedTableOnListTest, FindAndConsist) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(10, "ten");
    table.insert(20, "twenty");
    table.insert(30, "thirty");

    EXPECT_TRUE(table.consist(10));
    EXPECT_TRUE(table.consist(20));
    EXPECT_TRUE(table.consist(30));
    EXPECT_FALSE(table.consist(40));
    EXPECT_FALSE(table.consist(999));

    EXPECT_EQ(1, table.size(10));
    EXPECT_EQ(1, table.size(20));
    EXPECT_EQ(1, table.size(30));
    EXPECT_EQ(0, table.size(40));
    EXPECT_EQ(0, table.size(999));

    EXPECT_EQ("ten", table.find(10));
    EXPECT_EQ("twenty", table.find(20));
    EXPECT_EQ("thirty", table.find(30));
    EXPECT_THROW(table.find(40), std::runtime_error);
}

TEST(UnsortedTableOnListTest, Erase) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(1, table.size(1));
    EXPECT_EQ(1, table.size(2));
    EXPECT_EQ(1, table.size(3));

    EXPECT_NO_THROW(table.erase(2));
    EXPECT_FALSE(table.consist(2));
    EXPECT_EQ(0, table.size(2));
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(3));
    EXPECT_EQ(1, table.size(1));
    EXPECT_EQ(1, table.size(3));
    EXPECT_EQ("one", table.find(1));
    EXPECT_EQ("three", table.find(3));

    EXPECT_THROW(table.erase(999), std::runtime_error);
    EXPECT_EQ(0, table.size(999));

    EXPECT_NO_THROW(table.erase(1));
    EXPECT_NO_THROW(table.erase(3));
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size(1)); 
    EXPECT_EQ(0, table.size(3));
}


TEST(UnsortedTableOnListTest, Replace) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");

    EXPECT_EQ(1, table.size(1));
    EXPECT_EQ(1, table.size(2));
    EXPECT_EQ("one", table.find(1));
    EXPECT_EQ("two", table.find(2));

    EXPECT_NO_THROW(table.replace(1, "ONE"));
    EXPECT_EQ("ONE", table.find(1));
    EXPECT_EQ("two", table.find(2));
    EXPECT_EQ(1, table.size(1)); 
    EXPECT_EQ(1, table.size(2));

    EXPECT_NO_THROW(table.replace(2, "TWO"));
    EXPECT_EQ("TWO", table.find(2));
    EXPECT_EQ(1, table.size(2));

    EXPECT_THROW(table.replace(3, "three"), std::runtime_error);
    EXPECT_EQ(0, table.size(3));

    EXPECT_EQ("ONE", table.find(1));
    EXPECT_EQ("TWO", table.find(2));
}

TEST(UnsortedTableOnListTest, ComplexScenario) {
    UnsortedTableOnList<std::string, int> table;

    table.insert("banana", 100);
    table.insert("apple", 50);
    table.insert("cherry", 150);
    table.insert("date", 75);

    EXPECT_EQ(1, table.size("banana"));
    EXPECT_EQ(1, table.size("apple"));
    EXPECT_EQ(1, table.size("cherry"));
    EXPECT_EQ(1, table.size("date"));
    EXPECT_EQ(0, table.size("lemon"));

    EXPECT_EQ(50, table.find("apple"));
    EXPECT_EQ(100, table.find("banana"));
    EXPECT_EQ(150, table.find("cherry"));
    EXPECT_EQ(75, table.find("date"));

    table.replace("apple", 55);
    table.replace("cherry", 160);
    EXPECT_EQ(55, table.find("apple"));
    EXPECT_EQ(160, table.find("cherry"));
    EXPECT_EQ(1, table.size("apple")); 
    EXPECT_EQ(1, table.size("cherry"));

    table.erase("banana");
    table.erase("date");
    EXPECT_FALSE(table.consist("banana"));
    EXPECT_FALSE(table.consist("date"));
    EXPECT_EQ(0, table.size("banana"));
    EXPECT_EQ(0, table.size("date"));
    EXPECT_TRUE(table.consist("apple"));
    EXPECT_TRUE(table.consist("cherry"));
    EXPECT_EQ(1, table.size("apple"));
    EXPECT_EQ(1, table.size("cherry"));

    EXPECT_EQ(55, table.find("apple"));
    EXPECT_EQ(160, table.find("cherry"));

    table.insert("elderberry", 200);
    EXPECT_EQ(1, table.size("elderberry"));
    EXPECT_EQ(200, table.find("elderberry"));

    table.erase("apple");
    table.erase("cherry");
    table.erase("elderberry");
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size("apple"));
    EXPECT_EQ(0, table.size("cherry"));
    EXPECT_EQ(0, table.size("elderberry"));
}