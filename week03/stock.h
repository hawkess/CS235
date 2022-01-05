/***********************************************************************
 * Header:
 *    STOCK
 * Summary:
 *    This will contain just the prototype for stocksBuySell(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Sean Hawkes
 ************************************************************************/

#ifndef STOCK_H
#define STOCK_H

#include "dollars.h"

// the interactive stock buy/sell function
void stocksBuySell();

class Stock
{
public:
   explicit Stock(int count = 0, const Dollars& price = Dollars(),
                  const Dollars& profit = Dollars());
   void buy(int count, const Dollars& price);
   int count() const { return count_; }
   void count(int count) { count_ = count; }
   Dollars price() const { return price_; }
   void price(Dollars price) { price_ = price; }
   Dollars profit() const { return profit_; }
   void profit(Dollars profit) { profit_ = profit; }
   int sell(int count);
private:
   int count_;
   Dollars price_;
   Dollars profit_;
};

#endif // STOCK_H
