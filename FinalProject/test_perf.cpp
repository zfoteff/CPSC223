#include <iostream>
#include "cocktailSort.h"
#include "cocktailSort.cpp"
#include "sorting_algorithm.h"
#include "test_driver.h"

using namespace std;

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    cout<<"Usage: "<<argv[0]<<" filename # of elements"<<endl;
    return 1;
  }

  int new_length = atoi(argv[2]);
  CocktailSort* c = new CocktailSort(new_length);
  TestDriver driver(argv[1], c);
  driver.run_tests();
  driver.print_results();
}
