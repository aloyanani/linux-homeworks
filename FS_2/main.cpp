#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 10


int main(int argc, char** argv )
{
   // Check if there are not enough command-line arguments.
   if(argc < 2)
   {
    std::cerr << " Provide file path." << std::endl;
    exit(1);
   }

   char* file = argv[1];
   char* new_file = argv[2];

   // Open the file in read-only mode.
   int fd_file = open(file, O_RDONLY);
   
   // Check if the file couldn't be opened.
   if(fd_file < 0)
   {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
   }
   
   char buf[BUFFER_SIZE ];
   
   // Open the new file in read-only mode.
   int new_fd = open(new_file, O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

   // Check if the file couldn't be opened.
   if(new_fd < 0)
   {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
   }
   
   while(true)
   {
      // Read the file.
      ssize_t read_bytes = read(fd_file, buf, BUFFER_SIZE);

      // Check if there was an error while reading.
      if(read_bytes < 0)
      {
         std::cerr << strerror(errno) << std::endl;
         exit(errno);
        
      } 

      // Check if the end of the file has been reached.
      if(read_bytes == 0)
      {
        break;
      }
      
      // Write in the new file.
      ssize_t write_bytes = write(new_fd, buf, read_bytes);

      // Check if there was an error while writing.
      if(write_bytes < 0)
      {
         std::cerr << strerror(errno) << std::endl;
         exit(errno);
        
      } 

   }

   // Close the file using the file descriptor.
   int close_file = close(fd_file);
  
   // Check if there was an error while closing the file.
   if(close_file < 0)
   {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
   }

   int close_new_file = close(fd_file);

   // Check if there was an error while closing the file.
   if(close_new_file < 0)
   {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
   }

   return 0;

}
