all: test

main.o: main.cpp
	g++ -I ../ -o main.o -c main.cpp

test: main.o
	g++ main.o ../membuf.a -o test

clean: 
	rm main.o test test.txt