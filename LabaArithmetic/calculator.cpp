#include "calculator.h"
#include <iostream>
#include <iomanip>
#include "parser_exception.h"

void Calculator::createExpression(const std::string& expr) {
    std::cout << "Creating expression: " << expr << std::endl;
    Expression newExpr(nextId++, expr);
    try {
        newExpr.parse();
        expressions.push_back(newExpr);
        std::cout << "Expression created with ID: " << newExpr.getId() << std::endl;
    }
    catch (const ParserException& e) {
        std::cout << "Parser error: ";
        e.printError();
    }
    catch (const std::exception& e) {
        std::cout << "Error creating expression: " << e.what() << std::endl;
    }
}

void Calculator::deleteExpression(int id) {
    int index = findExpressionIndex(id);
    if (index != -1) {
        expressions.erase(index);
        std::cout << "Expression with ID " << id << " deleted." << std::endl;
    }
    else {
        std::cout << "Expression with ID " << id << " not found." << std::endl;
    }
}

void Calculator::setVariables(int id, const std::map<std::string, double>& variables) {
    Expression* expr = getExpression(id);
    if (expr) {
        expr->setVariables(variables);
        std::cout << "Variables set for expression ID " << id << std::endl;
    }
    else {
        std::cout << "Expression with ID " << id << " not found." << std::endl;
    }
}

double Calculator::evaluateExpression(int id) {
    Expression* expr = getExpression(id);
    if (expr) {
        try {
            double result = expr->evaluate();
            std::cout << "Result: " << result << std::endl;
            return result;
        }
        catch (const std::exception& e) {
            std::cout << "Error evaluating expression: " << e.what() << std::endl;
            return 0.0;
        }
    }
    else {
        std::cout << "Expression with ID " << id << " not found." << std::endl;
        return 0.0;
    }
}

void Calculator::displayAll() const {
    std::cout << "+-------------------------------------------------------------------+" << std::endl;
    std::cout << "| ID  | EXPRESSION                                   | VARIABLES    |" << std::endl;
    std::cout << "+-------------------------------------------------------------------+" << std::endl;

    for (int i = 0; i < expressions.size(); i++) {
        const Expression& expr = expressions[i];
        std::cout << "| " << std::setw(2) << expr.getId() << " | "
            << std::setw(45) << std::left << expr.getExpressionString() << " | ";

        const auto& vars = expr.getVariables();
        if (vars.empty()) {
            std::cout << "not set     |";
        }
        else {
            std::string varStr;
            for (const auto& var : vars) {
                if (!varStr.empty()) varStr += ", ";
                varStr += var.first + " = " + std::to_string(var.second);
            }
            if (varStr.length() > 11) {
                varStr = varStr.substr(0, 8) + "...";
            }
            std::cout << std::setw(11) << std::left << varStr << " |";
        }
        std::cout << std::endl;
    }
    std::cout << "+-------------------------------------------------------------------+" << std::endl;
}

bool Calculator::expressionExists(int id) const {
    return findExpressionIndex(id) != -1;
}

Expression* Calculator::getExpression(int id) {
    int index = findExpressionIndex(id);
    if (index != -1) {
        return &expressions[index];
    }
    return nullptr;
}

int Calculator::findExpressionIndex(int id) const {
    for (int i = 0; i < expressions.size(); i++) {
        if (expressions[i].getId() == id) {
            return i;
        }
    }
    return -1;
}