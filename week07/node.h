#ifndef NODE_H_
#define NODE_H_

template <typename T>
struct Node
{
   Node(const T& t = T{});
   T data_;
   Node<T>* pNext_;
   Node<T>* pPrev_;
};

/*************************************************************************
 Constructor
 Input: (optional) const T& t - value to initialize Node with
 Output:
 Constructs a Node with T(t) if supplied, otherwise defaults to T{}
**************************************************************************/
template <typename T>
Node<T>::Node(const T& t) :
   data_(t),
   pNext_(nullptr),
   pPrev_(nullptr)
{
}

#endif // NODE_H_
