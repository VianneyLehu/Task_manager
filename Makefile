opt = -c -Wall -Wextra -std=c++11
libs = -lpsapi

main: process.o main.o snapshot.o
	g++ -o main process.o main.o snapshot.o ${libs}

main.o: main.cpp
	g++ ${opt} main.cpp

process.o: process.cpp
	g++ ${opt} process.cpp

snapshot.o: snapshot.cpp
	g++ ${opt} snapshot.cpp 