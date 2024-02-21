#include "shared_array.h"

// Constructor definition
shared_array::shared_array(std::string _name, int _size): size(_size) {
    // Generate the name for the shared array
    array_name = _name + '_' + std::to_string(size);
    
    // Create or open the shared memory object
    open_fd = shm_open(array_name.c_str(), O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);

    // Check if shared memory object creation or opening was successful
    if(open_fd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // Calculate the number of pages
    int page_count;
    if(size % PAGE_SIZE > 0) {
        page_count = (size / PAGE_SIZE) + 1;
    }
    if(size % PAGE_SIZE == 0) {
        page_count = size / PAGE_SIZE;
    }

    // Resize the shared memory object to fit the required size
    int ret_franc = ftruncate(open_fd, page_count * PAGE_SIZE);
    if(ret_franc < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // Map the shared memory object into the address space of the process
    ptr = mmap(NULL, page_count * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, open_fd, 0);
    if(ptr == (void*) -1){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
}

// Destructor definition
shared_array::~shared_array(){
    // Unmap the shared memory object
    int ret_unmap = munmap(ptr, size * sizeof(int));
    if(ret_unmap < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // Close the file descriptor associated with the shared memory object
    close(open_fd);

    // Unlink the shared memory object
    shm_unlink(array_name.c_str());
}

// Overloaded operator [] definition
int& shared_array::operator[](int index){
    // Check if the index is within bounds
    if(index < 0 || index >= size){
        std::cerr << "Index out of range." << std::endl;
        exit(errno);
    }

    // Cast the pointer to int* and calculate the address of the element
    int* _ptr = static_cast<int*>(ptr);
    int* element_address = _ptr + index;

    // Return a reference to the element at the calculated address
    return *element_address;
}
