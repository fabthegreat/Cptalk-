CXX=g++
CXXFLAGS=-Wall
LDFLAGS=-lgloox -lpthread -lncurses -lpanel
EXEC_CPTALK=cptalk
EXEC_GUI=gui
EXEC_TEST=test

all: cptalk

cptalk: main.o interface.o Core.o
	$(CXX) -o $(EXEC_CPTALK) main.o Core.o interface.o $(CXXFLAGS) $(LDFLAGS)

main.o Core.o: main.cpp interface.h Core.h
	$(CXX) -c main.cpp interface.cpp Core.cpp $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean mrproper

clean: 
	rm -f *.o

mrproper: clean
		rm -f $(EXEC)

