#include <stdio.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

/*
  $ clang++ -std=c++11 -stdlib=libc++ solution-binarysearch.cpp
  (No optimization option)
  - real   0m2.843s
  - user   0m2.231s
  - sys    0m0.095s

  $ clang++ -std=c++11 -stdlib=libc++ -Os solution-binarysearch.cpp
  (-Os optimiztion)
  - real   0m1.541s
  - user   0m1.318s
  - sys    0m0.072s
*/


// range of 20-bit integer (2^20)
#define MAX_RANGE 1048576
#define BIT_SCALE 20

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

string fileID(const bitset<BIT_SCALE> bs, int hb, int lb) {
  string id = "";
  for (int i=hb; i>lb; i-=1) {
    id += bs[i] ? "1" : "0";
  }

  return id;
}

int missingNum(const bitset<BIT_SCALE> bs, int bitscale) {
  int n = 0;
  for (int i=bitscale-1; i>=0; i-=1) {
    if (!bs[i]) continue;
    n |= 1 << i;
  }
  
  return n;
}

string work_filename(const string &fileID) {
  return "problem-a_" + fileID + ".work";
}

void write_work_nums(const string &fileID, const vector<int> nums) {
  write_nums(work_filename(fileID), nums);
}

bool ith_bit(int i, int target) {
  int filter = 1 << i;
  return (target & filter) != 0;
}

int maxsize_for_ith_bit(int i) {
  return (1 << i) - 1;
}

int main () {
  vector<int> inputNums = read_nums("problem-a.input");

  vector<int> nums = inputNums;
  bitset<BIT_SCALE> bs(0);
  
  for(int i=0; i<BIT_SCALE; i+=1) {
    vector<int> numsOn;
    vector<int> numsOff;
    int targetBit = BIT_SCALE-i-1;
    
    for(int n: nums) {      
      if (ith_bit(targetBit, n)) {
	numsOn.push_back(n);
      } else {
	numsOff.push_back(n);
      }
    }

    vector<int> nextInputNums;
    if (numsOn.size() <= numsOff.size()) {
      bs.set(targetBit);
      nextInputNums = numsOn;
    } else {
      nextInputNums = numsOff;
    }

    string newFileID = fileID(bs, BIT_SCALE-1, targetBit-1);
    write_work_nums(newFileID, nextInputNums);

    if (numsOn.size() == 0 || numsOff.size() == 0) {
      int res = missingNum(bs, BIT_SCALE);
      cout << res << endl;
      return 0;
    }

    nums = read_nums(work_filename(newFileID));
  }
  
  return 0;
}
