/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: hw2.cpp
    Test file for Integer class object
* To build:   g++ hw2.cpp
* To execute: ./a.out
*/

#include "integer.h"
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
  //  LOGICAL OPERATORS
  //  Test case 1: check equalvalence
  Integer x1("6");
  Integer x2("6");

  assert(x1 == x2); //  passes cleanly

  //  Test case 2: less than
  Integer x3("20");
  Integer x4("110101011101010");

  assert(x3 < x4);  //  passes cleanly

  //  Test case 3: greater than
  Integer x5("105");
  Integer x6("104");

  assert(x5 > x6);  //  passes cleanly

  //  Test case 4: less than or equal to
  Integer x7("84");
  Integer x8("107");
  Integer x9("107");

  assert(x7 <= x8); //  tests that less than returns proper output
  assert(x8 <= x9); //  tests if equalvalence returns proper output
                    //  passes cleanly

  //  Test case 5: greater than or equal to
  Integer x10("5067");
  Integer x11("456");
  Integer x12("456");

  assert(x10 >= x11); //  tests that greater than returns proper output
  assert(x10 >= x12); //  tests that equalvalence returns proper output
                      //  passes cleanly

  //  Test case 6: check negation
  Integer x13("8675309");
  Integer x14("42");

  assert(x13 != x14); //  passes cleanly

  //  Addition tests
  //  Test case 1: addition of two numbers with equal length
  Integer s1("108");
  Integer s2("502");
  Integer sum1("610");
  //assert(s1 + s2 == sum1);

  //  Subraction tests
  //  Test case 1:  subtraction of two numbers with equal length
  //                no borrowing
  Integer s3("502");
  Integer s4("102");
  Integer sum2("400");
  assert(s3 - s4 == sum2);

}
