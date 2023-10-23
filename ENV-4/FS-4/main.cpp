#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void initialize(int argc, char** argv)
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

     // Close the file.
    int close_file = close(fd);
    if(close_file < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }


}
int main(int argc, char** argv)
{
    
   initialize(argc, argv);

   std::string input;
   std::cin >> input;

   std::string reversed = input; 

   
    for(int i = 0; i < reversed.length()/2; ++i)
    {
        char temp = reversed[i];
        reversed[i] = reversed[reversed.length() - i - 1];
        reversed[reversed.length() - i - 1] = temp;
    }
    

    std::cout << reversed << std::endl;
    return 0;
}