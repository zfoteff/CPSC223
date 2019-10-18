
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cassert>
#include "linked_list_collection.h"

using namespace std;
using namespace std::chrono;

typedef pair<string,double> pair_t;

const int INS_SORT = 0;
const int QCK_SORT = 1;
const int MRG_SORT = 2;

void do_sort(const vector<pair_t>& kv_pairs, int type)
{
  // create collection
  LinkedListCollection<string,double> c;
  for (pair_t p : kv_pairs)
    c.insert(p.first, p.second);
  // time sort

  if (type == INS_SORT) {
    auto start = high_resolution_clock::now();
    c.insertion_sort();
    auto end = high_resolution_clock::now();
    auto time = duration_cast<microseconds>(end - start);
    cout << "  Insertion Sort.: " << time.count() << " microseconds" << endl;
  }
  else if (type == QCK_SORT) {
    auto start = high_resolution_clock::now();
    c.quick_sort();
    auto end = high_resolution_clock::now();
    auto time = duration_cast<microseconds>(end - start);
    cout << "  Quick Sort.....: " << time.count() << " microseconds" << endl;
  }
  else if (type == MRG_SORT) {
    auto start = high_resolution_clock::now();
    c.merge_sort();
    auto end = high_resolution_clock::now();
    auto time = duration_cast<microseconds>(end - start);
    cout << "  Merge Sort.....: " << time.count() << " microseconds" << endl;
  }
  // check correctness
  vector<string> ks;
  c.keys(ks);
  assert(ks.size() == c.size());
  for (int i = 0; i < int(ks.size()) - 1; ++i)
    assert(ks[i] <= ks[i+1]);
}


int main(int argc, char** argv)
{
  if (argc != 3) {
    cout << "usage: " << argv[0] << " (q | m | i) filename " << endl;
    return 1;
  }
  // load the data
  vector<pair_t> kv_pairs;
  fstream in_file;
  in_file.open(argv[2]);
  while (in_file) {
    string op;
    in_file >> op;
    if (op == "insert") {
      string key;
      double val;
      in_file >> key;
      in_file >> val;
      pair_t p(key, val);
      kv_pairs.push_back(p);
    }
  }
  // run the sort algos
  if (string(argv[1]) == "q")
    do_sort(kv_pairs, QCK_SORT);
  else if (string(argv[1]) == "m") 
    do_sort(kv_pairs, MRG_SORT);
  else if (string(argv[1]) == "i")
    do_sort(kv_pairs, INS_SORT);
}
