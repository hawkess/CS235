/***********************************************************************
 * Module:
 *    Week 11, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   auto tree = custom::BST<T>{};
   for (auto index = 0; index < num; ++index)
      tree.insert(array[index]);
   auto count = 0;
   for (auto out_it = tree.cbegin(); out_it != tree.cend(); ++out_it)
      array[count++] = *out_it;
}


#endif // SORT_BINARY_H
