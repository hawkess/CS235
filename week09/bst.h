/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother Kirby, CS 235
 * Author:
 *    Sean Hawkes 
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

namespace custom
{

template <typename T>
class BST
{

public:
   class BNode
   {
   public:
      BNode(const T& t = T{});
      T data;
      bool isRed;
      BNode* pLeft;
      BNode* pParent;
      BNode* pRight;
   };

   template <bool isConst = false>
   class iterator_template
   {
   public:
      using ref = typename std::conditional<isConst, const BNode&,
                                            BNode&>::type;
      using ptr = typename std::conditional<isConst, const BNode*,
                                            BNode*>::type;
      using value_ref = typename std::conditional<isConst, const T&, T&>::type;
      using value_ptr = typename std::conditional<isConst, const T*, T*>::type;

      explicit iterator_template(ptr p = nullptr) : p_(p)
      {
      }
      iterator_template(const iterator_template& rhs)
      {
         *this = rhs;
      }
      iterator_template& operator=(const iterator_template& rhs)
      {
         if (this != &rhs)
            p_ = rhs.p_;
         return *this;
      }
      bool operator==(const iterator_template& rhs) const
      {
         return p_ == rhs.p_;
      }
      bool operator!=(const iterator_template& rhs) const
      {
         return !(*this == rhs);
      }
      iterator_template& operator++()
      {
         p_ = increment(p_);
         return *this;
      }
      iterator_template operator++(int)
      {
         iterator_template temp(*this);
         p_ = increment(p_);
         return temp;
      }
      iterator_template& operator--()
      {
         p_ = decrement(p_);
         return *this;
      }
      iterator_template operator--(int)
      {
         iterator_template temp(*this);
         p_ = decrement(p_);
         return temp;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<!isConst_, value_ref>::type
      operator*()
      {
         return p_->data;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<isConst_, value_ref>::type
      operator*() const
      {
         return p_->data;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<!isConst_, value_ptr>::type
      operator->()
      {
         return &p_->data;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<isConst_, value_ptr>::type
      operator->() const
      {
         return &p_->data;
      }
      ptr& _ptr()
      {
         return p_;
      }
   private:
      ptr p_;
      ptr increment(ptr p)
      {
         if (p == nullptr)
            return p;
         if (p->pRight != nullptr)
         {
            p = p->pRight;
            while (p->pLeft != nullptr)
               p = p->pLeft;
            return p;
         }
         auto save = p;
         p = p->pParent;
         if (p == nullptr)
            return p;
         if (save == p->pLeft)
            return p;
         while ((p != nullptr) && (save == p->pRight))
         {
            save = p;
            p = p->pParent;
         }
         return p;
      }
      ptr decrement(ptr p)
      {
         if (p == nullptr)
            return p;
         if (p->pLeft != nullptr)
         {
            p = p->pLeft;
            while (p->pRight != nullptr)
               p = p->pRight;
            return p;
         }
         auto save = p;
         p = p->pParent;
         if (p == nullptr)
            return p;
         if (save == p->pRight)
            return p;
         while ((p != nullptr) && (save == p->pLeft))
         {
            save = p;
            p = p->pParent;
         }
         return p;
      }
   }; // class iterator_template

     /***********************************************
    * LIST REVERSE_ITERATOR CLASS
    * Templatized reverse iterator for a list
    **********************************************/
   template <bool isConst = false>
   class reverse_iterator_template
   {
   public:
      using ref = typename std::conditional<isConst, const BNode&,
                                            BNode&>::type;
      using ptr = typename std::conditional<isConst, const BNode*,
                                            BNode*>::type;
      using value_ref = typename std::conditional<isConst, const T&, T&>::type;
      using value_ptr = typename std::conditional<isConst, const T*, T*>::type;

      explicit reverse_iterator_template(ptr p = nullptr) : p_(p) {}
      reverse_iterator_template(const reverse_iterator_template &rhs)
      {
         *this = rhs;
      }
      reverse_iterator_template& operator=(const reverse_iterator_template &rhs)
      {
         if (this != &rhs)
            this->p_ = rhs.p_;
         return *this;
      }
      bool operator==(const reverse_iterator_template& rhs) const
      {
         return this->p_ == rhs.p_;
      }
      bool operator!=(const reverse_iterator_template& rhs) const
      {
         return !(*this == rhs);
      }
      reverse_iterator_template& operator++()
      {
         p_ = decrement(p_);
         return *this;
      }
      reverse_iterator_template operator++(int)
      {
         reverse_iterator_template temp(*this);
         p_ = decrement(p_);
         return temp;
      }
      reverse_iterator_template& operator--()
      {
         p_ = increment(p_);
         return *this;
      }
      reverse_iterator_template operator--(int)
      {
         reverse_iterator_template temp(*this);
         p_ = increment(p_);
         return temp;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<!isConst_, value_ref>::type
      operator*()
      {
         return p_->data;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<isConst_, value_ref>::type
      operator*() const
      {
         return p_->data;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<!isConst_, value_ptr>::type
      operator->()
      {
         return &p_->data;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<isConst_, value_ptr>::type
      operator->() const
      {
         return &p_->data;
      }
      ptr& _ptr()
      {
         return p_;
      }
   private:
      ptr p_;
      ptr increment(ptr p)
      {
         if (p == nullptr)
            return p;
         if (p->pRight != nullptr)
         {
            p = p->pRight;
            while (p->pLeft != nullptr)
               p = p->pLeft;
            return p;
         }
         auto save = p;
         p = p->pParent;
         if (p == nullptr)
            return p;
         if (save == p->pLeft)
            return p;
         while ((p != nullptr) && (save == p->pRight))
         {
            save = p;
            p = p->pParent;
         }
         return p;
      }
      ptr decrement(ptr p)
      {
         if (p == nullptr)
            return p;
         if (p->pLeft != nullptr)
         {
            p = p->pLeft;
            while (p->pRight != nullptr)
               p = p->pRight;
            return p;
         }
         auto save = p;
         p = p->pParent;
         if (p == nullptr)
            return p;
         if (save == p->pRight)
            return p;
         while ((p != nullptr) && (save == p->pLeft))
         {
            save = p;
            p = p->pParent;
         }
         return p;
      }
   }; //class reverse_iterator_template

   typedef BST<T>::iterator_template<false> iterator;
   typedef BST<T>::iterator_template<true> const_iterator;
   typedef BST<T>::reverse_iterator_template<false> reverse_iterator;
   typedef BST<T>::reverse_iterator_template<true> const_reverse_iterator;

public:
   BST();
   BST(const BST& rhs);
   ~BST();
   BST& operator=(const BST& rhs);
   void clear();
   bool empty() const;
   void erase(iterator pos);
   void insert(const T& t);
   void printTree() const;
   int size() const;

   iterator begin() const;
   const_iterator cbegin() const;
   const_iterator cend() const;
   const_reverse_iterator crbegin() const;
   const_reverse_iterator crend() const;
   BNode* getRoot() { return root_; }
   iterator end() const;
   iterator find(const T& t) const;
   reverse_iterator rbegin() const;
   reverse_iterator rend() const;
private:
   int numElements_;
   BNode* root_;

   void copyBinaryTree(BNode* src, BNode*& dest);
   BNode* cloneNode(BNode* root, BNode* parent);
   void deleteBinaryTree(BNode*& del);
   BNode* getGrandparent(BNode* node) const;
   BNode* getParent(BNode* node) const ;
   BNode* getSibling(BNode* node) const;
   BNode* getUncle(BNode* node) const;
   BNode* findBranchMax(BNode* pos) const;
   BNode* findBranchMin(BNode* pos) const;
   void rebalanceForInsert(BNode* node);
   void rotateLeft(BNode* node);
   void rotateRight(BNode* node);


}; // BST class

/*************************************************************************
 Default constructor
 Input:
 Constructs a new empty BST
**************************************************************************/
template <typename T>
BST<T>::BST() :
   numElements_(0),
   root_(nullptr)
{
}

/*************************************************************************
 Copy constructor
 Input: const BST& rhs - BST to be copied from
 Constructs a new BST containing the same nodes as rhs
**************************************************************************/
template <typename T>
BST<T>::BST(const BST& rhs) :
   numElements_(0),
   root_(nullptr)
{
   copyBinaryTree(rhs.root_, root_);
}


/*************************************************************************
 Destructpr
 Frees all memory associated with the BST
**************************************************************************/
template <typename T>
BST<T>::~BST()
{
   clear();
}

/*************************************************************************
 Assignment operator
 Input: const BST& rhs - BST to assign lhs to
 Output: reference to BST
 Deep copies BST from rhs to lhs
**************************************************************************/
template <typename T>
BST<T>& BST<T>::operator=(const BST& rhs)
{
   clear();
   copyBinaryTree(rhs.root_, root_);
   return *this;
}

template <typename T>
typename BST<T>::iterator BST<T>::begin() const
{
   return BST<T>::iterator{findBranchMin(root_)};
}

template <typename T>
typename BST<T>::const_iterator BST<T>::cbegin() const
{
   return BST<T>::const_iterator{findBranchMin(root_)};
}

template <typename T>
typename BST<T>::const_iterator BST<T>::cend() const
{
   return BST<T>::const_iterator{};
}

/*************************************************************************
 clear()
 Input:
 Output:
 Empties BST and sets numElements_ to zero
**************************************************************************/
template <typename T>
void BST<T>::clear()
{
   deleteBinaryTree(root_);
   numElements_ = 0;
}

template <typename T>
typename BST<T>::const_reverse_iterator BST<T>::crbegin() const
{
   return BST<T>::const_reverse_iterator{findBranchMax(root_)};
}

template <typename T>
typename BST<T>::const_reverse_iterator BST<T>::crend() const
{
   return BST<T>::const_reverse_iterator{};
}

/*************************************************************************
 clonseNode()
 Input: BNode* src - node to be cloned
        BNode* parent - parent of node to be cloned
 Output: BNode*
 Creates a copy of a branch starting at src
**************************************************************************/
template <typename T>
typename BST<T>::BNode* BST<T>::cloneNode(BNode* src, BNode* parent)
{
   if (src == nullptr)
      return src;
   auto copyNode = new BNode(src->data);
   copyNode->pParent = parent;
   copyNode->pLeft = cloneNode(src->pLeft, copyNode);
   copyNode->pRight = cloneNode(src->pRight, copyNode);
   numElements_++;
   return copyNode;
}

/*************************************************************************
 copyBinaryTree()
 Input: BNode* src - root of tree to be copied from
        BNode*& dest - root of tree to copy to
 Output:
 Helper function to copy entire binary tree from src to dest
**************************************************************************/
template <typename T>
void BST<T>::copyBinaryTree(BNode* src, BNode*& dest)
{
   if (src == nullptr)
      return;
   auto par = (dest != nullptr) ? dest->pParent : nullptr;
   dest = cloneNode(src, par);
}

/*************************************************************************
 deleteBinaryTree()
 Input: BNode* del - root of tree to delete
 Output:
 Recursively deletes entire tree
**************************************************************************/
template <typename T>
void BST<T>::deleteBinaryTree(BNode*& del)
{
   if (del == nullptr)
      return;
   deleteBinaryTree(del->pLeft);
   deleteBinaryTree(del->pRight);
   delete del;
   del = nullptr;
}

template <typename T>
typename BST<T>::iterator BST<T>::end() const
{
   return BST<T>::iterator{};
}

/*************************************************************************
 empty()
 Input:
 Output: bool
 Returns true if BST is empty, false otherwise
**************************************************************************/
template <typename T>
bool BST<T>::empty() const
{
   return numElements_ == 0;
}

/*************************************************************************
 erase()
 Input: iterator pos - iterator to position of note to be removed
 Output:
 Deletes node at pos
**************************************************************************/
template <typename T>
void BST<T>::erase(iterator pos)
{
   auto node = pos._ptr();
   auto par = getParent(node);
   if (node == nullptr)
      return;
   if (node->pLeft == nullptr && node->pRight == nullptr)
   {
      if (node != root_)
      {
         if (par->pLeft == node)
            par->pLeft = nullptr;
         else
            par->pRight = nullptr;
      }
      delete node;
      node = nullptr;
   }
   else if (node->pLeft != nullptr && node->pRight != nullptr)
   {
      auto min = findBranchMin(node->pRight);
      auto value = min->data;
      erase(BST<T>::iterator{min});
      node->data = value;
   }
   else
   {
      auto child = (node->pLeft != nullptr) ? node->pLeft : node->pRight;
      if (node != root_)
      {
         if (node == par->pLeft)
            par->pLeft = child;
         else
            par->pRight = child;
         child->pParent = par;
      }
      else
         root_ = child;
      delete node;
      node = nullptr;
   }
   --numElements_;
}

/*************************************************************************
 find()
 Input: const T& t - key to searc hfor
 Output: iterator - position of key if found
 Returns an iterator to the position of key if found, end() if otherwise
**************************************************************************/
template <typename T>
typename BST<T>::iterator BST<T>::find(const T& t) const
{
   auto node = root_;
   while (node != nullptr)
   {
      if (t == node->data)
         return BST<T>::iterator{node};
      if (t < node->data)
         node = node->pLeft;
      else
         node = node->pRight;
   }
   return BST<T>::iterator(node);
}

/*************************************************************************
 findBranchMax()
 Input: BNode* pos - node in branch to find max
 Output:
 Finds furthest right node in current branch
**************************************************************************/
template <typename T>
typename BST<T>::BNode* BST<T>::findBranchMax(typename BST<T>::BNode* pos) const
{
   if (pos == nullptr)
      return nullptr;
   while (pos->pRight != nullptr)
      pos = pos->pRight;
   return pos;
}

/*************************************************************************
 findBranchMin()
 Input: BNode* pos - node in branch to find min
 Output:
 Finds furthest left node in current branch
**************************************************************************/
template <typename T>
typename BST<T>::BNode* BST<T>::findBranchMin(typename BST<T>::BNode* pos) const
{
   if (pos == nullptr)
      return nullptr;
   while (pos->pLeft != nullptr)
      pos = pos->pLeft;
   return pos;
}

/*************************************************************************
 getGrandparent()
 Input: BNode* node - node of which to find parent of parent
 Output: BNode*
 Returns parent of parent of node
**************************************************************************/
template <typename T>
typename BST<T>::BNode* BST<T>::getGrandparent(BNode* node) const
{
   return getParent(getParent(node));
}

/*************************************************************************
 getParent()
 Input: BNode* node - node of which to find parent
 Output: BNode*
 Returns parent of node
**************************************************************************/
template <typename T>
typename BST<T>::BNode* BST<T>::getParent(BNode* node) const
{
   return (node == nullptr) ? node : node->pParent;
}

/*************************************************************************
 getSinbling()
 Input: BNode* node - node of which to find sibling
 Output: BNode*
 Returns other child with same parent
**************************************************************************/
template <typename T>
typename BST<T>::BNode* BST<T>::getSibling(BNode* node) const
{
   auto par = getParent(node);
   if (par == nullptr)
      return nullptr;
   if (node == par->pLeft)
      return par->pRight;
   else
      return par->pLeft;
}

/*************************************************************************
 getUncle()
 Input: BNode* node - node of which to find uncle
 Output: BNode*
 Returns other child at same depth as parent of node
**************************************************************************/
template <typename T>
typename BST<T>::BNode* BST<T>::getUncle(BNode* node) const
{
   return getSibling(getParent(node));
}

/*************************************************************************
 insert()
 Input: const T& t - data inserted node will contain
 Output:
 Finds position and inserts node with value t
**************************************************************************/
template <typename T>
void BST<T>::insert(const T& t)
{
   auto parent = static_cast<BNode*>(nullptr);
   if (root_ == nullptr)
   {
      try
      {
         auto ins = new BNode{t};
         root_ = ins;
         rebalanceForInsert(ins);
      }
      catch (std::bad_alloc&)
      {
         throw "ERROR: Unable to allocate a node";
      }
   }
   else
   {
      auto node = root_;
      while (node != nullptr)
      {
         parent = node;
         if (t < node->data)
            node = node->pLeft;
         else
            node = node->pRight;
      }
      if (t < parent->data)
      {
         addLeft(parent, t);
         rebalanceForInsert(parent->pLeft);
      }
      else
      {
         addRight(parent, t);
         rebalanceForInsert(parent->pRight);
      }
   }
   ++numElements_;
}

template <typename T>
int BST<T>::size() const
{
   return numElements_;
}

template <typename T>
typename BST<T>::reverse_iterator BST<T>::rbegin() const
{
   return BST<T>::reverse_iterator{findBranchMax(root_)};
}

template <typename T>
void BST<T>::rebalanceForInsert(typename BST<T>::BNode* node)
{
   if (node == nullptr)
      return;
   if (getParent(node) == nullptr)
      node->isRed = false;
   else if (getParent(node)->isRed == false)
      return;
   else if (getUncle(node) != nullptr)
   {
      if ((getUncle(node)->isRed == true) &&
          (getGrandparent(node)->isRed == false))
      {
         getParent(node)->isRed = false;
         getUncle(node)->isRed = false;
         getGrandparent(node)->isRed = true;
         rebalanceForInsert(getGrandparent(node));
      }
   }
   else
   {
      auto par = getParent(node);
      auto gpar = getGrandparent(node);

      if ((node == par->pRight) && (par == gpar->pLeft))
      {
         rotateLeft(par);
         node = node->pLeft;
      }
      else if ((node == par->pLeft) && (par == gpar->pRight))
      {
         rotateRight(par);
         node = node->pRight;
      }

      par = getParent(node);
      gpar = getGrandparent(node);

      if (node == par->pLeft)
         rotateRight(gpar);
      else
         rotateLeft(gpar);
      par->isRed = false;
      gpar->isRed = true;
   }
   while (getParent(root_) != nullptr)
      root_ = getParent(root_);
}

template <typename T>
typename BST<T>::reverse_iterator BST<T>::rend() const
{
   return BST<T>::reverse_iterator{};
}

/*************************************************************************
 rotateLeft()
 Input: Node* node - node around which to rotate
 Output:
 Helper function to rotate nodes counterclockwise
**************************************************************************/
template <typename T>
void BST<T>::rotateLeft(BNode* node)
{
   auto newNode = node->pRight;
   auto par = getParent(node);

   if (newNode != nullptr)
   {
      node->pRight = newNode->pLeft;
      newNode->pLeft = node;
      node->pParent = newNode;
      if (node->pRight != nullptr)
         node->pRight->pParent = node;
   }

   if (par != nullptr)
   {
      if (node == par->pLeft)
         par->pLeft = newNode;
      else if (node == par->pRight)
         par->pRight = newNode;
   }
   newNode->pParent = par;
}

/*************************************************************************
 rotateRight()
 Input: Node* node - node around which to rotate
 Output:
 Helper function to rotate nodes clockwise
**************************************************************************/
template <typename T>
void BST<T>::rotateRight(BNode* node)
{
   auto newNode = node->pLeft;
   auto par = getParent(node);

   if (newNode != nullptr)
   {
      node->pLeft = newNode->pRight;
      newNode->pRight = node;
      node->pParent = newNode;
      if (node->pLeft != nullptr)
         node->pLeft->pParent = node;
   }

   if (par != nullptr)
   {
      if (node == par->pLeft)
         par->pLeft = newNode;
      else if (node == par->pRight)
         par->pRight = newNode;
   }
   newNode->pParent = par;
}

//BNode ctor
template <typename T>
BST<T>::BNode::BNode(const T& t) :
   data(t),
   isRed(true),
   pLeft(nullptr),
   pParent(nullptr),
   pRight(nullptr)
{
}

/*************************************************************************
 addLeft()
 Input: BNode* pos - position of parent of new node
        const T& t - value to be contained in new node
 Output:
 Inserts node as left child of pos
**************************************************************************/
template <typename T>
void addLeft(typename BST<T>::BNode* pos, const T& t)
{
   try
   {
      auto node = new typename custom::BST<T>::BNode{t};
      addLeft<T>(pos, node);
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/*************************************************************************
 addLeft()
 Input: BNode* pos - position of parent of new node
        BNode* node - node to be inserted
 Output:
 Inserts node as left child of pos
**************************************************************************/
template <typename T>
void addLeft(typename BST<T>::BNode* pos,
             typename BST<T>::BNode* node)
{
   if (node != nullptr)
      node->pParent = pos;
   if (pos != nullptr)
      pos->pLeft = node;
}

/*************************************************************************
 addRight()
 Input: BNode* pos - position of parent of new node
        const T& t - value to be contained in new node
 Output:
 Inserts node as right child of pos
**************************************************************************/
template <typename T>
void addRight(typename BST<T>::BNode* pos, const T& t)
{
   try
   {
      auto node = new typename BST<T>::BNode{t};
      addRight<T>(pos, node);
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/*************************************************************************
 addRight()
 Input: BNode* pos - position of parent of new node
        BNode* node - node to be inserted
 Output:
 Inserts node as left child of pos
**************************************************************************/
template <typename T>
void addRight(typename BST<T>::BNode* pos,
              typename BST<T>::BNode* node)
{
   if (node != nullptr)
      node->pParent = pos;
   if (pos != nullptr)
      pos->pRight = node;
}

} // namespace custom

#endif // BST_H
