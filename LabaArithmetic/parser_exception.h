#ifndef PARSER_EXCEPTION_H
#define PARSER_EXCEPTION_H

#include <exception>
#include <string>
#include <iostream>

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