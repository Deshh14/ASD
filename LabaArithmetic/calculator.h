#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "expression.h"
#include "TVector.h"
#include <iostream>
#include <map>

class Calculator {
private:
    Tvector<Expression> expressions;
    int nextId;

public:
    Calculator() : nextId(1) {}

    void createExpression(const std::string& expr);
    void deleteExpression(int id);
    void setVariables(int id, const std::map<std::string, double>& variables);
    double evaluateExpression(int id);

    void displayAll() const;
    bool expressionExists(int id) const;
    Expression* getExpression(int id);

private:
    int findExpressionIndex(int id) const;
};

#endif