#include "parser.h"
#include <sstream>
#include <cctype>
#include <algorithm>

List<Lexem> Parser::parse(const std::string& expression) {
    std::cout << "Parsing expression: " << expression << std::endl;
    List<Lexem> lexems;
    size_t pos = 0;

    while (pos < expression.length()) {
        if (isSpace(expression[pos])) {
            pos++;
            continue;
        }

        if (isDigit(expression[pos]) || (expression[pos] == '.' && pos + 1 < expression.length() && isDigit(expression[pos + 1]))) {
            processNumber(expression, pos, lexems);
        }
        else if (isAlpha(expression[pos])) {
            if (pos + 1 < expression.length() && isAlpha(expression[pos + 1])) {
                std::string potentialFunc;
                while (pos < expression.length() && isAlpha(expression[pos])) {
                    potentialFunc += expression[pos];
                    pos++;
                }

                if (isFunction(potentialFunc)) {
                    Lexem funcLexem(potentialFunc, TypeLexem::Function, 0.0, 4, getFunction(potentialFunc));
                    lexems.push_back(funcLexem);
                }
                else {
                    // Это переменная
                    pos -= potentialFunc.length();
                    processVariable(expression, pos, lexems);
                }
            }
            else {
                processVariable(expression, pos, lexems);
            }
        }
        else if (isOperator(expression[pos])) {
            processOperator(expression, pos, lexems);
        }
        else if (expression[pos] == '(' || expression[pos] == '[' || expression[pos] == '{') {
            processBracket(expression, pos, lexems);
        }
        else if (expression[pos] == ')' || expression[pos] == ']' || expression[pos] == '}') {
            processBracket(expression, pos, lexems);
        }
        else if (expression[pos] == '|') {
            processAbs(expression, pos, lexems);
        }
        else {
            throw ParserException("Unexpected character: " + std::string(1, expression[pos]), pos, expression);
        }
    }

    // Обработка унарного минуса и модулей
    handleUnaryMinus(lexems);
    replaceAbsWithFunction(lexems);

    std::cout << "Parsing completed. Found " << lexems.size() << " lexems." << std::endl;
    return lexems;
}

bool Parser::isDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c));
}

bool Parser::isAlpha(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
}

bool Parser::isAlphaNum(char c) {
    return isAlpha(c) || isDigit(c);
}

bool Parser::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool Parser::isSpace(char c) {
    return std::isspace(static_cast<unsigned char>(c));
}

bool Parser::isValidVariableChar(char c) {
    return isAlphaNum(c);
}

int Parser::getOperatorPriority(const std::string& op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

bool Parser::isFunction(const std::string& str) {
    static Tvector<std::string> functions = {
        "sin", "cos", "tan", "tg", "ln", "log", "exp", "sqrt", "abs"
    };

    for (int i = 0; i < functions.size(); i++) {
        if (functions[i] == str) {
            return true;
        }
    }
    return false;
}

std::function<double(double)> Parser::getFunction(const std::string& funcName) {
    if (funcName == "sin") return MathFunctions::my_sin;
    if (funcName == "cos") return MathFunctions::my_cos;
    if (funcName == "tan" || funcName == "tg") return MathFunctions::my_tan;
    if (funcName == "ln") return MathFunctions::my_ln;
    if (funcName == "exp") return MathFunctions::my_exp;
    if (funcName == "sqrt") return MathFunctions::my_sqrt;
    if (funcName == "abs") return MathFunctions::my_abs;
    return nullptr;
}

void Parser::processNumber(const std::string& expression, size_t& pos, List<Lexem>& lexems) {
    std::string numberStr;
    bool hasDecimal = false;

    while (pos < expression.length() && (isDigit(expression[pos]) || expression[pos] == '.')) {
        if (expression[pos] == '.') {
            if (hasDecimal) {
                throw ParserException("Invalid number format: multiple decimal points", pos, expression);
            }
            hasDecimal = true;
        }
        numberStr += expression[pos];
        pos++;
    }

    try {
        double value = std::stod(numberStr);
        Lexem numberLexem(numberStr, TypeLexem::Constant, value);
        lexems.push_back(numberLexem);
    }
    catch (const std::exception&) {
        throw ParserException("Invalid number format: " + numberStr, pos - numberStr.length(), expression);
    }
}

void Parser::processVariable(const std::string& expression, size_t& pos, List<Lexem>& lexems) {
    std::string varName;

    while (pos < expression.length() && isValidVariableChar(expression[pos])) {
        varName += expression[pos];
        pos++;
    }

    if (varName.empty()) {
        throw ParserException("Empty variable name", pos, expression);
    }

    Lexem varLexem(varName, TypeLexem::Variable);
    lexems.push_back(varLexem);
}

void Parser::processOperator(const std::string& expression, size_t& pos, List<Lexem>& lexems) {
    std::string op(1, expression[pos]);
    int priority = getOperatorPriority(op);

    Lexem opLexem(op, TypeLexem::Operator, 0.0, priority);
    lexems.push_back(opLexem);
    pos++;
}

void Parser::processBracket(const std::string& expression, size_t& pos, List<Lexem>& lexems) {
    char bracket = expression[pos];

    if (bracket == '(' || bracket == '[' || bracket == '{') {
        Lexem bracketLexem(std::string(1, bracket), TypeLexem::OpenBracket);
        lexems.push_back(bracketLexem);
    }
    else {
        Lexem bracketLexem(std::string(1, bracket), TypeLexem::CloseBracket);
        lexems.push_back(bracketLexem);
    }
    pos++;
}

void Parser::processAbs(const std::string& expression, size_t& pos, List<Lexem>& lexems) {
    // Определяем тип скобки модуля
    TypeLexem type;
    if (lexems.empty()) {
        type = TypeLexem::OpenedAbs;
    }
    else {
        // Получаем последнюю лексему
        Lexem lastLexem = lexems.back();
        type = (lastLexem.type == TypeLexem::Operator ||
            lastLexem.type == TypeLexem::OpenBracket ||
            lastLexem.type == TypeLexem::Function) ?
            TypeLexem::OpenedAbs : TypeLexem::ClosedAbs;
    }

    Lexem absLexem("|", type);
    lexems.push_back(absLexem);
    pos++;
}

void Parser::handleUnaryMinus(List<Lexem>& lexems) {
    if (lexems.empty()) return;

    List<Lexem> result;

    // Обработка первого элемента
    auto it = lexems.begin();
    if (it != lexems.end() && it->name == "-" && it->type == TypeLexem::Operator) {
        // Первый элемент - унарный минус
        result.push_back(Lexem("0", TypeLexem::Constant, 0.0));
        result.push_back(Lexem("-", TypeLexem::Operator, 0.0, 1));
        ++it;
    }
    else {
        result.push_back(*it);
        ++it;
    }

    // Обработка остальных элементов
    Lexem prevLexem = result.back();
    while (it != lexems.end()) {
        if (it->name == "-" && it->type == TypeLexem::Operator) {
            bool isUnary = (prevLexem.type == TypeLexem::Operator ||
                prevLexem.type == TypeLexem::OpenBracket);

            if (isUnary) {
                result.push_back(Lexem("0", TypeLexem::Constant, 0.0));
                result.push_back(Lexem("-", TypeLexem::Operator, 0.0, 1));
                prevLexem = result.back();
            }
            else {
                result.push_back(*it);
                prevLexem = *it;
            }
        }
        else {
            result.push_back(*it);
            prevLexem = *it;
        }
        ++it;
    }

    lexems = result;
}

void Parser::replaceAbsWithFunction(List<Lexem>& lexems) {
    List<Lexem> result;
    int absDepth = 0;

    for (auto it = lexems.begin(); it != lexems.end(); ++it) {
        if (it->type == TypeLexem::OpenedAbs) {
            if (absDepth == 0) {
                result.push_back(Lexem("abs", TypeLexem::Function, 0.0, 4, MathFunctions::my_abs));
                result.push_back(Lexem("(", TypeLexem::OpenBracket));
            }
            else {
                result.push_back(Lexem("abs", TypeLexem::Function, 0.0, 4, MathFunctions::my_abs));
                result.push_back(Lexem("(", TypeLexem::OpenBracket));
            }
            absDepth++;
        }
        else if (it->type == TypeLexem::ClosedAbs) {
            if (absDepth > 0) {
                result.push_back(Lexem(")", TypeLexem::CloseBracket));
                if (absDepth > 1) {
                    // Для вложенных модулей добавляем закрывающие скобки
                    for (int i = 1; i < absDepth; i++) {
                        result.push_back(Lexem(")", TypeLexem::CloseBracket));
                    }
                }
            }
            absDepth = (absDepth > 0) ? absDepth - 1 : 0;
        }
        else {
            result.push_back(*it);
        }
    }

    lexems = result;
}