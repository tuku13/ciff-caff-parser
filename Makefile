parser: main.o
	g++ main.o Caff.o Ciff.o utils.o -o parser -L./lib -lwebp -lsharpyuv -lpthread

main.o: main.cpp Caff.cpp Caff.h Ciff.cpp Ciff.h utils.cpp utils.h constants.h
	g++ -I/includes/webp -c main.cpp Caff.cpp Ciff.cpp utils.cpp

clean:
	rm *.o parser