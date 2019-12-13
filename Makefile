CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic -O3

program: main.o color.o image.o pendulum.o doublePendulum.o
	$(CC) $(CFLAGS) main.o color.o image.o pendulum.o doublePendulum.o -o program

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

color.o: color.cpp color.hpp
	$(CC) $(CFLAGS) -c color.cpp

image.o: image.cpp image.hpp color.hpp
	$(CC) $(CFLAGS) -c image.cpp

pendulum.o: pendulum.cpp pendulum.hpp pendulumParams.hpp initialConditions.hpp
	$(CC) $(CFLAGS) -c pendulum.cpp

doublePendulum.o: doublePendulum.cpp doublePendulum.hpp pendulumParams.hpp initialConditions.hpp
	$(CC) $(CFLAGS) -c doublePendulum.cpp

clean:
	rm -rf *.o program