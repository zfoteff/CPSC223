/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: hw6_tests.cpp
    unit test file for hw6 
*/

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "linked_list_collection.h"

using namespace std;

TEST(BasicCollectionTest, CorrectSize)
{
  LinkedListCollection<string, double> c;
  ASSERT_EQ(c.size(), 0);
  c.insert("a", 10.0);
  ASSERT_EQ(c.size(), 1);
  c.insert("b", 20.0);
  ASSERT_EQ(c.size(), 2);
}

TEST(BasicCollectionTest, InsertAndFind)
{
  LinkedListCollection<string, double> c;
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
  LinkedListCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  double v;
  c.remove("a");
  ASSERT_EQ(c.find("a", v), false);
  c.remove("b");
  ASSERT_EQ(c.find("b", v), false);
  c.remove("c");
  ASSERT_EQ(c.find("c", v), false);
  ASSERT_EQ(c.size(), 0);
}











TEST(BasicCollectionTest, GetKeys)
{
  LinkedListCollection<string, double> c;
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

TEST(BasicCollectionTest, GetKeyRange)
{
  LinkedListCollection<string, double> c;
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


TEST(BasicCollectionTest, KeySort)
{
  LinkedListCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  c.insert("d", 40.0);
  vector<string> sorted_ks;
  c.sort(sorted_ks);

  for (int i = 0; i < int(sorted_ks.size()) - 1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

TEST (BasicCollectionTest, CopyConstructorTest)
{
  LinkedListCollection<string, double> rhs;
  rhs.insert("a", 10.0);
  rhs.insert("b", 20.0);
  LinkedListCollection<string, double> lhs = rhs;
  double v;
  ASSERT_EQ(lhs.find("a", v), true);
  ASSERT_EQ(v, 10.0);
  ASSERT_EQ(lhs.find("b", v), true);
  ASSERT_EQ(v, 20.0);
}





TEST (BasicCollectionTest, DestructorTest)
{
  LinkedListCollection<string, double>* c
   = new LinkedListCollection<string, double>();
  c->insert("a", 10.0);
  c->insert("b", 20.0);
  c->insert("c", 30.0);
  delete c;
}

TEST (BasicCollectionTest, InsertionSortTest)
{
  LinkedListCollection<string, double> c;
  c.insert("c", 30.0);
  c.insert("a", 10.0);
  c.insert("d", 40.0);
  c.insert("e", 50.0);
  c.insert("b", 20.0);
  c.insertion_sort();
  vector<string> sorted_ks;
  c.keys(sorted_ks);

  for (int i = 0; i < int(sorted_ks.size()) - 1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

TEST (BasicCollectionTest, MergeSortTest)
{
  LinkedListCollection<string, double> c;
  c.insert("b", 30.0);
  c.insert("c", 10.0);
  c.insert("d", 40.0);
  c.insert("e", 50.0);
  c.insert("a", 20.0);
  c.merge_sort();
  cout<<"here"<<endl;
  vector<string> sorted_ks;
  c.keys(sorted_ks);

  for (int i = 0; i < int(sorted_ks.size()) - 1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

TEST (BasicCollectionTest, QuickSortTest)
{
  LinkedListCollection<string, double> c;
  c.insert("b", 30.0);
  c.insert("e", 50.0);
  c.insert("a", 20.0);
  c.insert("c", 10.0);
  c.insert("d", 40.0);
  c.quick_sort();
  vector<string> sorted_ks;
  c.keys(sorted_ks);

  for (int i = 0; i < int(sorted_ks.size()) - 1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
