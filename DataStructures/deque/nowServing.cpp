/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This program implements the deque data structure in which students 
 *    get help for a particular class by entering info into a command 
 *    prompt and are then placed in a wait list(deque). Students needing 
 *    immediate help can take priority and enter at the front of the deque. 
 *    Each student has a set number of minutes until their time is up
 *    and the program finishes once the deque is empty or the key word 
 *    "finished" is typed in the command prompt.
 * 
 * Author
 *    Jacob Bogdan, Jonah Green, Jared Garcia
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include <sstream>      // for STRINGSTREAM
#include <stdlib.h>     // for atoi
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ios;
using std::cerr;
using std::getline;
using std::istringstream;
using namespace custom;

/**********************************************************
* DISPLAY
* displays the student that is currently being helped.
**********************************************************/
void display(Student & helped)
{
   if (!helped.isEmergency())
   {
      cout << "\tCurrently serving " << helped.getName()
           << " for class "          << helped.getCourse() 
           << ". Time left: "        << helped.getMinutes()
           << endl;   
   }
   else
   {
      cout << "\tEmergency for "     << helped.getName()
           << " for class "           << helped.getCourse() 
           << ". Time left: "        << helped.getMinutes()
           << endl;  
   }
 
   // take off one minute
   helped.setMinutes(helped.getMinutes() - 1);
}

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // objects and main variables for our data
   Student student;
   Student helped;
   string input;
   string instuction_or_course;
   string course_or_name;
   string name_or_time;
   int time = 0;
   int count  = 0;
   deque <Student> help;
   
   do
   {
      cout << "<" << count << "> ";
      cin  >> instuction_or_course;
      getline (cin, input);

      istringstream iStr(input);
      iStr >> course_or_name >> name_or_time >> time;
   
      // Add an emergency student
      if (instuction_or_course == "!!")
      {
         // Set students values
         student.setEmergencyRequest(true);
         student.setCourse(course_or_name);
         student.setName(name_or_time);
         student.setMinutes(time);

         // push emergency student onto the front of help deque
         help.push_front(student);

         // set instuction_or_course to none to display
         instuction_or_course = "none";

      }

      // Add a normal student
      if (instuction_or_course != "finished" && instuction_or_course != "emergency"
          && instuction_or_course != "none")
      {
         // Set students values
         student.setEmergencyRequest(false);
         student.setCourse(instuction_or_course);
         student.setName(course_or_name);

         // convert name_or_time string to an int
         int a = atoi(name_or_time.c_str());
         student.setMinutes(a);

         // push normal student onto back of deque
         help.push_back(student);

         // set instuction_or_course to none to display
         instuction_or_course = "none";
      }

      // Just display current student
      if (instuction_or_course == "none")
      {
         // if helped students time is up get 
         // another student
         if (helped.getMinutes() == 0 && !help.empty())
         {
            // Set helped to student at the front of the deque
            helped = help.front();

            // pop the front student 
            help.pop_front();
         }
         
         if (helped.getMinutes() > 0)
            display(helped);

         // after we display increment count
         count++;
      }
   }
   while(instuction_or_course != "finished");   
         
   // end
   
   cout << "End of simulation\n";
}





