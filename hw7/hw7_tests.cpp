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
  c.insert("c", 30.0);
  ASSERT_EQ(c.size(), 3);
  c.remove("a");
  ASSERT_EQ(c.size(), 2);
  c.remove("b");
  ASSERT_EQ(c.size(), 1);
  c.remove("c");
  ASSERT_EQ(c.size(), 0);
}


TEST (BasicCollectionTest, DestructorTest)
{
  HashTableCollection<string, double>* c
  = new HashTableCollection<string, double>();
  c->insert("a", 10.0);
  c->insert("b", 20.0);
  c->insert("c", 30.0);
  delete c;
}


TEST (BasicCollectionTest, CopyConstructorTest)
{
  HashTableCollection<string, double> rhs;
  rhs.insert("a", 10.0);
  rhs.insert("b", 20.0);
  rhs.insert("c", 30.0);
  HashTableCollection<string, double> lhs(rhs);
  double v;
  ASSERT_EQ(lhs.find("a", v), true);
  ASSERT_EQ(v, 10.0);
  ASSERT_EQ(lhs.find("b", v), true);
  ASSERT_EQ(v, 20.0);
  ASSERT_EQ(lhs.find("c", v), true);
  ASSERT_EQ(v, 30.0);
}


TEST (BasicCollectionTest, AssignementOperatorTest)
{
  HashTableCollection<string, double> lhs;
  HashTableCollection<string, double> rhs;
  lhs.insert("a", 10.0);
  rhs.insert("b", 20.0);
  rhs.insert("c", 30.0);
  lhs = rhs;
  double v;
  ASSERT_EQ(lhs.find("b", v), true);
  ASSERT_EQ(v, 20.0);
  ASSERT_EQ(lhs.find("c", v), true);
  ASSERT_EQ(v, 30.0);
  ASSERT_EQ(lhs.find("a", v), false);
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
  c.insert("c", 30.0);
  ASSERT_EQ(c.find("c", v), true);
  ASSERT_EQ(v, 30.0);
}


TEST(BasicCollectionTest, RemoveElems)
{
  HashTableCollection<string, double> c;
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


TEST(BasicCollectionTest, KeySort)
{
  HashTableCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  c.insert("d", 40.0);
  vector<string> sorted_ks;
  c.sort(sorted_ks);

  for (int i = 0; i < int(sorted_ks.size()) - 1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
  }


TEST(BasicCollectionTest, Resize)
{
  HashTableCollection <int, int> c;
  //  11/16 ~= .69
  for (int i = 0; i < 12; ++i)
    c.insert(i, i+1);

  int selection_1_val;
  int selection_2_val;
  int selection_3_val;
  int selection_4_val;
  int k;
  ASSERT_EQ(c.find(7, selection_1_val), true);
  ASSERT_EQ(c.find(11, selection_2_val), true);

  vector<int> pre_merge_keys;
  vector<int> post_merge_keys;

  c.keys(pre_merge_keys);
  //  will tip the collection over the load threshold
  //  12/16 = 3/4 = .75
  c.insert(12, 13);
  c.keys(post_merge_keys);

  //  Assert that the same elements still exist
  ASSERT_EQ(c.find(7, selection_3_val), true);
  ASSERT_EQ(c.find(11, selection_4_val), true);
  //  Assert new insert exists in new list
  ASSERT_EQ(c.find(12, k), true);
  ASSERT_EQ(k, 13);
  //  Assert that the keys still contain the same values
  ASSERT_EQ(selection_1_val, selection_3_val);
  ASSERT_EQ(selection_2_val, selection_4_val);

  ASSERT_NE(pre_merge_keys, post_merge_keys);
}


TEST(BasicCollectionTest, MultipleResize)
{
  HashTableCollection<int, int> c;
  for (int i = 0; i < 12; ++i)
    c.insert(i, i+1);

  int selection_1_val;
  int selection_2_val;
  int selection_3_val;
  int selection_4_val;//  if bucket is empty

  int k;
  ASSERT_EQ(true, c.find(5, selection_1_val));
  ASSERT_EQ(true, c.find(8, selection_2_val));

  c.insert(12, 13);

  for (int i = 13; i < 23; ++i)
    c.insert(i, i+i);

  c.insert(24, 25);

  //  Assert keys still exist in collection and have same value as before
  ASSERT_EQ(true, c.find(5, selection_3_val));
  ASSERT_EQ(true, c.find(8, selection_4_val));
  ASSERT_EQ(selection_1_val, selection_3_val);
  ASSERT_EQ(selection_2_val, selection_4_val);
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
