#ifndef STOCK_H
#define STOCK_H

#include "security.h"
#include <string>
using namespace std;

class Stock : public Security
{
public:
  Stock();  // Constructor
  //Stock(); // Custom constructor

  //  Assigns a value to share_value
  void set_purchase_price(double price);

  //  Retrieves purchase price
  double get_purchase_price() const;

  //  Calculates net worth of a stock using a Price-Earnings Ratio
  //   PPE = price of stock / price per share
  double sell_value() const;

private:
  double purchase_price;
};

#endif
