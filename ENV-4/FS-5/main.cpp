#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    // Check if there are not enough command-line arguments.
    if(argc < 2)
    {
       std::cerr << "Provide file path." << std::endl;
       exit(1);
    }

    char* file = argv[1];

    // Open the file in read-only mode.
    int fd = open(file,  O_WRONLY | O_TRUNC | O_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
   
     // Check if the file couldn't be opened.
    if(fd < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
     
     // Duplicate the file.
    int fd2 = dup(fd);

    // Check if the file couldn't be duplicate.
    if(fd2  < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    const char* first = "first line\n";
    const char* second = "second line";

    ssize_t write_bytes = write(fd, first, strlen(first) );
        if(write_bytes < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);

        }

        write_bytes = write(fd2, second, strlen(second));
        if(write_bytes < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);

        }

    // Close the file.
    int close_file = close(fd);
    if(close_file < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // Close the file.
    int close_file2 = close(fd2);
    if(close_file2 < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }


    return 0;
}