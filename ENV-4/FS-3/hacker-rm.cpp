#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


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
    int fd = open(file, O_RDONLY | O_WRONLY | O_TRUNC);
   
     // Check if the file couldn't be opened.
    if(fd < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // Check information about the file.
    struct stat file_info ;
    if(stat(file, &file_info) != 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int file_size = file_info.st_size;

    int i = 0;
    char file_delete = '\0';

    // Overwrite the file with null bytes.
    while( i < file_size)
    {
          
        ssize_t write_bytes = write(fd, &file_delete, 1);
        if(write_bytes < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);

        }

        ++i;

    }


    // Close the file.
    int close_file = close(fd);
    if(close_file < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    
    // Delete the file from the file system.
    int unlink_file = unlink(file);
    if(unlink_file < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);

        }

    
    return 0;
}
