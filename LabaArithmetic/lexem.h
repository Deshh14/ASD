#ifndef LEXEM_H
#define LEXEM_H

#include <string>
#include <functional>
#include <cmath>

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
    inline double my_sin(double x) { return sin(x); }
    inline double my_cos(double x) { return cos(x); }
    inline double my_tan(double x) { return tan(x); }
    inline double my_ln(double x) { return log(x); }
    inline double my_exp(double x) { return exp(x); }
    inline double my_abs(double x) { return fabs(x); }
    inline double my_sqrt(double x) { return sqrt(x); }
}

#endif