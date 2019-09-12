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

  assert(x1 == x2);

  //  Test case 2: less than
  Integer x3("20");
  Integer x4("110101011101010");

  assert(x3 < x4);

  //  Test case 3: greater than
  Integer x5("105");
  Integer x6("104");

  assert(x5 > x6);

  //  Test case 4: less than or equal to
  Integer x7("84");
  Integer x8("107");
  Integer x9("107");

  assert(x7 <= x8); //  tests that less than returns proper output
  assert(x8 <= x9); //  tests if equalvalence returns proper output

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

  assert(x13 != x14);

  //  Addition tests
  //  Test case 1: addition of two numbers of equal length w/out carrying
  Integer p1("107");
  Integer p2("502");
  Integer sum1("609");

  assert(p1 + p2 == sum1);

  //  Test case 2: addition of two numbers of different lengths w/out carrying
  Integer p3("1028");
  Integer p4("511");
  Integer sum2("1539");

  assert(p3 + p4 == sum2);

  //  Test case 3: addition of two numbers of equal length w/ carrying
  Integer p5("2357");
  Integer p6("498");
  Integer sum3("2855");

  assert(p5 + p6 == sum3);

  //  Test case 4: addition of two numbers of different length w/ carrying
  Integer p7("90876");
  Integer p8("7689");
  Integer sum4("98565");

  assert(p7 + p8 == sum4);

  //  Subraction tests
  //  Test case 1:  subtraction of two numbers of equal length w/out borrowing
  Integer s1("502");
  Integer s2("102");
  Integer diff1("400");

  assert(s1 - s2 == diff1);

  //  Test case 2:  subtraction of two numbers of different length w/out
  //                borrowing
  Integer s3("7562");
  Integer s4("140");
  Integer diff2("7422");

  assert(s3 - s4 == diff2);

  //  Test case 3: subtraction of two numbers of equal length w/ borrowing
  Integer s5("8009");
  Integer s6("1234");
  Integer diff3("6774");

  assert(s5 - s6 == diff3);

  //  Test case 4: subtraction of two numbers of different length w/ borrowing
  Integer s7("56600");
  Integer s8("1006");
  Integer diff4("55594");

  assert(p5 + p6 == sum2);
}
