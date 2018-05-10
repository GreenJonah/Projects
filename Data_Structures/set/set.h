/**********************************************************
* SET.H
* Contains:
*     set class
* Authors: Jacob Bogdan, Jonah Green, Jared Garcia
**********************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>
using std::cerr;
using std::endl;
namespace custom
{

/**********************************************************
* SET CLASS
* This class will act somewhat like the deque class but
* very different in a few regards; in order to compare
* sets we must have a intersection and union operator,
* which hardly resemble anything from the deque class.
**********************************************************/
template <class T>
class set
{
   private:
   // Variables
   T * array;
   int numItems;
   int numCap;
   int findIndex(const T & t);
   void resize(int numCap = 0) throw(const char*);

   public:
   // Constructors/Destructor
   set(               ) : array(NULL), numItems(0), numCap(0) {}
   set(int numCap     ) throw (const char*);
   set(const set & rhs) throw (const char*);
   ~set() { if(numCap != 0) delete [] array; }
   
   set & operator =  (const set & rhs)           throw(const char *);
   set operator ||   (const set <T> & rhs) const throw(const char *);
   set operator &&   (const set <T> & rhs) const throw(const char *);
   set operator -    (const set <T> & rhs) const throw(const char *);

    // Methods
   int size()         const {return numItems;                       }
   int capacity()     const {return numCap;                         } 
   bool empty()       const {assert(size() >= 0);return size() == 0;}
   void clear()             { numItems = 0;                         }
   void insert(const T & t) throw(const char*);

    // Iterator Interfaces
   class iterator;
   iterator begin()           { return iterator (array);           }
   iterator end()             { return iterator (array + numItems);}
   iterator find(const T & t);
   void erase(iterator & it);

   class const_iterator;
   const_iterator cbegin() const { return const_iterator (array);           }
   const_iterator cend()   const { return const_iterator (array + numItems);}
};

/**************************************************
 * SET :: ITERATOR
 * this class is nessted in set class and will 
 * allow the user to cycle through the set using
 * an iterator for loop.
 *************************************************/
template <class T>
class set <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }
   
   // prefix decrement
   iterator & operator -- ()
   {
      p--;
      return *this;
   }
   
   // postfix decrement
   iterator & operator --(int postfix)
   {
      iterator temp(*this);
      p--;
      return *this;
   }
   
private:
   T * p;
};

/**************************************************
 * SET CONSTANT ITERATOR
 * A constant iterator through set
 *************************************************/
template <class T>
class set <T> :: const_iterator 
{
public:
   // constructors, destructors, and assignment operator
   const_iterator()      : p(NULL)      {              }
   const_iterator(T * p) : p(p)         {              }
   const_iterator(const const_iterator & rhs) { *this = rhs; }
   const_iterator & operator = (const const_iterator & rhs) 
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
   T operator * ()
   {
      return *p;
   }

   // prefix increment
   const_iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   const_iterator operator ++ (int postfix)
   {
      const_iterator tmp(*this);
      p++;
      return tmp;
   }

   const_iterator & operator -- ()
   {
        p--;
        return *this;
   }

   const_iterator operator -- (int postfix)
   {
        const_iterator temp(*this);
        p--;
        return temp;
   }
   
private:
   T * p;
};

/**********************************************************
* SET :: NON-DEFAULT CONSTRUCTOR
* This will make a new set with a set capacity
* Parameter: int numCap
**********************************************************/   
template <class T>
set <T> :: set(int numCap) throw (const char*) :
   array(NULL), numItems(0), numCap(0)
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
* SET :: COPY CONSTRUCTOR
* Copies data from one set to another 
* Parameter: set & rhs 
**********************************************************/
template <class T>
set <T> :: set(const set & rhs) throw (const char*) :
   array(NULL), numItems(0), numCap(0)
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
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
}

/**********************************************************
* SET :: ASSIGNMENT OPERATOR
* Takes in a lhs and rhs que and sets the left deque's 
* values to the right deque's values
* Parameter: set & rhs
**********************************************************/
template <class T>
set <T> & set <T> :: operator = (const set & rhs) throw(const char *)
{
   try
   {
      // See if deque is equal to the previous deque
      if (this == &rhs)
      {
         return *this;
      }
      
      // Clear this set
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
      numItems = rhs.numItems;
      numCap = rhs.numCap;

      for (int i = 0; i < numItems; i++)
         array[i] = rhs.array[i];

      return *this;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
} 

/**********************************************************
 * SET :: UNION OPERATOR 
 * Increases the capacity of the array. 
 * Parameter: An int that specifies the new capacity
 *********************************************************/
template <class T>
set <T> set <T> :: operator || (const set <T> & rhs) const throw(const char *)
{
   int iSet1 = 0;
   int iSet2 = 0;
   set <T> setReturn;

   while (iSet1 < this->numItems || iSet2 < rhs.numItems)
   {  
       // if this set is empty or the index is iSet1 = numElements,
       // place the remainder of rhs into this 
       if (iSet1 == this->numItems)
       {
          setReturn.insert(rhs.array[iSet2++]);
       }

       // if this set is empty or the index is iSet2 = numElements,
       // place the remainder of this into rhs 
       else if (iSet2 == rhs.numItems)
       {
          setReturn.insert(this->array[iSet1++]);
       }
      
       // if the element in iSet1 is equal to the one in iSet2,
       // just set the element in this to setReturn
       else if (this->array[iSet1] == rhs.array[iSet2])
       {	
          setReturn.insert(this->array[iSet1]);
          iSet1++;
          iSet2++;
       }
      
       // if the element of iSet1 is less than the element of
       // iSet2, then set the element in this to setReturn
       else if (this->array[iSet1] < this->array[iSet2])
       {
          setReturn.insert(this->array[iSet1++]);
       }
       
       // if nothing else applies, just set the element in
       // rhs to setReturn       
       else
       {
          setReturn.insert(rhs.array[iSet2++]);  	
       }
   } 

   return setReturn;	
}

/**********************************************************
 * SET :: INTERSECTION OPERATOR 
 * Increases the capacity of the array. 
 * Parameter: An int that specifies the new capacity
 *********************************************************/
template <class T>
set<T> set <T> :: operator && (const set <T> & rhs) const throw(const char *)
{
   int iSet1 = 0;
   int iSet2 = 0;
   set <T> setReturn;

   while (iSet1 < this->numItems || iSet2 < rhs.numItems)
   {  
       // if this set is empty or the index is iSet1 = numElements,
       // return setReturn 
       if (iSet1 == this->numItems)
       {	
           return setReturn;   
       }

       // if this set is empty or the index is iSet2 = numElements,
       // return setReturn 
       else if (iSet2 == rhs.numItems)
       {	
           return setReturn;   
       }
       
       // if the element in iSet1 is equal to the one in iSet2,
       // just set the element in this to setReturn
       else if (this->array[iSet1] == rhs.array[iSet2])
       {	
          setReturn.insert(this->array[iSet1]);
          iSet1++;
          iSet2++;
       }
      
       // if the element of iSet1 is less than the element of
       // iSet2, then post-increment iSet1
       else if (this->array[iSet1] < rhs.array[iSet2])
       {
        
          iSet1++;
       }
       // if nothing else applies, just post-increment iSet2
       else
       {
          iSet2++;
        
        } 
   } 

   return setReturn;	
} 

/**********************************************************
 * SET :: DIFFERENCE OPERATOR 
 * Increases the capacity of the array. 
 * Parameter: An int that specifies the new capacity
 *********************************************************/
template <class T>
set<T> set <T> :: operator - (const set <T> & rhs) const throw(const char *)
{
   int iSet1 = 0;
   int iSet2 = 0;
   set <T> setReturn;

   while (iSet1 < this->numItems || iSet2 < rhs.numItems)
   {  
       // if this set is empty or the index is iSet1 = numElements,
       // return setReturn 
       if (iSet1 == this->numItems)
       {  
           return setReturn;   
       }

       // if this set is empty or the index is iSet2 = numElements,
       // return setReturn 
       else if (iSet2 == rhs.numItems)
       {  
           setReturn.insert(this->array[iSet1++]);  
       }
       
       // if the element in iSet1 is equal to the one in iSet2,
       // just set the element in this to setReturn
       else if (this->array[iSet1] == rhs.array[iSet2])
       {  
          iSet1++;
          iSet2++;
       }
      
       // if the element of iSet1 is less than the element of
       // iSet2, then post-increment iSet1
       else if (this->array[iSet1] < rhs.array[iSet2])
       {
          setReturn.insert(this->array[iSet1++]);
       }
       // if nothing else applies, just post-increment iSet2
       else
       {
          iSet2++;
        
       } 
   } 

   return setReturn;  
} 


/**********************************************************
* SET :: FIND
* Takes in a value and searches the set for that value
* if found an iterator pointing to the value is returned
**********************************************************/
template <class T>
typename set <T> :: iterator set <T> :: find(const T & t)
{
   int index = findIndex(t);
   if (index >= 0)
      return iterator(array + index);
   return end();
}

/**********************************************************
* SET :: FINDINDEX
* FindIndex will return an int that 
* specifies where in the array a new item should be inserted
**********************************************************/
template <class T>
int set <T> :: findIndex(const T & t)
{
   int iBegin = 0;
   int iEnd   = numItems - 1;
   while (iBegin <= iEnd)
   {
      int iMiddle = (iBegin + iEnd) / 2;
      if (t == array[iMiddle])
      {
        return iMiddle;
      }
     
      if (t < array[iMiddle])
         iEnd = iMiddle - 1;

      else
         iBegin = iMiddle + 1;
   } 
   return -1;
}

/**********************************************************
* SET :: INSERT
* Takes in a template value and inserts the value into the
* set. Order will be preserved when adding an item
**********************************************************/
template <class T>
void set <T> :: insert(const T & t) throw(const char*)
{
   // Call resize if nessessary
   if (numItems >= numCap)
      resize(numCap * 2);
   
   // No need to call find index if array is empty
   // or if t is greater then the last item is array
   if (numItems == 0 || array[numItems - 1] < t)
   {
       array[numItems] = t;
       numItems++;
       return;
   }
    
   // index will return -1 if the value is
   // not in the array or it will return where t should go 
   int index = findIndex(t);
   
   if (index == -1)
      index = 0;

   if (array[index] != t)
   {
      // Loop through and bump each value up till
      // array[i] is less then t and put t in the array
      for (int i = numItems; i >= index; --i)
      {
        if (t < array[i])
        {
          array[i + 1] = array[i];
          array[i] = t; 
        }
      }
      numItems++;
   }
}

/**********************************************************
* SET :: ERASE
**********************************************************/
template <class T> 
void set <T> :: erase(set <T> :: iterator & it)
{
   int iErase = findIndex(*it);
   if (array[iErase] == *it)
   {
      for (int i = iErase; i < numItems - 1; i++)
      {
         array[i] = array[i + 1];
      }
      numItems--;
   }
}

/**********************************************************
 * SET :: RESIZE
 * Increases the capacity of the array. 
 * Parameter: An int that specifies the new capacity
 *********************************************************/
template <class T>
void set <T> :: resize(int numCap) throw (const char*)
{
   try
   {
      assert(numCap >= 0);
      if (numCap == 0)
         numCap = 1;

      T * newData = new T[numCap];
      for (int i = 0; i < numItems; i++)
      {
           newData[i] = array[i];
      }

      if (array != NULL)
         delete [] array;

      array = newData;
      this->numCap = numCap;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
}
   
}; // Custom Namspace
#endif // SET_H
