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
  $ clang++ -std=c++11 -stdlib=libc++ max-sublist-rec.cpp
  (No optimization option)
  - real   0m0.020s
  - user   0m0.010s
  - sys    0m0.002s

  $ clang++ -std=c++11 -stdlib=libc++ -Os max-sublist-rec.cpp
  (-Os optimiztion)
  - real   0m0.013s
  - user   0m0.005s
  - sys    0m0.002s
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

#define MAX_ELEMENTS 1001

int maxsublist(const vector<int> &data, int index, int currentMax) {
  if (index >= data.size()) {
    return currentMax;
  }

  int value = data[index];
  int nextmax = max(currentMax + value, value);
  
  int res = maxsublist(data, index+1, nextmax);
  return max(res, currentMax);
}

int main () {
  auto data = read_nums("input.dat");
  cout << maxsublist(data, 0, 0) << endl;

  return 0;
}
