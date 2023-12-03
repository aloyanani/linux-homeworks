#ifndef PARALLEL_SCHEDULER_H
#define PARALLEL_SCHEDULER_H

#include <queue>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

// Function pointer type for functions that can be executed in the thread pool
typedef void (*pool_function_t)(void*);

class parallel_scheduler {
private:
    int capacity;  
    // Vector to store worker threads
    std::vector<std::thread> workers;  

     // Queue to store tasks
    std::queue<std::function<void()>> task_queue; 

    // Mutex for synchronizing access to the task queue
    std::mutex queue_mutex;  

    // Condition variable for task synchronization
    std::condition_variable condition;  

    // Flag to signal worker threads to stop
    bool stop;  

public:
    // Constructor
    parallel_scheduler(int capacity);

    // Destructor
    ~parallel_scheduler();

    // Run function enqueues tasks to be executed in the thread pool
    void run(pool_function_t function, void* arg);

private:
    // Worker thread function waits  for tasks and executes them
    void worker_thread();
};

#endif // PARALLEL_SCHEDULER_H
