#ifndef STOCK_OPTION_H
#define STOCK_OPTION_H

#include "stock.h"
#include <string>
using namespace std;

class StockOption : public Stock
{
public:
  StockOption();  // Constructor

  //  Assigns a value
  void set_strike_price(double price);

  //  Retrieves strike price
  double get_strike_price();

  //  Calculates net worth of a stock option
  //  net worth = (current price - strike price)
  double sell_value();

private:
  double strike_price;
};

#endif
