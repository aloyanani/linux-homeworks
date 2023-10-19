#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>



#define BUFFER_SIZE 10


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "Provide file path." << std::endl;
        exit(1);
    }
    char* file = argv[1];

    int fd = open(file, O_RDONLY);

    if(fd < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    char buf[BUFFER_SIZE];
    
    while(true)
    {
        ssize_t reading_bytes = read(fd, buf, BUFFER_SIZE);
        if(reading_bytes < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }   
        if(reading_bytes == 0)
        {
            break;
        }
        
        buf[reading_bytes] = '\0';

        std::cout << buf;        
    }

    int close_result = close(fd);
    if(close_result < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }  
        
    return 0;    

}
