###############################################################
# Program:
#     Assignment 03, QUEUE
#     Brother Helfrich, CS235
# Author:
#     Jonah Green, Jared Garcia, Jacob Bogdan
# Summary:
#     The project that we worked on acts very much like
#     the std queue which is a data type that will
#     place new items on the back of the queue
#     and remove items from the front of the queue.

# Difficult:
#    The "red herring" of calling the re-size function twice.
#    This problem ate up a lot of our time and was very difficult
#    to solve because it was something that was actually supposed 
#    to happen, even though we thought it wasn't.
#   
# Time (in hours):    
#     Jared:           1.5 hours
#     Jacob:           1.0 hours
#     Jonah:           1.0 hours
#     Team Discussion: 1.0 hours
#     Team Project:    8.0 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h assignment03.o dollars.o stock.o
	g++ -o a.out assignment03.o dollars.o stock.o
	tar -cf assignment03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      assignment03.o : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
assignment03.o: queue.h assignment03.cpp
	g++ -c assignment03.cpp

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp

stock.o: stock.h stock.cpp queue.h
	g++ -c stock.cpp
