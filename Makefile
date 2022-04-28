CC = g++
CFLAGS = -std=c++11
EXECUTABLE = bin/kl

all: $(EXECUTABLE)

$(EXECUTABLE): src/main.cpp lk.o
	$(CC) $(CFLAGS) -o $(EXECUTABLE) src/main.cpp lk.o

lk.o: src/lk.h src/lk.cpp src/node.h src/node.h
	$(CC) $(CFLAGS) -c -o lk.o src/lk.cpp

clean:
	rm -rf *.o $(EXECUTABLE)
