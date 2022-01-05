/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include "wholeNumber.h"
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   // your code to display the first <number> Fibonacci numbers
   auto f1 = wholeNumber{1};
   auto f2 = wholeNumber{1};
   auto fib = wholeNumber{};
   std::cout << '\t' << f1 << '\n';
   std::cout << '\t' << f2 << '\n';
   for (auto i = 2; i < number; ++i)
   {
      fib = f1 + f2;
      f1 = f2;
      f2 = fib;
      std::cout << '\t' << fib << '\n';
   }

   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   f1 = wholeNumber{1};
   f2 = wholeNumber{1};
   fib = wholeNumber{};

   for (auto i = 2; i < number; ++i)
   {
      fib = f1 + f2;
      f1 = f2;
      f2 = fib;
   }

   std::cout << '\t' << fib << '\n';

   // your code to display the <number>th Fibonacci number
}
