#ifndef LIST_H_
#define LIST_H_

#include <functional>
#include <memory>
#include <new>
#include <type_traits>


namespace custom {
template <typename T>
class list;

namespace detail {


} // namespace detail

template <typename T>
class list
{
public:
   /***********************************************
    * NODE STRUCT
    * Node in a list
    **********************************************/
   struct Node
   {
      Node(const T& t = T{});
      T data_;
      Node* pNext_;
      Node* pPrev_;
   };
   /***********************************************
    * LIST ITERATOR CLASS
    * Templatized iterator for a list
    **********************************************/
   template <bool isConst = false>
   class iterator_template
   {
   public:
      iterator_template() : p_(nullptr) {}
      using ref = typename std::conditional<isConst, const Node&,
                                            Node&>::type;
      using ptr = typename std::conditional<isConst, const Node*,
                                            Node*>::type;
      using value_ref = typename std::conditional<isConst, const T&, T&>::type;
      using value_ptr = typename std::conditional<isConst, const T*, T*>::type;
      explicit iterator_template(ptr p) : p_(p) {}
      iterator_template(const iterator_template& rhs)
      {
         *this = rhs;
      }
      iterator_template& operator=(const iterator_template& rhs)
      {
         if (this != &rhs)
            this->p_ = rhs.p_;
         return *this;
      }
      bool operator==(const iterator_template& rhs) const
      {
         return this->p_ == rhs.p_;
      }
      bool operator!=(const iterator_template& rhs) const
      {
         return !(*this == rhs);
      }
      iterator_template& operator++()
      {
         p_ = p_->pNext_;
         return *this;
      }
      iterator_template operator++(int)
      {
         iterator_template temp(*this);
         p_ = p_->pNext_;
         return temp;
      }
      iterator_template& operator--()
      {
         p_ = p_->pPrev_;
         return *this;
      }
      iterator_template operator--(int)
      {
         iterator_template temp(*this);
         p_ = p_->pPrev_;
         return temp;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<!isConst_, value_ref>::type
      operator*()
      {
         return p_->data_;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<isConst_, value_ref>::type
      operator*() const
      {
         return p_->data_;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<!isConst_, value_ptr>::type
      operator->()
      {
         return &p_->data_;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<isConst_, value_ptr>::type
      operator->() const
      {
         return &p_->data_;
      }
      ptr& _ptr()
      {
         return p_;
      }
   private:
      ptr p_;
   }; //class iterator_template

     /***********************************************
    * LIST REVERSE_ITERATOR CLASS
    * Templatized reverse iterator for a list
    **********************************************/
   template <bool isConst = false>
   class reverse_iterator_template
   {
   public:
      reverse_iterator_template() : p_(nullptr) {}
      using ref = typename std::conditional<isConst, const Node&,
                                            Node&>::type;
      using ptr = typename std::conditional<isConst, const Node*,
                                            Node*>::type;
      using value_ref = typename std::conditional<isConst, const T&, T&>::type;
      using value_ptr = typename std::conditional<isConst, const T*, T*>::type;
      explicit reverse_iterator_template(ptr p) : p_(p) {}
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
         p_ = p_->pPrev_;
         return *this;
      }
      reverse_iterator_template operator++(int)
      {
         reverse_iterator_template temp(*this);
         p_ = p_->pPrev_;
         return temp;
      }
      reverse_iterator_template& operator--()
      {
         p_ = p_->pNext_;
         return *this;
      }
      reverse_iterator_template operator--(int)
      {
         reverse_iterator_template temp(*this);
         p_ = p_->pNext_;
         return temp;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<!isConst_, value_ref>::type
      operator*()
      {
         return p_->data_;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<isConst_, value_ref>::type
      operator*() const
      {
         return p_->data_;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<!isConst_, value_ptr>::type
      operator->()
      {
         return &p_->data_;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<isConst_, value_ptr>::type
      operator->() const
      {
         return &p_->data_;
      }
      ptr& _ptr()
      {
         return p_;
      }
   private:
      ptr p_;
   }; //class reverse_iterator_template


   typedef list<T>::iterator_template<false> iterator;
   typedef list<T>::iterator_template<true> const_iterator;
   typedef list<T>::reverse_iterator_template<false> reverse_iterator;
   typedef list<T>::reverse_iterator_template<true> const_reverse_iterator;

public:
   list();
   list(const list& rhs);
   ~list();
   list& operator=(const list& rhs);
   T& back() const;
   list<T>::iterator begin() const;
   list<T>::const_iterator cbegin() const;
   list<T>::const_iterator cend() const;
   void clear();
   list<T>::const_reverse_iterator crbegin() const;
   list<T>::const_reverse_iterator crend() const;
   void destroy(Node*& node);
   bool empty() const;
   list<T>::iterator end() const;
   void erase(list<T>::iterator pos);
   void erase(list<T>::reverse_iterator pos);
   void erase(list<T>::const_iterator pos);
   void erase(list<T>::const_reverse_iterator pos);
   list<T>::iterator find(const T& t) const;
   T& front() const;
   void hook(Node* pos, Node* node);
   void insert(list<T>::iterator pos, const T& t);
   void insert(list<T>::reverse_iterator pos, const T& t);
   void insert(list<T>::const_iterator pos, const T& t);
   void insert(list<T>::const_reverse_iterator pos, const T& t);
   int size() const;
   void pop_back();
   void pop_front();
   void push_back(const T& t);
   void push_front(const T& t);
   list<T>::reverse_iterator rbegin() const;
   list<T>::reverse_iterator rend() const;
   list<T>::Node*& unhook(Node*& pos);
private:
   int numElements_;
   Node* pHead_;
   Node* pTail_;
};

/*************************************************************************
 list Default Constructor
 Input:
 Output:
 Constructs a list of size 0 with a dummy node serving as a sentinel
**************************************************************************/
template <typename T>
list<T>::list() :
   numElements_(0),
   pHead_(nullptr),
   pTail_(nullptr)
{
   try
   {
      auto sentinel = new Node{};

      sentinel->pNext_ = sentinel;
      sentinel->pPrev_ = sentinel;
      pHead_ = sentinel;
      pTail_ = sentinel;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/*************************************************************************
 list Copy Constructor
 Input: const list& rhs - list to copy from
 Output:
 Copies the contents of rhs to the newly constructed list
**************************************************************************/
template <typename T>
list<T>::list(const list& rhs) :
   numElements_(0),
   pHead_(nullptr),
   pTail_(nullptr)
{
   try
   {
      auto sentinel = new Node{};

      sentinel->pNext_ = sentinel;
      sentinel->pPrev_ = sentinel;
      pHead_ = sentinel;
      pTail_ = sentinel;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   for (auto it = rhs.begin(); it != rhs.end(); ++it)
      push_back(*it);
}

/*************************************************************************
 list Destructor
 Input:
 Output:
 Clears contents of entire set leaving capacity unchanged
**************************************************************************/
template <typename T>
list<T>::~list()
{
   clear();
   pTail_ = nullptr;
   delete pHead_;
}

/*************************************************************************
 list assignment operator
 Input:
 Output:
 Clears contents of entire set leaving capacity unchanged
**************************************************************************/
template <typename T>
list<T>& list<T>::operator=(const list& rhs)
{
   if (this != &rhs)
   {

      auto lhs_first = begin();
      auto lhs_last = end();
      auto rhs_first = rhs.begin();
      auto rhs_last = rhs.end();
      for ( ;lhs_first != lhs_last && rhs_first != rhs_last;
           ++lhs_first, ++rhs_first)
      {
         lhs_first._ptr()->data_ = *rhs_first;
      }
      if (rhs_first == rhs_last)
      {
         while (numElements_ > rhs.numElements_)
            pop_back();
      }
      else
      {
         while (rhs_first != rhs_last)
            push_back(*rhs_first++);
      }

      /*
      clear();
      auto rhs_end = rhs.end();
      for (auto it = rhs.begin(); it != rhs_end; ++it)
      {
         push_back(*it);
      }
      */
   }
   return *this;
}

/*************************************************************************
 back()
 Input:
 Output:
 Returns value contained in the last node
**************************************************************************/
template <typename T>
T& list<T>::back() const
{
   if (numElements_ == 0)
      throw "ERROR: Unable to access data from an empty list";
   return pTail_->pPrev_->data_;
}

/*************************************************************************
 begin()
 Input:
 Output: list<T>::iterator - iterator to first node
 Returns iterator to the first node of the list
**************************************************************************/
template <typename T>
typename list<T>::iterator list<T>::begin() const
{
   return list<T>::iterator{pHead_->pNext_};
}

/*************************************************************************
 cbegin()
 Input:
 Output: list<T>::const_iterator - const iterator to first node
 Returns a const_iterator to the first node of the list
**************************************************************************/
template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const
{
   return list<T>::const_iterator{pHead_->pNext_};
}

/*************************************************************************
 cend()
 Input:
 Output: list<T>::const_iterator - const iterator to last node
 Returns an iterator to the last node of the list
**************************************************************************/
template <typename T>
typename list<T>::const_iterator list<T>::cend() const
{
   return list<T>::const_iterator{pTail_};
}

/*************************************************************************
 clear()
 Input:
 Output:
 Clears contents of entire list leaving only the sentinel
**************************************************************************/
template <typename T>
void list<T>::clear()
{
   while (numElements_ > 0)
      pop_back();
}

/*************************************************************************
 crbegin()
 Input:
 Output: list<T>::cost_reverse_iterator - const reverse iterator to last node
 Returns a const_reverse iterator to the last node in the list
**************************************************************************/
template <typename T>
typename list<T>::const_reverse_iterator list<T>::crbegin() const
{
   return list<T>::const_reverse_iterator{pTail_->pPrev_};
}

/*************************************************************************
 crend()
 Input:
 Output: list<T>::cost_reverse_iterator - const reverse iterator to irst node
 Returns a const_reverse iterator to the first node in the list
**************************************************************************/
template <typename T>
typename list<T>::const_reverse_iterator list<T>::crend() const
{
   return list<T>::const_reverse_iterator{pHead_};
}

/*************************************************************************
 destroy()
 Input: Node*& noed - node to delete
 Output:
 Deletes node passed in and sets it to nullptr
**************************************************************************/
template <typename T>
void list<T>::destroy(Node*& node)
{
   if (node != nullptr)
      delete node;
   node = nullptr;
}

/*************************************************************************
 empty()
 Input:
 Output: bool - True if empty, False otherwise
 Returns true if the list is empty (only sentinel node remains)
**************************************************************************/
template <typename T>
bool list<T>::empty() const
{
   return (numElements_ == 0);
}

/*************************************************************************
 end()
 Input:
 Output: list<T>::iterator - an iterator to the last node in the list
 Returns an iterator to the last node in the list
**************************************************************************/
template <typename T>
typename list<T>::iterator list<T>::end() const
{
   return list<T>::iterator{pTail_};
}

/*************************************************************************
 erase()
 Input: list<T>::iterator pos - position to remove node from
 Output:
 Removes node at pos
**************************************************************************/
template <typename T>
void list<T>::erase(list<T>::iterator pos)
{
   destroy(unhook(pos._ptr()));
   --numElements_;
}

template <typename T>
void list<T>::erase(list<T>::reverse_iterator pos)
{
   destroy(unhook(pos._ptr()));
   --numElements_;
}
/*************************************************************************
 erase()
 Input: list<T>::const_iterator pos - position to remove node from
 Output:
 Removes node at pos
**************************************************************************/
template <typename T>
void list<T>::erase(list<T>::const_iterator pos)
{
   destroy(unhook(const_cast<list<T>::Node*>(pos._ptr())));
   --numElements_;
}

template <typename T>
void list<T>::erase(list<T>::const_reverse_iterator pos)
{
   destroy(unhook(const_cast<list<T>::Node*>(pos._ptr())));
   --numElements_;
}
/*************************************************************************
 find()
 Input: const T& t - data to be found
 Output: iterator - iterator to node containing data if it exists, otherwise end
 Finds first node equal to data, otherwise returns end of list
**************************************************************************/
template <typename T>
typename list<T>::iterator list<T>::find(const T& t) const
{
   for (auto it = begin(); it != end(); ++it)
   {
      if (it->data == t)
         return it;
   }
   return end();
}

/*************************************************************************
 front()
 Input:
 Output:
 Returns data from node at the beginning of the list
**************************************************************************/
template <typename T>
T& list<T>::front() const
{
   if (numElements_ == 0)
      throw "ERROR: Unable to access data from an empty list";
   return pHead_->pNext_->data_;
}

/*************************************************************************
 hook()
 Input: Node* pos - position to hook node into
        Node* node - pointer to not to be hooked in
 Output:
 Hooks node in at pos by modifying pointers of next and previous nodes to
 point to node
**************************************************************************/
template <typename T>
void list<T>::hook(Node* pos, Node* node)
{
   if (pos != nullptr && node != nullptr)
   {
      node->pPrev_ = pos->pPrev_;
      node->pNext_ = pos;
      pos->pPrev_->pNext_ = node;
      pos->pPrev_ = node;
   }
}

/*************************************************************************
 insert()
 Input: iterator pos - position before which to insert new node
        const T& t         - data to initialize node with
 Output:
 Inserts a node before pos with specified data
**************************************************************************/
template <typename T>
void list<T>::insert(list<T>::iterator pos, const T& t)
{
   try
   {
      auto node = new Node(t);
      hook(pos._ptr(), node);
      ++numElements_;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

template <typename T>
   void list<T>::insert(list<T>::reverse_iterator pos, const T& t)
{
   try
   {
      auto node = new Node(t);
      hook(pos._ptr(), node);
      ++numElements_;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/*************************************************************************
 insert()
 Input: const_iterator pos - position before which to insert new node
        const T& t         - data to initialize node with
 Output:
 Inserts a node before pos with specified data
**************************************************************************/
template <typename T>
void list<T>::insert(list<T>::const_iterator pos, const T& t)
{
   try
   {
      auto node = new Node(t);
      hook(const_cast<list<T>::Node*>(pos._ptr()), node);
      ++numElements_;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

template <typename T>
   void list<T>::insert(list<T>::const_reverse_iterator pos, const T& t)
{
   try
   {
      auto node = new Node(t);
      hook(const_cast<list<T>::Node*>(pos._ptr()), node);
      ++numElements_;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/*************************************************************************
 size()
 Input:
 Output:
 Returns the number of nodes in the list
**************************************************************************/
template <typename T>
int list<T>::size() const
{
   return numElements_;
}

/*************************************************************************
 pop_back()
 Input:
 Output:
 Removes node at the end of the list
**************************************************************************/
template <typename T>
void list<T>::pop_back()
{
   if (numElements_ > 0)
   {
      destroy(unhook(rbegin()._ptr()));
      --numElements_;
   }
}

/*************************************************************************
 pop_front()
 Input:
 Output:
 Removes node at the beginning of the list
**************************************************************************/
template <typename T>
void list<T>::pop_front()
{
   if (numElements_ > 0)
   {
      destroy(unhook(begin()._ptr()));
      --numElements_;
   }
}

/*************************************************************************
 push_back()
 Input: const T& t - data to populate node with
 Output:
 Adds a new node to the end of list
**************************************************************************/
template <typename T>
void list<T>::push_back(const T& t)
{
   try
   {
      auto node = new Node(t);
      hook(end()._ptr(), node);
      ++numElements_;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/*************************************************************************
 push_front()
 Input: const T& t - data to populate node with
 Output:
 Adds a new node to the front of the list
**************************************************************************/
template <typename T>
void list<T>::push_front(const T& t)
{
   try
   {
      auto node = new Node(t);
      hook(begin()._ptr(), node);
      ++numElements_;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/*************************************************************************
 rbegin()
 Input:
 Output: list<T>::reverse_iterator - iterator to the first node in the list
 Returns a reverse iterator to the end of the list
**************************************************************************/
template <typename T>
typename list<T>::reverse_iterator list<T>::rbegin() const
{
   return list<T>::reverse_iterator{pTail_->pPrev_};
}

/*************************************************************************
 rend()
 Input:
 Output: list<T>::reverse_iterator - iterator to the last node in the list
 Returns a reverse iterator to the beginning of the list
**************************************************************************/
template <typename T>
typename list<T>::reverse_iterator list<T>::rend() const
{
   return list<T>::reverse_iterator{pHead_};
}

/*************************************************************************
 unhook()
 Input: Node* pos - node to unhook from the list
 Output: list<T>::Node*&
 Unhooks node at pos and returns a reference to pos to allow for deletion
**************************************************************************/
template <typename T>
typename list<T>::Node*& list<T>::unhook(Node*& pos)
{
   if (pos != nullptr)
   {
      pos->pNext_->pPrev_ = pos->pPrev_;
      pos->pPrev_->pNext_ = pos->pNext_;
   }
   return pos;
}

/*************************************************************************
 Node Default Constructor
 Input: (optional) const T& t - value to initialize Node with
 Output:
 Constructs a Node with T(t) if supplied, otherwise defaults to T{}
**************************************************************************/
template <typename T>
list<T>::Node::Node(const T& t) :
   data_(t),
   pNext_(nullptr),
   pPrev_(nullptr)
{
}

/*************************************************************************
 Node Insertion Operator
 Input:
 Output: std::ostream& - stream object to be printed
 Prints data contained in Node
**************************************************************************/
template <typename T>
std::ostream& operator<<(std::ostream& out, const typename list<T>::Node& node)
{
   out << node.data_;

   return out;
}


} // namespace custom

#endif // LIST_H_
