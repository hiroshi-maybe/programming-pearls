#include <stdio.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

/*
  $ clang++ -std=c++11 -stdlib=libc++ solution-reverse.cpp
  (No optimization option)
  - real   0m1.027s
  - user   0m0.934s
  - sys    0m0.029s

  $ clang++ -std=c++11 -stdlib=libc++ -Os solution-reverse.cpp
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

vector<int> reverse(vector<int> &nums, int start, int length) {
  int end = start + length;
  for(int i=0; i< length / 2; i+=1) {
    int i1 = start + i;
    int i2 = end - i - 1;
    int tmp = nums[i1];
    nums[i1] = nums[i2];
    nums[i2] = tmp;
  }

  return nums;
}

int main () {
  vector<int> inputNums = read_nums("problem-b.input");

  vector<int> numsWork;

  int rotatePos = 817698;
  //int rotatePos = 10;

  inputNums = reverse(inputNums, 0,         rotatePos);
  inputNums = reverse(inputNums, rotatePos, inputNums.size()-rotatePos);
  inputNums = reverse(inputNums, 0,         inputNums.size());

  write_nums("problem-b.output", inputNums);
  
  return 0;
}
