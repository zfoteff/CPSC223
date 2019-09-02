/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: security.h
    Implementation of a Security class object
    Objects contain information representing
      - stock symbol
      - current share value
      - number of current holdings
* To build:   g++ hw1.cpp
* To execute: ./a.out
*/

#include "security.h"
#include <string>

Security::Security()
{
  stock_symbol = "N/A";
  share_value = 0.0;
  number_of_holdings = 0;
}

void Security::set_symbol(std::string symb)
{
  stock_symbol = symb;
}

std::string Security::get_symbol() const
{
  return stock_symbol;
}

void Security::set_share_value(double new_value)
{
  share_value = new_value;
}

double Security::get_share_value() const
{
  return share_value;
}

void Security::set_holdings(int num)
{
  number_of_holdings = num;
}

int Security::get_holdings() const
{
  return number_of_holdings;
}

double Security::market_value() const
{
  return get_share_value() * get_holdings();
}
