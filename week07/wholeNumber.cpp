#include <iomanip>
#include <iostream>
#include "wholeNumber.h"

/*************************************************************************
 wholeNumber Default Constructor
 Input: (optional) int num - integer to initialize wholeNumber with
 Output:
 Constructs a wholeNumber with the value of num
**************************************************************************/
wholeNumber::wholeNumber(int num)
{
   while (num > 0)
   {
      num_.push_front(num % 1000);
      num /= 1000;
   }
}
wholeNumber::wholeNumber(const wholeNumber& rhs)
{
   num_ = rhs.num_;
}
wholeNumber& wholeNumber::operator=(const wholeNumber& rhs)
{
   if (this != &rhs)
      num_ = rhs.num_;
   return *this;
}
wholeNumber wholeNumber::operator+(int num)
{
   auto newNumber = wholeNumber{num};
   return *this + newNumber;
}
wholeNumber wholeNumber::operator+(const wholeNumber& rhs)
{
   auto remainder = 0;
   auto lhs_it = num_.rbegin();
   auto rhs_it = rhs.num_.rbegin();
   auto lhs_end = num_.rend();
   auto rhs_end = rhs.num_.rend();
   auto result = wholeNumber{};
   for ( ;lhs_it != lhs_end && rhs_it != rhs_end; ++lhs_it, ++rhs_it)
   {
      auto sum = *lhs_it + *rhs_it + remainder;
      result.num_.push_front(sum % 1000);
      remainder = sum / 1000;
   }
   while (rhs_it != rhs_end)
   {
      auto sum = *rhs_it + remainder;
      result.num_.push_front(sum % 1000);
      remainder = sum / 1000;
      ++rhs_it;
   }
   while (lhs_it != lhs_end)
   {
      auto sum = *lhs_it + remainder;
      result.num_.push_front(sum % 1000);
      remainder = sum / 1000;
      ++lhs_it;
   }
   if (remainder > 0)
      result.num_.push_front(remainder);
   return result;
}

wholeNumber& wholeNumber::operator+=(const wholeNumber& rhs)
{
   *this = *this + rhs;
   return *this;
}

custom::list<int>::iterator wholeNumber::begin()
{
   return num_.begin();
}

custom::list<int>::iterator wholeNumber::end()
{
   return num_.end();
}

std::ostream& operator<<(std::ostream& out, wholeNumber& wNum)
{
   std::string separator = "";
   auto width = 1;
   out << std::setfill('0');
   for (auto it = wNum.begin(); it != wNum.end(); ++it)
   {
      out << separator << std::setw(width) << *it;
      separator = ",";
      width = 3;
   }
   return out;
}
