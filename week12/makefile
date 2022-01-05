##############################################################
# The main rule
##############################################################
a.out: assignment12.o spellCheck.o
	g++ -o a.out assignment12.o spellCheck.o -g
	tar -cf assignment12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment12.o     : the driver program
#      spellCheck.o       : the spell-check program and driver
##############################################################
assignment12.o: hash.h assignment12.cpp bst.h
	g++ -c assignment12.cpp -g

spellCheck.o: hash.h spellCheck.h spellCheck.cpp vector.h
	g++ -c spellCheck.cpp -g

clean:
	rm -f *.o *.out

