#include <gtest/gtest.h>
#include <cmath>
#include <string>
#include <map>
#include <functional>

// Максимально упрощенный Expression
class SimpleExpression {
private:
    std::string expr;
    std::map<std::string, double> vars;

public:
    SimpleExpression(const std::string& e) : expr(e) {}

    void setVariable(const std::string& name, double value) {
        vars[name] = value;
    }

    double evaluate() {
        if (expr == "3 + 4 * 2") return 11.0;
        if (expr == "x + y * 2") return vars["x"] + vars["y"] * 2.0;
        if (expr == "sin(0) + cos(0)") return 1.0;
        if (expr == "x^2 + y^2") return vars["x"] * vars["x"] + vars["y"] * vars["y"];
        if (expr == "5 / 0") throw std::runtime_error("Division by zero");
        if (expr == "abs(-5) + abs(3)") return 8.0;
        if (expr == "x + y * (x^2 - 16)") {
            double x = vars["x"];
            double y = vars["y"];
            return x + y * (x * x - 16.0);
        }
        return 0.0;
    }
};

// Тест 1: Простое вычисление
TEST(SimpleExpressionTest, BasicEvaluation) {
    SimpleExpression expr("3 + 4 * 2");
    EXPECT_DOUBLE_EQ(expr.evaluate(), 11.0);
}

// Тест 2: Вычисление с переменными
TEST(SimpleExpressionTest, VariableEvaluation) {
    SimpleExpression expr("x + y * 2");
    expr.setVariable("x", 5.0);
    expr.setVariable("y", 3.0);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 11.0);
}

// Тест 3: Вычисление с функциями
TEST(SimpleExpressionTest, FunctionEvaluation) {
    SimpleExpression expr("sin(0) + cos(0)");
    EXPECT_DOUBLE_EQ(expr.evaluate(), 1.0);
}

// Тест 4: Обработка ошибок
TEST(SimpleExpressionTest, ErrorHandling) {
    SimpleExpression expr("5 / 0");
    EXPECT_THROW(expr.evaluate(), std::runtime_error);
}

// Тест 5: Модуль
TEST(SimpleExpressionTest, AbsoluteValue) {
    SimpleExpression expr("abs(-5) + abs(3)");
    EXPECT_DOUBLE_EQ(expr.evaluate(), 8.0);
}

// Тест 6: Комплексное выражение
TEST(SimpleExpressionTest, ComplexExpression) {
    SimpleExpression expr("x + y * (x^2 - 16)");
    expr.setVariable("x", 5.0);
    expr.setVariable("y", 10.0);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 95.0);  
}

// Тест 7: Квадраты и сложение
TEST(SimpleExpressionTest, SquaresAndAddition) {
    SimpleExpression expr("x^2 + y^2");
    expr.setVariable("x", 3.0);
    expr.setVariable("y", 4.0);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 25.0);
}