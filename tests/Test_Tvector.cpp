#include <gtest/gtest.h>
#include "Tvector.h"

TEST(TvectorIteratorTest, BasicIteratorOperations) {
    Tvector<int> vec = { 1, 2, 3, 4, 5 };

    auto begin_it = vec.begin();
    auto end_it = vec.end();

    EXPECT_EQ(*begin_it, 1);

    ++begin_it;
    EXPECT_EQ(*begin_it, 2);

    EXPECT_NE(begin_it, end_it);
    EXPECT_LT(vec.begin(), vec.end());
}

TEST(TvectorIteratorTest, IteratorArithmetic) {
    Tvector<int> vec = { 10, 20, 30, 40, 50 };
    auto it = vec.begin();

    auto it2 = it + 2;
    EXPECT_EQ(*it2, 30);

    auto it3 = it2 - 1;
    EXPECT_EQ(*it3, 20);

    EXPECT_EQ(it2 - it, 2);

    it += 3;
    EXPECT_EQ(*it, 40);
    it -= 2;
    EXPECT_EQ(*it, 20);
}

TEST(TvectorIteratorTest, IteratorElementAccess) {
    Tvector<int> vec = { 100, 200, 300 };
    auto it = vec.begin();

    struct Point { int x, y; };
    Tvector<Point> points = { {1, 2}, {3, 4} };
    auto point_it = points.begin();
    EXPECT_EQ(point_it->x, 1);
    EXPECT_EQ(point_it->y, 2);

    EXPECT_EQ(it[0], 100);
    EXPECT_EQ(it[2], 300);

    *it = 999;
    EXPECT_EQ(vec[0], 999);
}

TEST(TvectorIteratorTest, RangeBasedForLoop) {
    Tvector<int> vec = { 1, 2, 3 };

    int sum = 0;
    for (const auto& elem : vec) {
        sum += elem;
    }
    EXPECT_EQ(sum, 6);

    for (auto& elem : vec) {
        elem *= 2;
    }
    EXPECT_EQ(vec[0], 2);
    EXPECT_EQ(vec[1], 4);
    EXPECT_EQ(vec[2], 6);
}

TEST(TvectorIteratorTest, IteratorsAfterContainerModification) {
    Tvector<int> vec = { 1, 2, 3 };
    auto it = vec.begin() + 1; 

    vec.insert(it, 99);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 99);
    EXPECT_EQ(vec[2], 2);
    EXPECT_EQ(vec[3], 3);

    auto new_it = vec.begin() + 2; 
    vec.erase(new_it);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 99);
    EXPECT_EQ(vec[2], 3);
}