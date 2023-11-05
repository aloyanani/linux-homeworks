all: hacker

hacker:hacker-rm.o
	g++ hacker-rm.o -o hacker

hacker-rm.o: hacker-rm.cpp
	g++ -c hacker-rm.cpp

clean:
	rm .o hacker-rm
