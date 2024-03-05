#include <iostream>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

// Function to check if a number is prime
bool is_prime(int num)
{
    if(num <= 1)
    {
        return false;
    }

    for(int i = 2; i <= num / 2; ++i)
    {
        if(num % i == 0)
        {
            return false;
        }
    }

    return true;
}


// Function to find the m-th prime number
int prime_number(int m)
{
    int count = 0;
    int num = 2;

    while(true)
    {
        if(is_prime(num))
        {
            count++;
        }

        if(count == m)
        {
            return num;
        }

        num++;
    }
}


int main()
{
    // Pipe for sending input from parent to child
    int pipefd_1[2];

    // Pipe for sending output from child to parent
    int pipefd_2[2];

    // Creating pipes
    int pipe_res_1 = pipe(pipefd_1);
    if(pipe_res_1 < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int pipe_res_2 = pipe(pipefd_2);
    if(pipe_res_2 < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // Creating a child process
    int pid = fork();

    if(pid < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }


    // Child process
    if(pid == 0)
    {
        // Close write end of pipe 1
        close(pipefd_1[1]);

        // Close read end of pipe 2
        close(pipefd_2[0]);


        int m;


        while(true)
        {
            // Read input from parent
            int read_res = read(pipefd_1[0], &m, sizeof(int));

            if(read_res < 0)
            {
               std::cerr << strerror(errno) << std::endl;
               exit(errno); 
            }

            // Calculate m-th prime number
            int m_th_prime_num = prime_number(m);

            // Send calculated prime number to parent
            int write_res = write(pipefd_2[1], &m_th_prime_num, sizeof(int));

            if(write_res < 0)
            {
                std::cerr << strerror(errno) << std::endl;
                exit(errno); 
            }


        }
    }


    // Parent process
    if(pid > 0)
    {
        // Close read end of pipe 1
        close(pipefd_1[0]);

        // Close write end of pipe 2
        close(pipefd_2[1]);

        std::string input;
        
        while(true)
        {
            std::cout << "Please enter the number: ";
            std::cin >> input;

            if(input == "exit")
            {
                break;
            }


            int m = std::stoi(input);

            std::cout << "Sending " << m << " to the child process..." << std::endl;

            // Send input to child process
            int write_res = write(pipefd_1[1], &m, sizeof(int));

            if(write_res < 0)
            {
                std::cerr << strerror(errno) << std::endl;
                exit(errno); 
            }

            std::cout << "Waiting for the response from the child process..." << std::endl;

            int res;

            // Read response from child process
            int read_res = read(pipefd_2[0], &res, sizeof(int));

            if(read_res < 0)
            {
                std::cerr << strerror(errno) << std::endl;
                exit(errno); 
            }

            std::cout << "Received calculation result of prime(" << m << ") = " << res << "..." << std::endl;
        }
    }


}