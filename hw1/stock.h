/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: security.h
    Header file for an implementation of a stock object
    Objects contain information representing
      -   stock symbol
      -   current share value
      -   number of current holdings
      -   purchase price
* To build:   g++ hw1.cpp
* To execute: ./a.out
*/

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
