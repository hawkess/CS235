#ifndef HASH_H_
#define HASH_H_

#include "bst.h"

template <typename T>
class Hash
{
public:
   Hash(int numBuckets);
   explicit Hash(const Hash& rhs);
   ~Hash();
   Hash& operator=(const Hash& rhs);
   int capacity() const;
   void clear();
   bool empty() const;
   bool find(const T& t);
   virtual int hash(const T& t) const = 0;
   void insert(const T& t);
   int size() const;
   int hashStats() const;

private:
   bst::custom::BST<T>* array_;
   int numBuckets_;
   int numElements_;

   void allocateNew(const Hash& rhs);
   void destroy();
};

/*************************************************************************
 Non-default constructor
 Input: int numBuckets - capacity of hash to be created
 Constructs a new Hash with numBuckets elements
**************************************************************************/
template <typename T>
Hash<T>::Hash(int numBuckets) :
   numBuckets_(numBuckets),
   numElements_(0)
{
   try
   {
      array_ = new bst::custom::BST<T>[numBuckets];
   }
   catch (const std::bad_alloc&)
   {
      std::cout << "ERROR: Unable to allocate memory for the hash.";
   }
}

/*************************************************************************
 Copy constructor
 Input: const Hash& rhs - Hash to be copied from
 Constructs a new Hash containing the same elements as rhs
**************************************************************************/
template <typename T>
Hash<T>::Hash(const Hash& rhs)
{
   try
   {
      allocateNew(rhs);
   }
   catch (const std::bad_alloc& e)
   {
      std::cout << "ERROR: Unable to allocate memory for the hash.";
      throw e;
   }
}

/*************************************************************************
 Destructor
**************************************************************************/
template <typename T>
Hash<T>::~Hash()
{
   destroy();
}

/*************************************************************************
 operator=
 Input: const Hash& rhs - Hash to be assigned from
 Output: Hash& - reference to Hash being assigned to
 Assigns rhs to lhs via deep copy
**************************************************************************/
template <typename T>
Hash<T>& Hash<T>::operator=(const Hash& rhs)
{
   if (this != &rhs)
   {
      try
      {
         destroy();
         allocateNew(rhs);
      }
      catch (const std::bad_alloc& e)
      {
         std::cout << "ERROR: Unable to allocate memory for the hash.";
         throw e;
      }
   }
   return *this;
}

/*************************************************************************
 allocateNew()
 Input: const Hash& rhs - Hash to be copied from
 Helper function to allocate a new hash and copy to it
**************************************************************************/
template <typename T>
void Hash<T>::allocateNew(const Hash& rhs)
{
   numBuckets_ = rhs.numBuckets_;
   array_ = new bst::custom::BST<T>[numBuckets_];
   for (auto i = 0; i < rhs.capacity(); ++i)
      array_[i] = rhs.array_[i];
   numElements_ = rhs.numElements_;
}

/*************************************************************************
 capacity()
 Input:
 Output: int - capacity of Hash
 Returns the capacity of hash (stored in numBuckets_)
**************************************************************************/
template <typename T>
int Hash<T>::capacity() const
{
   return numBuckets_;
}

/*************************************************************************
 clear()
 Input:
 Output:
 Clears hash and resets size
**************************************************************************/
template <typename T>
void Hash<T>::clear()
{
   for (auto i = 0; i < numBuckets_; ++i)
      array_[i].clear();
   numElements_ = 0;
}

/*************************************************************************
 destroy()
 Input:
 Output:
 Helper function to destroy a hash
**************************************************************************/
template <typename T>
void Hash<T>::destroy()
{
   clear();
   delete [] array_;
}

/*************************************************************************
 empty()
 Input:
 Output: bool - returns true if empty
 Tests if hash is empty
**************************************************************************/
template <typename T>
bool Hash<T>::empty() const
{
   return numElements_ == 0;
}

/*************************************************************************
 find()
 Input: const T& t - value to be found in the hash
 Output: bool - returns true if found
 Searches hash for value, returns true if it is found
**************************************************************************/
template <typename T>
bool Hash<T>::find(const T& t)
{
   auto index = hash(t);
   return array_[index].find(t) != array_[index].end();
}

/*************************************************************************
 hashStats()
 Input:
 Output:
 Helper function to help determine how many buckets are filled
**************************************************************************/
template <typename T>
int Hash<T>::hashStats() const
{
   auto count = 0;
   for (auto i = 0; i < numBuckets_; ++i)
   {
      if (!(array_[i].empty()))
         ++count;
   }

   return count;
}

/*************************************************************************
 insert()
 Input: const T& t - value to be inserted
 Output:
 Inserts value at hashed index
**************************************************************************/
template <typename T>
void Hash<T>::insert(const T& t)
{
   auto index = hash(t);
   array_[index].insert(t);
   ++numElements_;
}

/*************************************************************************
 size()
 Input:
 Output: int - number of elements in the hash
 Returns size of hash (stored in numElements_)
**************************************************************************/
template <typename T>
int Hash<T>::size() const
{
   return numElements_;
}


#endif // HASH_H_
