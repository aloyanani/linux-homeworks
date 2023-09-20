#include <iostream>
#include <cmath>
#include <vector>


class Complex
{
    // a + bi, (a, b)

public:
   int a;
   int b;

   // Member initializer list
   Complex(int a, int b): a(a), b(b) {}

   // Overload + operator for complex numbers
   Complex operator+(const Complex& c1)
   {
     return Complex(a + c1.a, b + c1.b);
   }

   // Overload - operator for complex numbers
   Complex operator-(const Complex& c2)
   {
     return Complex(a - c2.a, b - c2.b);
   }

   // Overload * operator to multiply a complex number by a constant
   Complex operator*(int num)
   {
     return Complex(a * num , b * num);
   }

   // A function that returns the absolute value of a complex number
   double absolute_value()
   {
     return sqrt(a * a + b * b);
   }
   friend std::ostream& operator<<(std::ostream& out, const Complex& c)
   {
      out << "(" << c.a << ", " << c.b << ")";
      return out;
   }


};

