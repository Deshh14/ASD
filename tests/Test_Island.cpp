#include <gtest/gtest.h>
#include "Island.h"

TEST(IslandCounterTest, EmptyGrid) {
    Tvector<Tvector<int>> emptyGrid;
    IslandCounter counter(emptyGrid);
    EXPECT_EQ(counter.calculateIslands(), 0);
}

TEST(IslandCounterTest, SingleCellGrid_NoIsland) {
    Tvector<Tvector<int>> grid = { {0} };
    IslandCounter counter(grid);
    EXPECT_EQ(counter.calculateIslands(), 0);
}

TEST(IslandCounterTest, SingleCellGrid_OneIsland) {
    Tvector<Tvector<int>> grid = { {1} };
    IslandCounter counter(grid);
    EXPECT_EQ(counter.calculateIslands(), 1);
}

TEST(IslandCounterTest, SingleRowGrid) {
    Tvector<Tvector<int>> grid = { {1, 0, 1, 1, 0, 1} };
    IslandCounter counter(grid);
    EXPECT_EQ(counter.calculateIslands(), 3);
}

TEST(IslandCounterTest, SingleColumnGrid) {
    Tvector<Tvector<int>> grid = { {1}, {1}, {0}, {1}, {0}, {1} };
    IslandCounter counter(grid);
    EXPECT_EQ(counter.calculateIslands(), 3);
}

TEST(IslandCounterTest, TwoIslandsSeparated) {
    Tvector<Tvector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1}
    };
    IslandCounter counter(grid);
    EXPECT_EQ(counter.calculateIslands(), 2);
}

TEST(IslandCounterTest, DiagonalCellsNotConnected) {
    Tvector<Tvector<int>> grid = {
        {1, 0},
        {0, 1}
    };
    IslandCounter counter(grid);
    EXPECT_EQ(counter.calculateIslands(), 2);
}

TEST(IslandCounterTest, LargeSingleIsland) {
    Tvector<Tvector<int>> grid = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    };
    IslandCounter counter(grid);
    EXPECT_EQ(counter.calculateIslands(), 1);
}

TEST(IslandCounterTest, AllWater) {
    Tvector<Tvector<int>> grid = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    IslandCounter counter(grid);
    EXPECT_EQ(counter.calculateIslands(), 0);
}

TEST(IslandCounterTest, ComplexPattern) {
    Tvector<Tvector<int>> grid = {
        {1, 0, 1, 0, 1},
        {1, 0, 0, 1, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1}
    };
    IslandCounter counter(grid);
    EXPECT_EQ(counter.calculateIslands(), 7);
}

TEST(IslandCounterTest, SnakeLikeIsland) {
    Tvector<Tvector<int>> grid = {
        {1, 1, 1, 1},
        {0, 0, 0, 1},
        {1, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 1, 1, 1}
    };
    IslandCounter counter(grid);
    EXPECT_EQ(counter.calculateIslands(), 1);
}

TEST(IslandCounterTest, CheckerboardPattern) {
    Tvector<Tvector<int>> grid = {
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0}
    };
    IslandCounter counter(grid);
    // В шашечном порядке все клетки не соединены по горизонтали/вертикали
    EXPECT_EQ(counter.calculateIslands(), 10);
}

TEST(IslandCounterTest, GridWithOneRowMultipleIslands) {
    Tvector<Tvector<int>> grid = { {1, 1, 0, 1, 1, 1, 0, 1} };
    IslandCounter counter(grid);
    EXPECT_EQ(counter.calculateIslands(), 3);
}

TEST(IslandCounterTest, SingleIslandWithHole) {
    Tvector<Tvector<int>> grid = {
        {1, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 1}
    };
    IslandCounter counter(grid);
    EXPECT_EQ(counter.calculateIslands(), 1);
}

