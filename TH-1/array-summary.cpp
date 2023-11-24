#include <iostream>
#include <cstdlib>
#include <string.h>
#include <errno.h>
#include <vector>
#include <chrono>
#include <pthread.h>

// Structure to hold data for each thread
struct ThreadData {
    int start;          
    int end;           
    long long thread_sum; 
};

// Thread function to compute the sum of a portion of the array
void* ThreadSum(void* threadArg) {
    ThreadData* data = static_cast<ThreadData*>(threadArg);
    data->thread_sum = 0;

    for (int i = data->start; i < data->end; ++i) {
        data->thread_sum += i;
    }

    return nullptr;
}

int main(int argc, char** argv) {
    // Check if the required command-line arguments are provided
    if (argc < 3) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // Change command-line arguments to int
    int N = std::atoi(argv[1]); 
    int M = std::atoi(argv[2]); 

    // Initialize the array with random values
    std::vector<int> arr(N);
    for (int& value : arr) {
        value = rand();
    }
    
    // Compute sum without using threads
    auto start_time = std::chrono::high_resolution_clock::now();
    long long sum = 0;
    for (int& value : arr) {
        sum += value;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time spent without threads: " << duration.count() << std::endl;
    
    
    sum = 0;

    // Prepare data structures for threaded computation
    std::vector<ThreadData> thread_data(M);
    std::vector<pthread_t> threads(M);
    
    // Start measuring time for threaded computation
    start_time = std::chrono::high_resolution_clock::now();
    int currentIndex = 0;
    
    // Create threads and assign portions of the array to each thread
    for (int i = 0; i < M; ++i) {
        thread_data[i].start = currentIndex;
        thread_data[i].end = currentIndex + (N/M) + (i < (N % M) ? 1 : 0);
    
        // Create a thread for each portion
        int thread_result = pthread_create(&threads[i], nullptr, ThreadSum, &thread_data[i]);
        if(thread_result < 0)
        {
            std::cerr << strerror(thread_result) << std::endl;
            exit(thread_result);
        }

        currentIndex = thread_data[i].end;
    } 
      
    // Wait for all threads to finish
    for (int i = 0; i < M; ++i) {
        int join_result = pthread_join(threads[i], nullptr);
        if(join_result < 0)
        {
            std::cerr << strerror(join_result) << std::endl;
            exit(join_result);
        }
    }

    // Accumulate partial sums from threads
    for (int i = 0; i < M; ++i) {
        sum += thread_data[i].thread_sum;
    }

    // Measure the total time for threaded computation
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time spent with threads: " << duration.count()<<  std::endl;

    return 0;
}
