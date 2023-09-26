all: main

main: main.o complex.o
	g++ main.o complex.o -o main

complex.o: complex.cpp complex.h
	g++ -c complex.cpp

main.o: main.cpp complex.h sort.h
	g++ -c main.cpp

clean:
	rm *.o main

