CFLAGS=-Wall -std=c++17 #-Wshadow
LFLAGS=-lm
CC=g++
TARGET=main
DEPENDENCIAS=main.o

all: $(TARGET)

debug: $(DEPENDENCIAS)
	g++ -o $(TARGET) $^ -g $(LFLAGS)

$(TARGET): $(DEPENDENCIAS)
	g++ -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) -c $^ $(CFLAGS)

clean: 
	rm $(DEPENDENCIAS) $(TARGET)
