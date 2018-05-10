/***********************************************************************
 * Header:
 *    LIST_H
 * Summary:
 *    Contains:
 *    	 Node Class 
 *       list class
 *       list iterator   
 * Author
 *    Jonah Green, Jared Garcia, Jacob Bogdan
 ************************************************************************/
#ifndef LIST_H
#define LIST_H

#include <cassert>
using std::ostream;

namespace custom
{
/**********************************************************
* NODE CLASS
* Node class is one link in a linked list
* holds data and a pointer the the next and previous 
* Node
**********************************************************/
template <class T>
class Node
{
   	public:
       Node() : data(), pNext(NULL), pPrev(NULL) {}
       Node(const T & t) : data(t), pNext(NULL), pPrev(NULL) {}
       T data;
       Node *pNext;
       Node *pPrev; 


}; // NODE

/**********************************************************
* LIST CLASS
* List class will be a wrapper class to node and make a linked list
* that is easy for the user
**********************************************************/
template <class T>
class list
{
   private:
      Node <T> * pHead;
      Node <T> * pTail;
      T data;
      int numItems;
      Node <T> * place ( const T & t, Node <T> * pNode, bool after );
      Node <T> * copy ( const Node <T> * pSource ) throw (const char *);
      Node <T> * find ( Node <T> *& pHead, const T & t );

   public:
      list() : data(), pHead(NULL), pTail(NULL), numItems(0) {}
      list(list & rhs)              { *this = rhs;                       }
      ~list()                       { if(numItems != 0) clear(); }
      list & operator = (const list & rhs) throw(const char *);
      int size()                    { return numItems;                   }
      bool empty()                  {  assert(size() >= 0);
      	                               return size() == 0;               }           
      void clear();                
      T & front() const throw(const char*);
      T & front() throw(const char*);                  
      T & back()  const throw (const char*);
      T & back()  throw(const char*);        
      void push_back( const T & t );
      void pop_back();
      void push_front(const T & t);
      void pop_front();

      class iterator;
      iterator begin() { return iterator(pHead); }
      iterator end()   { return iterator(NULL); }
      iterator insert(iterator & it, const T & t) throw (const char*);
      iterator erase(iterator & it);
      

      class reverse_iterator;
      reverse_iterator rbegin() { return reverse_iterator(pTail); }
      reverse_iterator rend()   { return reverse_iterator(NULL); }
      reverse_iterator insert(reverse_iterator & it, const T & t) throw (const char*);
      reverse_iterator erase(reverse_iterator & it);
     

}; // LIST

/**********************************************************
* LIST ITERATOR 
* A class that allows the user to iterate through a list
**********************************************************/
template <class T>
class list <T> :: iterator
{
   private:
   Node <T> * p;

   public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(Node <T> * p) : p(p)         {              }
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
      if (p != NULL)
         return p->data;
   }

   // prefix increment
   iterator & operator ++ ()
   {
      if (p != NULL)
         p = p->pNext;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      if (p != NULL)
         p = p->pNext;
      return tmp;
   }
   
   // prefix decrement
   iterator & operator -- ()
   {
      if (p != NULL)
         p = p->pPrev;
      return *this;
   }
   
   // postfix decrement
   iterator & operator --(int postfix)
   {
      iterator temp(*this);
      if (p != NULL)
         p = p->pPrev;
      return temp;
   }

   // These two need to access node * p
   friend iterator list <T> :: insert(iterator & it, const T & t) throw (const char*);
   friend iterator list <T> :: erase(iterator & it);

}; // LIST ITERATOR

/**********************************************************
* LIST :: REVERSE_ITERATOR 
* Like list iterator but in reverse
**********************************************************/
template <class T>
class list <T> :: reverse_iterator
{
   private:
      Node <T> * p;

   public:
   // constructors, destructors, and assignment operator
   reverse_iterator()      : p(NULL)      {              }
   reverse_iterator(Node <T> * p) : p(p)         {              }
   reverse_iterator(const reverse_iterator & rhs) { *this = rhs; }
   reverse_iterator & operator = (const reverse_iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const reverse_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const reverse_iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
   T & operator * ()
   {
      if (p != NULL)
         return p->data;
   }

   // prefix increment
   reverse_iterator & operator ++ ()
   {
      if (p != NULL)
         p = p->pPrev;
      return *this;
   }

   // postfix increment
   reverse_iterator operator ++ (int postfix)
   {
      reverse_iterator tmp(*this);
      if (p != NULL)
         p = p->pPrev;
      return tmp;
   }
   
   // prefix decrement
   reverse_iterator & operator -- ()
   {
      if (p != NULL)
         p = p->pNext;
      return *this;
   }
   
   // postfix decrement
   reverse_iterator & operator --(int postfix)
   {
      reverse_iterator temp(*this);
      if (p != NULL)
         p = p->pNext;
      return *this;
   }

   // These two need to access node * p
   friend reverse_iterator list <T> :: insert(reverse_iterator & it, const T & t) throw (const char*);
   friend reverse_iterator list <T> :: erase(reverse_iterator & it);

}; // LIST REVERSE_ITERATOR

/**********************************************************
* LIST :: CLEAR
* Removes the data from a linked list
* parameters is the head of a linked list
**********************************************************/
template <class T>
void list <T> :: clear() 
{
  while (pHead != NULL)
  {
    Node <T> * pDelete = pHead;
    pHead = pHead->pNext;
    delete pDelete;
    pDelete = NULL;
  }
  pHead = NULL;
  pTail = NULL;
  numItems = 0;
}

/**********************************************************
* LIST :: = OPERATOR
* Copies the items in one list to antoher
* takes in the head of a list and returns the
* head of the copied list
**********************************************************/
template <class T>
list <T> & list <T> :: operator = (const list & rhs) throw(const char *)
{
  Node <T> * n = new Node <T> (rhs.pHead->data);
  Node <T> * nDes = n;

  // Copy over rhs
  for (Node <T> * p = rhs.pHead->pNext; p; p = p->pNext)
    nDes = place(p->data, nDes, true);
  numItems = rhs.numItems;
  pTail    = nDes;
  pHead    = n;

  return *this;
}

/**********************************************************
* LIST :: PLACE
* inserts a node into a linked list takes in three parameters
* a data item a node and a bool
* returns a the new node that was made
**********************************************************/
template <class T>
Node <T> * list <T> :: place(const T & t, Node <T> * pNode, bool after = false)
{
   Node <T> * pNew = new Node<T>(t);

   // If the new node is not at the end of the list
   if (pNode != NULL && after == false)
   {
      pNew->pNext  = pNode;
      pNew->pPrev  = pNode->pPrev;
      pNode->pPrev = pNew;
      if (pNew->pPrev)
        pNew->pPrev->pNext = pNew;
      else
        pHead = pNew;
   }
   // If node is at the end of the list   
   if (pNode != NULL && after == true)
   {
      pNew->pPrev  = pNode;
      pNew->pNext  = pNode->pNext;
      pNode->pNext = pNew;
      if (pNew->pNext)
        pNew->pNext->pPrev = pNew;
      else
        pTail = pNew;
   }

   return pNew;
}

/**********************************************************
* LIST :: INSERT
* inserts a node into a list takes in two parameters
* a data item and an iterator
* returns a the new iterator that was made
**********************************************************/
template <class T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator & it,
                             const T & t) throw (const char *) 
{
   if (it == end())
      place(t, pTail, true);
  
   else 
      place(t, it.p, false);
   return it;
}

/**********************************************************
* LIST :: REVERSE_INSERT
* its like normal insert but for a reverse iterator
**********************************************************/
template <class T>
typename list <T> :: reverse_iterator list <T> :: insert
         (list <T> :: reverse_iterator & it, const T & t) throw (const char *) 
{
   if (it == end())
      place(t, pTail, true);
  
   else 
      place(t, it.p, false);
   return it;
}

/**********************************************************
* LIST :: Erase
* Takes in an iterator to a node and removes the node from
* the list
**********************************************************/
template <class T>
typename list <T> :: iterator list <T> :: erase(list <T> :: iterator & it)
{
   if (NULL == it.p)
     return it;

   if (it.p->pPrev)
     it.p->pPrev->pNext = it.p->pNext;
   else
     pHead = it.p->pNext;
   if (it.p->pNext)
     it.p->pNext->pPrev = it.p->pPrev;
   else
     pTail = it.p->pPrev;
   
   delete it.p;

   return it;
}

/**********************************************************
* LIST :: REVERSER_ERASE
* Like normal erase but for a reverse iterator
**********************************************************/
template <class T>
typename list <T> :: reverse_iterator list <T> :: erase
                            (list <T> :: reverse_iterator & it)
{
   if (NULL == it.p)
     return it;

   if (it.p->pPrev)
     it.p->pPrev->pNext = it.p->pNext;
   else
     pHead = it.p->pNext;
   if (it.p->pNext)
     it.p->pNext->pPrev = it.p->pPrev;
   else
     pTail = it.p->pPrev;
   
   delete it.p;

   return it;
}

/**********************************************************
* FIND
* finds a node in a linked list takes in the head of the
* list and returns the node in the linked list that is
* holding the specified data
**********************************************************/
template <class T>
Node <T> * list <T> :: find (Node <T> *& pHead, const T & t)
{
    T * p;
    for (Node <T> * p = pHead; p; p = p->pNext)
       if (p->data == t)
          return p;
    return NULL;        
}  

/**********************************************************
* << OPERATOR
* Walks through a linked list and displays each item
**********************************************************/
template <class T>
ostream & operator << (ostream & out, Node <T> * pHead)
{
    for (Node <T> * p = pHead; p; p = p->pNext)
    {
      if (p->pNext == NULL)
         out << p->data;
      else
         out << p->data << ", "; 
    }
    return out;
} 

/**********************************************************
* LIST :: PUSH_BACK
* Push back takes in a t value and adds it to the 
* back of the list
**********************************************************/
template <class T>
void list <T> :: push_back(const T & t) // THIS THROWS
{ 
  pTail = place(t, pTail, true);

  if (empty())
    pHead = pTail;

  numItems++;
}

/**********************************************************
* LIST :: POP_BACK
* Pop back removes the item off of the back of the list
**********************************************************/
template <class T>
void list <T> :: pop_back() 
{
   remove(pTail);
   numItems--;
}

/**********************************************************
* LIST :: PUSH_FRONT
* Adds a T value to the front of a list
**********************************************************/
template <class T>      
void list <T> :: push_front(const T & t) // THIS THROWS
{ 
  pHead = place(t, pHead, false);  

  if (empty())
    pTail = pHead;   

  numItems++;
  
}

/**********************************************************
* POP_FRONT
* Removes the value from the front of the list
**********************************************************/
template <class T>
void list <T> :: pop_front()
{
   remove(pTail);
   numItems--;
}

/**********************************************************
* LIST :: FRONT
* Returns the value at the front of the list
* the value returned can be changed
**********************************************************/
template <class T>
T & list <T> :: front() throw (const char*)                  
{ 
	if (!empty())
	  return pHead->data;
	throw "ERROR: unable to access data from an empty list\n";  
}

/**********************************************************
* LIST :: CONST_FRONT
* Returns the value at the front of the list the 
* value returned cannot be changed
**********************************************************/
template <class T>
T & list <T> :: front() const throw (const char*)                  
{ 
	if (!empty())
	  return pHead->data;
	throw "ERROR: unable to access data from an empty list\n";   
}

/**********************************************************
* LIST :: BACK
* Returns the value at the back of the list
* this value can be changed
**********************************************************/
template <class T>
T & list <T> :: back() throw (const char *)
{ 
	if (!empty())
	   return pTail->data;
	throw "ERROR: unable to access data from an empty list\n";   
} 

/**********************************************************
* LIST :: CONST_BACK
* Returns the value at the back of the list
* this value cannot be changed
**********************************************************/
template <class T>
T & list <T> :: back() const throw (const char *)
{ 
	if (!empty())
	   return pTail->data;
	throw "ERROR: unable to access data from an empty list\n";   
} 

}; // CUSTOM
#endif //LIST_H