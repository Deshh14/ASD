#include "expression.h"
#include "parser.h"
#include "Stack.h"
#include <sstream>
#include <stdexcept>
#include <cmath>

Expression::Expression(int _id, const std::string& expr)
    : id(_id), expressionStr(expr), isParsed(false), isPostfixBuilt(false) {}

void Expression::setExpression(const std::string& expr) {
    expressionStr = expr;
    isParsed = false;
    isPostfixBuilt = false;
    infixNotation.clear();
    postfixNotation.clear();
}

void Expression::parse() {
    try {
        infixNotation = Parser::parse(expressionStr);
        isParsed = true;
        isPostfixBuilt = false; // Сбрасываем постфиксную запись
    }
    catch (const ParserException& e) {
        throw;
    }
}

void Expression::buildPostfix() {
    if (!isParsed) {
        parse();
    }

    postfixNotation.clear();
    ArrayStack<Lexem, 100> stack;

    for (auto it = infixNotation.begin(); it != infixNotation.end(); ++it) {
        const Lexem& lexem = *it;

        switch (lexem.type) {
        case TypeLexem::Constant:
        case TypeLexem::Variable:
            postfixNotation.push_back(lexem);
            break;

        case TypeLexem::Function:
            stack.push(lexem);
            break;

        case TypeLexem::OpenBracket:
            stack.push(lexem);
            break;

        case TypeLexem::CloseBracket:
            while (!stack.isEmpty() && stack.top().type != TypeLexem::OpenBracket) {
                postfixNotation.push_back(stack.pop());
            }
            if (stack.isEmpty()) {
                throw std::runtime_error("Mismatched brackets");
            }
            stack.pop(); // Удаляем открывающую скобку
            if (!stack.isEmpty() && stack.top().type == TypeLexem::Function) {
                postfixNotation.push_back(stack.pop());
            }
            break;

        case TypeLexem::Operator:
            while (!stack.isEmpty() &&
                (stack.top().type == TypeLexem::Operator ||
                    stack.top().type == TypeLexem::Function) &&
                stack.top().priority >= lexem.priority) {
                postfixNotation.push_back(stack.pop());
            }
            stack.push(lexem);
            break;

        default:
            break;
        }
    }

    while (!stack.isEmpty()) {
        if (stack.top().type == TypeLexem::OpenBracket) {
            throw std::runtime_error("Mismatched brackets");
        }
        postfixNotation.push_back(stack.pop());
    }

    isPostfixBuilt = true;
}

double Expression::evaluate() {
    if (!isPostfixBuilt) {
        buildPostfix();
    }

    ArrayStack<double, 100> stack;

    for (auto it = postfixNotation.begin(); it != postfixNotation.end(); ++it) {
        const Lexem& lexem = *it;

        switch (lexem.type) {
        case TypeLexem::Constant:
            stack.push(lexem.value);
            break;

        case TypeLexem::Variable: {
            auto varIt = variables.find(lexem.name);
            if (varIt == variables.end()) {
                throw std::runtime_error("Undefined variable: " + lexem.name);
            }
            stack.push(varIt->second);
            break;
        }

        case TypeLexem::Function: {
            if (stack.isEmpty()) {
                throw std::runtime_error("Not enough operands for function: " + lexem.name);
            }
            double arg = stack.pop();
            double result = lexem.function(arg);
            stack.push(result);
            break;
        }

        case TypeLexem::Operator: {
            if (stack.size() < 2) {
                throw std::runtime_error("Not enough operands for operator: " + lexem.name);
            }
            double right = stack.pop();
            double left = stack.pop();
            double result;

            if (lexem.name == "+") result = left + right;
            else if (lexem.name == "-") result = left - right;
            else if (lexem.name == "*") result = left * right;
            else if (lexem.name == "/") {
                if (right == 0) throw std::runtime_error("Division by zero");
                result = left / right;
            }
            else if (lexem.name == "^") result = pow(left, right);
            else throw std::runtime_error("Unknown operator: " + lexem.name);

            stack.push(result);
            break;
        }

        default:
            throw std::runtime_error("Unexpected lexem type in evaluation");
        }
    }

    if (stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return stack.pop();
}

void Expression::setVariable(const std::string& name, double value) {
    variables[name] = value;
}

void Expression::setVariables(const std::map<std::string, double>& vars) {
    variables = vars;
}

double Expression::getVariable(const std::string& name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    throw std::runtime_error("Variable not found: " + name);
}

const std::map<std::string, double>& Expression::getVariables() const {
    return variables;
}