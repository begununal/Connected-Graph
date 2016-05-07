CC = g++
CFLAGS  = -std=c++11 -g -Wall

project4: project4.o 
	$(CC) $(CFLAGS) project4.o -o project4

project4.o: project4.cpp
	$(CC) $(CFLAGS) -c project4.cpp

clean:
	rm -f *.o
	rm -f project4
