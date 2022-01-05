/***********************************************************************
 * Implementation:
 *    PORTFOLIO
 * Summary:
 *    Contains implementation for Portfolio class to allow stock queue handling
 * Author
 *    Sean Hawkes
 **********************************************************************/


#include "dollars.h"
#include "Portfolio.h"
#include <iostream>

void Portfolio::buy(const Stock& stock)
{
   Buy_.push(stock);
}

/*************************************************************************
 display()
 Input:
 Output:
 Prints a summary of transactions and current holdings
**************************************************************************/
void Portfolio::display() const
{
   if(!Buy_.empty())
   {
      // Lambda for printing using queue::for_each to avoid copying
      // large queues solely to pop for display
      std::cout << "Currently held:\n";
      auto buyprint = [](const Stock& stock) {
         std::cout << "\tBought " << stock.count() << " shares at "
         << Dollars(stock.price()) << '\n'; };
      Buy_.for_each(buyprint);
   }

   if(!Sell_.empty())
   {
      std::cout << "Sell history:\n";
      // Lambda for printing using queue::for_each to avoid copying
      // large queues solely to pop for display
      auto sellprint = [](const Stock& stock) {
         std::cout << "\tSold " << stock.count() << " shares at "
         << stock.price() << " for a profit of "
         << stock.profit() << '\n'; };
      Sell_.for_each(sellprint);
      auto sales = Sell_;
      auto proceeds = Dollars();
      while (!sales.empty())
      {
         proceeds += sales.front().profit();
         sales.pop();
      }
      std::cout << "Proceeds: " << Dollars(proceeds) << '\n';
   }
}

/*************************************************************************
 push()
 Input: count, price - amount to be sold at price
 Output:
 Sells specified number of stocks at specified price, popping batches as needed
 to fill demand
**************************************************************************/
void Portfolio::sell(int count, const Dollars& price)
{
   std::cerr << "Entered sell\n";
   auto countSold = 0;
   while (count > countSold)
   {
      if (!Buy_.empty())
      {
         auto profit = Dollars();
         // Sell shares as long as the amount sold is less than desired amount
         countSold += Buy_.front().sell(count - countSold);
         std::cout << Buy_.front().count() << " shares left.\n";
         profit += (price * countSold) - (Buy_.front().price() * countSold);
         // If no more shares in current batch, pop batch
         if (Buy_.front().count() == 0)
            Buy_.pop();
         Sell_.push(Stock(countSold, price, profit));
      }
      else
         throw "ERROR: Not enough shares to meet sell order";
   }
}
