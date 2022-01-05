##############################################################
# The main rule
##############################################################
CXX=g++
CXXFLAGS=-g -DDEBUG
all: a.out
a.out: deque.h assignment04.o nowServing.o
	$(CXX) $(CXXFLAGS) -o a.out assignment04.o nowServing.o 
	tar -cf assignment04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment04.o : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
assignment04.o: deque.h assignment04.cpp
	$(CXX) $(CXXFLAGS) -c assignment04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h task.h
	$(CXX) $(CXXFLAGS) -c nowServing.cpp
clean:
	rm -f *.o *.out
