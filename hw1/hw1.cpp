/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: hw1.cpp
    This program builds instances of Security, Stock, and StockOption class
    objects and tests each of their values and methods with the assert statement
* To build: g++ -g -Wall security.cpp stock.cpp stock_option.cpp hw1.cpp -o -hw1
* To execute: ./a.out
*/

#include <assert.h>
#include <iostream>
#include "security.h"
#include "stock.h"
#include "stock_option.h"

using namespace std;

bool should_sell(const Stock& stock);

int main(int argc, char** argv)
{
  //  Security Implementation
  Security s1;
  s1.set_symbol("GOOG");
  s1.set_share_value(1188.10);
  s1.set_holdings(347);
  assert(s1.get_symbol() == "GOOG");
  assert(s1.get_share_value() == 1188.10);
  assert(s1.market_value() == 1188.10 * 347);

  //  Stock Implementation
  Stock s2;
  const Stock& s2_referance = s2;
  s2.set_symbol("APPL");
  s2.set_share_value(204);
  s2.set_holdings(76);
  s2.set_purchase_price(175);
  assert(s2.get_symbol() == "APPL");
  assert(s2.get_share_value() == 204);
  assert(s2.get_holdings() == 76);
  assert(s2.get_purchase_price() == 175);
  assert(s2.sell_value() == (204-175)*76);

  //  Stock Option Implementation
  StockOption s3;
  const Stock& s3_referance = s3;
  s3.set_symbol("AMZN");
  s3.set_share_value(1823);
  s3.set_holdings(500);
  s3.set_purchase_price(5.25);
  s3.set_strike_price(1828);
  assert(s3.get_symbol() == "AMZN");
  assert(s3.get_share_value() == 1823);
  assert(s3.get_holdings() == 500);
  assert(s3.get_purchase_price() == 5.25);
  assert(s3.sell_value() == (1828-5.25)*500 - 1823*500);

  assert(should_sell(s2_referance) == true);
  assert(should_sell(s3_referance) == false);

  return 0;
}

bool should_sell(const Stock& stock)
{
  return stock.sell_value() > 0;
}
