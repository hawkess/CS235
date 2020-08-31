#ifndef WHOLENUMBER_H_
#define WHOLENUMBER_H_
#include "list.h"

class wholeNumber
{
public:
   wholeNumber(int num = 0);
   wholeNumber(const wholeNumber& rhs);
   wholeNumber& operator=(const wholeNumber& rhs);
   wholeNumber operator+(int num);
   wholeNumber operator+(const wholeNumber& num);
   wholeNumber& operator+=(const wholeNumber& rhs);
   custom::list<int>::iterator begin();
   custom::list<int>::iterator end();
private:
   custom::list<int> num_;
};

std::ostream& operator<<(std::ostream& out, wholeNumber& wNum);

#endif // WHOLENUMBER_H_
