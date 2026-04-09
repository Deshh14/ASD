#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>

class Monom {
private:
    double coef;     
    int degree[3];    

public:
    Monom();
    Monom(double c, int x_deg = 0, int y_deg = 0, int z_deg = 0);
    Monom(const Monom& other);
    Monom(const std::string& str);
    ~Monom();

    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;

    bool operator<(const Monom& other) const;
    bool operator>(const Monom& other) const;

    Monom operator+(const Monom& other) const; 
    Monom operator-(const Monom& other) const; 
    Monom operator*(const Monom& other) const;
    Monom operator/(const Monom& other) const;

    Monom operator*(double c) const;
    Monom operator/(double c) const;

    Monom operator-() const;

    Monom& operator=(const Monom& other);
    Monom& operator+=(const Monom& other);
    Monom& operator-=(const Monom& other);
    Monom& operator*=(const Monom& other);
    Monom& operator/=(const Monom& other);
    Monom& operator*=(double c);
    Monom& operator/=(double c);

    double evaluate(double x, double y, double z) const;

    double getCoef() const { return coef; }
    int getDegreeX() const { return degree[0]; }
    int getDegreeY() const { return degree[1]; }
    int getDegreeZ() const { return degree[2]; }

    void setCoef(double c) { coef = c; }

    friend std::ostream& operator<<(std::ostream& out, const Monom& m);
    friend std::istream& operator>>(std::istream& in, Monom& m);

    bool isSimilar(const Monom& other) const;
    bool isZero() const;
    std::string toString() const;
};

inline Monom::Monom() : coef(0.0) {
    degree[0] = degree[1] = degree[2] = 0;
}

inline Monom::Monom(double c, int x_deg, int y_deg, int z_deg) : coef(c) {
    degree[0] = (x_deg >= 0) ? x_deg : 0;
    degree[1] = (y_deg >= 0) ? y_deg : 0;
    degree[2] = (z_deg >= 0) ? z_deg : 0;
}

inline Monom::Monom(const Monom& other) : coef(other.coef) {
    degree[0] = other.degree[0];
    degree[1] = other.degree[1];
    degree[2] = other.degree[2];
}

inline Monom::~Monom() {}


inline bool Monom::operator==(const Monom& other) const {
    return degree[0] == other.degree[0] &&
        degree[1] == other.degree[1] &&
        degree[2] == other.degree[2];
}

inline bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

inline bool Monom::operator<(const Monom& other) const {
    if (degree[0] != other.degree[0])
        return degree[0] > other.degree[0];
    if (degree[1] != other.degree[1])
        return degree[1] > other.degree[1];
    return degree[2] > other.degree[2];
}

inline bool Monom::operator>(const Monom& other) const {
    return other < *this;
}

inline Monom Monom::operator+(const Monom& other) const {
    if (!isSimilar(other)) {
        throw std::runtime_error("Cannot add monoms with different degrees");
    }
    Monom result(*this);
    result.coef += other.coef;
    return result;
}

inline Monom Monom::operator-(const Monom& other) const {
    if (!isSimilar(other)) {
        throw std::runtime_error("Cannot subtract monoms with different degrees");
    }
    Monom result(*this);
    result.coef -= other.coef;
    return result;
}

inline Monom Monom::operator*(const Monom& other) const {
    Monom result;
    result.coef = coef * other.coef;
    result.degree[0] = degree[0] + other.degree[0];
    result.degree[1] = degree[1] + other.degree[1];
    result.degree[2] = degree[2] + other.degree[2];
    return result;
}

inline Monom Monom::operator/(const Monom& other) const {
    if (other.coef == 0) {
        throw std::runtime_error("Division by zero monom");
    }
    Monom result;
    result.coef = coef / other.coef;
    result.degree[0] = degree[0] - other.degree[0];
    result.degree[1] = degree[1] - other.degree[1];
    result.degree[2] = degree[2] - other.degree[2];

    if (result.degree[0] < 0 || result.degree[1] < 0 || result.degree[2] < 0) {
        throw std::runtime_error("Division results in negative degree");
    }
    return result;
}

inline Monom Monom::operator*(double c) const {
    Monom result(*this);
    result.coef *= c;
    return result;
}

inline Monom Monom::operator/(double c) const {
    if (c == 0) {
        throw std::runtime_error("Division by zero");
    }
    Monom result(*this);
    result.coef /= c;
    return result;
}

inline Monom Monom::operator-() const {
    Monom result(*this);
    result.coef = -coef;
    return result;
}

inline Monom& Monom::operator=(const Monom& other) {
    if (this != &other) {
        coef = other.coef;
        degree[0] = other.degree[0];
        degree[1] = other.degree[1];
        degree[2] = other.degree[2];
    }
    return *this;
}

inline Monom& Monom::operator+=(const Monom& other) {
    if (!isSimilar(other)) {
        throw std::runtime_error("Cannot add monoms with different degrees");
    }
    coef += other.coef;
    return *this;
}

inline Monom& Monom::operator-=(const Monom& other) {
    if (!isSimilar(other)) {
        throw std::runtime_error("Cannot subtract monoms with different degrees");
    }
    coef -= other.coef;
    return *this;
}

inline Monom& Monom::operator*=(const Monom& other) {
    coef *= other.coef;
    degree[0] += other.degree[0];
    degree[1] += other.degree[1];
    degree[2] += other.degree[2];
    return *this;
}

inline Monom& Monom::operator/=(const Monom& other) {
    if (other.coef == 0) {
        throw std::runtime_error("Division by zero monom");
    }
    coef /= other.coef;
    degree[0] -= other.degree[0];
    degree[1] -= other.degree[1];
    degree[2] -= other.degree[2];

    if (degree[0] < 0 || degree[1] < 0 || degree[2] < 0) {
        throw std::runtime_error("Division results in negative degree");
    }
    return *this;
}

inline Monom& Monom::operator*=(double c) {
    coef *= c;
    return *this;
}

inline Monom& Monom::operator/=(double c) {
    if (c == 0) {
        throw std::runtime_error("Division by zero");
    }
    coef /= c;
    return *this;
}

inline double Monom::evaluate(double x, double y, double z) const {
    double result = coef;
    result *= pow(x, degree[0]);
    result *= pow(y, degree[1]);
    result *= pow(z, degree[2]);
    return result;
}

inline bool Monom::isSimilar(const Monom& other) const {
    return *this == other;
}

inline bool Monom::isZero() const {
    return fabs(coef) < 1e-9;
}

inline std::string Monom::toString() const {
    if (isZero()) return "0";

    std::stringstream ss;

    if (fabs(coef - 1.0) > 1e-9 || (degree[0] == 0 && degree[1] == 0 && degree[2] == 0)) {
        ss << coef;
        if (coef == static_cast<int>(coef)) {
            ss << static_cast<int>(coef);
        }
        else {
            ss << coef;
        }
    }

    if (degree[0] > 0) ss << "x^" << degree[0];
    if (degree[1] > 0) ss << "y^" << degree[1];
    if (degree[2] > 0) ss << "z^" << degree[2];

    return ss.str();
}

inline std::ostream& operator<<(std::ostream& out, const Monom& m) {
    if (m.isZero()) {
        out << "0";
        return out;
    }

    if (fabs(m.coef - 1.0) > 1e-9 || (m.degree[0] == 0 && m.degree[1] == 0 && m.degree[2] == 0)) {
        out << m.coef;
    }
    else if (m.coef == -1.0) {
        out << "-";
    }

    if (m.degree[0] > 0) out << "x^" << m.degree[0];
    if (m.degree[1] > 0) out << "y^" << m.degree[1];
    if (m.degree[2] > 0) out << "z^" << m.degree[2];

    return out;
}

inline std::istream& operator>>(std::istream& in, Monom& m) {
    std::string str;
    in >> str;
    m = Monom(str);
    return in;
}

inline Monom::Monom(const std::string& str) : coef(1.0) {
    degree[0] = degree[1] = degree[2] = 0;

    if (str.empty() || str == "0") {
        coef = 0.0;
        return;
    }

    size_t pos = 0;
    bool neg = false;

    if (str[0] == '-') {
        neg = true;
        pos++;
    }

    std::string coef_str;
    while (pos < str.length() && (isdigit(str[pos]) || str[pos] == '.')) {
        coef_str += str[pos];
        pos++;
    }

    if (!coef_str.empty()) {
        coef = std::stod(coef_str);
    }
    if (neg) coef = -coef;

    while (pos < str.length()) {
        char var = str[pos];
        pos++;

        if (pos < str.length() && str[pos] == '^') {
            pos++;
            std::string deg_str;
            while (pos < str.length() && isdigit(str[pos])) {
                deg_str += str[pos];
                pos++;
            }
            int deg = std::stoi(deg_str);

            switch (var) {
            case 'x': degree[0] = deg; break;
            case 'y': degree[1] = deg; break;
            case 'z': degree[2] = deg; break;
            }
        }
        else {
            switch (var) {
            case 'x': degree[0] = 1; break;
            case 'y': degree[1] = 1; break;
            case 'z': degree[2] = 1; break;
            }
        }
    }
}