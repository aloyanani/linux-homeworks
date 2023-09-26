#include <iostream>
#include <cmath>

class Complex
{
   

public:
   int a;
   int b;

   // Member initializer list
   Complex(int a, int b): a(a), b(b) {}

   // Overload + operator for complex numbers
   Complex operator+(const Complex& c1);

   // Overload - operator for complex numbers
   Complex operator-(const Complex& c2);

   // Overload * operator to multiply a complex number by a constant
   Complex operator*(int num);

   // A function that returns the absolute value of a complex number
   double absolute_value();

   friend std::ostream& operator<<(std::ostream& out, const Complex& c)
   {
      out << "(" << c.a << ", " << c.b << ")";
      return out;
   }

};
