/***********************************************************************
 * Module:
 *    Week 11, Sort Select
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H

/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 ****************************************************/
template <class T>
void sortSelection(T array[], int num)
{
   auto min = 0;
   for (auto pivot = 0; pivot < num - 1; ++pivot)
   {
      min = pivot;
      for (auto i = pivot + 1; i < num; ++i)
      {
         if (array[i] < array[min])
            min = i;
      }
      auto temp = array[pivot];
      array[pivot] = array[min];
      array[min] = temp;
   }
}


#endif // SORT_SELECTION_H
