/***********************************************************************
 * Module:
 *    Week 11, Sort Insertion
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Insertion Sort
 ************************************************************************/

#ifndef SORT_INSERTION_H
#define SORT_INSERTION_H

#include <cassert>


template <typename T>
int binarySearch(T array[], const T& search, int begin, int end)
{
   auto middle = (begin + end) / 2;
   if (begin > end)
      return begin;
   if (array[middle] == search)
      return middle;
   if (search > array[middle])
      return binarySearch(array, search, middle + 1, end);
   else
      return binarySearch(array, search, begin, middle - 1);
}

/*****************************************************
 * SORT INSERTION
 * Perform the insertion sort
 ****************************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   auto insert = 0;
   auto shift = 0;
   for (auto pivot = num - 2; pivot >= 0; --pivot)
   {
      auto value = array[pivot];
      insert = binarySearch(array, value, pivot + 1, num - 1);
      --insert;
      for (shift = pivot; shift < insert; ++shift)
         array[shift] = array[shift + 1];
      array[shift] = value;
   }
}

#endif // SORT_INSERTION_H
