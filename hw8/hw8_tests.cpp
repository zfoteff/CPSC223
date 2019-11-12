#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "bst_collection.h"

using namespace std;

TEST(BasicCollectionTest, CorrectSize)
{
  BSTCollection<string, double> c;
  ASSERT_EQ(c.size(), 0);
  c.insert("a", 10.0);
  ASSERT_EQ(c.size(), 1);
  c.insert("b", 20.0);
  ASSERT_EQ(c.size(), 2);
  c.insert("c", 30.0);
  ASSERT_EQ(3, c.size());
}


TEST (BasicCollectionTest, DestructorTest)
{
  BSTCollection<string, double>* c
  = new BSTCollection<string, double>();
  c->insert("a", 10.0);
  c->insert("b", 20.0);
  c->insert("c", 30.0);
  delete c;
}


TEST (BasicCollectionTest, CopyConstructorTest)
{
  BSTCollection<string, double> rhs;
  rhs.insert("b", 20.0);
  rhs.insert("a", 10.0);
  rhs.insert("c", 30.0);
  BSTCollection<string, double> lhs(rhs);
  double v;
  ASSERT_EQ(true, lhs.find("a", v));
  ASSERT_EQ(v, 10.0);
  ASSERT_EQ(true, lhs.find("b", v));
  ASSERT_EQ(v, 20.0);
  ASSERT_EQ(true, lhs.find("c", v));
  ASSERT_EQ(v, 30.0);
}


TEST (BasicCollectionTest, AssignementOperatorTest)
{
  BSTCollection<string, double> lhs;
  BSTCollection<string, double> rhs;
  rhs.insert("b", 20.0);
  rhs.insert("a", 10.0);
  rhs.insert("c", 30.0);
  lhs = rhs;
  double v;
  ASSERT_EQ(lhs.find("b", v), true);
  ASSERT_EQ(v, 20.0);
  ASSERT_EQ(lhs.find("c", v), true);
  ASSERT_EQ(v, 30.0);
  ASSERT_EQ(lhs.find("a", v), true);
  ASSERT_EQ(10.0, v);
}


TEST(BasicCollectionTest, InsertAndFind)
{
  BSTCollection<string, double> c;
  double v;
  ASSERT_EQ(c.find("b", v), false);
  c.insert("b", 20.0);
  ASSERT_EQ(c.find("b", v), true);
  ASSERT_EQ(v, 20.0);
  ASSERT_EQ(c.find("a", v), false);
  c.insert("a", 10.0);
  ASSERT_EQ(c.find("a", v), true);
  ASSERT_EQ(v, 10.0);
  ASSERT_EQ(false, c.find("e", v));
  c.insert("e", 50.0);
  ASSERT_EQ(true, c.find("e", v));
  ASSERT_EQ(50.0, v);
  ASSERT_EQ(c.find("c", v), false);
  c.insert("c", 30.0);
  ASSERT_EQ(c.find("c", v), true);
  ASSERT_EQ(v, 30.0);
  ASSERT_EQ(false, c.find("d", v));
  c.insert("d", 40.0);
  ASSERT_EQ(true, c.find("d", v));
}

/*
TEST(BasicCollectionTest, RemoveElems)
{
  BSTCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  double v;
  c.remove("a");
  ASSERT_EQ(false, c.find("a", v));
  c.remove("b");
  ASSERT_EQ(false, c.find("b", v));
  c.remove("c");
  ASSERT_EQ(false, c.find("c", v));
  ASSERT_EQ(c.size(), 0);
}
*/

TEST(BasicCollectionTest, GetKeys)
{
  BSTCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("c", 30.0);
  c.insert("b", 20.0);
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
  BSTCollection<string, double> c;
  c.insert("b", 20.0);
  c.insert("a", 10.0);
  c.insert("c", 30.0);
  c.insert("e", 50.0);
  c.insert("d", 40.0);
  vector<string> ks;
  c.find("b", "d", ks);
  double v;
  ASSERT_EQ(c.find("b", v), true);
  ASSERT_EQ(c.find("c", v), true);
  ASSERT_EQ(c.find("d", v), true);
}


TEST(BasicCollectionTest, KeySort)
{
  BSTCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  c.insert("d", 40.0);
  vector<string> sorted_ks;
  c.sort(sorted_ks);

  for (int i = 0; i < int(sorted_ks.size()) - 1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

TEST(BasicCollectionTest, CorrectHeight)
{
  BSTCollection<string, double> c;
  c.insert("b", 20.0);
  c.insert("a", 10.0);
  c.insert("e", 50.0);
  c.insert("c", 30.0);
  c.insert("d", 40.0);

  ASSERT_EQ(4, c.height());
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
