//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: hw10_perf.cpp
// DATE: Spring 2022
// DESC: Simple performance test driver for HW-10. To run from the
//       command line use:
//          ./hw10_perf 
//       which will print out the corresponding HW-10 timing data. To
//       save this data to a file, run the command:
//          ./hw10_perf > output.dat
//       This file can then be used by the plotting script to generate
//       the corresponding performance graphs.
//---------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
#include "util.h"
#include "arrayseq.h"
#include "map.h"
#include "avlmap.h"
#include "btreemap.h"

using namespace std;
using namespace std::chrono;

// NOTE: all data is "shuffled"

double timed_insert(Map<int,int>& m, int key);
double timed_erase(Map<int,int>& m, int key);
double timed_contains(const Map<int,int>& m, int key);
double timed_find_range(const Map<int,int>& m, int key1, int key2);
double timed_next_key(const Map<int,int>& m, int key); 
double timed_sorted_keys(const Map<int,int>& m);

// test parameters
const int start = 0;
const int step = 100000; // 5000; // 15000
const int stop = 2000000; // 50000; // 150000
const int runs = 2;


int main(int argc, char* argv[])
{
  // configure output
  cout << fixed << showpoint;
  cout << setprecision(2);

  // output data header
  cout << "# All times in milliseconds (msec)" << endl;
  cout << "# Column 1 = input data size" << endl;

  cout << "# Column 2 = avl map insert" << endl;
  cout << "# Column 3 = 2-3-4 tree map insert" << endl;  
  
  cout << "# Column 4 = avl map erase" << endl;
  cout << "# Column 5 = 2-3-4 tree map erase" << endl;
  
  cout << "# Column 6 = avl map contains" << endl;
  cout << "# Column 7 = 2-3-4 tree map contains" << endl;
  
  cout << "# Column 8 = avl map find range" << endl;
  cout << "# Column 9 = 2-3-4 tree map find range" << endl;
  
  cout << "# Column 10 = avl map next key" << endl;
  cout << "# Column 11 = 2-3-4 tree map next key" << endl;
  
  cout << "# Column 12 = avl map sorted keys" << endl;
  cout << "# Column 13 = 2-3-4 tree map sorted keys" << endl;
  
  cout << "# Column 14 = avl map height" << endl;
  cout << "# Column 15 = 2-3-4 tree map height" << endl;
  cout << "# Column 16 = log base 2 of input size" << endl;  
  
  // generate shuffled data
  ArraySeq<int> keys, vals;
  for (int i = 2; i <= stop*2; i += 2) {
    keys.insert(i, keys.size());
    vals.insert(i, vals.size());
  }
  faro_shuffle(keys, 5);

  // generate the timing data
  for (int n = start; n <= stop; n += step) {
    // load shuffled data
    AVLMap<int,int> m1;
    BTreeMap<int,int> m2;
    for (int i = 0; i < n; ++i) {
      m1.insert(keys[i], vals[i]);
      m2.insert(keys[i], vals[i]);
    }

    int min = 2;
    int med = n;
    int max = n * 2;

    cout << n << " ";
    
    // insert 
    double c2 = timed_insert(m1, max + 1); // double c2 = timed_insert(m1, med + 1);
    cout << c2 << " " << flush;
    double c3 = timed_insert(m2, max + 1); // double c3 = timed_insert(m2, med + 1);    
    cout << c3 << " " << flush;

    // erase
    double c4 = timed_erase(m1, max + 1); // double c4 = timed_erase(m1, med + 1);
    cout << c4 << " " << flush;
    double c5 = timed_erase(m2, max + 1); // double c5 = timed_erase(m2, med + 1);
    cout << c5 << " " << flush;

    // check sizes
    assert(m1.size() == n);
    assert(m2.size() == n);
    
    // contains
    double c6 = timed_contains(m1, max + 1);
    cout << c6 << " " << flush;
    double c7 = timed_contains(m2, max + 1);
    cout << c7 << " " << flush;

    // key range (1/20th of values)
    double c8 = timed_find_range(m1, med, med + (n/20));
    cout << c8 << " " << flush;
    double c9 = timed_find_range(m2, med, med + (n/20));
    cout << c9 << " " << flush;

    // find next
    double c10 = timed_next_key(m1, med);
    cout << c10 << " " << flush;
    double c11 = timed_next_key(m2, med);
    cout << c11 << " " << flush;    

    // sort
    double c12 = timed_sorted_keys(m1);
    cout << c12 << " " << flush;
    double c13 = timed_sorted_keys(m2);
    cout << c13 << " " << flush;    
    
    // stats
    int c14 = m1.height();
    cout << c14 << " " << flush;
    int c15 = m2.height();
    cout << c15 << " " << flush;
    int c16 = (n == 0) ? 0 : ceil(log2(n));
    cout << c16 << " " << flush;
    
    cout << endl;
  }
  
}


// assumes keys are multiples of 2 and key to insert is odd
double timed_insert(Map<int,int>& m, int key)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.insert(key + (r * 2), key + (r * 2));
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

// removes the odd values inserted from timed_insert
double timed_erase(Map<int,int>& m, int key)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.erase(key + (r * 2));
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

double timed_contains(const Map<int,int>& m, int key) 
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.contains(key);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

double timed_find_range(const Map<int,int>& m, int key1, int key2)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.find_keys(key1, key2);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

double timed_next_key(const Map<int,int>& m, int key)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    int next_key;
    m.next_key(key, next_key);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}


double timed_sorted_keys(const Map<int,int>& m)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.sorted_keys();
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}




