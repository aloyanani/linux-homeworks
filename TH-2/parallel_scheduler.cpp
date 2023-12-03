
#include "parallel_scheduler.h"
#include <iostream>
#include <chrono>

// Initialize the thread pool with a specified capacity
parallel_scheduler::parallel_scheduler(int capacity): capacity(capacity), stop(false) {
    // Create worker threads
    for (int i = 0; i < capacity; ++i) {
        workers.push_back(std::thread([this] { worker_thread(); }));
    }
}

// Cleans up the thread pool
parallel_scheduler::~parallel_scheduler() {
    {
        // Notify worker threads to stop
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }

    // Notify all worker threads and wait for them to finish
    condition.notify_all();

    for (std::thread& worker : workers) {
        worker.join();
    }
}

// Run function
void parallel_scheduler::run(pool_function_t function, void* arg) {
    {
        // Enqueue the task
        std::unique_lock<std::mutex> lock(queue_mutex);
        task_queue.emplace([function, arg]() { function(arg); });
    }

    // Notify one worker thread to execute the task
    condition.notify_one();
}

// Worker thread function
void parallel_scheduler::worker_thread() {
    while (true) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            // Wait for a task to be available or stop signal
            condition.wait(lock, [this] { return stop || !task_queue.empty(); });

            // Check for stop signal and empty queue
            if (stop && task_queue.empty()) {
                return;
            }

            // Get the next task
            task = std::move(task_queue.front());
            task_queue.pop();
        }

        // Execute the task
        task();
    }
}

// Sample function to be executed in the thread pool
void sample_function(void* arg) {
    int* value = static_cast<int*>(arg);
    std::cout << "Thread ID: " << std::this_thread::get_id() << ", Value: " << *value << std::endl;
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

// Main function for demonstration purposes
int main() {
    // Create a thread pool with a capacity of 3
    parallel_scheduler scheduler(3);

    // Submit tasks to the thread pool
    for (int i = 0; i < 10; ++i) {
        scheduler.run(sample_function, new int(i));
    }

    // Allow some time for tasks to complete
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}
