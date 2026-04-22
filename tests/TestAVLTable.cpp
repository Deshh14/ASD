#include <gtest/gtest.h>
#include "AVLTree.h"
#include "AVLTable.h"

TEST(AVLTreeTest, BasicInsert) {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    EXPECT_EQ(tree.size(), 3);
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(20));
    EXPECT_TRUE(tree.contains(30));
    EXPECT_FALSE(tree.contains(40));
}

TEST(AVLTreeTest, Erase) {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    tree.erase(20);

    EXPECT_EQ(tree.size(), 2);
    EXPECT_TRUE(tree.contains(10));
    EXPECT_FALSE(tree.contains(20));
    EXPECT_TRUE(tree.contains(30));
}

TEST(AVLTreeTest, EraseNonExistent) {
    AVLTree<int> tree;

    tree.insert(10);

    EXPECT_THROW(tree.erase(20), std::runtime_error);
}

TEST(AVLTreeTest, MinMax) {
    AVLTree<int> tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    EXPECT_EQ(tree.min(), 20);
    EXPECT_EQ(tree.max(), 70);
}

TEST(AVLTreeTest, EmptyTreeExceptions) {
    AVLTree<int> tree;

    EXPECT_THROW(tree.min(), std::runtime_error);
    EXPECT_THROW(tree.max(), std::runtime_error);
    EXPECT_THROW(tree.find(10), std::runtime_error);
}

TEST(AVLTreeTest, Clear) {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    tree.clear();

    EXPECT_EQ(tree.size(), 0);
    EXPECT_TRUE(tree.empty());
}

TEST(AVLTableTest, InsertAndFind) {
    AVLTable<std::string, int> table;

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);

    EXPECT_EQ(table.find("one"), 1);
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_EQ(table.find("three"), 3);
    EXPECT_THROW(table.find("four"), std::runtime_error);
}

TEST(AVLTableTest, DuplicateInsert) {
    AVLTable<std::string, int> table;

    table.insert("key", 100);
    EXPECT_THROW(table.insert("key", 200), std::runtime_error);
}

TEST(AVLTableTest, Erase) {
    AVLTable<std::string, int> table;

    table.insert("one", 1);
    table.insert("two", 2);

    table.erase("one");

    EXPECT_FALSE(table.consist("one"));
    EXPECT_TRUE(table.consist("two"));
}

TEST(AVLTableTest, Replace) {
    AVLTable<std::string, int> table;

    table.insert("key", 100);
    table.replace("key", 200);

    EXPECT_EQ(table.find("key"), 200);
}

TEST(AVLTableTest, IsEmpty) {
    AVLTable<std::string, int> table;

    EXPECT_TRUE(table.is_empty());

    table.insert("key", 1);
    EXPECT_FALSE(table.is_empty());
}
