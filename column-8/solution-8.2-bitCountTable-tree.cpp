#include <stdio.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>
#include <math.h>

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

using namespace std;

/*
  $ clang++ -std=c++11 -stdlib=libc++ -Os solution-8.2-bitCountTable-tree.cpp
  (-Os optimiztion)
  - real  0m0.181s
  - user  0m0.091s
  - sys   0m0.048s
*/

#define EXPONENT 16

int countOnBit(int n, int len, int countTable[]) {
  if (countTable[n] != -1) return countTable[n];
  
  int leftLen = len / 2;
  int rightLen = len - leftLen;

  int left  = n >> rightLen;
  int fullbit = pow(2, rightLen)-1;
  int right = n & fullbit;

  int leftCount  = countOnBit(left,  leftLen,  countTable);
  int rightCount = countOnBit(right, rightLen, countTable);
  
  return leftCount + rightCount;
}

int main () {
  int N = pow(2, EXPONENT);
  int countTable[N];
  memset(countTable, -1, sizeof(countTable));
  countTable[0] = 0; countTable[1] = 1;    
  
  FOR(i, 2, N) {
    countTable[i] = countOnBit(i, EXPONENT, countTable);
    cout << i << ':' << countTable[i] << endl;
  }

  return 0;
}
