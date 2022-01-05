/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Helfrich, CS 235
 * Author:
 *    <author>
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

#include <iostream>

template <typename T>
void printArray(const T array[], int size);

template <typename T>
void merge(T dest[], const T source1[], int size1, const T source2[], int size2)
{
   auto index1 = 0;
   auto index2 = 0;

   for (auto index_dest = 0; index_dest < (size1 + size2); ++index_dest)
   {
      if ((index1 < size1) && ((index2 == size2) ||
                                (source1[index1] < source2[index2])))
      {
          dest[index_dest] = source1[index1++];
      }
       else
         dest[index_dest] = source2[index2++];
   };
}
/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{
   auto dest = new T[num];
   auto dest_ptr = dest;
   auto source = array;
   auto swapped = true;

   auto size = 0;

   do
   {
      swapped = false;
      auto iBegin1 = 0;
      auto iBegin2 = 0;
      auto iEnd1 = 0;
      auto iEnd2 = 0;

      while (iBegin1 < num)
      {
         for (iEnd1 = iBegin1 + 1; (iEnd1 < num) &&
                 !(source[iEnd1 - 1] > source[iEnd1]); ++iEnd1)
         {}
         iBegin2 = iEnd1;
         for (iEnd2 = iBegin2 + 1; (iEnd2 < num) &&
                 !(source[iEnd2 - 1] > source[iEnd2]); ++iEnd2)
         {}

         if (iBegin2 < num)
         {
            merge(dest + iBegin1,
                  source + iBegin1, iEnd1 - iBegin1,
                  source + iBegin2, iEnd2 - iBegin2);
            size = (iEnd1 - iBegin1) + (iEnd2 - iBegin2);
            swapped = true;
         }
         else
         {
            merge(dest + iBegin1, source + iBegin1, iEnd1 - iBegin1,
                  source, 0);
         }

         iBegin1 = iEnd2;
      }
      auto temp = source;
      source = dest;
      dest = temp;
   } while (swapped);

   if (array != source)
   {
      for (auto i = 0; i < num; ++i)
         array[i] = source[i];
   }
   delete dest_ptr;
}

template <typename T>
void printArray(const T array[], int size)
{
   auto separator = "";
   for (auto index = 0; index < size; ++index)
   {
      std::cout << separator << array[index];
      separator = ", ";
   }
   std::cout << '\n';
}

#endif // SORT_MERGE_H
