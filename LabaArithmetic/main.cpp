#include "calculator.h"
#include <iostream>
#include <map>
#include <sstream>

void displayMenu() {
    std::cout << "\n=== CALCULATOR MENU ===" << std::endl;
    std::cout << "1. Create new expression" << std::endl;
    std::cout << "2. Delete expression" << std::endl;
    std::cout << "3. Set variables" << std::endl;
    std::cout << "4. Evaluate expression" << std::endl;
    std::cout << "5. Display all expressions" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Your choice: ";
}

std::map<std::string, double> readVariables() {
    std::map<std::string, double> variables;
    std::string input;

    std::cout << "Enter variables in format 'name=value' (separated by commas, empty to finish): ";
    std::getline(std::cin, input);

    if (!input.empty()) {
        std::stringstream ss(input);
        std::string pair;

        while (std::getline(ss, pair, ',')) {
            size_t equalsPos = pair.find('=');
            if (equalsPos != std::string::npos) {
                std::string name = pair.substr(0, equalsPos);
               
                name.erase(0, name.find_first_not_of(" \t"));
                name.erase(name.find_last_not_of(" \t") + 1);

                std::string valueStr = pair.substr(equalsPos + 1);
                valueStr.erase(0, valueStr.find_first_not_of(" \t"));
                valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

                try {
                    double value = std::stod(valueStr);
                    variables[name] = value;
                    std::cout << "Set variable: " << name << " = " << value << std::endl;
                }
                catch (const std::exception&) {
                    std::cout << "Invalid value for variable " << name << std::endl;
                }
            }
        }
    }

    return variables;
}

int main() {
    Calculator calculator;
    int choice;

    std::cout << "=== CALCULATOR STARTED ===" << std::endl;

    // Добавляем примеры из задания
    std::cout << "Creating example expressions..." << std::endl;
    calculator.createExpression("x + y * (x^2 - 16)");
    calculator.createExpression("x_1 * sin(y + 7) + y * (-|x_2 - 17| + 23)");

    // Устанавливаем переменные для первого выражения
    std::cout << "Setting variables for expression 1..." << std::endl;
    std::map<std::string, double> vars1 = { {"x", 5.0}, {"y", 10.0} };
    calculator.setVariables(1, vars1);

    // Показываем все выражения
    calculator.displayAll();

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
        case 1: {
            std::string expression;
            std::cout << "Enter expression: ";
            std::getline(std::cin, expression);
            calculator.createExpression(expression);
            break;
        }
        case 2: {
            int id;
            std::cout << "Enter expression ID to delete: ";
            std::cin >> id;
            calculator.deleteExpression(id);
            break;
        }
        case 3: {
            int id;
            std::cout << "Enter expression ID: ";
            std::cin >> id;
            std::cin.ignore(); 

            if (calculator.expressionExists(id)) {
                std::map<std::string, double> variables = readVariables();
                calculator.setVariables(id, variables);
            }
            else {
                std::cout << "Expression with ID " << id << " not found." << std::endl;
            }
            break;
        }
        case 4: {
            int id;
            std::cout << "Enter expression ID: ";
            std::cin >> id;
            calculator.evaluateExpression(id);
            break;
        }
        case 5:
            calculator.displayAll();
            break;
        case 0:
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}