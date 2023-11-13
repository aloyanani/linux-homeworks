#include <iostream>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>


void do_command(char** argv) {
   
    struct tms start, end;
    clock_t start_time, end_time;
    start_time = times(&start);

    // Creates a new process
    pid_t pid = fork();

    if (pid < 0) {
        // Error handling: Unable to create a child process
        std::cerr <<strerror(errno) << std::endl;
        exit(errno);
    } 

    else if (pid == 0) {
        // Child process
        // Execute the given command with its arguments
        int exec_result = execvp(argv[0], argv);

        if (exec_result < 0) {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
    } 
    
    else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        // Measure and calculate the command execution time
        end_time = times(&end);
        double time = (end_time - start_time);

        // Print the result of the command execution
        std::cout << "Command completed with exit code " << WEXITSTATUS(status)
                  << " and took " << time << " seconds." << std::endl;
    }
}

int main(int argc, char** argv) {
    // Check if the minimum number of arguments is provided
    if (argc < 2) {
         std::cerr << strerror(errno) << std::endl;
         exit(errno);
    }

    // Allocate memory for a copy of command-line arguments to pass to do_command
    char** args_vector = new char*[argc];
    for (int i = 1; i < argc; ++i) {
        args_vector[i - 1] = argv[i];
    }
    args_vector[argc - 1] = nullptr; // Null-terminate the argument vector

    // Call do_command to execute the specified command
    do_command(args_vector);

    // Free the allocated memory
    delete[] args_vector;

    return 0;
}
