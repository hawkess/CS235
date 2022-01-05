#ifndef NODE_H_
#define NODE_H_

template <typename T>
class Node
{
public:
   Node(const T& t = T{});
   T data;
   Node<T>* pNext;
   Node<T>* pPrev;
};

/*************************************************************************
 Constructor
 Input: (optional) const T& t - value to initialize Node with
 Output:
 Constructs a Node with T(t) if supplied, otherwise defaults to T{}
**************************************************************************/
template <typename T>
Node<T>::Node(const T& t) :
   data(t),
   pNext(nullptr),
   pPrev(nullptr)
{
}

/*************************************************************************
 operator<<
 Input: std::ostream& out - output stream, const Node<T>* - pointer to node
 Output: std::ostream& - stream to output to
 Converts Node data to a printable stream
**************************************************************************/
template <typename T>
std::ostream& operator<<(std::ostream& out, Node<T>* node)
{
   if (node != nullptr)
   {
      out << node->data;
      while (node->pNext != nullptr)
      {
         out << ", " << node->pNext->data;
         node = node->pNext;
      }
   }
   return out;
}

/*************************************************************************
 copy()
 Input: const Node<T>* - pointer to position to copy from
 Output: Node<T>* - poiner to head of new list
 Copies list starting from source node
**************************************************************************/
template <typename T>
Node<T>* copy(Node<T>* source)
{
   if (source == nullptr)
      return source;
   auto head = new Node<T>(source->data);
   auto current = head;
   while (source->pNext != nullptr)
   {
      source = source->pNext;
      current = insert(current, source->data, true);
   }
   return head;
}

/*************************************************************************
 find()
 Input: const T& - value to find in list
 Output: Node<T>* - pointer to found value (nullptr if not found)
 Finds a given value and returns a pointer to the node containing it or null
 if one does not exist
**************************************************************************/
template <typename T>
Node<T>* find(Node<T>* head, const T& value)
{
   while (head != nullptr)
   {
      if (head->data == value)
         return head;
      head = head->pNext;
   }
   return nullptr;
}

/*************************************************************************
 freeData()
 Input: const Node<T>* - pointer to head of list
 Output:
 Frees all memory in list with head at passed in pointer
**************************************************************************/
template <typename T>
void freeData(Node<T>*& head)
{
   if (head == nullptr)
      return;
   freeData(head->pNext);
   delete head;
   head = nullptr;
}

/*************************************************************************
 insert()
 Input: const Node<T>* - pointer to insertion node, const T& value - data to insert
 bool - true if pre-insertion, false if post-insertion
 Output: Node<T>* - pointer to inserted node
 Inserts node before or after position depending on third parameter
**************************************************************************/
template <typename T>
Node<T>* insert(Node<T>* const pos, const T& value, bool after=false)
{
   auto node = new Node<T>(value);
   if (pos != nullptr)
   {
      if (after == true)
      {
         if (pos->pNext != nullptr)
            pos->pNext->pPrev = node;
         node->pNext = pos->pNext;
         node->pPrev = pos;
         pos->pNext = node;
      }
      else
      {
         if (pos->pPrev)
            pos->pPrev->pNext = node;
         node->pPrev = pos->pPrev;
         node->pNext = pos;
         pos->pPrev = node;
      }
   }
   return node;
}

/*************************************************************************
 remove()
 Input: const Node<T>* - pointer to node to be removed
 Output: Node<T>* - pointer to node previous (or null)
 Removes node at pos and returns previous node or next if none exists
**************************************************************************/
template <typename T>
Node<T>* remove(Node<T>* pos)
{
   if (pos == nullptr)
      return nullptr;
   if (pos->pPrev != nullptr)
      pos->pPrev->pNext = pos->pNext;
   if (pos->pNext != nullptr)
      pos->pNext->pPrev = pos->pPrev;
   auto newPos = ((pos->pPrev != nullptr) ? pos->pPrev : pos->pNext);
   delete pos;
   return newPos;
}

#endif // NODE_H_
