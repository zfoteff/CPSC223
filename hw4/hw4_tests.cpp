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

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST (BasicCollectionTest, CopyConstructorTest)
{
  LinkedListCollection<string, double> rhs;
  rhs.insert("a", 10.0);
  rhs.insert("b", 20.0);
  LinkedListCollection<string, double> lhs(rhs);
  double v;
  ASSERT_EQ(lhs.find("a", v), true);
  ASSERT_EQ(v, 10.0);
  ASSERT_EQ(lhs.find("b", v), true);
  ASSERT_EQ(v, 20.0);
}

TEST (BasicCollectionTest, AssignementOperatorTest)
{
  LinkedListCollection<string, double> lhs;
  LinkedListCollection<string, double> rhs;
  lhs.insert("a", 10.0);
  rhs.insert("b", 20.0);
  rhs.insert("c", 30.0);
  lhs = rhs;
  double v;
  ASSERT_EQ(lhs.find("b", v), true);
  ASSERT_EQ(v, 20.0);
  ASSERT_EQ(lhs.find("c", v), true);
  ASSERT_EQ(v, 30.0);
}

TEST (BasicCollectionTest, DestructorTest)
{
  LinkedListCollection<string, double>* c = new LinkedListCollection<string, double>();
  c->insert("a", 10.0);
  c->insert("b", 20.0);
  c->insert("c", 30.0);
  delete c;
}
