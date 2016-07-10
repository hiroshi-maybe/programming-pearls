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

void printVector(const vector<int> &v) {
  cout << v[0] << endl;
  for (int n: v) {
    cout << n << " ";
  }
  cout << "(" << v.size() << ")" << endl;
}

/*
  $ clang++ -std=c++11 -stdlib=libc++ max-subrect-rec.cpp
  (No optimization option)
  - real  0m0.011s
  - user  0m0.003s
  - sys   0m0.002s

  $ clang++ -std=c++11 -stdlib=libc++ -Os max-subrect-rec.cpp
  (-Os optimiztion)
  - real  0m0.010s
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

#define COL 25
#define ROW 40
#define MIN_VAL -100

// create 33 * 30 matrix
vector<vector<int>> buildRect(const vector<int> &data) {
  vector<vector<int>> rect;

  for (int i=0; i < ROW; i+=1) {
    auto first = data.begin() + i * COL;
    auto last =  data.begin() + (i+1) * COL;
    vector<int> row(first, last);
    rect.push_back(row);
  }
  
  return rect;
}

int maxsublist(const vector<int> &data, int index, int currentMax) {
  if (index >= data.size()) {
    return currentMax;
  }

  int value = data[index];
  int nextmax = max(currentMax + value, value);
  
  int res = maxsublist(data, index+1, nextmax);
  
  return max(res, currentMax);
}

int maxsubrect(const vector<vector<int>> &rect) {
  int maxRect = MIN_VAL;
  
  for (int left = 0; left < COL; left+=1) {
    vector<int> rectSumDP(ROW, 0);
    for (int right = left; right < COL; right+=1) {
      // calc sum of rect by DP
      for(int i=0; i < ROW; i+=1) {
	rectSumDP[i] += rect[i][right];
      }
      int thisMax = maxsublist(rectSumDP, 0, MIN_VAL);
      
      maxRect = max(maxRect, thisMax);
    }
  }

  return maxRect;
}

int main () {
  auto data = read_nums("input.dat");
  auto rect = buildRect(data);

  cout << maxsubrect(rect) << endl;
  return 0;
}
