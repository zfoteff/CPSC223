/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: security.h
    Header file for an implementation of a security object
    Objects contain information representing
      - stock symbol
      - current share value
      - number of current holdings
* To build:   g++ hw1.cpp
* To execute: ./a.out
*/
#include <string>
#ifndef SECURITY_H
#define SECURITY_H
using namespace std;

class Security
{
  public:
    Security();   // constructor
    Security(string symbol, double value, int holdings);

  private:
    string stock_symbol;
    double share_value;
    int number_of_holdings;
};

#endif
