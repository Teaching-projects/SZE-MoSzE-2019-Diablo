OBJS=File.o Terminal.o Directory.o main.o
CXXFLAGS=-O2 -std=c++11

a.out: $(OBJS)
	g++ -o a.out $(OBJS)

main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)

Terminal.o: Terminal.cpp
	g++ -c Terminal.cpp $(CXXFLAGS)

Directory.o: Directory.cpp
	g++ -c Directory.cpp $(CXXFLAGS)

File.o: File.cpp
	g++ -c File.cpp $(CXXFLAGS)

clean:
	rm -f *.o

