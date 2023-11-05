#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 400

int main(int argc, char** argv)
{
    // Check if there are not enough command-line arguments.
    if (argc < 3)
    {
        std::cerr << "Provide source file path and destination file path." << std::endl;
        exit(1);
    }

    char* source_file_path = argv[1];
    char* destination_path = argv[2];  // Corrected variable name.

    // Open the source file in read-only mode.
    int fd_source_file = open(source_file_path, O_RDONLY);

    // Check if the source file couldn't be opened.
    if (fd_source_file < 0)
    {
        std::cerr << "Error opening source file: " << strerror(errno) << std::endl;
        exit(errno);
    }

    // Open the destination file.
    int fd_dest_file = open(destination_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    // Check if the destination file couldn't be opened.
    if (fd_dest_file < 0)
    {
        std::cerr << "Error opening destination file: " << strerror(errno) << std::endl;
        exit(errno);
    }

    char buffer[BUFFER_SIZE];
    ssize_t total_bytes_copied = 0;

    while (true)
    {
        // Read from the source file.
        ssize_t read_bytes = read(fd_source_file, buffer, BUFFER_SIZE);

        // Check if there was an error while reading.
        if (read_bytes < 0)
        {
            std::cerr << "Error reading from source file: " << strerror(errno) << std::endl;
            exit(errno);
        }

        if (read_bytes == 0)
        {
            // End of file reached.
            break;
        }

        // Write to the destination file.
        ssize_t write_bytes = write(fd_dest_file, buffer, read_bytes);  

        if (write_bytes < 0)
        {
            std::cerr << "Error writing to destination file: " << strerror(errno) << std::endl;
            exit(errno);
        }

        total_bytes_copied += write_bytes;
    }

    // Close both files after the loop.
    close(fd_source_file);
    close(fd_dest_file);

    std::cout << "It was copied " << total_bytes_copied << " bytes." << std::endl;

    return 0;  
}
