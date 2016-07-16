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
  $ clang++ -std=c++11 -stdlib=libc++ -Os solution-8.2-bitCountTable-linear.cpp
  (-Os optimiztion)
  - real  0m0.182s
  - user  0m0.093s
  - sys   0m0.050s
*/

#define EXPONENT 16

int main () {
  int N = pow(2, EXPONENT);
  int countTable[N];
  memset(countTable, -1, sizeof(countTable));
  countTable[0] = 0;
  
  FOR(i, 1, EXPONENT+1) {
    int prev = pow(2, i-1);
    FOR(j, pow(2, i-1), pow(2, i)) {
      countTable[j] = countTable[j-prev] + 1;
      cout << j << ':' << countTable[j] << endl;
    }
  }

  return 0;
}
