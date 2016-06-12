#include <stdio.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

// one thousand 16-bit words of storage in main memory
#define MAX_RANGE 27000

bool isLeapYear(int year) {

  if (year % 400 == 0) { return true;  }
  if (year % 100 == 0) { return false; }
  if (year % 4 == 0)   { return true;  }

  return false;
}

int main () {
  int year;

  cout << "Enter the year : ";
  cin >> year;

  if (isLeapYear(year)) {
    cout << "Leap" << endl;
  } else {
    cout << "Not Leap" << endl;
  }

  return 0;
}

