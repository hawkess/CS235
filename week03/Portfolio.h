/***********************************************************************
 * Header:
 *    PORTFOLIO
 * Summary:
 *    Contains portfolio class for holding multiple stocks
 * Author
 *    Sean Hawkes
 ************************************************************************/

#ifndef PORTFOLIO_H_
#define PORTFOLIO_H_

#include "queue.h"
#include "stock.h"

class Portfolio
{
public:
   Portfolio() = default;
   explicit Portfolio(const Stock& stock) { Buy_.push(stock); }
   void buy(const Stock& stock);
   void display() const;
   void sell(int count, const Dollars& price);
private:
   custom::queue<Stock> Buy_;
   custom::queue<Stock> Sell_;
};

#endif // PORTFOLIO_H_
