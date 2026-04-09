#pragma once
#include "Monom.h"
#include "List.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

class Polynom {
private:
    List<Monom> monoms;

    void simplify();                   
    void sortMonoms();                  
    void removeZeroMonoms();           

public:
    Polynom();
    Polynom(const Polynom& other);
    Polynom(const std::string& str);
    ~Polynom();

    Polynom& operator=(const Polynom& other);

    Polynom operator+(const Polynom& other) const;
    Polynom operator-(const Polynom& other) const;
    Polynom operator*(const Polynom& other) const;
    Polynom operator*(double c) const;
    Polynom operator/(double c) const;
    Polynom operator-() const;

    Polynom& operator+=(const Polynom& other);
    Polynom& operator-=(const Polynom& other);
    Polynom& operator*=(const Polynom& other);
    Polynom& operator*=(double c);
    Polynom& operator/=(double c);

    bool operator==(const Polynom& other) const;
    bool operator!=(const Polynom& other) const;

    double evaluate(double x, double y, double z) const;

    void addMonom(const Monom& m);

    int getSize() const { return monoms.size(); }
    bool isEmpty() const { return monoms.empty(); }

    friend std::ostream& operator<<(std::ostream& out, const Polynom& p);
    friend std::istream& operator>>(std::istream& in, Polynom& p);

    Monom& operator[](int index);
    const Monom& operator[](int index) const;
};

inline Polynom::Polynom() {}

inline Polynom::Polynom(const Polynom& other) : monoms(other.monoms) {}

inline Polynom::Polynom(const std::string& str) {
    std::string s = str;
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

    size_t pos = 0;
    size_t plus_pos = s.find('+', pos);

    while (plus_pos != std::string::npos) {
        std::string token = s.substr(pos, plus_pos - pos);
        if (!token.empty()) {
            try {
                Monom m(token);
                addMonom(m);
            }
            catch (...) {
            }
        }
        pos = plus_pos + 1;
        plus_pos = s.find('+', pos);
    }

    std::string last_token = s.substr(pos);
    if (!last_token.empty()) {
        try {
            Monom m(last_token);
            addMonom(m);
        }
        catch (...) {
        }
    }

    simplify();
}

inline Polynom::~Polynom() {}

inline void Polynom::simplify() {
    sortMonoms();

    List<Monom> simplified;

    for (auto it = monoms.begin(); it != monoms.end(); ++it) {
        Monom current = *it; 

        if (simplified.empty()) {
            simplified.push_back(current);
            continue;
        }

        Monom& last = simplified.back();

        if (last.isSimilar(current)) {
            Monom sum = last + current;
            if (sum.isZero()) {
                simplified.pop_back();
            }
            else {
                last = sum;
            }
        }
        else {
            simplified.push_back(current);
        }
    }

    monoms = simplified;
}

inline void Polynom::sortMonoms() {
    int size = monoms.size();
    if (size <= 1) return;

    Monom* arr = new Monom[size];
    int i = 0;
    for (auto it = monoms.begin(); it != monoms.end(); ++it) {
        arr[i++] = *it; 
    }

    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] < arr[j]) {
                Monom temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    monoms.clear();
    for (int i = 0; i < size; ++i) {
        monoms.push_back(arr[i]);
    }

    delete[] arr;
}

inline void Polynom::removeZeroMonoms() {
    for (auto it = monoms.begin(); it != monoms.end(); ) {
        if ((*it).isZero()) { 
            it = monoms.erase(it);
        }
        else {
            ++it;
        }
    }
}

inline Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        monoms = other.monoms;
    }
    return *this;
}

inline Polynom Polynom::operator+(const Polynom& other) const {
    Polynom result(*this);
    result += other;
    return result;
}

inline Polynom Polynom::operator-(const Polynom& other) const {
    Polynom result(*this);
    result -= other;
    return result;
}

inline Polynom Polynom::operator*(const Polynom& other) const {
    Polynom result;

    for (auto it1 = monoms.begin(); it1 != monoms.end(); ++it1) {
        for (auto it2 = other.monoms.begin(); it2 != other.monoms.end(); ++it2) {
            result.addMonom((*it1) * (*it2));  
        }
    }

    result.simplify();
    return result;
}

inline Polynom Polynom::operator*(double c) const {
    Polynom result(*this);
    result *= c;
    return result;
}

inline Polynom Polynom::operator/(double c) const {
    Polynom result(*this);
    result /= c;
    return result;
}

inline Polynom Polynom::operator-() const {
    Polynom result;
    for (auto it = monoms.begin(); it != monoms.end(); ++it) {
        result.addMonom(-(*it)); 
    }
    return result;
}

inline Polynom& Polynom::operator+=(const Polynom& other) {
    for (auto it = other.monoms.begin(); it != other.monoms.end(); ++it) {
        addMonom(*it);  
    }
    simplify();
    return *this;
}

inline Polynom& Polynom::operator-=(const Polynom& other) {
    for (auto it = other.monoms.begin(); it != other.monoms.end(); ++it) {
        addMonom(-(*it));  
    }
    simplify();
    return *this;
}

inline Polynom& Polynom::operator*=(const Polynom& other) {
    *this = *this * other;
    return *this;
}

inline Polynom& Polynom::operator*=(double c) {
    for (auto it = monoms.begin(); it != monoms.end(); ++it) {
        *it = (*it) * c;  
    }
    return *this;
}

inline Polynom& Polynom::operator/=(double c) {
    if (c == 0) {
        throw std::runtime_error("Division by zero");
    }
    for (auto it = monoms.begin(); it != monoms.end(); ++it) {
        *it = (*it) / c;
    }
    return *this;
}


inline bool Polynom::operator==(const Polynom& other) const {
    if (monoms.size() != other.monoms.size()) return false;

    auto it1 = monoms.begin();
    auto it2 = other.monoms.begin();

    while (it1 != monoms.end() && it2 != other.monoms.end()) {
        if ((*it1) != (*it2)) return false; 
        ++it1;
        ++it2;
    }

    return true;
}

inline bool Polynom::operator!=(const Polynom& other) const {
    return !(*this == other);
}

inline double Polynom::evaluate(double x, double y, double z) const {
    double result = 0.0;
    for (auto it = monoms.begin(); it != monoms.end(); ++it) {
        result += (*it).evaluate(x, y, z); 
    }
    return result;
}

inline void Polynom::addMonom(const Monom& m) {
    if (m.isZero()) return;

    for (auto it = monoms.begin(); it != monoms.end(); ++it) {
        if ((*it).isSimilar(m)) {  
            Monom sum = (*it) + m; 
            if (sum.isZero()) {
                monoms.erase(it);
            }
            else {
                *it = sum;
            }
            sortMonoms();
            return;
        }
    }

    monoms.push_back(m);
    sortMonoms();
}

inline std::ostream& operator<<(std::ostream& out, const Polynom& p) {
    if (p.monoms.empty()) {
        out << "0";
        return out;
    }

    bool first = true;
    for (auto it = p.monoms.begin(); it != p.monoms.end(); ++it) {
        if (!first && (*it).getCoef() > 0) {  
            out << " + ";
        }
        else if (!first && (*it).getCoef() < 0) {
            out << " - ";
            out << -(*it);
            continue;
        }
        out << *it;
        first = false;
    }
    return out;
}

inline std::istream& operator>>(std::istream& in, Polynom& p) {
    std::string str;
    std::getline(in, str);
    p = Polynom(str);
    return in;
}

inline Monom& Polynom::operator[](int index) {
    if (index < 0 || index >= static_cast<int>(monoms.size())) {
        throw std::out_of_range("Index out of range");
    }
    auto it = monoms.begin();
    for (int i = 0; i < index; ++i) {
        ++it;
    }
    return *it;
}

inline const Monom& Polynom::operator[](int index) const {
    if (index < 0 || index >= static_cast<int>(monoms.size())) {
        throw std::out_of_range("Index out of range");
    }
    auto it = monoms.begin();
    for (int i = 0; i < index; ++i) {
        ++it;
    }
    return *it;
}