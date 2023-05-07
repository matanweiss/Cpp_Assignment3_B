#include "Fraction.hpp"

// constructors
Fraction::Fraction() : numerator(1), denominator(1) {}
Fraction::Fraction(float number)
{
    numerator = number * 1000;
    denominator = 1000;
    reduce();
}

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
    handleMinus();
}

void Fraction::handleMinus()
{
    if (denominator < 0)
    {
        numerator = -numerator;
        denominator = -denominator;
    }
}
void Fraction::checkOverflow(long long numeratorResult, long long denominatorResult)
{
    if (numeratorResult < INT_MIN || INT_MAX < numeratorResult || denominatorResult < INT_MIN || INT_MAX < denominatorResult)
        throw std::overflow_error("result overflows");
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
int Fraction::getNumerator()
{
    return numerator;
}
int Fraction::getDenominator()
{
    return denominator;
}
// cout & cin
std::ostream &operator<<(std::ostream &stream, const Fraction &fraction)
{
    stream << fraction.numerator << "/" << fraction.denominator;
    return stream;
}
std::istream &operator>>(std::istream &stream, Fraction &fraction)
{
    if (stream.peek() == EOF)
    {
        throw std::runtime_error("wrong number of arguments");
    }
    stream >> fraction.numerator;
    if (stream.peek() == EOF)
    {
        throw std::runtime_error("wrong number of arguments");
    }
    stream >> fraction.denominator;
    if (!fraction.denominator)
        throw std::runtime_error("received zero denominator");
    fraction.reduce();
    return stream;
}

// arithmetic
Fraction Fraction::operator+(const Fraction &other)
{
    long long numeratorResult = (long long)numerator * other.denominator + (long long)other.numerator * denominator;
    long long denominatorResult = (long long)denominator * other.denominator;
    checkOverflow(numeratorResult, denominatorResult);
    return Fraction((int)numeratorResult, (int)denominatorResult);
}
Fraction Fraction::operator-(const Fraction &other)
{
    long long numeratorResult = (long long)numerator * other.denominator - (long long)other.numerator * denominator;
    long long denominatorResult = (long long)denominator * other.denominator;
    checkOverflow(numeratorResult, denominatorResult);
    return Fraction((int)numeratorResult, (int)denominatorResult);
}
Fraction Fraction::operator/(const Fraction &other)
{
    if (!other.numerator)
        throw std::runtime_error("division by zero");
    long long numeratorResult = (long long)numerator * other.denominator;
    long long denominatorResult = (long long)other.numerator * denominator;
    checkOverflow(numeratorResult, denominatorResult);
    return Fraction((int)numeratorResult, (int)denominatorResult);
}
Fraction Fraction::operator*(const Fraction &other)
{
    long long numeratorResult = (long long)numerator * other.numerator;
    long long denominatorResult = (long long)denominator * other.denominator;
    checkOverflow(numeratorResult, denominatorResult);
    return Fraction((int)numeratorResult, (int)denominatorResult);
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
    if (!other.numerator)
        throw std::runtime_error("division by zero");
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
    if (!number)
        throw std::runtime_error("division by zero");
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
    printf("result of >= is %d\n", compareTo(f));
    if (compareTo(f) >= 0)
        return true;
    return false;
}
bool Fraction::operator<=(float number)
{
    Fraction f(number * 1000, 1000);
    if (compareTo(f) <= 0)
        return true;
    return false;
}
bool operator<=(float number, const Fraction &fraction)
{
    Fraction f(number * 1000, 1000);
    if (fraction.compareTo(f) >= 0)
        return true;
    return false;
}
bool operator>=(float number, const Fraction &fraction)
{
    Fraction f(number * 1000, 1000);
    if (fraction.compareTo(f) <= 0)
        return true;
    return false;
}
bool operator<(float number, const Fraction &fraction)
{
    Fraction f(number * 1000, 1000);
    if (fraction.compareTo(f) > 0)
        return true;
    return false;
}
bool operator>(float number, const Fraction &fraction)
{
    Fraction f(number * 1000, 1000);
    if (fraction.compareTo(f) < 0)
        return true;
    return false;
}
bool Fraction::operator==(const Fraction &fraction) const
{
    if (numerator == fraction.numerator && denominator == fraction.denominator)
        return true;
    return false;
}
bool Fraction::operator==(float number)
{
    Fraction f(number * 1000, 1000);
    return f == *this;
}
bool operator==(float number, const Fraction &fraction)
{
    Fraction f(number * 1000, 1000);
    return f == fraction;
}
