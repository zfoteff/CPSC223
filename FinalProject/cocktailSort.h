#ifndef COCKTAILSORT_H
#define COCKTAILSORT_H

class CocktailSort : public SortingAlgoritm
{
 public:

 CocktailSort();

 void insert(const int& number);

 void sort(std::vector<int> numbers_list);

 void printOriginalArray(int arr[], int len);

 void cocktailSort(int arr[], int len);

 private:
  int len = 0
  int arr[len];
};

#endif
