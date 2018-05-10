###############################################################
# Program:
#     Assignment 10, Map
#     Brother Helfrich, CS235
# Author:
#     Jonah Green, Jared Garcia, Jacob Bogdan
# Summary:
# This assignment goes through an array of data looking to sort how
# many times a given word appears in a text file, as well as testing
# the basic operations of the map class.
# 
# Difficult:
# Trying to get the iterators of the map class and the bst class
# to cooperate together was very diffucult. We had to make them
# friends so they could access their privates. 
#
# Time:
#     Jared:           1.0 hours
#     Jacob:           0.5 hours
#     Jonah:           1.0 hours
#     Team Discussion: 1.0 hours
#     Group work:      5.0 hours 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment10.o wordCount.o
	g++ -o a.out assignment10.o wordCount.o -g
	tar -cf assignment10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment10.o : the driver program
#      wordCount.o    : the wordCount() function
##############################################################
assignment10.o: pair.h map.h assignment10.cpp
	g++ -c assignment10.cpp -g

wordCount.o: map.h wordCount.h wordCount.cpp 
	g++ -c wordCount.cpp -g 
