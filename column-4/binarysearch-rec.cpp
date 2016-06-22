#include <stdio.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

/*
  $ clang++ -std=c++11 -stdlib=libc++ binarysearch-rec.cpp
  (No optimization option)
  - real   0m2.843s
  - user   0m2.231s
  - sys    0m0.095s

  $ clang++ -std=c++11 -stdlib=libc++ -Os binarysearch-rec.cpp
  (-Os optimiztion)
  - real   0m1.541s
  - user   0m1.318s
  - sys    0m0.072s
*/

vector<int> data = { 1, 2, 3, 5, 5, 5, 6, 6, 6, 8, 11, 11, 11, 13, 13, 16, 16, 17, 18, 18, 19, 19, 20, 21, 23, 23, 23, 25, 26, 27, 28, 28, 29, 31, 32, 32, 34, 34, 34, 36, 37, 41, 41, 43, 47, 48, 48, 49, 50, 50, 51, 51, 52, 52, 53, 57, 58, 58, 58, 58, 58, 59, 60, 60, 62, 63, 63, 64, 65, 65, 66, 66, 69, 69, 69, 70, 72, 73, 74, 75, 76, 79, 80, 81, 83, 83, 85, 87, 88, 92, 93, 93, 94, 95, 95, 95, 99, 100, 100, 100 };

int indexOf(const vector<int> &data, int key, int start, int end) {
  if (end <= start) { return -1; }

  int midPos = start + (end - start) / 2;

  //  cout << start << ',' << midPos << ',' << end << endl;

  int mid = data[midPos];
  if (mid == key) return midPos;
  if (mid >  key) return indexOf(data, key, start,  midPos);
  if (mid <  key) return indexOf(data, key, midPos+1,  end);

  return -1;
}

int binarySearch(const vector<int> &data, int key) {
  int start = 0;
  int end = data.size();

  return indexOf(data, key, start, end);
}

int main () {
  int key = 0;
  
  scanf ("%d", &key);
  cout << binarySearch(data, key) << endl;

  return 0;
}
