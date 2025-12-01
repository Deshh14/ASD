#ifndef PARSER_H
#define PARSER_H

#include "lexem.h"
#include "List.h"
#include "Tvector.h"  // Используем Tvector вместо vector
#include <string>
#include <map>
#include <iostream>

namespace Parser {
    List<Lexem> parse(const std::string& expression);

    // Вспомогательные функции
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphaNum(char c);
    bool isOperator(char c);
    bool isSpace(char c);
    bool isValidVariableChar(char c);

    int getOperatorPriority(const std::string& op);
    bool isFunction(const std::string& str);
    std::function<double(double)> getFunction(const std::string& funcName);

    void processNumber(const std::string& expression, size_t& pos, List<Lexem>& lexems);
    void processVariable(const std::string& expression, size_t& pos, List<Lexem>& lexems);
    void processOperator(const std::string& expression, size_t& pos, List<Lexem>& lexems);
    void processBracket(const std::string& expression, size_t& pos, List<Lexem>& lexems);
    void processFunction(const std::string& expression, size_t& pos, List<Lexem>& lexems);
    void processAbs(const std::string& expression, size_t& pos, List<Lexem>& lexems);

    void handleUnaryMinus(List<Lexem>& lexems);
    void replaceAbsWithFunction(List<Lexem>& lexems);
}

class ParserException : public std::exception {
private:
    std::string message;
    size_t position;
    std::string expression;

public:
    ParserException(const std::string& msg, size_t pos, const std::string& expr)
        : message(msg), position(pos), expression(expr) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    size_t getPosition() const { return position; }
    const std::string& getExpression() const { return expression; }

    void printError() const {
        std::cout << "Input expression: " << expression << std::endl;
        std::cout << std::string(position, ' ') << "^" << std::endl;
        std::cout << "Error in function 'Parser::parse()' at " << position + 1
            << " symbol: " << message << std::endl;
    }
};

#endif