CXX=g++
CXXFLAGS=-Wall
LDFLAGS=-lgloox -lpthread -lncurses -lpanel
EXEC_CPTALK=cptalk2
EXEC_GUI=gui
EXEC_TEST=test

all: cptalk

cptalk: main.o interface.o Core.o
	$(CXX) -o $(EXEC_CPTALK) main.o Core.o interface.o $(CXXFLAGS) $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp $(CXXFLAGS) $(LDFLAGS)

Core.o: Core.cpp Core.h
	$(CXX) -c Core.cpp $(CXXFLAGS) $(LDFLAGS)

interface.o: interface.cpp interface.h
	$(CXX) -c interface.cpp $(CXXFLAGS) $(LDFLAGS)


# Nouvelle organisation
test: cptalk2

cptalk2: main.o ICore.o common.o IO.o Linker.o XMPP.o
	$(CXX) -o $(EXEC_CPTALK) main.o ICore.o common.o IO.o Linker.o XMPP.o $(CXXFLAGS) $(LDFLAGS)

ICore.o: ICore.cpp ICore.h
	$(CXX) -c ICore.cpp $(CXXFLAGS) $(LDFLAGS)

common.o: common.cpp common.h
	$(CXX) -c common.cpp $(CXXFLAGS) $(LDFLAGS)

IO.o: IO.cpp IO.h
	$(CXX) -c IO.cpp $(CXXFLAGS) $(LDFLAGS)

Linker.o: Linker.cpp Linker.h
	$(CXX) -c Linker.cpp $(CXXFLAGS) $(LDFLAGS)

XMPP.o: XMPP.cpp XMPP.h
	$(CXX) -c XMPP.cpp $(CXXFLAGS) $(LDFLAGS)

# cibles particulieres: si jamais un fichier "clean" existe il ne sera pas pris en compte
.PHONY: clean mrproper

clean: 
	rm -f *.o

mrproper: clean
		rm -f $(EXEC)

