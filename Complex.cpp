// complex.cpp
#include "complex.h"
#include <sstream>
#include <iomanip>
#include <random>
#include <cmath>

std::string Complex::toString() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << re;
    if (im >= 0) oss << " + " << im << "i";
    else         oss << " - " << -im << "i";
    return oss.str();
}

Complex add(const Complex& a, const Complex& b)
{
    return { a.re + b.re, a.im + b.im };
}

Complex subtract(const Complex& a, const Complex& b)
{
    return { a.re - b.re, a.im - b.im };
}

Complex multiply(const Complex& a, const Complex& b)
{
    return { a.re * b.re - a.im * b.im,
             a.re * b.im + a.im * b.re };
}

Complex divide(const Complex& a, const Complex& b)
{
    double denom = b.re * b.re + b.im * b.im;
    return { (a.re * b.re + a.im * b.im) / denom,
             (a.im * b.re - a.re * b.im) / denom };
}

Complex randomComplex(int lower, int upper)
{
    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<double> dist(lower, upper);
    return { dist(rng), dist(rng) };
}