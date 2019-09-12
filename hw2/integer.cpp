/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: integer.cpp
    Implementation for a Integer class object
    Objects contain information representing
      - vector containing digits of integer
      - boolean for representing/handling a negative number
* To build:   g++ hw2.cpp
* To execute: ./a.out
*/

#include "integer.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

Integer::Integer()
{
  digits.push_back(0);
  negative = false;
}

Integer::Integer(std::string val)
{
  negative = false;
  int n = int(val.size());

  //  empty string
  if (n == 0)
  {
    digits.push_back(0);
    return;
  }

  //  leading zero
  if (val[0] == '0' && n > 1)
  {
    digits.push_back(0);
    return;
  }

  for (int i = n-1; i >= 0; --i)
  {
    char c = val[i];
    if(std::isdigit(c))
      digits.push_back(c-'0');
    else
    {
      digits.clear();
      digits.push_back(0);
      return;
    }
  }
}

Integer Integer::operator-() const
{
  Integer tmp;
  tmp.digits = digits;
  tmp.negative = !negative;
  return tmp;
}

Integer Integer::operator+(const Integer& rhs) const
{
  Integer tmp;
  tmp.digits = add(digits, rhs.digits);
  tmp.negative = false;
  return tmp;
}

Integer Integer::operator-(const Integer& rhs) const
{
  Integer tmp;
  //tmp.digits = this->sub(rhs);
  tmp.negative = false;
  return tmp;
}

bool Integer::operator<(const Integer& rhs) const
{
  return less_than(this->digits, rhs.digits);
}

bool Integer::operator>(const Integer& rhs) const
{
  return !less_than(this->digits, rhs.digits);
}

bool Integer::operator==(const Integer& rhs) const
{
  unsigned int i;

  if(digits.size() == rhs.digits.size())
  {
    for (i = 0; i < digits.size(); ++i)
    {
      if(digits.at(i) != rhs.digits.at(i))
      {
        return false;
      }
    }

    //  if the sizes are equal && every int stored in the vector matches at
    //  every index, then the two are equal
    return true;
  }

  //  if the numbers are not the same size there is no possible way they could
  //  be equal
  return false;
}

bool Integer::operator!=(const Integer& rhs) const
{
  if (!(this->digits == rhs.digits))
    return true;

  return false;
}

bool Integer::operator<=(const Integer& rhs) const
{
  if(less_than(this->digits, rhs.digits) == true || this->digits == rhs.digits)
    return true;

  return false;
}

bool Integer::operator>=(const Integer& rhs) const
{
  if ( !less_than(this->digits, rhs.digits) == true || this->digits == rhs.digits)
    return true;

  return false;
}

digit_list Integer::add(const digit_list& lhs, const digit_list& rhs) const
{
  digit_list new_expression;
  int length;
  std::vector<int> bigger;
  unsigned int i;

  if(lhs.size() > rhs.size())
  {
    length = rhs.size();
    bigger = lhs;
  }

  else
  {
    length = lhs.size();
    bigger = rhs;
  }

  for (i = 0; i < length; ++i)
  {
    int sum;
    int new_digit;
    int carry = 0;

    sum = lhs.at(i) + rhs.at(i) + carry;
    carry = sum % 10;
    new_digit = sum - (carry*10);

    new_expression.push_back(new_digit);
  }

  for(int j = i; j < bigger.size(); ++j)
    new_expression.push_back(bigger.at(j));

  return new_expression;
}

digit_list Integer::sub(const digit_list& lhs, const digit_list& rhs) const
{
  digit_list new_expression;
  unsigned int i;
  int length;

  if (lhs.size() > rhs.size())
    length = rhs.size();
  else
    length = lhs.size();

  for (i = 0; i < length; ++i)
  {
    int sum;
    int borrow = 0;

    if (rhs.at(i) > lhs.at(i))
      borrow += 1;

    sum = (lhs.at(i) + borrow*10) - rhs.at(i);

    new_expression.push_back(sum);
  }

  return new_expression;
}

bool Integer::less_than(const digit_list& lhs, const digit_list& rhs) const
{
  unsigned int i;

  if(lhs.size() < rhs.size()) {return true;}

  else if (rhs.size() > lhs.size()) {return false;}

  if(lhs.size() == rhs.size())
  {
    for(i = 0; i < lhs.size(); ++i)
    {
      if(lhs.at(i) < rhs.at(i))

        return true;

      if(lhs.at(i) == rhs.at(i))
        continue;

      else
        return false;
    }
  }

  return false;
}

std::ostream& operator<<(std::ostream& out, const Integer& val)
{
  unsigned int i;
  for(i = (val.digits.size()-1); i > 0; --i)
    out<<val.digits.at(i);

  out<<val.digits.at(0);
  return out;
}
