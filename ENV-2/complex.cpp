#include <iostream>
#include "complex.h"


// Overload + operator for complex numbers
Complex Complex::operator+(const Complex& c1)
{
  return Complex(a + c1.a, b + c1.b);
}

// Overload - operator for complex numbers
Complex Complex::operator-(const Complex& c2)
{
  return Complex(a - c2.a, b - c2.b);
}

// Overload * operator to multiply a complex number by a constant
Complex Complex::operator*(int num)
{
  return Complex(a * num , b * num);
}

double Complex::absolute_value()
{
  return sqrt(a * a + b * b);
}
