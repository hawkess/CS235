#ifndef SET_H_
#define SET_H_

#include <cassert>
#include <iostream>
#include <functional>
#include <memory>
#include <new>
#include <type_traits>

namespace custom
{

namespace setdetail
{

template <class T>
T* allocAndCopy(int capacity, int size, const T* data)
{
   try
   {
      auto newdata = new T[capacity];
      for (auto i = 0; i < size && i < capacity; ++i)
         newdata[i] = data[i];
      return newdata;
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: Unable to allocate a new buffer for set";
   }
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
      throw "ERROR: unable to allocate a new buffer for set";
   }
}

} // namespace detail

/***************
*  Set class
****************/
template <class T>
class set
{
public:
   template <bool isConst = false>
   class iterator_template
   {
   public:
      iterator_template() : p_(nullptr) {}
      using ref = typename std::conditional<isConst, const T&, T&>::type;
      using ptr = typename std::conditional<isConst, const T*, T*>::type;
      using difference_type = unsigned int;
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
      bool operator==(const iterator_template& rhs) const
      {
         return this->p_ == rhs.p_;
      }
      bool operator!=(const iterator_template& rhs) const
      {
         return !(*this == rhs);
      }
      bool operator>(const iterator_template& rhs) const
      {
         return this->p_ > rhs.p_;
      }
      bool operator<(const iterator_template& rhs) const
      {
         return this->p_ < rhs.p_;
      }
      difference_type operator-(const iterator_template& rhs) const
      {
         return this->p_ - rhs.p_;
      }
      iterator_template operator-(int offset) const
      {
         return iterator_template{this->p_ - offset};
      }
      iterator_template operator+(int offset) const
      {
         return iterator_template{this->p_ + offset};
      }
      iterator_template& operator++()
      {
         ++p_;
         return *this;
      }
      iterator_template operator++(int)
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
      iterator_template operator--(int)
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

   typedef set<T>::iterator_template<false> iterator;
   typedef set<T>::iterator_template<true> const_iterator;

   set(int numCapacity = 0);
   set(const set &rhs);
   set<T>& operator=(const set& rhs);
   set<T> operator&&(const set& rhs) const;
   set<T> operator||(const set& rhs) const;
   set<T> operator-(const set& rhs) const;

   void clear();
   bool empty() const
   {
      return numElements_ == 0;
   }
   set<T>::iterator erase(set<T>::iterator pos);
   set<T>::iterator erase(set<T>::const_iterator pos);
   set<T>::iterator find(const T& t);
   set<T>::const_iterator find(const T& t) const;
   void insert(const T& t);
   int size() const
   {
      return numElements_;
   }

   set<T>::iterator begin();
   set<T>::const_iterator cbegin() const;
   set<T>::iterator end();
   set<T>::const_iterator cend() const;


private:
   std::unique_ptr<T[]> arrayPtr_;
   int numCapacity_;
   int numElements_;

   void resize(int numCapacity);
   T* search(int begin, int end, T* data, const T& key);
   const T* search(int begin, int end, const T* data, const T& key) const;

}; // class set

/*************************************************************************
 Default constructor
 Input: int numCapacity - desired capacity
 Constructs a new set with capacity of numCapacity
**************************************************************************/
template <class T>
set<T>::set(int numCapacity) :
   numCapacity_(numCapacity),
   numElements_(0)
{
   arrayPtr_ = setdetail::allocNew<T>(numCapacity_);
}

/*************************************************************************
 Copy Constructor
 Input: const set& rhs - set to be copied from
 Constructs a new set containing the same elements as rhs
**************************************************************************/
template <class T>
set<T>::set(const set& rhs)
{
   numElements_ = rhs.size();
   numCapacity_ = numElements_;
   arrayPtr_.reset(setdetail::allocAndCopy(numCapacity_, numElements_,
                                        rhs.arrayPtr_.get()));
}

/*************************************************************************
 Assignment operator
 Input: const set& rhs - set to assign to lhs
 Output: reference to set being assigned to
 Copies elements from rhs to lhs so containers are equal
**************************************************************************/
template <class T>
set<T>& set<T>::operator=(const set& rhs)
{
   if (this != &rhs)
   {
      numElements_ = rhs.size();
      numCapacity_ = numElements_;
      if (numCapacity_ < rhs.size())
         resize(rhs.numCapacity_);
      set<T>::iterator lhs_it = this->begin();
      for (set<T>::const_iterator rhs_it = rhs.cbegin();
           rhs_it != rhs.cend(); ++rhs_it, ++lhs_it)
      {
         *lhs_it = *rhs_it;
      }
   }
   return *this;
}

/*************************************************************************
 Operator && (intersection)
 Input: const set& rhs - right hand side to intersect with
 Output: set - resulting intersection
 Returns a set where all elements are contained in both sets
*************************************************************************/
template <class T>
set<T> set<T>::operator&&(const set& rhs) const
{
   auto lhs_start = cbegin();
   auto lhs_finish = cend();
   auto rhs_start = rhs.cbegin();
   auto rhs_finish = rhs.cend();
   auto output = set<T>{numElements_ + rhs.numElements_};
   auto output_dest = output.begin();

   // Loop while not at the end of either container
   while (lhs_start != lhs_finish && rhs_start != rhs_finish)
   {
      if (*lhs_start < *rhs_start) // If lhs is less, ignore it
         ++lhs_start;
      else
      {
         if (*lhs_start == *rhs_start) // If both are equal, add lhs to container
         {
            *output_dest++ = *lhs_start++;
            ++output.numElements_;
         }
         ++rhs_start; // Move up rhs to begin next comparison
      }
   }
   return output;
}

/*************************************************************************
 Operator || (union)
 Input: const set& rhs - right hand side to unite with
 Output: set - resulting union
 Returns a set where all elements are contained in either set
*************************************************************************/
template <class T>
set<T> set<T>::operator||(const set& rhs) const
{
   auto lhs_start = cbegin();
   auto lhs_finish = cend();
   auto rhs_start = rhs.cbegin();
   auto rhs_finish = rhs.cend();
   auto output = set<T>{numElements_ + rhs.numElements_};
   auto output_dest = output.begin();

   // Loop until end of lhs
   for (;lhs_start != lhs_finish; ++output_dest)
   {
      if (rhs_start == rhs_finish) // If at the end of rhs
      {
         while (lhs_start != lhs_finish) // Copy remainder of lhs to output
         {
            *output_dest++ = *lhs_start++;
            ++output.numElements_;
         }
         return output; // Return resulting container
      }
      if (*rhs_start < *lhs_start) // If rhs is less, add it to output
      {
         *output_dest = *rhs_start++; // Increment rhs
         ++output.numElements_;
      }
      else
      {
         *output_dest = *lhs_start; // Else add left side
         ++output.numElements_;
         if (*lhs_start == *rhs_start) // If both are equal, move up rhs
            ++rhs_start;
         ++lhs_start; // increment lhs to begin next comparison
      }
   }

   while (rhs_start < rhs_finish) // Dump remainder of rhs into output
   {
      *output_dest++ = *rhs_start++;
      ++output.numElements_;
   }
   return output;
}

/*************************************************************************
 Operator -
 Input: const set& rhs - set to be subtracted
 Output: set - resulting difference
 Returns a set with all elements in rhs subtracted from lhs
*************************************************************************/
template <class T>
set<T> set<T>::operator-(const set& rhs) const
{
   auto lhs_start = cbegin();
   auto lhs_finish = cend();
   auto rhs_start = rhs.cbegin();
   auto rhs_finish = rhs.cend();
   auto output = set<T>{numElements_};
   auto output_dest = output.begin();

   while (lhs_start != lhs_finish) // While not at the end of the lhs
   {
      if(rhs_start == rhs_finish) // If at the end of rhs
      {
         while (lhs_start != lhs_finish) // Copy the remainder of lhs to output
         {
            *output_dest++ = *lhs_start++;
            ++output.numElements_;
         }
         return output; // Return resulting container
      }
      if (*lhs_start < *rhs_start) // if lhs is less than the right hand side
      {
         *output_dest++ = *lhs_start++; // add it to the output
         ++output.numElements_;
      }
      else
      {
         if (*lhs_start == *rhs_start) // if both sides are equal
            ++lhs_start; // ignore lhs element and move past it
         ++rhs_start; // increment rhs to begin next comparison
      }
   }
   return output;
}

/*************************************************************************
 clear()
 Input:
 Output:
 Clears contents of entire set leaving capacity unchanged
**************************************************************************/
template <class T>
void set<T>::clear()
{
   for(auto it = this->begin(); it != this->end(); ++it)
      (*it).~T();
   numElements_ = 0;
}
/*************************************************************************
 erase()
 Input: set<T>::iterator - position to delete from
 Output: set<T>::iterator - next element after deletion point
 Deletes element at given position
**************************************************************************/
template <class T>
typename set<T>::iterator set<T>::erase(set<T>::iterator pos)
{
   if (pos > begin() && pos < end())
   {
      for (auto it = pos; it < (end() - 1); ++it)
         *it = *(it + 1);
      *(end() - 1) = T{};
      --numElements_;
   }
   return pos;
}

/*************************************************************************
 erase()
 Input: set<T>::iterator - position to delete from
 Output: set<T>::iterator - next element after deletion point
 Deletes element at given position
**************************************************************************/
template <class T>
typename set<T>::iterator set<T>::erase(set<T>::const_iterator pos)
{
   if (pos > begin() && pos < end())
   {
      for (auto it = pos; it < (end() - 1); ++it)
         *it = *(it + 1);
      *(end() - 1) = T{};
      --numElements_;
   }
   return pos;
}

/*************************************************************************
 find()
 Input: const T& t - key to be found
 Output:
 Finds element with given key if it exists
**************************************************************************/
template <class T>
typename set<T>::iterator set<T>::find(const T& t)
{
   auto ptr = search(0, numElements_ - 1, arrayPtr_.get(), t);
   return ptr != nullptr ? set<T>::iterator(ptr) : end();
}

/*************************************************************************
 find()
 Input: const T& t - key to be found
 Output:
 Finds element with given key if it exists
**************************************************************************/
template <class T>
typename set<T>::const_iterator set<T>::find(const T& t) const
{
   auto ptr = search(0, numElements_ - 1, arrayPtr_.get(), t);
   return ptr != nullptr ? set<T>::const_iterator(ptr) : end();
}

/*************************************************************************
 insert()
 Input: const T& t - key to be inserted
 Output:
 Inserts elemeent if it does not already exist
**************************************************************************/
template <class T>
void set<T>::insert(const T& t)
{
 if (find(t) == end())
   {
      if (numElements_ >= numCapacity_)
         resize(numCapacity_ * 2);
      auto it = end() - 1;
      for (; (it > (begin() - 1)) && (t < *it); --it)
         *(it + 1) = *it;
      *(it + 1) = t;
      ++numElements_;
   }
}

/*************************************************************************
 resize()
 Input: numCapacity - new capacity to resize to
 Output:
 Resizes sets to numCapacity and truncates any elements past capacity
*************************************************************************/
template <class T>
void set<T>::resize(int numCapacity)
{
   const auto tempCapacity = (numCapacity == 0) ? 2 : numCapacity;
   arrayPtr_.reset(setdetail::allocAndCopy(tempCapacity, numElements_,
                                           arrayPtr_.get()));
   numCapacity_ = tempCapacity;
}

/*************************************************************************
 search()
 Input: int begin, int end. const T* data, const T& key - beginning index,
 ending index, raw data container, key to be found
 Output: const T* - pointer to element where key was found
 Searches for key, returns null pointer if not found
*************************************************************************/
template <class T>
T* set<T>::search(int begin, int end, T* data,
                const T& key)
{
   if (begin > end)
      return nullptr;
   auto mid = begin + ((end - begin) / 2);
   if (key == data[mid])
      return &data[mid];
   if (key < data[mid])
      return search(begin, mid - 1, data, key);
   return search(mid + 1, end,  data, key);
}

/*************************************************************************
 search()
 Input: int begin, int end. const T* data, const T& key - beginning index,
 ending index, raw data container, key to be found
 Output: const T* - pointer to element where key was found
 Searches for key, returns null pointer if not found
*************************************************************************/
template <class T>
const T* set<T>::search(int begin, int end, const T* data,
                        const T& key) const
{
   if (end <= begin)
      return nullptr;
   auto mid = begin + ((end - begin) / 2);
   if (key == data[mid])
      return &data[mid];
   if (key > data[mid])
      return search(++mid, end, data, key);
   return search(begin, --mid, data, key);
}

/*************************************************************************
 begin()
 Input:
 Output: iterator - pointer to beginning of the container
 Returns iterator to beginning of container
**************************************************************************/
template <class T>
typename set<T>::iterator set<T>::begin()
{
   return set<T>::iterator(arrayPtr_.get());
}

/*************************************************************************
 cbegin()
 Input:
 Output: const_iterator - pointer to beginning of the container
 Returns const iterator to beginning of container
**************************************************************************/
template<class T>
typename set<T>::const_iterator set<T>::cbegin() const
{
   return set<T>::const_iterator(arrayPtr_.get());
}

/*************************************************************************
 end()
 Input:
 Output: iterator - pointer to end of the container
 Returns iterator to end of container
**************************************************************************/
template <class T>
typename set<T>::iterator set<T>::end()
{
   return set<T>::iterator(arrayPtr_.get() + numElements_);
}

/*************************************************************************
 cend()
 Input:
 Output: const_iterator - pointer to end of the container
 Returns const iterator to end of container
**************************************************************************/
template <class T>
typename set<T>::const_iterator set<T>::cend() const
{
   return set<T>::const_iterator(arrayPtr_.get() + numElements_);
}

} // namespace custom

#endif // SET_H_
