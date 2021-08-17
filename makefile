CC=g++ -std=c++17 -O3

all: build clean

Visualizer.cpp: Visualizer.h

Visualizer.h: map.h

Visualizer.o: Visualizer.cpp
	$(CC) -c Visualizer.cpp

map.cpp: map.h

map.h: cell.h

map.o: map.cpp
	$(CC) -c map.cpp

cell.cpp: cell.h

cell.h:

cell.o: cell.cpp
	$(CC) -c cell.cpp

main.cpp: Visualizer.h

main.o: main.cpp
	$(CC) -c main.cpp

GameOfLife: Visualizer.o map.o cell.o main.o
	$(CC) -o GameOfLife main.o Visualizer.o map.o cell.o -lsfml-graphics -lsfml-window -lsfml-system

build: GameOfLife

clean:
	rm *.o
