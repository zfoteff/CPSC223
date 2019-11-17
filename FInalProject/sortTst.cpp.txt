#include <iostream>
#include "cocktailSort.h"
#include "cocktailSort.cpp"
using namespace std;

int main()
{
 CocktailSort c;
 int len = 9;
 int arr[len] = {3, 6, 5, 4, 1, 2, 7, 8, 9};
 c.printOriginalArray(arr, len);
 c.cocktailSort(arr, len);
 c.printOriginalArray(arr, len);
 
 return 0;
}