#include <iostream>
#include <string>
#include "linked_list_collection.h"

using namespace std;

int main(int argc, char** argv)
{
  LinkedListCollection<std::string, double> x;
  x.insert("b", 20.0);
  x.insert("c", 30.0);
  x.insert("a", 10.0);
  x.insert("d", 40.0);
  x.insert("g", 70.0);
  x.insert("f", 60.0);
  x.insert("h", 80.0);
  x.insert("e", 50.0);
  x.insert("i", 90.0);

  cout<<"here"<<endl;
  x.insertion_sort();
  cout<<"here"<<endl;
}
