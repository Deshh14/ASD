#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "lexem.h"
#include "list.h"
#include <string>
#include <map>

class Expression {
private:
    int id;
    std::string expressionStr;
    List<Lexem> infixNotation;
    List<Lexem> postfixNotation;
    std::map<std::string, double> variables;
    bool isParsed;
    bool isPostfixBuilt;

public:
    Expression(int _id = 0, const std::string& expr = "");

    void setExpression(const std::string& expr);
    void parse();
    void buildPostfix();
    double evaluate();

    void setVariable(const std::string& name, double value);
    void setVariables(const std::map<std::string, double>& vars);
    double getVariable(const std::string& name) const;
    const std::map<std::string, double>& getVariables() const;

    int getId() const { return id; }
    const std::string& getExpressionString() const { return expressionStr; }
    bool getIsParsed() const { return isParsed; }
    bool getIsPostfixBuilt() const { return isPostfixBuilt; }

    const List<Lexem>& getInfixNotation() const { return infixNotation; }
    const List<Lexem>& getPostfixNotation() const { return postfixNotation; }
};

#endif