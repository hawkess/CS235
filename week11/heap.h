#ifndef HEAP_H_
#define HEAP_H_

namespace custom {

template <typename T>
class heap
{
public:
   heap(const T array[], int size);
   ~heap();
   void toArray(T dest[], int dest_size);
   void heapify();
   void printHeap();
   void sort();
private:
   T* data_;
   int size_;

   void maxHeapify(int index, int size);
   void swap(int left, int right);
};

// Ctor
template <typename T>
heap<T>::heap(const T array[], int size) :
   size_(size)
{
   data_ = new T[size_];
   for (auto i = 0; i < size; ++i)
      data_[i] = array[i];
   heapify();
}

// Dtor
template <typename T>
heap<T>::~heap()
{
   delete [] data_;
}

/*****************************************************
 * toArray()
 * input: T dest[] - array to write to
 *        int dest_size - size of array to write to
 * Dumps array contained in data_ to dest
 ****************************************************/
template <typename T>
void heap<T>::toArray(T dest[], int dest_size)
{
   for (auto i = 0; i < size_ && i < dest_size; ++i)
      dest[i] = data_[i];
}

/*****************************************************
 * heapify()
 * Create heap from array
 ****************************************************/
template <typename T>
void heap<T>::heapify()
{
   for (auto i = size_ / 2 - 1; i >= 0; --i)
      maxHeapify(i, size_);
}

/*****************************************************
 * maxHeapify()
 * input: int index - starting index
 *        int size - size of array to percolate
 * Convert heap to max heap
 ****************************************************/
template <typename T>
void heap<T>::maxHeapify(int index, int size)
{
   auto max = index;
   auto iLeft = index * 2 + 1;
   auto iRight = iLeft + 1;

   if ((iLeft < size) && (data_[iLeft] > data_[max]))
      max = iLeft;
   if ((iRight < size) && (data_[iRight] > data_[max]))
      max = iRight;
   if (max != index)
   {
      swap(index, max);
      maxHeapify(max, size);
   }
}

/*****************************************************
 * sort()
 * Sort max heap by swapping first and last-- elements
 ****************************************************/
template <typename T>
void heap<T>::sort()
{
   auto num = size_ - 1;
   while (num >= 0)
   {
      swap(0, num);
      --num;
      maxHeapify(0, num);
   }
}

/*****************************************************
 * swap()
 * input: int left - index of left element to swap
 *        int right - index of right element to swap
 * Swaps the values of two elements
 ****************************************************/
template <typename T>
void heap<T>::swap(int left, int right)
{
      auto temp = data_[left];
      data_[left] = data_[right];
      data_[right] = temp;
}

/*****************************************************
 * printHeap()
 * Debugging function to print heap
 ****************************************************/
template <typename T>
void heap<T>::printHeap()
{
   std::cout << "Heap: \n";
   for (auto i = 0; i < size_; ++i)
      std::cout << data_[i] << ", ";
   std::cout << '\n';
}

} // namespace custom

#endif // HEAP_H_
