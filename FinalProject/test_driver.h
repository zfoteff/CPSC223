#ifndef __TEST_DRIVER_H
#define __TEST_DRIVER_H

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include "sorting_algorithm.h"

class TestDriver
{
public:
  TestDriver(const std::string& file, SortingAlgorithm* algo);
  void run_tests();
  void print_results() const;

private:
  //  test file
  std::string filename;
  //  collection under test
  SortingAlgorithm* algorithm;

  int total_ins;
  int total_srt, srt_times;

  int timed_sort(std::fstream& in_file);

  void print_details(std::string test, int total, int times) const;
};

TestDriver::TestDriver(const std::string& file, SortingAlgorithm* algo)
{
  filename = file;
  algorithm = algo;
}

void TestDriver::run_tests()
{
  //  open file
  std::fstream in_file;
  in_file.open(filename);
  //  initialize data (ms)
  total_ins = 0;
  total_srt = 0, total_srt = 0;

  while (in_file)
  {
    int number;
    in_file >> number;

    algorithm->insert(number);
    total_ins++;
  }

  srt_times += timed_sort(in_file);
  total_srt += 1;

  in_file.close();
}

void TestDriver::print_details(std::string test, int total, int times) const
{
  using namespace std;

  cout<<" " << test << " Calls: " << total << endl;
  cout<<" " << test << " Time: " << times << "microseconds" << endl;
  cout<<" " << test << " Average: " << ((1.0 * times) / total) << "microseconds"
      << endl << endl;
}

void TestDriver::print_results() const
{
  using namespace std;
  cout << "TEST RESULTS"<<endl;
  cout << "============"<<endl<<endl;
  print_details("Insert", total_ins, 1);
  print_details("Sort", total_srt, srt_times);
}

int TestDriver::timed_sort(std::fstream& in_file)
{
  using namespace std::chrono;
  std::vector<int> numbers;
  auto start = high_resolution_clock::now();
  algorithm->sort(numbers);
  auto end = high_resolution_clock::now();
  auto time = duration_cast<microseconds>(end - start);
  int duration = time.count();
  return duration;
}

#endif
