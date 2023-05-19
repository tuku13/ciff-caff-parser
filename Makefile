parser: main.o
	g++ main.o Caff.o Ciff.o Pixel.o utils.o -o parser

#main.o: main.c Caff.c Caff.h  Ciff.c Ciff.h utils.c utils.h Pixel.c Pixel.h constants.h
#	g++ -c main.c Caff.c Ciff.c Pixel.c utils.c

main.o: main.cpp Caff.cpp Caff.h  Ciff.cpp Ciff.h utils.cpp utils.h Pixel.cpp Pixel.h constants.h
	g++ -c main.cpp Caff.cpp Ciff.cpp utils.cpp Pixel.cpp

clean:
	rm *.o parser