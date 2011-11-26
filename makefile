CXX=g++
CXXFLAGS=-Wall
LDFLAGS=-lgloox -lpthread
EXEC=cptalk

all: cptalk

cptalk: main.o
	$(CXX) -o $(EXEC) main.o $(CXXFLAGS) $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean mrproper

clean: 
	rm -f *.o

mrproper: clean
		rm -f $(EXEC)

