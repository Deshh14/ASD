#include <gtest/gtest.h>
#include "dsu.h" 
#include <string>

TEST(DSUTest, ConstructorCreatesDisjointSets) {
    const size_t SIZE = 5;
    DSU dsu(SIZE);

    for (int i = 0; i < SIZE; i++) {
        EXPECT_EQ(dsu.find(i), i);
    }
}

TEST(DSUTest, UniteConnectsElements) {
    DSU dsu(5);

    dsu.unite(0, 1);
    dsu.unite(2, 3);

    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.find(2), dsu.find(3));

    EXPECT_NE(dsu.find(0), dsu.find(2));
    EXPECT_NE(dsu.find(1), dsu.find(3));
}

TEST(DSUTest, UnionIsTransitive) {
    DSU dsu(5);

    dsu.unite(0, 1);
    dsu.unite(1, 2);

    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.find(1), dsu.find(2));
    EXPECT_EQ(dsu.find(0), dsu.find(2));
}

TEST(DSUTest, UniteAlreadyConnectedElements) {
    DSU dsu(3);

    dsu.unite(0, 1);
    int root_before = dsu.find(0);

    dsu.unite(0, 1);
    int root_after = dsu.find(0);

    EXPECT_EQ(root_before, root_after);
    EXPECT_EQ(dsu.find(0), dsu.find(1));
}

TEST(DSUTest, SingleElementSet) {
    DSU dsu(3);

    EXPECT_EQ(dsu.find(2), 2);

    dsu.unite(0, 1);

    EXPECT_EQ(dsu.find(2), 2);
    EXPECT_NE(dsu.find(2), dsu.find(0));
    EXPECT_NE(dsu.find(2), dsu.find(1));
}

TEST(DSUTest, ChainOfUnions) {
    const size_t SIZE = 10;
    DSU dsu(SIZE);

    for (int i = 0; i < SIZE - 1; i++) {
        dsu.unite(i, i + 1);
    }

    int root = dsu.find(0);
    for (int i = 1; i < SIZE; i++) {
        EXPECT_EQ(dsu.find(i), root);
    }
}

TEST(DSUTest, UniteDifferentSets) {
    DSU dsu(6);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    dsu.unite(4, 5);

    int root1 = dsu.find(0);
    int root2 = dsu.find(3);
    EXPECT_NE(root1, root2);

    dsu.unite(0, 3);

    EXPECT_EQ(dsu.find(0), dsu.find(3));
    EXPECT_EQ(dsu.find(1), dsu.find(4));
    EXPECT_EQ(dsu.find(2), dsu.find(5));
}

TEST(DSUTest, SameRankUnion) {
    DSU dsu(4);

    dsu.unite(0, 1);
    dsu.unite(2, 3);

    dsu.unite(0, 2);

    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.find(0), dsu.find(2));
    EXPECT_EQ(dsu.find(0), dsu.find(3));
}

TEST(DSUTest, SingleElementDSU) {
    DSU dsu(1);

    EXPECT_EQ(dsu.find(0), 0);

    dsu.unite(0, 0);
    EXPECT_EQ(dsu.find(0), 0);
}