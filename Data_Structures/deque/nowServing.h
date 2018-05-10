/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This class holds the nowServing function which will be implemented
 *  in the .cpp file to run the student wati list program. This class 
 *  also holds a student class that will be used to hold the student 
 *  information given in the command prompt.
 *
 * Author
 *    Jacob Bogdan, Jonah Green, Jared Garcia
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

#include <string>

using std::string;

#include "deque.h"     // for DEQUE
// the class for the student to set the information
class Student
{
   private:
      string course;
      string name;
      int minutes;
      bool emergencyRequest;
   
   public:
      Student() : emergencyRequest(false), minutes(0) {};
      string getCourse() const                       { return course;                            }
      void setCourse(string course)                  { this->course = course;                    }
      string getName() const                         { return name;                              }
      void setName(string name)                      { this->name = name;                        }
      int getMinutes() const                         { return minutes;                           }
      void setMinutes(int minutes)                   { this->minutes = minutes;                  }
      bool isEmergency()                             { return emergencyRequest == true;          }
      void setEmergencyRequest(bool emergencyRequest){ this->emergencyRequest = emergencyRequest;}
};

// the interactive nowServing program
void nowServing();

#endif // NOW_SERVING_H

