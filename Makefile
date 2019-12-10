CC = g++
CFLAGS = -Wall -Wextra -pedantic -O3

program: main.o image.o
	$(CC) $(CFLAGS) main.o image.o -o program

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

image.o: image.cpp image.hpp color.hpp
	$(CC) $(CFLAGS) -c image.cpp

clean:
	rm -rf *.o program