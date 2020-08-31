#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <functional>
#include <memory>

namespace custom {

namespace detail {
template <class T>
std::unique_ptr<T[]> allocNew(int numCapacity)
{
   try
   {
      return std::make_unique<T[]>(numCapacity);
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: unable to allocate a new buffer for queue";
   }
}

template <class T>
T* allocAndCopy(int newCapacity, int oldCapacity,
                int head, int tail, const T* data)
{
   try
   {
      auto newdata = new T[newCapacity];
      auto temp = newdata;
      auto newindex = 0;
      for (auto i = head; i < tail; ++i)
         temp[newindex++] = data[i % oldCapacity];
      return newdata;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: Unable to allocate a new buffer for queue";
   }
}

} // namespace detail

template <class T>
class queue
{
public:
   queue(int numCapacity = 0);
   queue(const queue& rhs);
   queue& operator=(const queue& rhs);
   int size() const;
   void clear();
   bool empty() const;
   void push(const T& t);
   void pop();
   T& front();
   const T& front() const;
   T& back();
   const T& back() const;
   void for_each(std::function<void(const T& t)> func) const;
private:
   std::unique_ptr<T[]> arrayPtr_;
   int numCapacity_;
   int numPop_;
   int numPush_;

   void resize(int numCapacity_);
   int iHead() const;
   int iTail() const;
};

/*************************************************************************
 Default constructor
 Input: number of elements
 Constructs a new queue with capacity of numCapacity
**************************************************************************/
template <class T>
queue<T>::queue(int numCapacity) :
   numCapacity_(numCapacity),
   numPop_(0),
   numPush_(0)
{
   arrayPtr_ = detail::allocNew<T>(numCapacity_);
}

/*************************************************************************
 Copy constructor
 Input: rhs - queue to be copied from
 Constructs a new queue containing the same elements as rhs
**************************************************************************/
template <class T>
queue<T>::queue(const queue& rhs) :
   numCapacity_(rhs.numCapacity_),
   numPop_(0),
   numPush_(0)
{
//   if (rhs.empty())
//      numCapacity_ = rhs.numCapacity_;
   arrayPtr_ = detail::allocNew<T>(numCapacity_);
   for (auto i = rhs.numPop_; i < rhs.numPush_; ++i)
      push(rhs.arrayPtr_[i % rhs.numCapacity_]);
}

/*************************************************************************
 Assignment operator
 Input: rhs - queue to assign lhs to
 Output: reference to queue being assigned to
 Copies elements from rhs to lhs so containers are equal
**************************************************************************/
template <class T>
queue<T>& queue<T>::operator=(const queue& rhs)
{
   if (this != &rhs)
   {
      numPop_ = 0;
      numPush_ = 0;
      if (numCapacity_ <= rhs.size())
         resize(rhs.numCapacity_);
      for (auto i = rhs.numPop_; i < rhs.numPush_; ++i)
         push(rhs.arrayPtr_[i % rhs.numCapacity_]);
   }
   return *this;
}


/*************************************************************************
 back()
 Input:
 Output: T& - reference to element at the back of the queue
 Returns element at the back of the queue
**************************************************************************/
template <class T>
T& queue<T>::back()
{
   if (empty())
      throw "ERROR: attempting to access an element in an empty queue";
   return arrayPtr_[iTail()];
}

/*************************************************************************
 back()
 Input:
 Output: const T& - const reference to element at the top of the queue
 Returns element at the back of the queue as a const
**************************************************************************/
template <class T>
const T& queue<T>::back() const
{
   if (empty())
      throw "ERROR: attempting to access an element in an empty queue";
   return arrayPtr_[iTail()];
}

/*************************************************************************
 clear()
 Input:
 Output:
 Clears contents of entire queue
**************************************************************************/
template <class T>
void queue<T>::clear()
{
   for (auto i = numPop_; i < numPush_; ++i)
      arrayPtr_[i % numCapacity_].~T();
   numPop_ = 0;
   numPush_ = 0;
}

/*************************************************************************
 empty()
 Input:
 Output: bool - true if empty
 Returns empty state of queue
**************************************************************************/
template <class T>
bool queue<T>::empty() const
{
   return numPush_ == numPop_;
}

/*************************************************************************
 for_each()
 Input: funcPtr - pointer to a function
 Output:
 Performs funcPtr on every element of the queue
 Function must be of the signature void func();
**************************************************************************/
template <class T>
void queue<T>::for_each(std::function<void(const T& t)> func) const
{
   for (auto i = numPop_; i < numPush_; ++i)
      func(arrayPtr_[i % numCapacity_]);
}

/*************************************************************************
 front()
 Input:
 Output: T& - reference to element at the front of the queue
 Returns element at the front of the queue
**************************************************************************/
template <class T>
T& queue<T>::front()
{
   if (empty())
      throw "ERROR: attempting to access an element in an empty queue";
   return arrayPtr_[iHead()];
}

/*************************************************************************
 front()
 Input:
 Output: const T& - reference to element at the front of the queue
 Returns element at the front of the queue as a const
**************************************************************************/
template <class T>
const T& queue<T>::front() const
{
   if (empty())
      throw "ERROR: attempting to access an element in an empty queue";
   return arrayPtr_[iHead()];
}


/*************************************************************************
 iHead()
 Input:
 Output: int - numPop normalized to numCapacity
 Returns the index of front of queue as normalized to the circular array
**************************************************************************/
template <class T>
int queue<T>::iHead() const
{
   return (numPop_ % numCapacity_);
}

/*************************************************************************
 iTail()
 Input:
 Output: int - numPush normalized to numCapacity
 Returns the index of back of queue as normalized to the circular array
**************************************************************************/
template <class T>
int queue<T>::iTail() const
{
   return ((numPush_ - 1) % numCapacity_);
}

/*************************************************************************
 pop()
 Input:
 Output:
 Removes the front of the queue
**************************************************************************/
template <class T>
void queue<T>::pop()
{
   if (!empty())
      numPop_++;
}

/*************************************************************************
 push()
 Input: t - datum to be pushed onto queue
 Output:
 Places t on top of the queue
**************************************************************************/
template <class T>
void queue<T>::push(const T& t)
{
   if (numCapacity_ == 0)
      *this = queue<T>(2);
   else if (size() >= numCapacity_)
      resize(numCapacity_ * 2);
   ++numPush_;
   arrayPtr_[iTail()] = t;
}

/*************************************************************************
 resize()
 Input: numCapacity - new capacity to resize to
 Output: const T& - const reference to element at the top  of the stack
 Resizes stack to numCapacity and truncates any elements beyond capacity
**************************************************************************/
template <class T>
void queue<T>::resize(int numCapacity)
{
   const auto tempCapacity = numCapacity;
   arrayPtr_.reset(detail::allocAndCopy(tempCapacity, numCapacity_,
                                        numPop_, numPush_, arrayPtr_.get()));
   numCapacity_ = tempCapacity;
   if (size() > numCapacity_)
      numPush_ = numCapacity_;
   else
      numPush_ = size();
   numPop_ = 0;
}

/*************************************************************************
 size()
 Input:
 Output: int - size of queue
 Returns the number of elements in the queue
**************************************************************************/
template <class T>
int queue<T>::size() const
{
   return numPush_ - numPop_;
}

} // namespace custom

#endif // QUEUE_H_
