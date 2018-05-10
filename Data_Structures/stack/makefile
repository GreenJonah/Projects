###############################################################
# Program:
#     Assignment 02, STACK
#     Brother Helfrich, CS235
# Author:
#     Jonah Green, Jared Garcia, Jacob Bogdan
# Summary:
#     This program will act a lot like the stack from std
#     it will work as a first in last out container.
#     
# Difficult: 
#     I think the part that we struggled with the most was
#     doing the infix to postfix. We had a hard time getting 
#     the function to produce the postfix with the proper spacing
# Time:
#     Jonah:               2 hours
#     Jared:               2 hours
#     Jacob:               1.5 hours
#     Discussion Time:     1 hour
#     Team (Project):      5 hours
#     Team (extra credit): 4 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h assignment02.o infix.o 
	g++ -o a.out assignment02.o infix.o 
	tar -cf assignment02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment02.o : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
assignment02.o: stack.h infix.h assignment02.cpp
	g++ -c assignment02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp

