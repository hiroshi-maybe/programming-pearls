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
  $ clang++ -std=c++11 -stdlib=libc++ max-sublist-dp.cpp
  (No optimization option)
  - real  0m0.011s
  - user  0m0.002s
  - sys   0m0.002s

  $ clang++ -std=c++11 -stdlib=libc++ -Os max-sublist-dp.cpp
  (-Os optimiztion)
  - real  0m0.011s
  - user  0m0.002s
  - sys   0m0.002s
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

#define MAX_ELEMENTS 1000
int dp[MAX_ELEMENTS];

void walkSublist(const vector<int> &data) {
  int succeeding = 0;
  REP(i, data.size()) {
    int value = data[i];
    int succeeding = max(succeeding + value, value);
    dp[i] = succeeding;
  }
}

int main () {
  auto data = read_nums("input.dat");
  REP(i, data.size()) dp[i] = 0;

  walkSublist(data);

  int res = 0;
  REP(i, data.size()) res = max(res, dp[i]);

  cout << res << endl;

  return 0;
}
