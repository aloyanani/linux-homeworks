#include "parallel_scheduler.cpp"
#include <iostream>

// Sample function to be executed in the thread pool
void sample_function(void* arg) {

   int* value = static_cast<int*>(arg); 
    std::cout << " Value: " << *value << std::endl;
    
}


int main() {

    // Create a thread pool with a capacity of 3
    parallel_scheduler scheduler(3);

    // Submit tasks to the thread pool
    for (int i = 0; i < 5; ++i) {
        scheduler.run(&sample_function, new int(i));
    }

    return 0;
}