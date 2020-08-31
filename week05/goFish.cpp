/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/
#include <algorithm>
#include <fstream>
#include <iostream>
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   ifstream fs;

   fs.open("/home/cs235/week05/hand.txt");
   auto myCard = Card{};
   auto myHand = custom::set<Card>{};

   while (fs >> myCard)
   {
      myHand.insert(myCard);
   }
   std::cout << "We will play 5 rounds of Go Fish.  "
             << "Guess the card in the hand\n";

   auto matches = 0;
   for (auto i = 0; i < 5; ++i)
   {
      auto cardGuess = Card{};
      std::cout << "round " << i + 1 << ": ";
      std::cin >> cardGuess;
      auto cardLocation = myHand.find(cardGuess);
      if (cardLocation != myHand.end())
      {
         myHand.erase(cardLocation);
         std::cout << "\tYou got a match!\n";
         ++matches;
      }
      else
      {
         std::cout << "\tGo Fish!\n";
      }
   }
   std::cout << "You have " << matches << " matches!\n";
   std::cout << "The remaining cards: ";
   auto it = myHand.begin();
   std::cout << *it++;
   for (; it != myHand.end(); ++it)
      std::cout << ", " << *it;
   std::cout << '\n';
}
