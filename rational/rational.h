#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <exception>
#include <string>

namespace rational {

class denominator_error: public std::runtime_error {
public:
    explicit denominator_error(const std::string& s): std::runtime_error(s) {}
};

int gcd(int a, int b) {
    int r;
    while (b) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

class Rational {
public:
    Rational(int numerator = 0, int denominator = 1): n(numerator), d(denominator)
    {
        if (denominator == 0) {
            throw denominator_error("denominator can not be 0");
        }
        if (d != 1) { 
            int g = gcd(n, d);
            n /= g;
            d /= g;
        }
    }
    Rational(const Rational& r): n(r.n), d(r.d) {}
    ~Rational() {}

    int numerator() const { return n; }
    int denominator() const { return d; }

private:
    int n;
    int d;

};

std::ostream& operator<<(std::ostream& out, const Rational& r) {
    return out << "R(" << r.numerator() << ", " << r.denominator() << ")";
}

const Rational operator+(const Rational& lhs, const Rational& rhs) {
    int den = lcm(lhs.denominator(), rhs.denominator());
    int num = (lhs.numerator() * den / lhs.denominator())
            + (rhs.numerator() * den / rhs.denominator());
    return Rational(num, den);
}

const Rational operator-(const Rational& lhs, const Rational& rhs) {
    int den = lcm(lhs.denominator(), rhs.denominator());
    int num = (lhs.numerator() * den / lhs.denominator())
            - (rhs.numerator() * den / rhs.denominator());
    return Rational(num, den);
}

const Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator() * rhs.numerator(),
                    lhs.denominator() * rhs.denominator());
}

const Rational operator/(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator() * rhs.denominator(),
                    lhs.denominator() * rhs.numerator());
}

} // rational

#endif //RATIONAL_H
