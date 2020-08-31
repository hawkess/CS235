#ifndef VECTOR_H_
#define VECTOR_H_

#include <cassert>
#include <iostream>
#include <new>
#include <type_traits>

namespace custom {

namespace detail {

template <typename T>
T* allocAndCopy(int capacity, int size, const T* data)
{
   try
   {
      auto newdata = new T[capacity];
      auto temp = newdata;
      for (auto i = 0; i < size; ++i)
         *(temp++) = *(data++);
      return newdata;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: Unable to allocate a new buffer for vector";
   }
}

} // namespace detail

/***************
*  Vector class
****************/
template <typename T>
class vector
{
public:
   template <bool isConst = false>
   class iterator_template
   {
   public:
      iterator_template() : p_(nullptr) {}
      using ref = typename std::conditional<isConst, const T&, T&>::type;
      using ptr = typename std::conditional<isConst, const T*, T*>::type;
      iterator_template(ptr p) : p_(p) {}
      iterator_template(const iterator_template &rhs)
      {
         *this = rhs;
      }
      iterator_template& operator=(const iterator_template &rhs)
      {
         if (this != &rhs)
            this->p_ = rhs.p_;

         return *this;
      }
      bool operator==(const iterator_template &rhs) const
      {
         return this->p_ == rhs.p_;
      }
      bool operator!=(const iterator_template &rhs) const
      {
         return !(*this == rhs);
      }
      iterator_template& operator++()
      {
         ++p_;
         return *this;
      }
      iterator_template& operator++(int)
      {
         iterator_template temp(*this);
         ++p_;
         return temp;
      }
      iterator_template& operator--()
      {
         --p_;
         return *this;
      }
      iterator_template& operator--(int)
      {
         iterator_template temp(*this);
         --p_;
         return temp;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<!isConst_, ref>::type
      operator*()
      {
         return *p_;
      }
      template <bool isConst_ = isConst>
      typename std::enable_if<isConst_, ref>::type
      operator*() const
      {
         return *p_;
      }
   private:
      ptr p_;
   }; //class iterator_template
//   using iterator = typename vector<T>::iterator_template<false>;
   typedef vector<T>::iterator_template<false> iterator;
//   using const_iterator = typename vector<T>::iterator_template<true>;
   typedef vector<T>::iterator_template<true> const_iterator;
   vector(int numElements = 0, const T& t = T());
   vector(const vector &rhs);
   ~vector()
   {
      delete[] array_;
   }

   vector& operator=(const vector &rhs);
   T& operator[](int index);
   const T& operator[] (int index) const;
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
   void push_back(const T& t);
   vector<T>::iterator begin();
   vector<T>::const_iterator cbegin() const;
   vector<T>::iterator end();
   vector<T>::const_iterator cend() const;

private:
   T* array_;
   int numCapacity_;
   int numElements_;

   void resize(int numCapacity);
}; // class vector

//Default Constructor
template <typename T>
vector<T>::vector(int numElements, const T& t) :
   numCapacity_(numElements),
   numElements_(numElements)
{
   try
   {
      array_ = new T[numCapacity_];
   }
   catch (std::bad_alloc&) {
      throw "ERROR: Unable to allocate a new buffer for vector";
   }
   for (vector<T>::iterator it = this->begin(); it != this->end(); ++it)
      *it = t;
}

//Copy constructor
//Params: rhs : vector - right-hand side to be copied from
template <typename T>
vector<T>::vector(const vector& rhs)
{
   numElements_ = rhs.size();
   numCapacity_ = numElements_;
   try
   {
      array_ = new T[numElements_];
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: Unable to allocate a new buffer for vector";
   }
   vector<T>::iterator lhs_it = this->begin();
   for (vector<T>::const_iterator rhs_it = rhs.cbegin();
        rhs_it != rhs.cend(); ++rhs_it, ++lhs_it)
   {
      *lhs_it = *rhs_it;
   }
}

//Assignment operator
//Params: rhs : vector& - right-hand side of = operation to assign from
template <typename T>
vector<T>& vector<T>::operator=(const vector& rhs)
{
   if (this != &rhs)
   {
      delete[] array_;
      numElements_ = rhs.size();
      numCapacity_ = numElements_;
      try
      {
         array_ = new T[numElements_];
      }
      catch (std::bad_alloc&)
      {
         throw "ERROR: Unable to allocate a new buffer for vector";
      }
      vector<T>::iterator lhs_it = this->begin();
      for (vector<T>::const_iterator rhs_it = rhs.cbegin();
           rhs_it != rhs.cend(); ++rhs_it, ++lhs_it)
      {
         *lhs_it = *rhs_it;
      }
   }
   return *this;
}

//Index operator
template <typename T>
T& vector<T>::operator[](int index)
{
   if ((index >= 0) && (index < this->size()))
      return array_[index];
   else
      throw "ERROR: Invalid index";
}

//Index operator
template <typename T>
const T& vector<T>::operator[](int index) const
{
   if ((index >= 0) && (index < this->size()))
      return array_[index];
   else
      throw "ERROR: Invalid index";
}
//clear()
//Clears the vector and invalidates pointers, leaving capacity unchanged
template <typename T>
void vector<T>::clear()
{
   for(vector<T>::iterator it = this->begin(); it != this->end(); ++it)
      (*it).~T();
   numElements_ = 0;
}

//push_back()
//Adds element to the end of the vector
template <typename T>
void vector<T>::push_back(const T& t)
{
   if (numCapacity_ == 0)
   {
      *this = vector<T>(1, t);
      return;
   }
   else if (numElements_ >= numCapacity_)
      resize(numCapacity_ * 2);
   array_[numElements_] = t;
   ++numElements_;
}

//begin()
//Returns vector::iterator pointing to the beginning of vector
template <typename T>
typename vector<T>::iterator vector<T>::begin()
{
   return vector<T>::iterator(array_);
}
//cbegin()
//Returns vector::const_iterator pointing to the beginning of vector
template<typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const
{
   return vector<T>::const_iterator(array_);
}
//end()
//Returns vector::iterator pointing to the next element past the end of vector
template <typename T>
typename vector<T>::iterator vector<T>::end()
{
   return vector<T>::iterator(array_ + numElements_);
}
//cbegin()
//Returns const vector::const_iterator pointing to the next element past the end of vector
template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const
{
   return vector<T>::const_iterator(array_ + numElements_);
}


template <typename T>
void vector<T>::resize(int numCapacity)
{
      const auto tempCapacity = numCapacity;
      auto oldarray = array_;
      array_ = detail::allocAndCopy(tempCapacity, numElements_, array_);
      delete[] oldarray;
      numCapacity_ = tempCapacity;
      if (numElements_ > numCapacity_)
         numElements_ = numCapacity_;

}

} // namespace custom

#endif // VECTOR_H_
