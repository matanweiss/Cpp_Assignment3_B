#include "Fraction.hpp"

// constructors
Fraction::Fraction() : numerator(1), denominator(1) {}
Fraction::Fraction(int number1, int number2) : numerator(number1), denominator(number2)
{
    if (!number2)
        throw std::invalid_argument("received zero denominator");
    reduce();
}

// helper function
void Fraction::reduce()
{
    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}
int Fraction::compareTo(const Fraction &other) const
{
    int numeratorL = numerator * other.denominator;
    int numeratorR = other.numerator * denominator;
    if (numeratorR < numeratorL)
        return 1;
    else if (numeratorL < numeratorR)
        return -1;
    else
        return 0;
}

// cout & cin
std::ostream &operator<<(std::ostream &stream, const Fraction &fraction)
{
    stream << fraction.numerator << "/" << fraction.denominator;
    return stream;
}
std::istream &operator>>(std::istream &stream, Fraction &fraction)
{
    stream >> fraction.numerator;
    stream >> fraction.denominator;
    if (!fraction.denominator)
        throw std::invalid_argument("received zero denominator");
    fraction.reduce();
    return stream;
}

// arithmetic
Fraction Fraction::operator+(const Fraction &other)
{
    int numeratorL = numerator * other.denominator;
    int denominatorLR = denominator * other.denominator;
    int numeratorR = other.numerator * denominator;
    return Fraction(numeratorL + numeratorR, denominatorLR);
}
Fraction Fraction::operator-(const Fraction &other)
{
    int numeratorL = numerator * other.denominator;
    int denominatorLR = denominator * other.denominator;
    int numeratorR = other.numerator * denominator;
    return Fraction(numeratorL - numeratorR, denominatorLR);
}
Fraction Fraction::operator/(const Fraction &other)
{
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}
Fraction Fraction::operator*(const Fraction &other)
{
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

Fraction operator*(float number, const Fraction &other)
{
    Fraction f(number * 1000, 1000);
    return f * other;
}
Fraction operator-(float number, const Fraction &other)
{
    Fraction f(number * 1000, 1000);
    return f - other;
}
Fraction operator/(float number, const Fraction &other)
{
    Fraction f(number * 1000, 1000);
    return f / other;
}
Fraction operator+(float number, const Fraction &other)
{
    Fraction f(number * 1000, 1000);
    return f + other;
}

Fraction Fraction::operator+(float number)
{
    Fraction f(number * 1000, 1000);
    return *this + f;
}
Fraction Fraction::operator-(float number)
{
    Fraction f(number * 1000, 1000);
    return *this - f;
}
Fraction Fraction::operator*(float number)
{
    Fraction f(number * 1000, 1000);
    return *this * f;
}
Fraction Fraction::operator/(float number)
{
    Fraction f(number * 1000, 1000);
    return *this / f;
}

Fraction &Fraction::operator++()
{
    numerator += denominator;
    return *this;
}
Fraction Fraction::operator++(int dummy)
{
    Fraction temp = *this;
    numerator += denominator;
    return temp;
}
Fraction &Fraction::operator--()
{
    numerator -= denominator;
    return *this;
}
Fraction Fraction::operator--(int dummy)
{
    Fraction temp = *this;
    numerator -= denominator;
    return temp;
}
bool Fraction::operator<=(const Fraction &fraction) const
{
    if (compareTo(fraction) <= 0)
        return true;
    return false;
}
bool Fraction::operator>=(const Fraction &fraction) const
{
    if (0 <= compareTo(fraction))
        return true;
    return false;
}
bool Fraction::operator<(const Fraction &fraction) const
{
    if (compareTo(fraction) < 0)
        return true;
    return false;
}
bool Fraction::operator>(const Fraction &fraction) const
{
    if (0 < compareTo(fraction))
        return true;
    return false;
}
bool Fraction::operator>(float number)
{
    Fraction f(number * 1000, 1000);
    if (0 < compareTo(f))
        return true;
    return false;
}
bool Fraction::operator<(float number)
{
    Fraction f(number * 1000, 1000);
    if (compareTo(f) < 0)
        return true;
    return false;
}
bool Fraction::operator>=(float number)
{
    Fraction f(number * 1000, 1000);
    if (compareTo(f) <= 0)
        return true;
    return false;
}
bool Fraction::operator<=(float) { return false; }
bool operator<=(float number, const Fraction &fraction) { return false; }
bool operator>=(float number, const Fraction &fraction) { return false; }
bool operator<(float number, const Fraction &fraction) { return false; }
bool operator>(float number, const Fraction &fraction) { return false; }
bool Fraction::operator==(const Fraction &fraction) const { return false; }
bool Fraction::operator==(float number) { return false; }
bool operator==(float number, const Fraction &fraction) { return false; }
