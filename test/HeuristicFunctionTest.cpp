#include "heuristicFunctions.h"

#include <gtest/gtest.h>

TEST(ManhattanDistanceTest, Test01)
{
    std::array<int, 2> cell1{1, 2};
    std::array<int, 2> cell2{9, 3};
    int expected = 9;
    int result = getManhattanDistance(cell1, cell2);
    ASSERT_EQ(expected, result);
}

TEST(ManhattanDistanceTest, Test02)
{
    std::array<int, 2> cell1{2, 3};
    std::array<int, 2> cell2{5, 11};
    int expected = 11;
    int result = getManhattanDistance(cell1, cell2);
    ASSERT_EQ(expected, result);
}

TEST(ManhattanDistanceTest, Test03)
{
    std::array<int, 2> cell1{22, 8};
    std::array<int, 2> cell2{9, 3};
    int expected = 18;
    int result = getManhattanDistance(cell1, cell2);
    ASSERT_EQ(expected, result);
}

TEST(ManhattanDistanceTest, Test04)
{
    std::array<int, 2> cell1{20, 2};
    std::array<int, 2> cell2{10, 6};
    int expected = 14;
    int result = getManhattanDistance(cell1, cell2);
    ASSERT_EQ(expected, result);
}