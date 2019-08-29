#include "stock.h"
#include <iostream>
#include <string>
using namespace std;

Stock::Stock() : Security()
{
  Security();
  set_symbol("N/A");
  set_share_value(0.0);
  set_holdings(0);
  purchase_price = 0.0;
}

void Stock::set_purchase_price(double price)
{
  purchase_price = price;
}

double Stock::get_purchase_price() const
{
  return purchase_price;
}

double Stock::sell_value() const
{
  double price_of_stock = get_share_value();
  return (price_of_stock/get_share_value());
}