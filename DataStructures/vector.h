/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    Vector is going to act like the vector from the STL
 *
 *    This will contain the class definition of:
 *       Vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Jonah Green
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

namespace custom
{

/************************************************
 * VECTOR
 * The vector class is suppose to be silimar to 
 * the stl vector
 ***********************************************/
template <class T>
class vector
{
public:
   /****************** 
   * Constructors
   ******************/
   // Default
   vector() : data(NULL), numItems(0), cap(0){}

   // Non-Default
   vector(int numItems) throw(const char *);
      
     // copy constructor : copy it
   vector(const vector & rhs) throw (const char *);
   
   // destructor : free everything
   ~vector()        { if (cap != 0) delete [] data; }
 
   /******************
   * Operators
   ******************/
   // = operator 
   vector & operator = (const vector & rhs) throw (const char *); 
     
   // [] operator array-specific interfaces
   T & operator [] (int index)       throw (const char *)
   {
      return data[index];
   }
   T   operator [] (int index) const throw (const char *)
   {
      return data[index];
   }
   
   // Iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();
   
   // Constant iterator interfaces
   class const_iterator;
   const_iterator cbegin() const{ return const_iterator (data); }
   const_iterator cend() const;
   
   /****************
   * Methods
   ****************/ 
   int size() const  { return numItems;}
   int capacity()    const{ return cap; }
   void clear()      { numItems = 0; } 
   bool empty() const{ return numItems == 0; } 
   void push_back (const T & item) throw (const char *);
    
private:
  void resize(int _cap) throw(const char*);
   T * data;          
   int cap;
   int numItems;   
};

/**************************************************
 * VECTOR ITERATOR
 * this class is nessted in Vector class and will 
 * allow the user to cycle through the vector using
 * an iterator for loop.
 *************************************************/
template <class T>
class vector <T> :: iterator
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
      p--;
      return *this;
   }
   
private:
   T * p;
};

/**************************************************
 * VECTOR :: CONST_ITERATOR
 * this class is nessted in Vector class and will 
 * allow the user to cycle through the vector using
 * an iterator for loop this iterator will be 
 * a read only meaning the user will be unable to 
 * change data if this iterator is used.
 *************************************************/
template <class T>
class vector <T> :: const_iterator
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
   bool operator != (const const_iterator & rhs) 
                      const { return rhs.p != this->p; }
   bool operator == (const const_iterator & rhs) 
                      const { return rhs.p == this->p; }

   // dereference operator
   const T & operator * ()
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
      iterator tmp(*this);
      p++;
      return tmp;
   }
   
   // prefix decrement
   const_iterator & operator -- ()
   {
      p--;
      return *this;
   }
   
   // postfix decrement
   const_iterator & operator -- (int postfix)
   {
      p--;
      return *this;
   }
   
private:
   T * p;
};

/********************************************
 * VECTOR :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: iterator vector <T> :: end ()
{
   return iterator (data + numItems);
}

template <class T>
typename vector <T> :: const_iterator vector <T> :: cend() const
{
   return const_iterator (data + numItems);
}
/*******************************************
 * VECTOR :: Assignment
 * This is the overloaded Assignment operator
 * I will allow the data structure to be used
 * like this D1 = D2 
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
          throw (const char *)
{
   if (this == &rhs)
   {
      return *this;
   }
   else
   {
      if (rhs.numItems > cap)
      {
         delete [] data;
         data = new T[rhs.numItems];
         cap = rhs.numItems;
      }
      for (int i = 0; i < rhs.numItems; i++)
      {
        data[i] = rhs.data[i];
      }
      numItems = rhs.numItems;
      return *this;
   }
}


/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 * Gets a Vector passed in and copies the 
 * data from the current vector to the new
 * vector.
 *******************************************/ 
template <class T>
vector <T> :: vector(const vector <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = 0;
      numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < cap; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "numItems"
 **********************************************/
template <class T>
vector <T> :: vector(int numItems) throw (const char *)
{
   assert(numItems >= 0);
    
   // do nothing if there is nothing to do.
   if (numItems == 0)
   {
      this->cap = 0;
      this->data = NULL;
      return;
   }

   // If numItems is something set the newly made vector's
   // numItems and cap to specified numItem
   this->cap = numItems;
   this->numItems = numItems;
   
   // attempt to allocate
   try
   {
      data = new T[cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
}

/**********************************************************
* VECTOR :: Push_Back
* Push a new item onto the back of the vector if the 
* numItems is less then the capacity if not call
* the resize function
**********************************************************/  
template <class T> 
void vector <T> :: push_back(const T & item) throw (const char *)
{
   if(numItems >= cap)
   {
      resize(cap * 2);   
   }
   data[numItems] = item;
   numItems++;  
}
  
/**********************************************************
* VECTOR :: RESIZE
* Resize is called when the vectors size has reached 
* capacity Resize will double the arrays capacity
**********************************************************/
template <class T>
void vector <T> :: resize(int _cap) throw (const char *)
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
      for(int i = 0; i < numItems; i++)
      {
         tempArray[i] = data[i];
      }
      delete [] data;
      cap = _cap;
      data = tempArray;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR unable to allocate buffer";
   }
}

}; // namespace custom

#endif // ARRAY_H
