CXX=g++
CXXFLAGS=-Wall
LDFLAGS=-lgloox -lpthread -lncurses -lpanel
EXEC_CPTALK=cptalk
EXEC_GUI=gui
EXEC_TEST=test

all: cptalk

cptalk: main.o interface.o
	$(CXX) -o $(EXEC_CPTALK) main.o interface.o $(CXXFLAGS) $(LDFLAGS)

main.o: main.cpp interface.h 
	$(CXX) -c main.cpp interface.cpp $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean mrproper

clean: 
	rm -f *.o

mrproper: clean
		rm -f $(EXEC)

