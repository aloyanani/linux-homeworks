all: first second

first: first.o shared_array.o
	g++ first.o shared_array.o -o first 

second: second.o shared_array.o
	g++ second.o shared_array.o  -o second

first.o: first.cpp shared_array.h
	g++ first.cpp -c -o first.o

second.o: second.cpp shared_array.h
	g++ second.cpp -c -o second.o


clean:
	rm *.o first second