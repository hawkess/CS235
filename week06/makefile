##############################################################
# The main rule
##############################################################
a.out: node.h assignment06.o
	g++ -Wall -g -o a.out assignment06.o
	tar -cf assignment06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment06.o      : the driver program
#      <anything else?>
##############################################################
assignment06.o: node.h assignment06.cpp sortInsertion.h
	g++ -Wall -g -c assignment06.cpp
