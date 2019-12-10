CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic -O3

program: main.o image.o pendulum.o doublePendulum.o
	$(CC) $(CFLAGS) main.o image.o pendulum.o doublePendulum.o -o program

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

image.o: image.cpp image.hpp color.hpp
	$(CC) $(CFLAGS) -c image.cpp

pendulum.o: pendulum.cpp pendulum.hpp
	$(CC) $(CFLAGS) -c pendulum.cpp

doublePendulum.o: doublePendulum.cpp doublePendulum.hpp
	$(CC) $(CFLAGS) -c doublePendulum.cpp

clean:
	rm -rf *.o program