#ifndef STACK_H_
#define STACK_H_

#include <iostream>
#include <memory>
#include <new>

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
      throw "ERROR: unable to allocate a new buffer for Stack.";
   }
}

template <class T>
T* allocAndCopy(int capacity, int size, const T* data)
{
   try
   {
      auto newdata = new T[capacity];
      auto temp = newdata;
      for (auto i = 0; i < size; ++i)
//         *(temp++) = *(data++);
         temp[i] = data[i];
      return newdata;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: Unable to allocate a new buffer for Stack";
   }
}

} // namespace detail

template<class T>
class stack
{
public:
   stack(int numCapacity = 0);
   stack(const stack& rhs);
   //~stack();
   stack& operator=(const stack& rhs);
   int size() const
   {
      return numElements_;
   }
   int capacity() const
   {
      return numCapacity_;
   }
   bool empty() const
   {
      return numElements_ == 0;
   }
   void clear();
   void push(const T& t);
   void pop();
   T& top();
   const T& top() const;


private:
   std::unique_ptr<T[]> arrayPtr_;
   int numCapacity_;
   int numElements_;

   void resize(int numCapacity);
}; //stack class


/*************************************************************************
 Default constructor
 Input: number of elements
 Constructs a new stack with [numElements] elements
**************************************************************************/
template <class T>
stack<T>::stack(int numCapacity) :
   numCapacity_(numCapacity),
   numElements_(0)
{
   arrayPtr_ = detail::allocNew<T>(numCapacity_);
}

/*************************************************************************
 Copy constructor
 Input: rhs - stack to be copied from
 Constructs a new stack containing the same elements as rhs
**************************************************************************/
template <class T>
stack<T>::stack(const stack& rhs)
{
   numElements_ = rhs.size();
   numCapacity_ = numElements_;
   arrayPtr_ = detail::allocNew<T>(numCapacity_);
   for (auto i = 0; i < numElements_; ++i)
      arrayPtr_[i] = rhs.arrayPtr_[i];
}

/*************************************************************************
 Assignment operator
 Input: rhs - stack to assign lhs to
 Output: reference to stack being assigned to
 Copies elements from rhs to lhs so containers are equal
**************************************************************************/
template <class T>
stack<T>& stack<T>::operator=(const stack& rhs)
{
   if (this != &rhs)
   {
      numElements_ = rhs.size();
      numCapacity_ = rhs.capacity();
      arrayPtr_ = detail::allocNew<T>(numCapacity_);
      for (auto i = 0; i < numElements_; ++i)
         arrayPtr_[i] = rhs.arrayPtr_[i];
   }
   return *this;
}

/*************************************************************************
 clear()
 Input:
 Output:
 Empties stack and sets numElements to zero, capacity remains unchanged
**************************************************************************/
template <class T>
void stack<T>::clear()
{
   for (auto i = 0; i < numElements_; ++i)
      arrayPtr_[i].~T();
   numElements_ = 0;
}

/*************************************************************************
 push()
 Input: t - datum to be pushed onto stack
 Output:
 Places t on top of the stack
**************************************************************************/
template <class T>
void stack<T>::push(const T& t)
{
   if (numCapacity_ == 0)
      *this = stack<T>(1);
   else if (numElements_ >= numCapacity_)
      resize(numCapacity_ * 2);
   arrayPtr_[numElements_] = t;
   ++numElements_;
}

/*************************************************************************
 pop()
 Input:
 Output:
 Removes the top of the stack
**************************************************************************/
template <class T>
void stack<T>::pop()
{
   arrayPtr_[numElements_ - 1].~T();
   --numElements_;
}


/*************************************************************************
 top()
 Input:
 Output: T& - reference to element at the top of the stack
 Returns element at the top of the stack
**************************************************************************/
template <class T>
T& stack<T>::top()
{
   if (numElements_ > 0)
      return arrayPtr_[numElements_ - 1];
   else
      throw "ERROR: Unable to reference the element from an empty Stack";
}

/*************************************************************************
 top()
 Input:
 Output: const T& - const reference to element at the top  of the stack
 Returns const element at the top of the stack (prevents modifying stack)
**************************************************************************/
template <class T>
const T& stack<T>::top() const
{
   if (numElements_ > 0)
      return arrayPtr_[numElements_ - 1];
   else
      throw "ERROR: Unable to reference the element from an empty Stack";
}

/*************************************************************************
 resize()
 Input: numCapacity - new capacity to resize to
 Output: const T& - const reference to element at the top  of the stack
 Resizes stack to numCapacity and truncates any elements beyond capacity
**************************************************************************/
template <class T>
void stack<T>::resize(int numCapacity)
{
   const auto tempCapacity = numCapacity;
   arrayPtr_.reset(detail::allocAndCopy(tempCapacity, numElements_, arrayPtr_.get()));
   numCapacity_ = tempCapacity;
   if (numElements_ > numCapacity_)
      numElements_ = numCapacity_;
}

} //namespace custom
#endif //STACK_H_
