#ifndef DEQUE_H_
#define DEQUE_H_

#include <iostream>
#include <functional>
#include <memory>

namespace custom {

namespace detail {
/*************************************************************************
 mormalize()
 Input: int - index to be normalized
 Output: int - index normalized to numCapacity
 Helper to return the index of deque as normalized to the circular array
**************************************************************************/
static int normalize(int index, int capacity)
{
   auto out = index % capacity;
   return index < 0 ? (out != 0 ? ((out) + capacity) : (out))
                  : (index % capacity);
}

template <class T>
std::unique_ptr<T[]> allocNew(int numCapacity)
{
   try
   {
      return std::make_unique<T[]>(numCapacity);
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: unable to allocate a new buffer for deque";
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
      for (auto i = head; i <= tail; ++i)
         temp[newindex++] = data[normalize(i, oldCapacity)];
      return newdata;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: Unable to allocate a new buffer for deque";
   }
}

} // namespace detail

template <class T>
class deque
{
public:
   deque(int numCapacity = 0);
   deque(const deque& rhs);
   deque& operator=(const deque& rhs);
   int size() const;
   void clear();
   bool empty() const;
   void push_front(const T& t);
   void push_back(const T& t);
   void pop_front();
   void pop_back();
   T& front();
   const T& front() const;
   T& back();
   const T& back() const;
   void for_each(std::function<void(const T& t)> func) const;
private:
   std::unique_ptr<T[]> arrayPtr_;
   int numCapacity_;
   int iBack_;
   int iFront_;

   int iBackNormalize() const;
   int capacity() { return numCapacity_; }
   int iFrontNormalize() const;
   int normalize(int index) const;
   void resize(int numCapacity_);
};

/*************************************************************************
 Default constructor
 Input: number of elements
 Constructs a new deque with capacity of numCapacity
**************************************************************************/
template <class T>
deque<T>::deque(int numCapacity) :
   numCapacity_(numCapacity),
   iFront_(0),
   iBack_(-1)
{
   arrayPtr_ = detail::allocNew<T>(numCapacity_);
}

/*************************************************************************
 Copy constructor
 Input: rhs - deque to be copied from
 Constructs a new deque containing the same elements as rhs
**************************************************************************/
template <class T>
deque<T>::deque(const deque& rhs) :
   numCapacity_(rhs.numCapacity_),
   iFront_(0),
   iBack_(-1)
{
   arrayPtr_.reset(detail::allocAndCopy(numCapacity_, rhs.numCapacity_,
                                        rhs.iFront_,
                                        rhs.iBack_,
                                        rhs.arrayPtr_.get()));
   iBack_ = rhs.size() - 1;
}

/*************************************************************************
 Assignment operator
 Input: rhs - deque to assign lhs to
 Output: reference to deque being assigned to
 Copies elements from rhs to lhs so containers are equal
**************************************************************************/
template <class T>
deque<T>& deque<T>::operator=(const deque& rhs)
{
   if (this != &rhs)
   {
      iFront_ = 0;
      iBack_ = -1;
      if (numCapacity_ <= rhs.size())
         resize(rhs.numCapacity_);
      for (auto i = rhs.iFront_; i <= rhs.iBack_; ++i)
         push_back(rhs.arrayPtr_[detail::normalize(i, rhs.numCapacity_)]);
   }
   return *this;
}


/*************************************************************************
 back()
 Input:
 Output: T& - reference to element at the back of the deque
 Returns element at the back of the deque
**************************************************************************/
template <class T>
T& deque<T>::back()
{
   if (empty())
      throw "ERROR: unable to access data from an empty deque";
   return arrayPtr_[iBackNormalize()];
}

/*************************************************************************
 back()
 Input:
 Output: const T& - const reference to element at the top of the deque
 Returns element at the back of the deque as a const
**************************************************************************/
template <class T>
const T& deque<T>::back() const
{
   if (empty())
      throw "ERROR: unable to access data from an  empty deque";
   return arrayPtr_[iBackNormalize()];
}

/*************************************************************************
 clear()
 Input:
 Output:
 Clears contents of entire deque
**************************************************************************/
template <class T>
void deque<T>::clear()
{
   for (auto i = iFront_; i <= iBack_; ++i)
      arrayPtr_[normalize(i)].~T();
   iFront_ = 0;
   iBack_ = -1;
}

/*************************************************************************
 empty()
 Input:
 Output: bool - true if empty
 Returns empty state of deque
**************************************************************************/
template <class T>
bool deque<T>::empty() const
{
   return ((iBack_ - iFront_ + 1) == 0);
}

/*************************************************************************
 for_each()
 Input: funcPtr - pointer to a function
 Output:
 Performs funcPtr on every element of the deque
 Function must be of the signature void func();
**************************************************************************/
template <class T>
void deque<T>::for_each(std::function<void(const T& t)> func) const
{
   for (auto i = iFront_; i <= iBack_; ++i)
      func(arrayPtr_[normalize(i)]);
}

/*************************************************************************
 front()
 Input:
 Output: T& - reference to element at the front of the deque
 Returns element at the front of the deque
**************************************************************************/
template <class T>
T& deque<T>::front()
{
   if (empty())
      throw "ERROR: unable to access data from an empty deque";
   return arrayPtr_[iFrontNormalize()];
}

/*************************************************************************
 front()
 Input:
 Output: const T& - reference to element at the front of the deque
 Returns element at the front of the deque as a const
**************************************************************************/
template <class T>
const T& deque<T>::front() const
{
   if (empty())
      throw "ERROR: unable to access data from an empty deque";
   return arrayPtr_[iFrontNormalize()];
}

/*************************************************************************
 iBackNormalize()
 Input:
 Output: int - iBack normalized to numCapacity
 Returns the index of back of deque as normalized to the circular array
**************************************************************************/
template <class T>
int deque<T>::iBackNormalize() const
{
   return numCapacity_ > 0 ? (detail::normalize(iBack_, numCapacity_)) : -1;
}

/*************************************************************************
 iFrontNormalize()
 Input:
 Output: int - iFront normalized to numCapacity
 Returns the index of front of deque as normalized to the circular array
**************************************************************************/
template <class T>
int deque<T>::iFrontNormalize() const
{
   return numCapacity_ > 0 ? (detail::normalize(iFront_, numCapacity_)) : 0;
}

/*************************************************************************
 mormalize()
 Input: int - index to be normalized
 Output: int - index normalized to numCapacity
 Helper to return the index of deque as normalized to the circular array
**************************************************************************/
template <class T>
int deque<T>::normalize(int index) const
{
   return (detail::normalize(index, numCapacity_));
}

/*************************************************************************
 pop_back()
 Input:
 Output:
 Removes the front of the deque
**************************************************************************/
template <class T>
void deque<T>::pop_back()
{
   if (!empty())
      iBack_--;
}

/*************************************************************************
 pop_front()
 Input:
 Output:
 Removes the front of the deque
**************************************************************************/
template <class T>
void deque<T>::pop_front()
{
   if (!empty())
      iFront_++;
}

/*************************************************************************
 push()
 Input: t - datum to be pushed onto deque
 Output:
 Places t on top of the deque
**************************************************************************/
template <class T>
void deque<T>::push_back(const T& t)
{
   if (numCapacity_ == 0)
      *this = deque<T>{2};
   else if (size() >= numCapacity_)
      resize(numCapacity_ * 2);
   ++iBack_;
   arrayPtr_[iBackNormalize()] = t;
}

/*************************************************************************
 push()
 Input: t - datum to be pushed onto deque
 Output:
 Places t on top of the deque
**************************************************************************/
template <class T>
void deque<T>::push_front(const T& t)
{
   if (numCapacity_ == 0)
      *this = deque<T>{2};
   else if (size() >= numCapacity_)
      resize(numCapacity_ * 2);
   --iFront_;
   arrayPtr_[iFrontNormalize()] = t;
}

/*************************************************************************
 resize()
 Input: numCapacity - new capacity to resize to
 Output: const T& - const reference to element at the top  of the stack
 Resizes stack to numCapacity and truncates any elements beyond capacity
**************************************************************************/
template <class T>
void deque<T>::resize(int numCapacity)
{
   const auto tempCapacity = numCapacity;
   arrayPtr_.reset(detail::allocAndCopy(tempCapacity, numCapacity_,
                                        iFront_,
                                        iBack_, arrayPtr_.get()));
   numCapacity_ = tempCapacity;
   if (size() > numCapacity_)
      iBack_ = numCapacity_ - 1;
   else
      iBack_ = size() - 1;
   iFront_ = 0;
}

/*************************************************************************
 size()
 Input:
 Output: int - size of deque
 Returns the number of elements in the deque
**************************************************************************/
template <class T>
int deque<T>::size() const
{
   return (iBack_ - iFront_ + 1);
}

} // namespace custom

#endif // DEQUE_H_
