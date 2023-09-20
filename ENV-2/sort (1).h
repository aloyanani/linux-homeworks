#include <iostream>
#include <vector>

template <class T>
void bubble_sort(std::vector<T>& arr, int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j) 
        {
            if (arr[j].absolute_value() > arr[j + 1].absolute_value())
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
   for (int i = 0; i < size ; ++i)
   {
      std::cout<<arr[i]<<" ";
   }
}