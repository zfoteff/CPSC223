/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: stock_option.h
    Header file for an implementation of a stock option object
    Objects contain information representing
      -   stock symbol
      -   current share value
      -   number of current holdings
      -   purchase price
      -   strike price
* To build:   g++ hw1.cpp
* To execute: ./a.out
*/

#ifndef STOCK_OPTION_H
#define STOCK_OPTION_H

#include "stock.h"
#include <string>

class StockOption : public Stock
{
public:
  StockOption();  // Constructor

  //  Assigns a value
  void set_strike_price(double price);

  //  Retrieves strike price
  double get_strike_price() const;

  //  Calculates net worth of a stock option
  //  net worth =
  //  (strike price - purchase price)*holdings - share value * holdings
  double sell_value() const;

private:
  double strike_price;
};

#endif
