#include <iostream>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

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
    int pipefd_1[2];
    int pipefd_2[2];

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

    int pid = fork();

    if(pid < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }


    if(pid == 0)
    {
        close(pipefd_1[1]);
        close(pipefd_2[0]);


        int m;


        while(true)
        {
            int read_res = read(pipefd_1[0], &m, sizeof(int));

            if(read_res < 0)
            {
               std::cerr << strerror(errno) << std::endl;
               exit(errno); 
            }

            int m_th_prime_num = prime_number(m);

            int write_res = write(pipefd_2[1], &m_th_prime_num, sizeof(int));

            if(write_res < 0)
            {
                std::cerr << strerror(errno) << std::endl;
                exit(errno); 
            }


        }
    }

    if(pid > 0)
    {
        close(pipefd_1[0]);
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

            int write_res = write(pipefd_1[1], &m, sizeof(int));

            if(write_res < 0)
            {
                std::cerr << strerror(errno) << std::endl;
                exit(errno); 
            }

            std::cout << "Waiting for the response from the child process..." << std::endl;

            int res;

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