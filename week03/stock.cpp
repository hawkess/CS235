/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    Sean Hawkes
 **********************************************************************/

#include <algorithm>
#include <cassert>     // for ASSERT
#include <cctype>
#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <sstream>
#include <vector>
#include "Portfolio.h"
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
using namespace std;

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   const std::string kBuy = "BUY";
   const std::string kSell = "SELL";
   const std::string kDisplay = "DISPLAY";
   const std::string kQuit = "QUIT";

   Portfolio myPortfolio;

   std::cin.ignore();
   while (true)
   {
      std::vector<std::string> tokens;
      std::string line;
      std::getline(std::cin, line);
      std::stringstream ls(line);
      std::string token;
      // Tokenize input and normalize to all uppercase to avoid mismatches
      while (ls >> token)
      {
         std::transform(
            token.begin(), token.end(), token.begin(),
            [](unsigned char c) ->
            unsigned char { return std::toupper(c); });
         tokens.emplace_back(token);
      }
      auto option = tokens.front();
      auto count = 0;
      auto price = Dollars();
      if (option == kBuy || option == kSell)
      {
         // Convert tokens to appropriate data types
         std::cerr << tokens[1] << '\n';
         stringstream shares(tokens[1]);
         shares >> count;
         std::cerr << tokens[2] << '\n';
         stringstream pricing(tokens[2]);
         pricing >> price;
         std::cerr << "Price recorded as " << price << '\n';
      }
      if (option == kBuy)
         myPortfolio.buy(Stock(count, price));
      else if (option == kSell)
         myPortfolio.sell(count, price);
      else if (option == kDisplay)
         myPortfolio.display();
      else if (option == kQuit)
      {
         myPortfolio.display();
         return;
      }
   }
}

Stock::Stock(int count, const Dollars& price, const Dollars& profit) :
   count_(count),
   price_(price),
   profit_(profit)
{
}

void Stock::buy(int count, const Dollars& price)
{
   count_ += count;
   price_ = price;
}

int Stock::sell(int count)
{
   auto countSold = 0;
   while (count_ > 0 && countSold < count)
   {
      --count_;
      ++countSold;
   }
   return countSold;
}


