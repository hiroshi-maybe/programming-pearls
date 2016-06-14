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

#define nonLeapYearDays 365
vector<int> nonLeapDays = { 31, 28, 31, 30, 31, 30, 31, 30, 31, 31, 30, 31 };
#define leapYearDays 366
vector<int> leapDays    = { 31, 29, 31, 30, 31, 30, 31, 30, 31, 31, 30, 31 };

int daysForYear(int year) {
  return isLeapYear(year) ? leapYearDays : nonLeapYearDays;
}

vector<int> monthDaysForYear(int year) {
  return isLeapYear(year) ? leapDays : nonLeapDays;
}

int fullYearDays(int year1, int year2) {
  int yearSmall = year1 < year2 ? year1 : year2;
  int yearLarge = year1 < year2 ? year2 : year1;

  int current = yearSmall + 1;
  int days = 0;
  while(current < yearLarge) {
    days += daysForYear(current);
    current += 1;
  }

  return days;
}

int fullMonthDays(int year, int month1, int month2) {
  int monthSmall = month1 < month2 ? month1 : month2;
  int monthLarge = month1 < month2 ? month2 : month1;

  monthSmall = max(monthSmall,  1);
  monthSmall = min(monthSmall, 12);
  monthLarge = max(monthLarge,  1);
  monthLarge = min(monthLarge, 12);
  
  int current = monthSmall + 1;
  int days = 0;
  auto yearDays = monthDaysForYear(year);
  
  while(current < monthLarge) {
    days += yearDays[current-1];
    current += 1;
  }
  
  return days;  
}

int daysBetween(int year, int month1, int day1, int month2, int day2) {
  // TODO: day range validation
  if (month1 == month2) {
    return abs(day1 - day2);
  }

  // 6/14-6/14 => 0 day
  auto yearDays = monthDaysForYear(year);
  int m1days = daysBetween(year, month1, day1, month1, yearDays[month1-1]+1);
  int m2days = daysBetween(year, month2,    0, month2,             day2);

  return m1days + fullMonthDays(year, month1, month2) + m2days;
}

int main () {
  int year1, month1, day1,
      year2, month2, day2;

  cout << "Enter two dates (mm/dd/YYYY-mm/dd/YYYY): ";
  scanf ("%d/%d/%d-%d/%d/%d",&month1, &day1, &year1, &month2, &day2, &year2);

  int days = 0;
  if (year1 == year2) {
    days = daysBetween(year1, month1, day1, month2, day2);
  } else {
    days += fullYearDays(year1, year2);
    days += daysBetween(year1, month1, day1,     12,   32);
    days += daysBetween(year2, 1,         0, month2, day2);
  }
  cout << days << endl;  

  return 0;
}
