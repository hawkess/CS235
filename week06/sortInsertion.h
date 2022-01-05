/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   auto i = 1; // ignore sorting first element, pointless
   while (i < num) // while we haven't reached the end of the array
   {
      auto sortee = array[i]; // select current element for comparison
      auto j = i - 1; // start comparison point at previous element
      // keep going towards the beginning of array as long as sortee
      // is smaller than the current element
      while ((j >= 0) && (array[j] > sortee))
      {
         array[j + 1] = array[j]; // swap elements to move space down
         --j;
      }
      // we leave loop at position before where sortee belongs
      array[j + 1] = sortee; // place sortee
      ++i; // move to next element for comparison
   }
}

#endif // INSERTION_SORT_H

