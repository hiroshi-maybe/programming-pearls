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
  $ clang++ -std=c++11 -stdlib=libc++ max-sublist-bruteforce.cpp
  (No optimization option)
  - real   0m0.490s
  - user   0m0.472s
  - sys    0m0.006s

  $ clang++ -std=c++11 -stdlib=libc++ -Os max-sublist-bruteforce.cpp
  (-Os optimiztion)
  - real   0m0.090s
  - user   0m0.077s
  - sys    0m0.003s
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

int sumForRange(const vector<int> &data, int start, int end) {
  int sum = 0;
  FOR(i, start, end+1) {
    sum += data[i];
  }

  return sum;
}

int maxsublist(const vector<int> &data) {
  int res = 0;
  REP(i, data.size()) {
    FOR(j, i, data.size()) {
      res = max(res, sumForRange(data, i, j));
    }
  }
  
  return res;
}

int main () {
  auto data = read_nums("input.dat");
  cout << maxsublist(data) << endl;

  return 0;
}
