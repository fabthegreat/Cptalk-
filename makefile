CXX=g++
CXXFLAGS=-Wall
LDFLAGS=-lgloox -lpthread
EXEC=cptalk

all: cptalk

cptalk: main.o Core.o
	$(CXX) -o $(EXEC) main.o Core.o $(CXXFLAGS) $(LDFLAGS)

main.o Core.o: main.cpp Core.cpp Core.h interface.cpp interface.h
	$(CXX) -c main.cpp Core.cpp interface.cpp $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean mrproper

clean: 
	rm -f *.o

mrproper: clean
		rm -f $(EXEC)

