#include <stdio.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

/*
  $ clang++ -std=c++11 -stdlib=libc++ solution-bitmap.cpp
  (No optimization option)
  - real   0m0.030s
  - user   0m0.012s
  - sys    0m0.002s

  $ clang++ -std=c++11 -stdlib=libc++ -Os solution-bitmap.cpp
  (-Os optimiztion)
  - real   0m0.017s
  - user   0m0.007s
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

void write_nums(const string &filename, const vector<int> nums) {
  ofstream file;
  file.open (filename);
  for(int n: nums) {
    file << n << '\n';
  }
  file.close();
}

// one thousand 16-bit words of storage in main memory
#define MAX_RANGE 27000

int main () {
  vector<int> inputNums = read_nums("input.dat");

  bitset<MAX_RANGE> bs(0);
  for(int n: inputNums) {
    bs.set(n-1);
  }

  vector<int> outputNums;
  for(int i=0; i<MAX_RANGE; i+=1) {
    if (!bs[i]) { continue; }
    outputNums.push_back(i+1);
  }

  write_nums("output.dat", outputNums);
  
  return 0;
}

