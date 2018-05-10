/**********************************************************
* QUEUE.H
* Contains:
*     Queue class
* Authors: Jonah Green, Jared Garcia, Jacob Bogdan
**********************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>
namespace custom
{

/**********************************************************
* QUEUE CLASS
* This class will act a lot like the std queue
* an item will be added on to the back 
* and removed from the front
**********************************************************/
template <class T>
class queue
{
   private:
      // Variables
      T * array;
      int numPush;
      int numPop;
      int numCap;
      
      // Methods
      void resize(int numCap = 0) throw(const char*);
      int iHead()const { return numPop % numCap;       }
      int iTail()const { return (numPush - 1) % numCap;}
      
   public:
      // Constructors / Destructor
      queue(               ) : array(NULL), numPush(0), numPop(0), numCap(0) {}
      queue(int numCap     )   throw (const char*);
      queue(const queue & rhs) throw (const char*);
      ~queue() { if(numCap != 0) delete [] array; }
      
      // Overloaded Operators
      queue & operator = (const queue & rhs) throw(const char *);
   
      // Methods
      int size()     const { return numPush - numPop;      }
      int capacity() const { return numCap;                }
      bool empty()   const { return numPush - numPop == 0; }
      void clear()         { numPush = 0; numPop = 0; }
      void push(const T & t);
      void pop()           { if (!empty()) numPop++;       }
      T & front();   
      T front() const;
      T & back();      
      T back()  const;
};

/**********************************************************
* QUEUE :: NON-DEFAULT CONSTRUCTOR
* This will make a new queue with a set capacity
* Parameter: int numCap
**********************************************************/
template <class T>
queue <T> :: queue(int numCap) throw (const char*) :
  numCap(0), numPush(0), numPop(0), array(NULL)
{
   assert(numCap >= 0);
   
   // if numCap is zero return 
   if (numCap == 0)
   {
      return;
   }
   
   // attempt to allocate
   try
   {
      resize(numCap);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
}

/**********************************************************
* QUEUE :: COPY CONSTRUCTOR
* Copies data from one queue to another 
* Parameter: queue & rhs 
**********************************************************/   
template <class T>
queue <T> :: queue(const queue & rhs) throw(const char *) :
   numCap(0), numPush(0), numPop(0), array(NULL)
{
   try
   {
      // Use the assignment operator. 
      *this = rhs;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
}

/**********************************************************
* QUEUE :: ASSIGNMENT OPERATOR
* Takes in a lhs and rhs que and sets the left queue's 
* values to the right queue's values
* Parameter: queue & rhs
**********************************************************/
template <class T>
queue <T> & queue <T> :: operator = (const queue & rhs) throw(const char *)
{
   try
   {
      if (this == &rhs)
      {
         return *this;
      }
      
      if (rhs.numCap == 0)
      {
         numPush = 0;
         numPop = 0;
         array = NULL;
         return *this;
      }
      
      // Reallocate if necessary. 
      if (this->capacity() <= rhs.size())
      {
         resize(rhs.size());
      }

      // Copy over all the elements from the right side into left hand side.
      numPush = rhs.numPop;
      numPop = rhs.numPop;
      for (int i = rhs.numPop; i < rhs.numPush; i++) 
      {
         this->push(rhs.array[i % rhs.numCap]);
      }
      numPush = rhs.numPush;

      return *this;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
} 

/**********************************************************
* QUEUE :: PUSH
* Push will add an item at the end of the queue
* Parameter: A const T item
**********************************************************/
template <class T>
void queue <T> :: push(const T & t)
{
    try
    {
       if (size() == capacity())
          resize(capacity() * 2);
       numPush++;
       array[iTail()] = t;
    } 
    catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }   
}

/**********************************************************
* QUEUE :: FRONT
* Front will return the item at the front of the queue
* This front can be changed
**********************************************************/
template <class T>
T & queue <T> :: front() 
{
   if (empty())
      throw "ERROR: attempting to access an item in an empty queue";
   else
      return array[iHead()];          
}

/**********************************************************
* QUEUE :: FRONT CONST
* Front will return the item at the front of the queue
* This front is constant and cannot be changed
**********************************************************/
template <class T>
T queue <T> :: front() const
{
   if (empty())
      throw "ERROR: attempting to access an item in an empty queue";
   else
      return array[iHead()];   
} 

/**********************************************************
* QUEUE :: BACK
* Back will return the item at the end of the queue
* This back can be changed
**********************************************************/
template <class T>
T & queue <T> :: back() 
{ 
   if (empty())
      throw "ERROR: attempting to access an item in an empty queue";
   else
      return array[iTail()];           
}

/**********************************************************
* QUEUE :: BACK CONST
* Back will return the item at the end of the queue
* This back is a constant and cannot be changed
**********************************************************/
template <class T>
T queue <T> :: back() const 
{ 
   if (empty())
      throw "ERROR: attempting to access an item in an empty queue";
   else
      return array[iTail()];    
} 

/**********************************************************
* QUEUE RESIZE
* Reallocates new capacity for the array. If the array had
* been wrapped, the array is then unwrapped into a newly
* allocated array. 
**********************************************************/
template <class T>
void queue <T> :: resize(int numCap) throw (const char *)
{
   try
   {
      if (numCap == 0) 
      {
         numCap = 1;
      }
      
      T * tempArray = new T[numCap];
      int temp = size();
      
      for (int i = 0; i < temp; i++)
      {
         tempArray[i] = array[iHead()];
         pop();
      }
      
      if (array != NULL)
         delete [] array;
      
      numPop = 0;
      numPush = temp;
      array = tempArray;
      this->numCap = numCap;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
}
   
}; // Namespace Custom
#endif //QUEUE_H
