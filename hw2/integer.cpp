#include <iostream>
#include <vector>
#include <string>
#include "integer.h"

Integer::Integer()
{
  digits[0] = "0";
  negative = false;
}


Integer::Integer(std::string val)
{
  if(val.charAt(0) == '-')
    negative = true;

  for(int i = 0; i < val.length(); i++)
  {
    char compare = val.charAt(val.length()-i);

    if(std::isdigit(compare))
      digits[i] = compare;
  }
}


Integer Integer::operator-() const
{
  Integer tmp;
  tmp.digits = digits;
  tmp.negative != negative;
  return tmp;
}


digit_list add(const digit_list& lhs, const digit_list& rhs) const
{
  int carry = 0;
  digit_list new_expression;
  int[] expression;
  int length = 0;

  if(lhs.size() > rhs.size())
    length = rhs.size();
  else
    length = lhs.size();

  for (int i = 0; i < length; i++)
  {
    int sum;
    int new_digit;

    sum = lhs[0] + rhs[0] + carry;
    carry = sum % 10;
    new_digit = sum - carry;

    expression[i] new_digit;
  }
}
