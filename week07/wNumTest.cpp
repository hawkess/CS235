#include <iostream>
#include "wholeNumber.h"

int main()
{
   auto wNumTest1 = wholeNumber{1};
   auto wNumTest2 = wholeNumber{1000000};
   auto wNumTest3 = wNumTest2;

   std::cout << "wNumTest1: " << wNumTest1 << '\n';
   std::cout << "wNumTest2: " << wNumTest2 << '\n';
   std::cout << "wNumTest3: " << wNumTest3 << '\n';

   auto wNumTest4 = wholeNumber{999} + wholeNumber{241};
   auto wNumTest5 = wNumTest4 + wholeNumber{999999};
   auto wNumTest6 = wholeNumber{wNumTest5};

   std::cout << "wNumTest4: " << wNumTest4 << '\n';
   std::cout << "wNumTest5: " << wNumTest5 << '\n';
   std::cout << "wNumTest6: " << wNumTest6 << '\n';

   auto wNumTest7 = wholeNumber{999999} + wholeNumber {222222};
   auto wNumTest8 = wholeNumber{1234};
   auto wNumTest9 = wholeNumber{1234567};
   auto wNumTest10 = wNumTest8 + wNumTest9;

   std::cout << "wNumTest7: " << wNumTest7 << '\n';
   std::cout << "wNumTest8: " << wNumTest8 << '\n';
   std::cout << "wNumTest9: " << wNumTest9 << '\n';
   std::cout << "wNumTest10: " << wNumTest10 << '\n';

   return 0;
}
