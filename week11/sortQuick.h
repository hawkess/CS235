/***********************************************************************
 * Module:
 *    Week 11, Sort Quick
 *    Brother Helfrich, CS 235
 * Author:
 *    <author>
 * Summary:
 *    This program will implement the Quick Sort
 ************************************************************************/

#ifndef SORT_QUICK_H
#define SORT_QUICK_H

template <typename T>
void swap(T array[], int left, int right);

/*****************************************************
 * SORT QUICK
 * Perform the quick sort
 ****************************************************/
template <class T>
void sortQuick(T array[], int num)
{
   if (num <= 1)
      return;
   auto iDown = num - 1;
   auto iEnd = iDown;
   auto iUp = 0;
   auto pivotValue = array[iEnd / 2];

   while (iUp <= iDown)
   {
      while ((iUp <= iEnd) && (pivotValue > array[iUp]))
         ++iUp;
      while ((iDown >= 0) && (array[iDown] > pivotValue))
         --iDown;
      if (iUp <= iDown)
         swap(array, iUp++, iDown--);
   }

   sortQuick(array, iUp);
   sortQuick(array + iUp, iEnd - iUp + 1);

}

template <typename T>
void swap(T array[], int left, int right)
{
   auto temp = array[left];
   array[left] = array[right];
   array[right] = temp;
}

#endif // SORT_QUICK_H
