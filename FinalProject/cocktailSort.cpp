#include <iostream>
using namespace std;

#include "cocktailSort.h"

CocktailSort::CocktailSort()
{
 //len = 0;
 //arr[len];
}

void CocktailSort::printOriginalArray(int arr[], int len)
{
 for (int i = 0; i < len; i++)
 {
  cout << arr[i] << " ";
 }
 cout << endl;
 cout << endl;
}

void swap(int *numHigh, int *numLow)
{
 int tmp = *numHigh;
 *numHigh = *numLow;
 *numLow = tmp;
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
