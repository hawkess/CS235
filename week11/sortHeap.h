/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

#include "heap.h"


/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
   auto heaparray = custom::heap<T>{array, num};
   heaparray.sort();
   heaparray.toArray(array, num);
}


#endif // SORT_HEAP_H
