#ifndef BNODE_H
#define BNODE_H

template <class T>
class BNode
{
public:
   // Default Constructor
   BNode() : pLeft(NULL), pRight(NULL), pParent(NULL), data(NULL) {}
      
   // Non-Default Constructor
   BNode(T data) : pLeft(NULL), pRight(NULL), pParent(NULL)
      { this->data = data; }
   
   // Add new node to the left
   BNode & addLeft(T data) throw (const char *);
   BNode & addLeft(BNode * node) throw (const char *);
   
   // Add new node to the right
   BNode & addRight(T data) throw (const char *);
   BNode & addRight(BNode * node) throw (const char *);
   
   // Calculate numItems
   void calculateSize(BNode * node);

   // Assignment Operator
   BNode<T>& operator = (const BNode* rhs);
   
   int size() {numItems = 0; calculateSize(this); return numItems;}
   
   BNode * pParent;
   BNode * pLeft;
   BNode * pRight;
   int numItems;
   T data;
};


template <class T>
BNode<T> & BNode<T> :: operator = (const BNode<T> * rhs)
{
   this->parent = rhs.parent;
   this->pLeft = rhs.pLeft;
   this->pRight = rhs.pRight;
   this->data = rhs.data;
   
   return *this;
}



template <class T>
BNode<T> & BNode<T> :: addLeft(T data) throw (const char *)
{
   try
   {  
      BNode<T> * newLeft = new BNode<T>(data);
      this->pLeft = newLeft;
      newLeft->pParent = this;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return *this;
}


template <class T>
BNode<T> & BNode<T> :: addLeft(BNode * node) throw (const char *)
{   
   try
   {  
      // Link the pointers
      if (node != NULL)
      {
         this->pLeft = node;
         node->pParent = this;
      }
      else
      {
         this->pLeft = NULL;
      }
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return *this;
}


template <class T>
BNode<T> & BNode<T> :: addRight(T data) throw (const char *)
{
   try
   {
      BNode<T> * newRight = new BNode<T>(data);
      this->pRight = newRight;
      newRight->pParent = this;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return *this;
}


template <class T>
BNode<T> & BNode<T> :: addRight(BNode * node) throw (const char *)
{  
   try
   {
      if (node != NULL)
      {
         this->pRight = node;
         node->pParent = this;
      }
      else
      {
         this->pRight = NULL;
      }
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return *this;
}


template <typename T>
BNode<T>* copyBTree(BNode<T>* source)
{
	if (source == nullptr)
		return source;
	auto copyNode = new BNode<T>(source->data);
	copyNode->pLeft = copyBTree(source->pLeft);
	copyNode->pRight = copyBTree(source->pRight);
	return copyNode;
}


template <class T>
void BNode<T> :: calculateSize(BNode<T> * node)
{
   if (node->pLeft)
      calculateSize(node->pLeft);
   if (node->pRight)
      calculateSize(node->pRight);
   numItems++;
}


template <class T>
void deleteBinaryTree(BNode<T> * node)
{
   if(node->pLeft)
      deleteBinaryTree(node->pLeft);
   if(node->pRight)
      deleteBinaryTree(node->pRight);
   delete node;
   
}



template <class T>
std::ostream & operator << (std::ostream & out, const BNode<T> *rhs)
{
   if(!rhs) 
      return out;
   return out << rhs->pLeft << rhs->data << " " << rhs->pRight;
}

#endif

