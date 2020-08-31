##############################################################
# The main rule
##############################################################
CXXFLAGS := -g
a.out: assignment05.o goFish.o card.o
	g++ $(CXXFLAGS) -o a.out assignment05.o goFish.o card.o
	tar -cf assignment05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment05.o : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
assignment05.o: set.h goFish.h assignment05.cpp
	g++ $(CXXFLAGS) -c assignment05.cpp

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ $(CXXFLAGS) -c goFish.cpp

card.o: card.h card.cpp
	g++ $(CXXFLAGS) -c card.cpp

clean:
	@rm -f *.o *.out
