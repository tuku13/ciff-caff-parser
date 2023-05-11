parser: main.o
	g++ main.o -o parser

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o parser