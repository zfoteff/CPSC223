#include <iostream>
#include <vector>
#include "cocktailSort.h"
#include "cocktailSort.cpp"
#include "sorting_algorithm.h"
using namespace std;

int main()
{
  vector<int> num_list;

  CocktailSort* c = new CocktailSort(10);

  for (int i = 10; i > 0; --i)
    c->insert(i);

  c->print();
  c->sort(num_list);
  c->print();

 return 0;
}
