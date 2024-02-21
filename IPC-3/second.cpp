#include "shared_array.h"
#include <semaphore.h>

int main()
{
    sem_t* sem_address = sem_open("my_semaphore",  O_RDWR | O_CREAT, S_IRWXU | S_IRWXG);
    if(sem_address == SEM_FAILED){
        std::cerr << strerror(errno) <<std::endl;
        exit(errno);
    }

    shared_array arr("my_array", 25);

    while(true){
        sem_wait(sem_address);
        for(int i = 0; i < 25; ++i){
            std::cout << "In my second programe arr[" << i << "] = " << arr[i] << std::endl;
 
        }

        sem_post(sem_address);
        sleep(2);
    }

    sem_close(sem_address);

    return 0;

}