##############################################################
# The main rule
##############################################################
a.out: list.h assignment07.o fibonacci.o wholeNumber.o
	clang++ -o a.out assignment07.o fibonacci.o wholeNumber.o -g
	tar -cf assignment07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment07.o : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
assignment07.o: list.h assignment07.cpp
	clang++ -c assignment07.cpp -g

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	clang++ -c fibonacci.cpp -g

wholeNumber.o: wholeNumber.h wholeNumber.cpp list.h
	clang++ -c wholeNumber.cpp -g

