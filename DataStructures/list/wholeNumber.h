/***********************************************************************
 * Header:
 *    WHOLE_NUMBER.H
 *   
 * Author
 *    Jonah Green, Jared Garcia, Jacob Bogdan
 ************************************************************************/
#ifndef WHOLE_NUMBER_H
#define WHOLE_NUMBER_H

#include <iostream>
#include <fstream>
#include "list.h"

using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::cerr;
using std::ostream;

using namespace custom;

class wholeNumber
{

   public:
      wholeNumber() { digits.push_front(0); }
      wholeNumber(wholeNumber & rhs)         { this->digits = rhs.digits; }
      wholeNumber(unsigned int number)       { digits.push_front(number); }
      friend wholeNumber & operator += (wholeNumber & lhs, wholeNumber & rhs);
      friend ostream & operator << (ostream & out, wholeNumber & rhs);
      list <int> digits;

}; // WHOLE_NUMBER
#endif // WHOLE_NUMBER_H

