###############################################################
# Program:
#     Assignment 05, SET
#     Brother Helfrich, CS235
# Author:
#     Jonah Green, Jared Garcia, Jacob Bogdan
# Summary:
#     This program implements the set data structure as well
#     as the go fish game. The set class has all of the methods
#     to create and implement the data structure, as well as 
#     an iterator class both const and non-const.
# Difficult:
#     The most difficult part of this assignment was passing
#     test three which implemented the insert and erase methods. 
#     We seemed to be off by one item and were seg-faulting. 
#     Eventually we found the error and needed to take care the 
#     last item in the array. 
# Time:
#     Jared:           1.5 hours
#     Jacob:           1.0 hours
#     Jonah:           2.5 hours
#     Team Discussion: 1.0 hours
#     Group work:      6.0 hours 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment05.o goFish.o card.o
	g++ -o a.out assignment05.o goFish.o card.o
	tar -cf assignment05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment05.o : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
assignment05.o: set.h goFish.h assignment05.cpp
	g++ -c assignment05.cpp

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c goFish.cpp

card.o: card.h card.cpp
	g++ -c card.cpp 
