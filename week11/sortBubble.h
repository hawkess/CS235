/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
   auto swapped = true;
   // move pivot down as each elemeent is sorted
   for (auto pivot = num - 1; (pivot > 0) && swapped; pivot--)
   {
      swapped = false; // hit pivot without a swap, array is sorted
      for (auto comp = 0; comp < pivot; comp++) // start comparing from left
         if (array[comp] > array[comp + 1]) // if right > left, swap
         {
            auto temp = array[comp];
            array[comp] = array[comp + 1];
            array[comp + 1] = temp;
            swapped = true; // swap occured so sort again after this
         }
   }
}


#endif // SORT_BUBBLE_H
