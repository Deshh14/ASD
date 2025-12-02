#include <gtest/gtest.h>
#include <string>
#include "algorithms.h"

TEST(CheckBracketsTest, CorrectBrackets) {
    EXPECT_TRUE(check_brackets("()"));
    EXPECT_TRUE(check_brackets("[]"));
    EXPECT_TRUE(check_brackets("{}"));
    EXPECT_TRUE(check_brackets("({[]})"));
    EXPECT_TRUE(check_brackets("()[]{}"));
}

TEST(CheckBracketsTest, IncorrectBrackets) {
    EXPECT_FALSE(check_brackets("("));
    EXPECT_FALSE(check_brackets(")"));
    EXPECT_FALSE(check_brackets("{(})"));
}

TEST(CheckBracketsTest, ExpressionWithText) {
    EXPECT_TRUE(check_brackets("(a + b)"));
    EXPECT_FALSE(check_brackets("(a + b"));
    EXPECT_FALSE(check_brackets("array[10] = {1, 2, 3"));
}

TEST(CheckBracketsTest, EmptyOrNoBrackets) {
    EXPECT_TRUE(check_brackets(""));
    EXPECT_TRUE(check_brackets("abc"));
    EXPECT_TRUE(check_brackets("test string"));
}

TEST(CheckBracketsTest, ComplexCases) {
    EXPECT_TRUE(check_brackets("((([{}])))"));
    EXPECT_FALSE(check_brackets("((([{]])))"));
    EXPECT_FALSE(check_brackets(")))))"));
}
