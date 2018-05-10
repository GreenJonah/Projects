/**********************************************************
* MAP.H
* Contains:
*     Map class
* Authors: Jacob Bogdan, Jonah Green, Jared Garcia
*
* Summary:
*   This is a map data structure that encapsulates a binary
* search tree as its back bone for storing keys and values.
* The map has an iterator that uses bst's iterator. The map
* also has functions methods that are directly connected to
* the bst's methods.
**********************************************************/

#ifndef  MAP_H 
#define  MAP_H

#include <cassert>
#include "pair.h"

using std::cerr;
using std::endl;

namespace custom
{

template <class T>
class BST;

/**********************************************************
* MAP CLASS
* The map class has methods and iterators methods that are
* directly connected to the bst's methods. 
**********************************************************/	
template <class K, class V>
class map 
{
	public:
		// Constructors
		map() : bst() {}
		map(const map & rhs) throw (const char *) {*this = rhs; }
		
        // Operators
		map & operator = (const map & rhs) throw (const char*) { this->bst = rhs.bst; }
		V & operator [] (const K & k) throw (const char*);

    // These methods call the bst's methods 
		int size()   const { return bst.size(); } 
		bool empty() const { return size() == 0;  } 
		void clear()   { bst.clear();         }
    void insert(const K & k, const V & v) { Pair<K, V>pair(k, v); bst.insert(pair);} 
		
		// Nested Class
		class iterator;
		iterator begin() { return iterator (bst.begin()); }
    iterator end()   { return iterator(bst.end());    }
    iterator find(const K & k);

	private:
		BST <Pair<K, V> > bst;
};

/**********************************************************
* MAP :: FIND
* This function uses the find method of the bst class and 
* returns a maps iterator. 
**********************************************************/
template <class K, class V>
typename map <K, V> :: iterator map <K, V> :: find(const K & k)
{
   Pair<K, V> pair;
   pair.first = k;

   map <K, V> :: iterator it; 
   it.it = bst.find(pair); 

   return it;   
}

/**********************************************************
* MAP :: [] Operator
* This method takes a key and either returns the value from
* the key or returns the address to the value so the actual
* value can be assigned to that address. 
**********************************************************/
template <class K, class V>
V & map <K, V> :: operator [](const K & k) throw (const char *)
{
   Pair<K, V> pair;
   pair.first = k;

   map <K, V> :: iterator it; 
   it.it = bst.find(pair);
   if (it.it != NULL)
   {
      return it.it.p->data.second;
   }
   else
   {
      bst.insert(pair);
      return bst.find(pair).p->data.second;
   }  
   
}

/**************************************************
* MAP :: ITERATOR
* This is an iterator that is used by the map class
* and directly connects to the same methods of the 
* bst iterator. 
***************************************************/
template <class K, class V>
class map <K, V> :: iterator
{
   private:
       typename BST <Pair <K, V> > :: iterator it;

   public:
     // constructors, destructors, and assignment operator
     iterator() : it(NULL)      { }
     iterator(typename BST <Pair<K, V> >  :: iterator it) : it(it) { }
     iterator(const iterator & rhs) { *this = rhs; }
     iterator & operator = (const iterator  & rhs)
     {
        this->it = rhs.it;
        return *this;
     }

     // equals, not equals operator
     bool operator != (const iterator & rhs) const { return rhs.it != this->it; }
     bool operator == (const iterator & rhs) const { return rhs.it == this->it; }

     // dereference operator
     Pair<K, V> operator * () const
     {
        if (it != NULL)
           return it.p->data;
     }

     // prefix increment
     iterator & operator ++ ()
     {
        ++it;
        return *this;
     }

     // postfix increment
     iterator operator ++ (int postfix)
     {
        iterator tmp(*this);
        it++;
        return tmp;
     }

     iterator & operator -- ()
     {
          --it;
          return *this;
     }

     iterator operator -- (int postfix)
     {
          iterator temp(*this);
          it--;
          return temp;
     }

     friend class map;
};

/**************************************************
* CLASS BST
* Binary Search Tree Class
**************************************************/
template <class T>
class BST 
{
   public:
      // constructors / destructors
      BST() : root(NULL), numItems(0) {}
      BST(BST & rhs) throw(const char *) { *this = rhs; }
      ~BST() { if(numItems == 0){clear();} }

      // Operators
      BST & operator = (const BST <T> & rhs) throw(const char *);

      class BNode;
      // Methods
      int size()   const { return numItems;      }
      bool empty() const { return numItems == 0; }
      void clear();
      void insert(const T & t) throw (const char *);
      BNode * getRoot();
  
      //Iterator
      class iterator;
      void erase(iterator & it);
      iterator find(const T & t);
      iterator begin();
      iterator end()   { return iterator(NULL); }

      //reverse_iterator
      class reverse_iterator;
      void erase(reverse_iterator it);
      reverse_iterator rbegin();
      reverse_iterator rend()   { return reverse_iterator(NULL); }

   private:
      BNode * root;
      int numItems;
      void deleteNode(BNode * pNode, bool right);
      void deleteBinaryTree(BNode *& pNode);
      BNode * copyBinaryTree(const BNode * pSource) throw(const char *);
      BNode * traverse(BNode *& node, const T & t);
      void addRight(BNode * pNode, BNode * pAdd);
      void addLeft(BNode * pNode, BNode * pAdd);
      void addLeft(BNode * pNode, const T & t) throw (const char *);
      void addRight(BNode * pNode, const T & t) throw (const char *);
};

/**********************************************************
* BNODE CLASS
* This class represents each binary node inside of the binary
* tree. 
**********************************************************/
template <class T>
class BST <T> :: BNode
{
    public:
       BNode() : data(), pLeft(NULL), pRight(NULL), pParent(NULL), isRed(false){}
       BNode(const T & t) : data(t), pLeft(NULL), pRight(NULL), pParent(NULL), isRed(false) {}
       T data;
       BNode * pLeft;
       BNode * pRight;
       BNode * pParent;
       bool isRed; 

}; // BNODE 

/**********************************************************
* BST :: BEGIN
* returns an iterator at the begining of the bst
**********************************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: begin()
{
   if (root == NULL)
      return end();

   BST <T> :: BNode * p = root;
   while (p->pLeft != NULL)
     p = p->pLeft;
   return iterator(p);
}

/**********************************************************
* BST :: RBEGIN
* returns an iterator at the RBEGIN of the bst
**********************************************************/
template <class T>
typename BST<T> :: reverse_iterator BST <T> :: rbegin()
{
   BST <T> :: BNode * p = root;
   while (p->pRight != NULL)
     p = p->pRight;
   return reverse_iterator(p);
}

/**********************************************************
* BST :: ERASE
* Deletes the node that the passed in iterator is pointing to
**********************************************************/
template <class T>
void BST <T> :: erase(BST <T> :: iterator & it)
{
   // If it is a leaf
   if (it.p->pLeft == NULL && it.p->pRight == NULL)
   {
      if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
        it.p->pParent->pRight = NULL;
      if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
        it.p->pParent->pLeft = NULL;
      delete it.p;
   }

   // If it has one child 
   else if (it.p->pRight == NULL && it.p->pLeft != NULL)
   {
      it.p->pLeft->pParent = it.p->pParent;
      if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
        it.p->pParent->pRight = it.p->pLeft;

      if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
        it.p->pParent->pLeft = it.p->pLeft;

      delete it.p;
   }

   else if (it.p->pLeft == NULL && it.p->pRight != NULL)
   {
      it.p->pLeft->pParent == it.p->pParent;
      if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
        it.p->pParent->pRight = it.p->pRight;
      if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
        it.p->pParent->pLeft = it.p->pRight;

      delete it.p;
   }

   else
   {
     // Two Children
     BST <T> :: BNode * temp;
     // Successor
     if (it.p->pRight != NULL)
     {
        temp = it.p;
        ++it;
     
        if (it.p->pRight != NULL)
           it.p->pRight->pParent = it.p->pParent;
        it.p->pParent->pLeft = it.p->pRight;
        it.p->pParent = temp->pParent;
          if (temp->pParent != NULL)
           it.p->pParent->pRight = it.p;
        it.p->pLeft   = temp->pLeft;
        it.p->pLeft->pParent = it.p;
          it.p->pRight  = temp->pRight;
          it.p->pRight->pParent = it.p;

          delete temp;
     }
     
     // Predecessor
     if (it.p->pLeft != NULL && it.p->pRight == NULL)
     {
        temp = it.p;
        --it;
     
        if (it.p->pLeft != NULL)
           it.p->pLeft->pParent = it.p->pParent;
        it.p->pParent->pRight = it.p->pLeft;
        it.p->pParent = temp->pParent;
          if (temp->pParent != NULL)
           it.p->pParent->pLeft = it.p;
        it.p->pRight   = temp->pRight;
        it.p->pRight->pParent = it.p;
          it.p->pLeft  = temp->pLeft;
          it.p->pRight->pParent = it.p;

          delete temp; 
     }
   }
}

/**********************************************************
* BST :: FIND
* finds a node that is holding t if it does not exist
* returns end()
**********************************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: find(const T & t)
{
   if (root == NULL)
      return end();

   BST <T> :: iterator it;
   BST <T> :: BNode * node = traverse(root, t);
   
   it.p = node;

   if (node->data == t)
      return it;

   return end();   
}

/**********************************************************
* BST :: CLEAR
* Clear calls deleteBinaryTree and passes in root
* it will delete the bst
**********************************************************/
template <class T>
void BST<T> :: clear()
{
  deleteBinaryTree(root);
  numItems = 0;
}

/**********************************************************
* BST :: TRAVERSE
* Will take in a t value and travese the tree it will return
* a node if the item is found if it is not found it will return
* the previous node
**********************************************************/
template <class T>
typename BST <T> :: BNode * BST <T> :: traverse(BST <T> :: BNode *& node, const T & t)
{
   if (node->data == t)
     return node;
  
   if (node->data < t)
   {
      if (node->pRight == NULL)
        return node;
      else
        traverse(node->pRight, t);
   }
   else if (node->data > t)
   { 
      if (node->pLeft == NULL) 
        return node;
      else  
        traverse(node->pLeft, t);
   } 
}

/**********************************************************
* BST :: GET ROOT
* Returns the root of the BST class
**********************************************************/
template <class T>
typename BST <T> :: BNode * BST <T> :: getRoot()
{
   return root;
}

/**********************************************************
* BST :: = OPERATOR
* Copies the Nodes in one BST to antoher
* takes in the ROOT of a BST and returns the
* ROOT of the copied list
**********************************************************/
template <class T>
BST <T> & BST <T> :: operator = (const BST <T> & rhs) throw(const char *)
{
  this->root = copyBinaryTree(rhs.root);
  this->numItems = rhs.numItems;
  return *this;
}

/**********************************************************
* BST :: INSERT 
* Inserts a new BNode with its data set to t
* if a bst is not already made make a new one
**********************************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char *)
{
   if (root == NULL)
   {
      root = new BST <T> :: BNode(t);
      numItems++;
      return;
   }

   BST <T> :: BNode * node = traverse(root, t);
   
   if (node->data > t)
      addLeft(node, t);
   else
      addRight(node, t);
        
   numItems++;
}

/*********************************************************
* BST :: DELETE BTREE 
* deletes a nodes pLeft and pRight
* and then deletes the node
*********************************************************/
template <class T>
void BST <T> :: deleteBinaryTree(BST <T> :: BNode *& pNode)
{
   if (pNode == NULL)
     return;

   deleteBinaryTree(pNode->pLeft);
   deleteBinaryTree(pNode->pRight);
   delete pNode;
   pNode = NULL;
}

/*********************************************************
* BST :: COPY BTREE
* makes a new node and copies pLeft and PRight from
* the tree that is passed in
*********************************************************/
template <class T>
typename BST <T> :: BNode * BST <T> :: copyBinaryTree(const BST <T> :: BNode * pSource) throw (const char *)
{
   if (pSource == NULL)
      return NULL;
   BST <T> :: BNode * des = new BST <T> :: BNode(pSource->data);

   des->pLeft = copyBinaryTree(pSource->pLeft);
   if (des->pLeft != NULL)
      des->pLeft->pParent = des;

   des->pRight = copyBinaryTree(pSource->pRight);
   if (des->pRight != NULL)
      des->pRight->pParent = des; 

   return des;
}

/*********************************************************
* BST :: ADD LEFT 
* a root is passed in and a node the 
* node is set = to the roots pLeft pointer
*********************************************************/
template <class T>
void BST <T> :: addLeft(BST <T> :: BNode * pNode, BST <T> :: BNode * pAdd)
{
  if (pAdd != NULL)
    pAdd->pParent = pNode;
  pNode->pLeft = pAdd;
}

/*********************************************************
* BST :: ADD RIGHT 
* a root is passed in and a node the 
* node is set = to the roots pRight pointer
*********************************************************/
template <class T>
void BST <T> :: addRight(BST <T> :: BNode * pNode, BST <T> :: BNode * pAdd)
{
  if (pAdd != NULL)
    pAdd->pParent = pNode;
  pNode->pRight = pAdd;
}

/*********************************************************
* ADD LEFT
* a root is passed in and a value the 
* value is placed in a node and the
* node is set = to the roots pLeft pointer
*********************************************************/
template <class T>
void BST <T> :: addLeft(BST <T> :: BNode * pNode, const T & t) throw (const char *)
{
  BST <T> :: BNode * pAdd = new BST <T> :: BNode(t);
  pAdd->isRed = true;
  pAdd->pParent = pNode;
  pNode->pLeft = pAdd;
}

/*********************************************************
* ADD RIGHT
* a root is passed in and a value the 
* value is placed in a node and the
* node is set = to the roots pRight pointer
*********************************************************/
template <class T>
void BST <T> :: addRight(BST <T> :: BNode * pNode, const T & t) throw (const char *)
{
  BST <T> :: BNode * pAdd = new BST <T> :: BNode(t);
  pAdd->isRed = true;
  pAdd->pParent = pNode;
  pNode->pRight = pAdd;
}

/**************************************************
* BST :: ITERATOR
* this is an iterator the will allow the user to 
* move though an binary search tree
***************************************************/
template <class T>
class BST <T> :: iterator
{
   private:
       BST <T> :: BNode * p;

   public:
     // constructors, destructors, and assignment operator
     iterator()      : p(NULL)      {              }
     iterator(BST <T> :: BNode * p) : p(p)         {              }
     iterator(const iterator & rhs) { *this = rhs; }
     iterator(const reverse_iterator & rhs) : p(rhs.p) {}
     iterator & operator = (const iterator & rhs)
     {
        this->p = rhs.p;
        return *this;
     }

     // equals, not equals operator
     bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
     bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

     // dereference operator
     const T & operator * () 
     {
        if (p != NULL)
           return p->data;
     }

     // prefix
     iterator & operator ++ ();
     iterator operator ++ (int postfix) 
     {
     	iterator itReturn = *this;
     	++(*this);
     	return itReturn;
     }
     
     // prefix
     iterator & operator -- ();
     iterator & operator --(int postfix)
     {
     	iterator itReturn = *this;
     	--(*this);
     	return itReturn;
     }

     friend iterator BST <T> :: find(const T & t);
     friend void BST <T> :: erase(iterator & it);
     friend class reverse_iterator;

     template <class K, class V>
     friend class map <K, V> :: iterator;
     template <class K, class V>
     friend V & map <K, V> :: operator [](const K & k) throw (const char *);
};

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
{
   // do nothing if we have nothing
   if (NULL == p)
      return *this;

   // if there is a left node, take it
   if (NULL != p->pLeft)
   {
      // go left
      p = p->pLeft;

      // jig right - there might be more right-most children
      while (p->pRight)
         p = p->pRight;
      return *this;
   }

   // there are no left children, the right are done
   assert(NULL == p->pLeft);
   BST <T> :: BNode * pSave = p;

   // go up
   p = p->pParent;

   // if the parent is the NULL, we are done!
   if (NULL == p)
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == p->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (NULL != p && pSave == p->pLeft)
   {
      pSave = p;
      p = p->pParent;
   }

   return *this;
}

/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator ++ ()
{
   // do nothing if we have nothing
   if (NULL == p)
      return *this;

   // if there is a Right node, take it
   if (NULL != p->pRight)
   {
      // go Right
      p = p->pRight;

      // jig left - there might be more left-most children
      while (p->pLeft)
         p = p->pLeft;
      return *this;
   }

   // there are no right children, the left are done
   assert(NULL == p->pRight);
   BST <T> :: BNode * pSave = p;

   // go up
   p = p->pParent;

   // if the parent is the NULL, we are done!
   if (NULL == p)
      return *this;

   // if we are the left-child, got to the parent.
   if (pSave == p->pLeft)
      return *this;

   // we are the Right-child, go up as long as we are the right child!
   while (NULL != p && pSave == p->pRight)
   {
      pSave = p;
      p = p->pParent;
   }

   return *this;
}

/**************************************************
* BST :: REVERSE_ITERATOR
* this is an iterator the will allow the user to 
* move though an binary search tree backwards
***************************************************/
template <class T>
class BST <T> :: reverse_iterator
{
   private:
       BST <T> :: BNode * p;

   public:
     // constructors, destructors, and assignment operator
     reverse_iterator()      : p(NULL)      {              }
     reverse_iterator(BST <T> :: BNode * p) : p(p)         {              }
     reverse_iterator(const reverse_iterator & rhs) { *this = rhs; }
     reverse_iterator(const iterator & rhs) : p(rhs.p) {}
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

     // prefix
     reverse_iterator & operator ++ ();
     reverse_iterator operator ++ (int postfix)
     {
       	reverse_iterator itReturn = *this;
       	++(*this);
       	return itReturn;
     }
     
     // prefix
     reverse_iterator & operator -- ();
     reverse_iterator & operator --(int postfix)
     {
       	reverse_iterator itReturn = *this;
       	--(*this);
       	return itReturn;
     }
     friend class iterator;
     template <class K, class V>
     friend V & map <K, V> :: operator [](const K & k) throw (const char *);
};

/**************************************************
 * BST REVERSE_ITERATOR :: DECREMENT PREFIX
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
typename BST <T> :: reverse_iterator & BST <T> :: reverse_iterator :: operator -- ()
{
   // do nothing if we have nothing
   if (NULL == p)
      return *this;

   // if there is a left node, take it
   if (NULL != p->pLeft)
   {
      // go left
      p = p->pLeft;

      // jig right - there might be more right-most children
      while (p->pRight)
         p = p->pRight;
      return *this;
   }

   // there are no left children, the right are done
   assert(NULL == p->pLeft);
   BST <T> :: BNode * pSave = p;

   // go up
   p = p->pParent;

   // if the parent is the NULL, we are done!
   if (NULL == p)
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == p->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (NULL != p && pSave == p->pLeft)
   {
      pSave = p;
      p = p->pParent;
   }

   return *this;
}

/**************************************************
 * BST REVERSE ITERATOR :: DECREMENT PREFIX
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
typename BST <T> :: reverse_iterator & BST <T> :: reverse_iterator :: operator ++ ()
{
   // do nothing if we have nothing
   if (NULL == p)
      return *this;

   // if there is a Right node, take it
   if (NULL != p->pRight)
   {
      // go Right
      p = p->pRight;

      // jig left - there might be more left-most children
      while (p->pLeft)
         p = p->pLeft;
      return *this;
   }

   // there are no right children, the left are done
   assert(NULL == p->pRight);
   BST <T> :: BNode * pSave = p;

   // go up
   p = p->pParent;

   // if the parent is the NULL, we are done!
   if (NULL == p)
      return *this;

   // if we are the left-child, got to the parent.
   if (pSave == p->pLeft)
      return *this;

   // we are the Right-child, go up as long as we are the right child!
   while (NULL != p && pSave == p->pLeft)
   {
      pSave = p;
      p = p->pParent;
   }

   return *this;
}

}; // Custom Namespace

#endif // MAP_H