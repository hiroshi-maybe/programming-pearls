#include <stdio.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

/*
  $ clang++ -std=c++11 -stdlib=libc++ binarysearch-loop.cpp
  - real   0m0.017s -> 17
  - user   0m0.008s ->  8
  - sys    0m0.002s ->  2

  $ clang++ -std=c++11 -stdlib=libc++ -Os binarysearch-loop.cpp
  - real   0m0.014s -> 15
  - user   0m0.005s ->  5
  - sys    0m0.002s ->  2

  No difference regardless of code tuning
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

int sequentialSearch(const vector<int> &data, int t) {
  int i = 0;
  int n = data.size();

  while (i<n && data[i] != t) {
    i+=1;
  }

  return i;
}

int sequentialSearchTuned(vector<int> &data, int t) {
  data.push_back(t);
  int i = 0;
  int n = data.size();

  while (data[i] != t) {
    i+=1;
  }

  return i;
}

int main () {
  int t = 9001;
  
  auto data = read_nums("input.dat");
  cout << sequentialSearchTuned(data, t) << endl;

  return 0;
}
