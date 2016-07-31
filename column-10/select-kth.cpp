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
  $ clang++ -std=c++11 -stdlib=libc++ select-kth.cpp
  (No optimization option)
  - real  0m0.011s
  - user  0m0.002s
  - sys   0m0.002s

  $ clang++ -std=c++11 -stdlib=libc++ -Os select-kth.cpp
  (-Os optimiztion)
  - real  0m0.009s
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

int select_kth(vector<int> &data, int start, int end, int k) {
  //  if (start == k && end == k+1) return data[start];
  
  int idx = partition(data, start, end);
  if (idx == k) return data[idx];
  
  return idx > k ? select_kth(data, start, idx, k) : select_kth(data, idx+1, end, k);
}

int main () {
  auto data = read_nums("input.dat");

  int k = 747;
  int kth = select_kth(data, 0, data.size(), k);

  cout << kth << endl;

  return 0;
}
