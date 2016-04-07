#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

bool comparator(int i, int j) {
  return i==j;
}

std::vector<int> read_random_nums(const string &filename) {
  ifstream infile(filename);
  std::vector<int> vect;
  string line;
  while (getline(infile, line)) {
    istringstream iss(line);
    int n;
    if (!(iss >> n)) { break; } // error
    vect.push_back(n);
  }
  return vect;
}

int main () {
  vector<int> myvector = read_random_nums("bootstrap.dat");
  
  sort(myvector.begin(), myvector.end());
  vector<int>::iterator it = unique(myvector.begin(), myvector.end());

  myvector.resize(distance(myvector.begin(), it));

  random_shuffle(myvector.begin(), myvector.end());

  for(it=myvector.begin(); it!=myvector.end(); ++it) {
    std::cout << *it << '\n';
  }
  return 0;
}

