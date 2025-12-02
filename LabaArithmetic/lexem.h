#ifndef LEXEM_H
#define LEXEM_H

#include <string>
#include <functional>
#include <cmath>
#include <limits>

constexpr int MAX_ITERATIONS = 100;
constexpr double EPSILON = 1e-15;
constexpr double PI = 3.14159265358979323846;
constexpr double TWO_PI = 6.28318530717958647692;

enum class TypeLexem {
    Constant,
    Variable,
    OpenBracket,
    CloseBracket,
    Function,
    Operator,
    UnOperator,
    OpenedAbs,
    ClosedAbs
};

struct Lexem {
    std::string name;
    TypeLexem type;
    double value;
    int priority;
    std::function<double(double)> function;

    Lexem(const std::string& _name = "", TypeLexem _type = TypeLexem::Variable,
        double _value = 0.0, int _priority = -1,
        std::function<double(double)> _function = nullptr)
        : name(_name), type(_type), value(_value), priority(_priority), function(_function) {}

    bool operator==(const Lexem& other) const {
        return name == other.name && type == other.type && value == other.value;
    }

    bool operator!=(const Lexem& other) const {
        return !(*this == other);
    }
};

// Математические функции - делаем inline
namespace MathFunctions {
    // Вспомогательная функция для факториала
    inline double factorial(int n) {
        double result = 1.0;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

    // Вспомогательная функция для приведения угла в диапазон [-π, π]
    inline double normalize_angle(double x) {
        x = fmod(x, TWO_PI);
        if (x > PI) x -= TWO_PI;
        if (x < -PI) x += TWO_PI;
        return x;
    }

    // Функция абсолютного значения
    inline double my_abs(double x) {
        return (x < 0) ? -x : x;
    }

    // Синус через ряд Тейлора: sin(x) = x - x³/3! + x⁵/5! - ...
    inline double my_sin(double x) {
        x = normalize_angle(x);

        double term = x;
        double sum = term;
        double x_squared = x * x;
        double sign = -1.0;

        for (int n = 3; n < MAX_ITERATIONS; n += 2) {
            term *= x_squared / (n * (n - 1));
            sum += sign * term;
            sign = -sign;

            if (my_abs(term) < EPSILON) break;
        }

        return sum;
    }

    // Косинус через ряд Тейлора: cos(x) = 1 - x²/2! + x⁴/4! - ...
    inline double my_cos(double x) {
        x = normalize_angle(x);

        double term = 1.0;
        double sum = term;
        double x_squared = x * x;
        double sign = -1.0;

        for (int n = 2; n < MAX_ITERATIONS; n += 2) {
            term *= x_squared / (n * (n - 1));
            sum += sign * term;
            sign = -sign;

            if (my_abs(term) < EPSILON) break;
        }

        return sum;
    }

    // Тангенс как отношение синуса к косинусу
    inline double my_tan(double x) {
        double cos_x = my_cos(x);
        if (my_abs(cos_x) < EPSILON) {
            return std::numeric_limits<double>::infinity();
        }
        return my_sin(x) / cos_x;
    }

    // Натуральный логарифм через ряд Тейлора для ln(1+x)
    // Для x > 2 используем ln(x) = ln(x/2) + ln(2)
    inline double my_ln(double x) {
        if (x <= 0) {
            return -std::numeric_limits<double>::infinity();
        }
        if (x == 1.0) return 0.0;

        // Приводим x к диапазону (0, 2]
        int power = 0;
        while (x > 2.0) {
            x /= 2.0;
            power++;
        }
        while (x < 0.5) {
            x *= 2.0;
            power--;
        }

        // Вычисляем ln(1 + y) где y = x - 1 ∈ (-0.5, 1]
        double y = x - 1.0;
        double term = y;
        double sum = term;
        double sign = -1.0;

        for (int n = 2; n < MAX_ITERATIONS; n++) {
            term *= y;
            sum += sign * term / n;
            sign = -sign;

            if (my_abs(term) < EPSILON) break;
        }

        // Добавляем ln(2^power) = power * ln(2)
        return sum + power * 0.6931471805599453; 
    }

    // Экспонента через ряд Тейлора: exp(x) = 1 + x + x²/2! + x³/3! + ...
    inline double my_exp(double x) {
        if (x < -50) return 0.0;

        int iterations = 0;
        while (my_abs(x) > 1.0) {
            x /= 2.0;
            iterations++;
        }

        double term = 1.0;
        double sum = term;

        for (int n = 1; n < MAX_ITERATIONS; n++) {
            term *= x / n;
            sum += term;

            if (my_abs(term) < EPSILON) break;
        }

        for (int i = 0; i < iterations; i++) {
            sum *= sum;
        }

        return sum;
    }

    // Квадратный корень через метод Ньютона
    inline double my_sqrt(double x) {
        if (x < 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        if (x == 0.0) return 0.0;
        if (x == 1.0) return 1.0;

        double guess = x;
        double last_guess;

        // Метод Ньютона: x_{n+1} = 0.5 * (x_n + a/x_n)
        for (int i = 0; i < MAX_ITERATIONS; i++) {
            last_guess = guess;
            guess = 0.5 * (guess + x / guess);

            if (my_abs(guess - last_guess) < EPSILON) break;
        }

        return guess;
    }
}

#endif