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
  $ clang++ -std=c++11 -stdlib=libc++ quick-sort-two-pointers.cpp
  (No optimization option)
  - real  0m0.012s
  - user  0m0.002s
  - sys   0m0.003s

  $ clang++ -std=c++11 -stdlib=libc++ -Os quick-sort
  (-Os optimiztion)
  - real  0m0.011s
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

int partition(vector<int> &data, int start, int end) {
  // data should not be empty
  int t = data[start];
  
  int i = start;
  int j = end;
  while (true) {
    // i < j, data[start+1..i] <= t, data[j..end-1] >= t

    // swaps even if data[i] or data[j] is equal to t
    do { i+=1; } while (i<end && data[i]<t);
    do { j-=1; } while (j>start && data[j]>t);

    // i==end or data[i]>=t
    // j==start or data[j]<=t
    if (j<i) break;
    
    int tmp=data[i]; data[i]=data[j]; data[j]=tmp;
  }

  int tmp=data[j]; data[j]=data[start]; data[start]=tmp;
  
  return j;
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
