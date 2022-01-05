##############################################################
# The main rule
##############################################################
CXX=g++
CXXFLAGS=-g
all: a.out
a.out: queue.h assignment03.o dollars.o stock.o Portfolio.o
	$(CXX) $(CXXFLAGS) -o a.out assignment03.o dollars.o stock.o Portfolio.o
	tar -cf assignment03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	$(CXX) $(CXXFLAGS) -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      assignment03.o : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
assignment03.o: queue.h assignment03.cpp
	$(CXX) $(CXXFLAGS) -c assignment03.cpp

dollars.o: dollars.h dollars.cpp
	$(CXX) $(CXXFLAGS) -c dollars.cpp

Portfolio.o: Portfolio.h Portfolio.cpp stock.h
	$(CXX) $(CXXFLAGS) -c Portfolio.cpp

stock.o: stock.h stock.cpp queue.h
	$(CXX) $(CXXFLAGS) -c stock.cpp
clean:
	rm -f *.o *.out
