/***********************************************************************
 * Header:
 *    WHOLE_NUMBER.CPP
 *   
 * Author
 *    Jonah Green, Jared Garcia, Jacob Bogdan
 ************************************************************************/
#include "wholeNumber.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>

/**********************************************************
* << OPERATOR
* Displays a single whole number after each iteration
* a comma will need to be added
**********************************************************/
ostream & operator << (ostream & out, wholeNumber & rhs)
{
   // Make two iterators and output a tab
   list <int> :: iterator it;
   list <int> :: iterator temp;
   out << "\t"; 
   
   for (it = rhs.digits.begin(); it != rhs.digits.end(); ++it)
   {
      temp = it;
      // Handles the first Node if there is ONLY one node
      if (rhs.digits.size() == 1)
      {
         out << *it;
      }
      // Handles nodes in the middle of the linked list
      else if (++temp != NULL)
      {
         if (it == rhs.digits.begin())
            out << *it << ",";
         else
         { 
            out << std::setfill('0') << std::setw(3);  
            out << *it << ",";
         }
      }
      // Handles last node in the linked list
      else 
         out << *it;
     
   } 
   return out;  
}

/**********************************************************
* += OPERATOR
* Adds a whole number to another whole number and places 
* each of the number in nodes that are less then 1000
**********************************************************/
wholeNumber & operator += (wholeNumber & lhs, wholeNumber & rhs)
{
   // Create an iterator for lhs and rhs
   list <int> :: reverse_iterator rIt;
   list <int> :: reverse_iterator lIt = lhs.digits.rbegin();

   // loop through the rhs iterator
   for (rIt = rhs.digits.rbegin(); rIt != rhs.digits.rend(); ++rIt)
   {
      // Add the dereferenced rhs iterator to lhs iterator
      assert(lIt != NULL);
      *lIt += *rIt;

      // if the node is full carry the one
      // this may make a new node
      if (*lIt > 999)
      {
         *lIt -= 1000;
         ++lIt;
         if (lIt == NULL && rIt != NULL)
           lhs.digits.push_front(1);
         else
            *lIt += 1;
      }

      // if we are smaller then 999 go the the next node
      else
        ++lIt;    
   } 
}

