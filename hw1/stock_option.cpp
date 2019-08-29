#include "stock_option.h"
#include <string>
using namespace std;

StockOption::StockOption() : Stock()
{
  Stock();
  set_symbol("N/A");
  set_share_value(0.0);
  set_holdings(0);
  set_purchase_price(0.0);
  strike_price = 0.0;
}

void StockOption::set_strike_price(double price)
{
  strike_price = price;
}

double StockOption::get_strike_price()
{
  return strike_price;
}

double StockOption::sell_value()
{
  return (get_share_value() - get_strike_price());
}
