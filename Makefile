parser: main.o
	g++ main.o Caff.o Ciff.o utils.o -o parser

main.o: main.cpp Caff.cpp Caff.h  Ciff.cpp Ciff.h utils.cpp utils.h constants.h
	g++ -c main.cpp Caff.cpp Ciff.cpp utils.cpp

clean:
	rm *.o parser