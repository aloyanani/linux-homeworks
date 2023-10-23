all: hacker

hacker:hacker.o
	g++ hacker.o -o hacker

hacker.o: hacker-rm.cpp
	g++ -c hacker-rm.cpp

clean:
	rm .o hacker
