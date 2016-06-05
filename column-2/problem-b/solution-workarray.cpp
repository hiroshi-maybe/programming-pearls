#include <stdio.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

/*
  $ clang++ -std=c++11 -stdlib=libc++ solution-workarray.cpp
  (No optimization option)
  - real   0m1.027s
  - user   0m0.934s
  - sys    0m0.029s

  $ clang++ -std=c++11 -stdlib=libc++ -Os solution-workarray.cpp
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

void write_nums(const string &filename, const vector<int> nums) {
  ofstream file;
  file.open (filename);
  for(int n: nums) {
    file << n << '\n';
  }
  file.close();
}

int main () {
  vector<int> inputNums = read_nums("problem-b.input");

  vector<int> numsWork;

  int rotatePos = 817698;
  
  for(int i=0; i< rotatePos; i+=1) {
    numsWork.push_back(inputNums[i]);
  }

  for(int i=rotatePos; i< inputNums.size(); i+=1) {
    inputNums[i-rotatePos] = inputNums[i];
  }

  for(int i=0; i< rotatePos; i+=1) {
    inputNums[rotatePos+i] = numsWork[i];
  }

  write_nums("problem-b.output", inputNums);
  
  return 0;
}
