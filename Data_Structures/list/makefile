###############################################################
# Program:
#     Assignment 07, LIST
#     Brother Helfrich, CS235
# Author:
#     Jonah Green, Jared Garcia, Jacob Bogdan
# Summary:
#     list.h will function like std list.
#     it has an node class nested in it and
#     a list iterator.
# Difficult:
#     The hardest time we had on this assignment
#     was figuring out that to access the node 
#     in iterator we needed to make insert/erase
#     friends to iterator. we also had some difficulty
#     with the fibonacci application
#
# Time:
#     Jared:           1.0 hours
#     Jacob:           1.0 hours
#     Jonah:           1.5 hours
#     Team Discussion: 1.0 hours
#     Group work:      11.0 hours 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h assignment07.o fibonacci.o wholeNumber.o
	g++ -o a.out assignment07.o fibonacci.o wholeNumber.o -g  -std=c++11
	tar -cf assignment07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment07.o : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
assignment07.o: list.h assignment07.cpp
	g++ -c assignment07.cpp -g  -std=c++11

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	g++ -c fibonacci.cpp -g  -std=c++11

wholeNumber.o: wholeNumber.h wholeNumber.cpp list.h
	g++ -c wholeNumber.cpp -g  -std=c++11

