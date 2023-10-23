all: cin

cin: main.o
	g++ main.o -o cin

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o cin