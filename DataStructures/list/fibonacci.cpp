/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    Jonah Green, Jared Garcia, Jacob Bogdan
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"    // for fibonacci() prototype
#include "list.h"         // for LIST
#include "wholeNumber.h" // for storing large numbers

using namespace custom;

/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   // your code to display the first <number> Fibonacci numbers
   // Make two whole numbers one to keep track of the last fibonacci
   // the other will keep track of the current fib.
   // the two will add together and store the new number in current and 
   // prev will become current
   wholeNumber current(1);
   wholeNumber temp;
   wholeNumber prev;
   
   // loop through and add each fibonacci to the 
   for (int i = 0; i != number; i++)
   {  
 
      cout << current << endl;

      // add current to prev
      temp = current;
      current += prev;
      prev = temp;
   }
   
   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   wholeNumber curr(1);
   wholeNumber tem;
   wholeNumber pre;

   for (int i = 0; i != number; i++)
   {  
      // add current to prev
      tem = curr;
      curr += pre;
      pre = tem;
   }
   cout << tem << endl;
}


