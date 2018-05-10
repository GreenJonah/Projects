/**********************************************************
* DEQUE.H
* Contains:
*     deque class
* Authors: Jonah Green, Jared Garcia, Jacob Bogdan
**********************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>
using std::cerr;
using std::endl;
namespace custom
{

/**********************************************************
* DEQUE CLASS
* This class will act a lot like the std deque
* an item will be added on to the back 
* and removed from the front
**********************************************************/
template <class T>
class deque
{
   private:
      // Variables
      T * array;
      int numCap;
      int iBack;
      int iFront;
      
      // Methods
      void resize(int numCap = 0) throw(const char*);
      
      int iFrontNormalized()  
      { 
         return convert(iFront, numCap);     
      }

      int iBackNormalized()   
      {
         return convert(iBack, numCap);
      }

      // Called by Ifront/back normalized
      // This function will change the index value
      // to a value that array can use. 
      int convert(int value, int numCap)
      {
        if ( value % numCap < 0)
            return (numCap + (value % numCap));
        else
        	return value % numCap;
      }

   public:
      // Constructors / Destructor
      deque(               ) : array(NULL), iFront(0), iBack(-1), numCap(0) {}
      deque(int numCap     )   throw (const char*);
      deque(const deque & rhs) throw (const char*);
      ~deque() { if(numCap != 0) delete [] array; }
      
      // Overloaded Operators
      deque & operator = (const deque & rhs) throw(const char *);
   
      // Methods
      int size()     const { return iBack - iFront + 1;      }
      int capacity() const { return numCap;                  }
      bool empty()   const { assert(size() >= 0);
      	                     return size() == 0;             }
      void clear()         { iFront = 0; iBack = -1;         }
      void push_front(const T & t);
      void push_back(const T & t) throw (const char*);
      void pop_front();      
      void pop_back();   
      T & front()      throw (const char*);   
      T front() const  throw (const char*);
      T & back()       throw (const char*); 
      T back()  const  throw (const char*);
};

/**********************************************************
* DEQUE :: NON-DEFAULT CONSTRUCTOR
* This will make a new deque with a set capacity
* Parameter: int numCap
**********************************************************/
template <class T>
deque <T> :: deque(int numCap) throw (const char*) :
  numCap(0), iFront(0), iBack(-1), array(NULL)
{
   assert(numCap >= 0); // making sure NumCap is at least 0
   
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
* DEQUE :: COPY CONSTRUCTOR
* Copies data from one deque to another 
* Parameter: deque & rhs 
**********************************************************/   
template <class T>
deque <T> :: deque(const deque & rhs) throw(const char *) :
   numCap(0), iFront(0), iBack(-1), array(NULL)
{
   try
   {
   	  assert(rhs.numCap >= 0); // right hand numCap should not
                               // be less than 0
   	  assert(numCap >= 0);     // just to make extra sure it's
                               // not
                               
      // Use the assignment operator. 
      *this = rhs;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
}

/**********************************************************
* DEQUE :: ASSIGNMENT OPERATOR
* Takes in a lhs and rhs que and sets the left deque's 
* values to the right deque's values
* Parameter: deque & rhs
**********************************************************/
template <class T>
deque <T> & deque <T> :: operator = (const deque & rhs) throw(const char *)
{
   try
   {
   	  // See if deque is equal to the previous deque
      if (this == &rhs)
      {
         return *this;
      }
      
      // Clear this deque
      clear();

      // Make sure clear worked and check to see if rhs
      // is equal to 0 if so return
      assert(size() == 0);
      if (rhs.size() == 0)
      {
         return *this;
      }
      
      // Resize if necessary. 
      if (this->capacity() < rhs.size())
      {
         resize(rhs.size());
      }
      
      // Copy over all the elements from the right side into left hand side.
      int j = convert(rhs.iFront, rhs.numCap);
      for (int i = rhs.iFront; i <= rhs.iBack; i++) 
      {
         this->push_back(rhs.array[j]);
         j++;

         if (j == rhs.numCap)
            j = 0;
      }

      return *this;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

} 

/**********************************************************
* DEQUE :: PUSH_FRONT
* Push will add an item at the front of the deque
* Parameter: A const T item
**********************************************************/
template <class T>
void deque <T> :: push_front(const T & t)
{
    try
    {
       if (size() == capacity())
          resize(capacity() * 2);
       iFront--;
       array[iFrontNormalized()] = t; // Allocates Normalized
                                      // Front into object t
    } 
    catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }   
}

/**********************************************************
* DEQUE :: PUSH_BACK
* Push will add an item at the end of the deque
* Parameter: A const T item
**********************************************************/
template <class T>
void deque <T> :: push_back(const T & t) throw (const char*)
{
       if (size() == capacity())
          resize(capacity() * 2);
       iBack++;
       array[iBackNormalized()] = t; // Allocates Normalized
                                     // Front into object t
}

 /**********************************************************
* DEQUE :: POP_FRONT 
* Front will delete the item at the front of the deque
**********************************************************/
template <class T>
void deque <T> :: pop_front()
{
   if (empty())
      return;
   else
      iFront++;          
}

/**********************************************************
* DEQUE :: POP_BACK
* pop_back will delete the item at the back of the deque
**********************************************************/
template <class T>
void deque <T> :: pop_back()
{
   if (empty())
      return;
   else
      iBack--;          
}

/**********************************************************
* DEQUE :: FRONT
* Front will return the item at the front of the deque
* This front can be changed
* Returns: A Template item.
**********************************************************/
template <class T>
T & deque <T> :: front() throw (const char*)
{
   if (empty())
      throw "ERROR: unable to access data from an empty deque";
   else
      return array[iFrontNormalized()];          
}

/**********************************************************
* DEQUE :: FRONT CONST
* Front will return the item at the front of the deque
* This front is constant and cannot be changed
* Returns: A T item.
**********************************************************/
template <class T>
T deque <T> :: front() const throw(const char*)
{
   if (empty())
      throw "ERROR: unable to access data from an empty deque";
   else
      return array[iFrontNormalized()];   
} 

/**********************************************************
* DEQUE :: BACK
* Back will return the item at the end of the deque
* This back can be changed
* Returns: A T item.
**********************************************************/
template <class T>
T & deque <T> :: back() throw (const char*)
{ 
   if (empty())
      throw "ERROR: unable to access data from an empty deque";
   else
      return array[iBackNormalized()];           
}

/**********************************************************
* DEQUE :: BACK CONST
* Back will return the item at the end of the deque
* This back is a constant and cannot be changed
* Returns: A T item.
**********************************************************/
template <class T>
T deque <T> :: back() const throw (const char*)
{ 
   if (empty())
      throw "ERROR: unable to access data from an empty deque";
   else
      return array[iBackNormalized()];    
} 

/**********************************************************
* DEQUE :: RESIZE
* Reallocates new capacity for the array. If the array had
* been wrapped, the array is then unwrapped into a newly
* allocated array. 
* Parameter: An int that specifies the new capacity
**********************************************************/
template <class T>
void deque <T> :: resize(int numCap) throw (const char *)
{
   try
   {
   	  assert(numCap >= 0);
      if (numCap == 0) 
      {
         numCap = 1;
      }
      
      T * tempArray = new T[numCap];
      // temp holds the size value so iBack
      // can be reset to the right value
      int temp = size();
      for (int i = 0; i < temp; i++)
      {
         tempArray[i] = array[iFrontNormalized()];
         pop_front();
      }
      
      if (array != NULL)
         delete [] array;
      
      iFront = 0;
      iBack = temp - 1;
      array = tempArray;
      this->numCap = numCap;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
}
   
}; // Namespace Custom
#endif //DEQUE_H
