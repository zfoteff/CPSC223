#include <iostream>
#include <string>
#include <algorithm>
#include <gtest/gtest.h>
#include "cocktailSort.h"
#include "cocktailSort.cpp"

using namespace std;

TEST(BasicCollectionTest, InsertCorrectly)
{
  CocktailSort* c = new CocktailSort(10);

  for (int i = 0; i < 10; ++i)
    c->insert(i);
}


TEST (BasicCollectionTest, SortCorrectly)
{
  CocktailSort* c = new CocktailSort(10);
  std::vector<int> sorted_numbers;

  for (int i = 10; i > 0; --i)
    c->insert(i);

  c->sort(sorted_numbers);

  for (int i = 0; i < (sorted_numbers.size() - 1); ++i)
    ASSERT_LE(sorted_numbers.at(i), sorted_numbers.at(i+1));
}


TEST (BasicCollectionTest, InsertAndSort)
{
  CocktailSort* c = new CocktailSort(10);
  std::vector<int> sorted_numbers;

  for (int i = 10; i > 0; i -= 2)
    c->insert(i);

  c->sort(sorted_numbers);

  for (int i = 0; i < 5; ++i)
    ASSERT_LE(sorted_numbers.at(i), sorted_numbers.at(i+1));

  for (int i = 9; i > 0; i -= 2)
    c->insert(i);

  sorted_numbers.clear();
  c->sort(sorted_numbers);

  for (int i = 0; i < (sorted_numbers.size() - 1); ++i)
    ASSERT_LE(sorted_numbers.at(i), sorted_numbers.at(i+1));
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
