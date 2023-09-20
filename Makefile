all: main

main: main.o
        g++ main.o -o main

main.o: main.cpp
        g++ main.cpp  -c -o main.o

complex.h:
        g++ complex.h  -c

sort.h:
        g++ sort.h  -c

clean:
        rm *.o main

