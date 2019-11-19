#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "cocktailSort.h"
#include "cocktailSort.cpp"

using namespace std;

TEST(BasicCollectionTest, Insert)
{
  int new_length = 10;
  CocktailSort* c = new CocktailSort(new_length);

  for (int i = 0; i < 10; ++i)
    c->insert(i);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
