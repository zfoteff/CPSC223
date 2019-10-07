#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "binsearch_collection.h"

using namespace std;

TEST(BasicCollectionTest, CorrectSize)
{
  BinSearchCollection<string, double> c;
  ASSERT_EQ(c.size(), 0);
  c.insert("a", 10.0);
  ASSERT_EQ(c.size(), 1);
  c.insert("b", 20.0);
  ASSERT_EQ(c.size(), 2);
}


TEST(BasicCollectionTest, InsertAndFind)
{
  BinSearchCollection<string, double> c;
  double v;
  cout<<"Here"<<endl;
  ASSERT_EQ(c.find("a", v), false);
  cout<<"Here"<<endl;
  c.insert("a", 10.0);
  ASSERT_EQ(c.find("a", v), true);
  ASSERT_EQ(v, 10.0);
  ASSERT_EQ(c.find("b", v), false);
  c.insert("b", 20.0);
  ASSERT_EQ(c.find("b", v), true);
  ASSERT_EQ(v, 20.0);
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
