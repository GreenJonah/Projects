/**********************************************************
* STACK.H
* Contains:
*     Stack class
* Author: Jonah Green, Jared Garcia, Jacob Bogdan
**********************************************************/

#ifndef STACK_H
#define STACK_H

#include <cassert>

namespace custom
{
/**********************************************************
* STACK CLASS
**********************************************************/
template <class T>
class stack
{
private:
   int numElements;
   int cap;
   T* array;
   void resize(int cap) throw(const char*);
   
public:
   // Constructors / Destructor
   stack(                 ) : array(NULL), numElements(0), cap(0) {}
   stack(          int cap) throw(const char *);
   stack(const stack & rhs) throw(const char *);
   ~stack(                ) { if(cap != 0) delete [] array; }
   
   // Overloaded Operators
   stack & operator = (const stack & rhs) throw(const char *);
   
   // Methods
   int size()      const { return numElements;        }
   int capacity()  const { return cap;                }
   bool empty()    const { return numElements == 0;   }
   void clear()          { numElements = 0;           }
   void push(const T & t) throw (const char*);
   
   
   void pop()            {if (!empty()) numElements--;}
   // We assume that both of these call the same method below.
   T top()               throw (const char*);
   const T & top() const throw (const char*);  
};

/**********************************************************
* STACK :: NON-DEFAULT CONSTRUCTOR
* Allows user to make a new stack and set the capacity
**********************************************************/
template <class T>
stack <T> :: stack(int cap) throw(const char *)
{
   // our cap cannot be less than 0
   assert(cap >= 0);
    
   // do nothing if there is nothing to do.
   if (cap == 0)
   {
      this->numElements = 0;
      this->array = NULL;
      return;
   }

   // If numItems is something set the newly made vector's
   // numItems and cap to specified numItem
   this->cap = cap;
   numElements = 0;
   
   // attempt to allocate
   try
   {
      array = new T[cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
}

/**********************************************************
* STACK :: COPY CONSTRUCTOR
* Copies data from one stack to another 
**********************************************************/   
template <class T>
stack <T> :: stack(const stack & rhs) throw(const char *) :
   cap(0), numElements(0), array(NULL)
{
   *this = rhs;
}

/*******************************************
 * STACK :: Assignment
 * This is the overloaded Assignment operator
 * I will allow the data structure to be used
 * like this D1 = D2 
 *******************************************/
template <class T>
stack <T> & stack <T> :: operator = (const stack <T> & rhs)
          throw (const char *)
{
   assert(rhs.cap >= 0);
   
   // if the pointer equals the reference to the stack, 
   //   return it dereferenced
   if (this == &rhs)
   {
      return *this;
   } 
   else if (rhs.cap == 0)
   {
      cap = 0;
      numElements = 0;
      array = NULL;
      return *this;
   }
   else if (rhs.numElements > cap)
   {
      try
      {
         resize(rhs.numElements);
      }
      catch(std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for stack";
      }
   }
   
   for (int i = 0; i < rhs.numElements; i++)
      array[i] = rhs.array[i];
   
   numElements = rhs.numElements;
   
   return *this;
}

/**********************************************************
* STACK :: PUSH
* Push a new element on the end of the stack
**********************************************************/
template <class T>
void stack <T> :: push(const T & t) throw (const char*)
{
   try
   {
      if (numElements == cap)
      {
         resize(cap * 2);   
      }
      array[numElements++] = t; // the array of elements is allocated 
   }                            // into our const 't' object
   catch (std::bad_alloc)
   {
      throw "Error: Unable to allocate a new buffer for Stack";
   }
}

/****************************************************************
* STACK :: TOP
* Returns the end of the stack in this case it is numElements -1
****************************************************************/
template <class T>
T stack <T> :: top() throw (const char*)
{
   try
   {
      if (!empty())
      { 
         return array[numElements - 1];  
      }
      else
      {
         throw "error";
      }
   }
   catch (const char * error)
   {
      throw "ERROR: Unable to reference the element from an empty Stack";
   }
}
 
/**********************************************************
* STACK :: RESIZE
* Resize is called when the stack size has reached 
* capacity Resize will double the arrays capacity
**********************************************************/
template <class T>
void stack <T> :: resize(int _cap) throw (const char *)
{
   try
   {     
      if(_cap == 0)
      {
         // 0 cannot be doubled 
         _cap = 1;
      } 

      // double cap
      T * tempArray = new T[_cap];
   
      // transfer the data
      for(int i = 0; i < numElements; i++)
      {
         tempArray[i] = array[i];
      }
      delete [] array;
      cap = _cap;
      array = tempArray;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: unable to allocate buffer";
   }
} 
}; //namespace custom

#endif //STACK_H