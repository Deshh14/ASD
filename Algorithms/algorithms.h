#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <string>
#include "algorithms.h"
#include "stack.h"


bool check_brackets(const std::string& expression);
bool check_brackets(const std::string& expression) {
    ArrayStack<char> stack;

    for (char c : expression) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {

            if (stack.isEmpty()) {
                return false;
            }

            char top = stack.pop();

            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }

    return stack.isEmpty();
}

#endif