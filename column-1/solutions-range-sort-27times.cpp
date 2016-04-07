#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

/*
  $ clang++ -std=c++11 -stdlib=libc++ solutions-range-sort-27times.cpp 
  (No optimization option)
  - real0m0.311s
  - user0m0.237s
  - sys0m0.024s
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

// one thousand 16-bit words of storage in main memory
#define MAX_STORAGE_SIZE 1000
#define MAX_RANGE 27000
int storage[MAX_STORAGE_SIZE];

int main () {

  for(int i=0; i<MAX_RANGE/MAX_STORAGE_SIZE; ++i) {
    int min = (i * MAX_STORAGE_SIZE) + 1;
    int max = min + MAX_STORAGE_SIZE;
    vector<int> myvector = read_nums("input.dat");

    int stidx = 0;
    for(auto n: myvector) {
      if (n >= min && n < max) {
	storage[stidx] = n;
	stidx++;
      }
    }

    sort(storage, storage + stidx);

    for(int j=0; j<stidx; ++j) {
      std::cout << storage[j] << '\n';
    }
  }
  
  return 0;
}

