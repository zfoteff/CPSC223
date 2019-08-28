/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: security.h
    Implementation of a security object
    Objects contain information representing
      - stock symbol
      - current share value
      - number of current holdings
* To build:   g++ hw1.cpp
* To execute: ./a.out
*/

#include "security.h"
#include <iostream>
#include <string>
using namespace std;

Security::Security()
{
  stock_symbol = "N/A";
  share_value = 0.0;
  number_of_holdings = 0;
}

Security::Security(string symbol, double value, int holdings)
{
  stock_symbol = symbol;
  share_value = value;
  number_of_holdings = holdings;
}
