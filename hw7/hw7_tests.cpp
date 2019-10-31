/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: hw7_tests.cpp
    Test file for HashTableCollection class object
*/

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "hash_table_collection.h"

using namespace std;

TEST(BasicCollectionTest, CorrectSize)
{
  HashTableCollection<string, double> c;
  ASSERT_EQ(c.size(), 0);
  c.insert("a", 10.0);
  ASSERT_EQ(c.size(), 1);
  c.insert("b", 20.0);
  ASSERT_EQ(c.size(), 2);
}


TEST(BasicCollectionTest, InsertAndFind)
{
  HashTableCollection<string, double> c;
  double v;
  ASSERT_EQ(c.find("a", v), false);
  c.insert("a", 10.0);
  ASSERT_EQ(c.find("a", v), true);
  ASSERT_EQ(v, 10.0);
  ASSERT_EQ(c.find("b", v), false);
  c.insert("b", 20.0);
  ASSERT_EQ(c.find("b", v), true);
  ASSERT_EQ(v, 20.0);
}


TEST(BasicCollectionTest, RemoveElems)
{
  HashTableCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);

  c.insert("t", 30.0);

  double v;
  c.remove("a");
  ASSERT_EQ(c.find("a", v), false);
  c.remove("b");
  ASSERT_EQ(c.find("b", v), false);
  c.remove("c");
  ASSERT_EQ(c.find("c", v), false);
  ASSERT_EQ(c.size(), 0);
}


TEST(BasicCollectionTest, GetKeyRange)
{
  HashTableCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  c.insert("d", 40.0);
  c.insert("e", 50.0);
  vector<string> ks;

  c.find("b", "d", ks);
  double v;
  ASSERT_EQ(c.find("b", v), true);
  ASSERT_EQ(c.find("c", v), true);
  ASSERT_EQ(c.find("d", v), true);
}


TEST(BasicCollectionTest, GetKeys)
{
  HashTableCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  vector<string> ks;
  c.keys(ks);
  vector<string>::iterator iter;
  iter = find(ks.begin(), ks.end(), "a");
  ASSERT_NE(iter, ks.end());

  iter = find(ks.begin(), ks.end(), "b");
  ASSERT_NE(iter, ks.end());
  iter = find(ks.begin(), ks.end(), "c");
  ASSERT_NE(iter, ks.end());
}


TEST(BasicCollectionTest, KeySort)
{
  HashTableCollection<string, double> c;
  c.insert("c", 30.0);
  c.insert("b", 20.0);
  c.insert("a", 10.0);
  c.insert("d", 40.0);
  vector<string> sorted_ks;
  c.sort(sorted_ks);

  for (int i = 0; i < int(sorted_ks.size()) - 1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}


//  Ensures integer division leads to the right index being returned for a
//  collection with an even amount of elements
TEST (BasicCollectionTest, BinSearchEven)
{
  HashTableCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  c.insert("d", 40.0);
  c.insert("e", 50.0);
  c.insert("f", 60.0);
  vector<string> k;
  c.keys(k);
  double v;
  //  Checks that the size is evenly divisible by 2 (even number)
  ASSERT_EQ(c.size() % 2, 0);
  /*
    This code block checks that the element:
      - exists in the collection
      - it is in the correct index in the collection
      - it returns the correct value
  */
  ASSERT_EQ(c.find("a", v), true);
  ASSERT_EQ(k[0], "a");
  ASSERT_EQ(v, 10.0);
  //  end block
  ASSERT_EQ(c.find("b", v), true);
  ASSERT_EQ(k[1], "b");
  ASSERT_EQ(v, 20.0);
  ASSERT_EQ(c.find("c", v), true);
  ASSERT_EQ(k[2], "c");
  ASSERT_EQ(v, 30.0);
  ASSERT_EQ(c.find("d", v), true);
  ASSERT_EQ(k[3], "d");
  ASSERT_EQ(v, 40.0);
  ASSERT_EQ(c.find("e", v), true);
  ASSERT_EQ(k[4], "e");
  ASSERT_EQ(v, 50.0);
  ASSERT_EQ(c.find("f", v), true);
  ASSERT_EQ(k[5], "f");
  ASSERT_EQ(v, 60.0);
}


//  Ensures integer division leads to the right index being returned for a
//  collection with an odd amount of elements
TEST (BasicCollectionTest, BinSearchOdd)
{
  HashTableCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  c.insert("d", 40.0);
  c.insert("e", 50.0);
  c.insert("f", 60.0);
  c.insert("g", 70.0);
  vector<string> k;
  c.keys(k);
  double v;
  //  Checks that 2 divides the size with a remainder of 1 (odd number)
  ASSERT_EQ(c.size() % 2, 1);

  /*
    This code block checks that the element:
      - exists in the collection
      - it is in the correct index in the collection
      - it returns the correct value
  */
  ASSERT_EQ(c.find("a", v), true);
  ASSERT_EQ(k[0], "a");
  ASSERT_EQ(v, 10.0);
  //  end block
  ASSERT_EQ(c.find("b", v), true);
  ASSERT_EQ(k[1], "b");
  ASSERT_EQ(v, 20.0);
  ASSERT_EQ(c.find("c", v), true);
  ASSERT_EQ(k[2], "c");
  ASSERT_EQ(v, 30.0);
  ASSERT_EQ(c.find("d", v), true);
  ASSERT_EQ(k[3], "d");
  ASSERT_EQ(v, 40.0);
  ASSERT_EQ(c.find("e", v), true);
  ASSERT_EQ(k[4], "e");
  ASSERT_EQ(v, 50.0);
  ASSERT_EQ(c.find("f", v), true);
  ASSERT_EQ(k[5], "f");
  ASSERT_EQ(v, 60.0);
  ASSERT_EQ(c.find("g", v), true);
  ASSERT_EQ(k[6], "g");
  ASSERT_EQ(v, 70.0);

}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
