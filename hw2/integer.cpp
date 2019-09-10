#include <iostream>
#include <vector>
#include <string>
#include "integer.h"

Integer::Integer()
{
  digits[0] = 0;
  negative = false;
}


Integer::Integer(std::string val)
{
  negative = false;
  int n = int(val.size());

  //  if empty string is passed
  if (n == 0)
  {
    digits.push_back(0);
    return;
  }

  //  if first digit is a 0
  if (val[0] == '0' && n > 1)
  {
    digits.push_back(0);
    return;
  }

  for (int i = n; i >= 0; --i)
  {
    char c = val[i];
    if(std::isdigit(c))
      digits.push_back(c - '0');

    //  if c is not a character
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
  tmp.negative != negative;
  return tmp;
}

Integer Integer::operator+(const Integer& rhs) const
{
  Integer tmp;
  tmp.digits = this->add(rhs);
  tmp.negative = false;
  return tmp;
}

Integer Integer::operator-(const Integer& rhs) const
{
  Integer tmp;
  tmp.digits = this->sub(rhs);
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
  if(digits.size() == rhs.digits.size())
  {
    for (int i = 0; i < digits.size(); ++i)
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

bool Integer::operator<=(const Integer& rhs) const
{
  if(less_than(this->digits, rhs.digits) == true || this == rhs)
    return true;

  return false;
}

digit_list Integer::add(const digit_list& lhs, const digit_list& rhs) const
{
  int carry = 0;
  digit_list new_expression;
  int expression[];
  int length = 0;

  if(lhs.size() > rhs.size())
    length = rhs.size();
  else
    length = lhs.size();

  for (int i = 0; i < length; ++i)
  {
    int sum;
    int new_digit;

    sum = lhs[i] + rhs[i] + carry;
    carry = sum % 10;
    new_digit = sum - (carry*10);

    new_expression.push_back(new_digit);
  }

  return new_expression;
}

bool Integer::less_than(const digit_list& lhs, const digit_list& rhs) const
{
  if(lhs.size() < rhs.size())
    return True;

  if(lhs.size() == rhs.size())
  {
    for(int i = 0; i < lhs.size(); ++i)
    {
      if(lsh.at(i) < rhs.at(i))
        return true;

      if(lsh.at(i) == rhs.at(i))
        continue;

      else
        return false;
    }
  }

  return false;
}
