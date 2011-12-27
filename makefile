CXX=g++
CXXFLAGS=-Wall
LDFLAGS=-lgloox -lpthread -lncurses -lpanel
EXEC_CPTALK=cptalk
EXEC_GUI=gui
EXEC_TEST=test

all: cptalk

cptalk: main.o Core.o interface.o
	$(CXX) -o $(EXEC_CPTALK) main.o Core.o interface.o $(CXXFLAGS) $(LDFLAGS)

main.o Core.o: main.cpp Core.cpp Core.h interface.h
	$(CXX) -c main.cpp Core.cpp interface.cpp $(CXXFLAGS) $(LDFLAGS)

gui: interface.o gui.o 
	$(CXX) -o $(EXEC_GUI) gui.o interface.o $(CXXFLAGS) $(LDFLAGS)

interface.o gui.o: interface.cpp gui.cpp
	$(CXX) -c gui.cpp interface.cpp $(CXXFLAGS) $(LDFLAGS)

test: new_main.o interface.o
	$(CXX) -o $(EXEC_TEST) new_main.o interface.o $(CXXFLAGS) $(LDFLAGS)

new_main.o interface.o: new_main.cpp interface.cpp
	$(CXX) -c new_main.cpp interface.cpp $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean mrproper

clean: 
	rm -f *.o

mrproper: clean
		rm -f $(EXEC)

