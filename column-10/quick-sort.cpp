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
  $ clang++ -std=c++11 -stdlib=libc++ quick-sort.cpp
  (No optimization option)
  - real  0m0.013s
  - user  0m0.002s
  - sys   0m0.003s

  $ clang++ -std=c++11 -stdlib=libc++ -Os quick-sort.cpp
  (-Os optimiztion)
  - real  0m0.007s
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

void write_nums(const string &filename, const vector<int> nums) {
  ofstream file;
  file.open (filename);
  for(int n: nums) {
    file << n << '\n';
  }
  file.close();
}

int partition(vector<int> &data, int start, int end) {
  // data should not be empty
  int t = data[start];

  int p = start;
  FOR (i, start+1, end) {
    // x<t | x in data[start+1..p], data[p+1]>=t
    if (data[i] < t) {
      p += 1;
      int tmp=data[i]; data[i]=data[p]; data[p]=tmp;
    }
  }

  int tmp=data[start]; data[start]=data[p]; data[p]=tmp;
  return p;
}

void quick_sort(vector<int> &data, int start, int end) {
  if (end - start < 2) return; // more than 1 element
  
  int idx = partition(data, start, end);
  
  quick_sort(data, start, idx);
  quick_sort(data, idx+1, end);
}

int main () {
  auto data = read_nums("input.dat");

  quick_sort(data, 0, data.size());

  write_nums("output.dat", data);

  return 0;
}
