
#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H


#include <iostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


#define PAGE_SIZE 4096


class shared_array {
private:
    std::string array_name;
    int size;
    void* ptr;
    int open_fd;

public:
    shared_array(std::string _name, int _size);
    ~shared_array();

    int& operator[](int index);

};

#endif