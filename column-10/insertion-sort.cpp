#include <stdio.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

using namespace std;

/*
  $ clang++ -std=c++11 -stdlib=libc++ insertion-sort.cpp
  (No optimization option)
  - real  0m0.012s
  - user  0m0.002s
  - sys   0m0.002s

  $ clang++ -std=c++11 -stdlib=libc++ -Os insertion-sort.cpp
  (-Os optimiztion)
  - real  0m0.012s
  - user  0m0.002s
  - sys   0m0.003s
*/

vector<int> read_nums(const string &filename) {
  ifstream infile(filename);
  vector<int> vect;
  string line;
  while (getline(infile, line)) {
    istringstream iss(line);
    int n;
    if (!(iss >> n)) { break; } // error
    vect.push_back(n);
  }
  return vect;
}

void write_nums(const string &filename, const vector<int> nums) {
  ofstream file;
  file.open (filename);
  for(int n: nums) {
    file << n << '\n';
  }
  file.close();
}

void insertion_sort(vector<int> &data) {
  REP(i, data.size()) {
    // data[0..i-1] are sorted
    int j = i;
    while (j >= 1 && data[j] < data[j-1]) {
      // data[0..j-1] are sorted. j>=1. data[j] should find a place in 0..j-1
      int tmp = data[j]; data[j-1]=data[j]; data[j]=tmp; // swap
      j -=1;
    }
  }
}

int main () {
  auto data = read_nums("input.dat");

  insertion_sort(data);

  write_nums("output.dat", data);

  return 0;
}
