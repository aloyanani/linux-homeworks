#include <iostream>
#include <vector>
#include "complex.h"
#include "sort.h"
int main()
{
    Complex a(20 , 6);
    Complex b(7 , 8);
    Complex c(10 , 8);

    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << a * 5 << std::endl;
    std::cout << a.absolute_value() << std::endl;

    std::vector<Complex> array;
    array.push_back(a);
    array.push_back(b);
    array.push_back(c);
    
    bubble_sort<Complex>(array, 3);
    std::cout << std::endl;
    return 0;
}
