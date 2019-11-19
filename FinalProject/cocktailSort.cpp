#include <iostream>
#include <vector>
#include "cocktailSort.h"
#include "sorting_algorithm.h"
using namespace std;

CocktailSort::CocktailSort()
{
  len = 0;
  arr = new int[len];
}

CocktailSort::CocktailSort(const int& length)
{
  len = length;
  arr = new int[len];
}

void CocktailSort::insert(const int& number)
{
  for (int i = 0; i < len; ++i)
  {
    if (arr[i] == 0)
    {
      arr[i] = number;
      return;
    }
  }
}

void CocktailSort::print()
{
  for (int i = 0; i < len; i++)
    cout << arr[i] << " ";

  cout << endl;
  cout << endl;
}


void CocktailSort::sort(std::vector<int>& numbers_list)
{
  cocktailSort(arr, len);
  for (int i = 0; i < len; ++i)
    numbers_list.push_back(arr[i]);
}

void CocktailSort::cocktailSort(int arr[], int len)
{
  int startPoint = 0;
  int last = len-1;
  bool keepGoing = true;

  while (keepGoing)
  {
    keepGoing = false;
    for (int i = startPoint; i < last; i++)
    {
      if (arr[i] > arr[i+1])
      {
        swap(&arr[i], &arr[i+1]);
        keepGoing = true;
      }
    }

    last--;

    for (int j = last-1; j >= startPoint; j--)
    {
      if (arr[j] > arr[j+1])
      {
        swap(&arr[j], &arr[j+1]);
      }
    }
    startPoint++;
  }
}

void CocktailSort::swap(int *numHigh, int *numLow)
{
  int tmp = *numHigh;
  *numHigh = *numLow;
  *numLow = tmp;
}
