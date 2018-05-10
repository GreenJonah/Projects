###############################################################
# Program:
#     Assignment 04, DEQUE
#     Brother Helfrich, CS235
# Author:
#     Jonah Green, Jared Garcia, Jacob Bogdan
# Summary:
#     This program creates the deque data structure and its 
#  various methods and variables. The deque is very similar to
#  the queue except that it can push and pop elements from both
#  ends of the strucutre. The deque is also implemented in a now 
#  serving program, in which students get help for a particular 
#  class by entering info into a command prompt and are then 
#  placed in a wait list(deque). Students needing immediate help 
#  can take priority and enter at the front of the deque. Each
#  student has a set number of minutes until their time is up
#  and the program finishes once the deque is empty or the key
#  word "finished" is typed in the command prompt.  
#
# Difficult:
# 	  The most difficulet part of this assignment, was trying 
#  get the iBackNormalized and iFrontNormalized functions to work.
#  We tried a few different methods and were close but always seemed
#  to have one or two bugs. Eventually with the help of the class
#  on Wednesday we figured out the code that was needed. 
# 
# Time:
#     Jared:           1.0 hours
#     Jacob:           0.5 hours
#     Jonah:           2.5 hours
#     Team Discussion: 1.0 hours
#     Group work:      4.0 hours     
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h assignment04.o nowServing.o
	g++ -o a.out assignment04.o nowServing.o
	tar -cf assignment04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment04.o : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
assignment04.o: deque.h assignment04.cpp
	g++ -c assignment04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp
