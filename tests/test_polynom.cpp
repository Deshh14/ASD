#include <gtest/gtest.h>
#include "Polynom.h"

// Тесты для Monom
TEST(MonomTest, ConstructorAndGetters) {
    Monom m1(5.5, 2, 1, 3);
    EXPECT_DOUBLE_EQ(5.5, m1.getCoef());
    EXPECT_EQ(2, m1.getDegreeX());
    EXPECT_EQ(1, m1.getDegreeY());
    EXPECT_EQ(3, m1.getDegreeZ());

    Monom m2(-3.0);
    EXPECT_DOUBLE_EQ(-3.0, m2.getCoef());
    EXPECT_EQ(0, m2.getDegreeX());
}

TEST(MonomTest, StringConstructor) {
    Monom m1("3x^2y^1z^3");
    EXPECT_DOUBLE_EQ(3.0, m1.getCoef());
    EXPECT_EQ(2, m1.getDegreeX());
    EXPECT_EQ(1, m1.getDegreeY());
    EXPECT_EQ(3, m1.getDegreeZ());

    Monom m2("-5");
    EXPECT_DOUBLE_EQ(-5.0, m2.getCoef());

    Monom m3("x^2y");
    EXPECT_DOUBLE_EQ(1.0, m3.getCoef());
    EXPECT_EQ(2, m3.getDegreeX());
    EXPECT_EQ(1, m3.getDegreeY());
}

TEST(MonomTest, Similarity) {
    Monom m1(3.0, 2, 1, 0);
    Monom m2(5.0, 2, 1, 0);
    Monom m3(4.0, 1, 2, 0);

    EXPECT_TRUE(m1.isSimilar(m2));
    EXPECT_FALSE(m1.isSimilar(m3));
    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m1 != m3);
}

TEST(MonomTest, Arithmetic) {
    Monom m1(3.0, 2, 1, 0);
    Monom m2(5.0, 2, 1, 0);
    Monom m3(2.0, 1, 1, 0);

    Monom sum = m1 + m2;
    EXPECT_DOUBLE_EQ(8.0, sum.getCoef());

    Monom product = m1 * m3;
    EXPECT_DOUBLE_EQ(6.0, product.getCoef());
    EXPECT_EQ(3, product.getDegreeX());
    EXPECT_EQ(2, product.getDegreeY());
}

TEST(MonomTest, Evaluate) {
    Monom m(2.0, 2, 1, 3);
    double val = m.evaluate(2, 3, 4);
    EXPECT_DOUBLE_EQ(1536.0, val);
}

TEST(MonomTest, MultiplyByConstant) {
    Monom m(3.0, 2, 1, 0);
    Monom result = m * 2.5;
    EXPECT_DOUBLE_EQ(7.5, result.getCoef());
}

// Тесты для Polynom
TEST(PolynomTest, ConstructorAndAdd) {
    Polynom p;
    EXPECT_TRUE(p.isEmpty());
    EXPECT_EQ(0, p.getSize());

    p.addMonom(Monom(3.0, 2, 0, 0));
    p.addMonom(Monom(5.0, 1, 1, 0));
    EXPECT_EQ(2, p.getSize());
}

TEST(PolynomTest, StringConstructor) {
    Polynom p("3x^2 + 2xy + 5");
    EXPECT_EQ(3, p.getSize());
}

TEST(PolynomTest, Simplify) {
    Polynom p;
    p.addMonom(Monom(3.0, 2, 0, 0));
    p.addMonom(Monom(5.0, 2, 0, 0));
    p.addMonom(Monom(2.0, 1, 1, 0));

    EXPECT_EQ(2, p.getSize());
}

TEST(PolynomTest, Addition) {
    Polynom p1("3x^2 + 2xy");
    Polynom p2("5x^2 + 3yz");
    Polynom result = p1 + p2;

    EXPECT_EQ(3, result.getSize()); 
}

TEST(PolynomTest, Subtraction) {
    Polynom p1("3x^2 + 5x");
    Polynom p2("x^2 + 2x");
    Polynom result = p1 - p2;

    EXPECT_EQ(2, result.getSize()); 
}

TEST(PolynomTest, Multiplication) {
    Polynom p1("x + y");
    Polynom p2("x - y");
    Polynom result = p1 * p2;

    EXPECT_EQ(2, result.getSize());
}

TEST(PolynomTest, Evaluate) {
    Polynom p("3x^2 + 2x + 1");
    double val = p.evaluate(2, 0, 0);
    EXPECT_DOUBLE_EQ(17.0, val);
}

TEST(PolynomTest, EvaluateWithThreeVariables) {
    Polynom p("2x^2y + 3yz");
    double val = p.evaluate(2, 3, 4);
    EXPECT_DOUBLE_EQ(60.0, val);
}

TEST(PolynomTest, CompoundOperations) {
    Polynom p("x^2 + x");
    p += Polynom("2x^2 + 3");
    EXPECT_EQ(3, p.getSize());

    p *= 2;
    EXPECT_DOUBLE_EQ(6.0, p[0].getCoef());
}
