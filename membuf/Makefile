all: membuf.a
membuf.o: membuf.cpp
	g++ -o membuf.o -c membuf.cpp

membuf.a: membuf.o
	ar rcs membuf.a membuf.o

clean:
	rm -f membuf.o membuf.a