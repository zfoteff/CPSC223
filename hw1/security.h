/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: security.h
    Header file for an implementation of a security object
    Objects contain information representing
      -   stock symbol
      -   current share value
      -   number of current holdings
*/

#ifndef SECURITY_H
#define SECURITY_H

#include <string>

class Security
{
  public:
    Security();   // Constructor

    //  Assigns value to private member variable stock_symbol
    void set_symbol(std::string symb);

    // Retrieves security indentification symbol
    std::string get_symbol() const;

    //  Assigns value to private member variable share_value
    void set_share_value(double new_value);

    //  Retrieves share value
    double get_share_value() const;

    //  Assigns value to private member variable number_of_holdings
    void set_holdings(int num);

    //  Retrieves number of holdings
    int get_holdings() const;

    //  Current value of all holdings
    double market_value() const;

  private:
    std::string stock_symbol;
    double share_value;
    int number_of_holdings;
};

#endif
