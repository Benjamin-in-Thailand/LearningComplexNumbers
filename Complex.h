// complex.h
#pragma once

#include <string>

struct Complex
{
    double re;   // real part
    double im;   // imaginary part

    // Human‑readable representation
    std::string toString() const;
};

// Arithmetic – each returns the result
Complex add(const Complex& a, const Complex& b);
Complex subtract(const Complex& a, const Complex& b);
Complex multiply(const Complex& a, const Complex& b);
Complex divide(const Complex& a, const Complex& b);

// Random generation
Complex randomComplex(int lower = -10, int upper = 10); // generates the random numbers, alllowing the user to solve the problems by hand. 