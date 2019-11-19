#ifndef SORTING_ALGORITHM
#define SORTING_ALGORITHM

#include <vector>

class SortingAlgorithm
{
public:
  //  insert a number into the algorithm's array of number
  virtual void insert(const int& number) = 0;

  //  sort the keys in the algorthm and returns them in ascending order
  virtual void sort(std::vector<int>& numbers_list) = 0;
};


#endif
