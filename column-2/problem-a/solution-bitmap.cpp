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
  - real   0m1.027s
  - user   0m0.934s
  - sys    0m0.029s

  $ clang++ -std=c++11 -stdlib=libc++ -Os solution-bitmap.cpp
  (-Os optimiztion)
  - real   0m0.578s
  - user   0m0.531s
  - sys    0m0.018s
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

// range of 20-bit integer (2^20)
#define MAX_RANGE 1048576

int main () {
  vector<int> inputNums = read_nums("problem-a.input");

  bitset<MAX_RANGE> bs(0);
  for(int n: inputNums) {
    bs.set(n);
  }

  for(int i=0; i<MAX_RANGE; i+=1) {
    if (!bs[i]) {
      cout << i << endl;
      break;
    }
  }
  
  return 0;
}
