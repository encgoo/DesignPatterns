
CFLAGS= -std=c++11 -Wdelete-incomplete
all: membuf.a

membuf.o: membuf.cpp
	g++ $(CFLAGS) -o membuf.o -c membuf.cpp
BufferCommands.o: BufferCommands.cpp
	g++ $(CFLAGS) -o BufferCommands.o -c BufferCommands.cpp

CommandCommon.o: CommandCommon.cpp
	g++ $(CFLAGS) -o CommandCommon.o -c CommandCommon.cpp

StateController.o: StateController.cpp
	g++ $(CFLAGS) -o StateController.o -c StateController.cpp

Memento.o: Memento.cpp
	g++ $(CFLAGS) -o Memento.o -c Memento.cpp
 
membuf.a: membuf.o CommandCommon.o StateController.o BufferCommands.o Memento.o
	ar rcs membuf.a membuf.o CommandCommon.o StateController.o BufferCommands.o Memento.o

clean:
	rm -f *.o membuf.a