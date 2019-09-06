#ifndef INTEGER_H
#define INTEGER_H

#include <string>
#include <vector>
#include <iostream>

typedef std::vector<int> digit_list;

class Integer
{
public:
  Integer();
  Integer(std::string val);

  //  Logical Operators
  //  unary negation
  Integer operator-() const;

  //  binary addition
  Integer operator+(const Integer& rhs) const;

  //  binary subtraction
  Integer operator-(const Integer& rhs) const;

  //  Relational Comparison Operators
  //  less than
  bool operator<(const Integer& rhs) const;

  //  equal to
  bool operator=(const Integer& rhs) const;

  //  greater than
  bool operator>(const Integer& rhs) const;

  //  less-than or equal to
  bool operator<=(const Integer& rhs) const;

  //  greater-than or equal to
  bool operator>=(const Integer& rhs) const;

  // comparison operator
  bool operator==(const Integer& rhs) const;

  //  output an Integer to ostream
  friend std::ostream& operator<<(std::ostream& out, const Integer& val);

private:
  digit_list digits;  // least significant digit first
  bool negative;      //  true if value is less than zero

  //  private helpers
  digit_list add(const digit_list& lhs, const digit_list& rhs) const;
  digit_list add(const digit_list& lhs, const digit_list& rhs) const;

  //  private helper to see if lhs is less than the rhs
  bool less_than(const digit_list& lhs, const digit_list& rhs) const;
};

#endif
