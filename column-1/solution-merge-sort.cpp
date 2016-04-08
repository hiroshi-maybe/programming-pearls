#include <stdio.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

/*
  $ clang++ -std=c++11 -stdlib=libc++ solutions-merge-sort.cpp 
  (No optimization option)
  - real 0m0.077s
  - user 0m0.044s
  - sys  0m0.008s

  $ clang++ -std=c++11 -stdlib=libc++ -Os solutions-merge-sort.cpp
  (-Os optimiztion)
  - real 0m0.087s
  - user 0m0.034s
  - sys  0m0.014s
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

string tmp_filename(int fileid) {
  return "mergesort_chunk_"+to_string(fileid)+".tmp";
}

// one thousand 16-bit words of storage in main memory
#define MAX_STORAGE_SIZE 1000
#define MAX_RANGE 27000
int storage[MAX_STORAGE_SIZE];

int create_chunks(const vector<int> nums) {
  int chunkNum = 0;
  int stidx = 0;
  for(auto n: nums) {
    storage[stidx] = n;
    stidx++;
    if (stidx == MAX_STORAGE_SIZE) {
      sort(storage, storage + stidx);
      write_nums(tmp_filename(chunkNum), vector<int>(storage, storage + stidx));
      chunkNum += 1;
      stidx = 0;
    }
  }

  if (stidx > 0) {
    sort(storage, storage + stidx);
    write_nums(tmp_filename(chunkNum), vector<int>(storage, storage + stidx));
    chunkNum += 1;
  }

  return chunkNum;
}

int fetch(ifstream &file) {
  string line;
  if (getline(file, line)) {
    istringstream iss(line);
    int n;
    if (!(iss >> n)) { return MAX_RANGE+1; }
    return n;
  }

  return MAX_RANGE+1;
}

void merge(int pairid) {
  int fileid1 = pairid*2;
  int fileid2 = pairid*2+1;
  string file1 = tmp_filename(fileid1);
  string file2 = tmp_filename(fileid2);
  // input
  ifstream infile1(file1);
  ifstream infile2(file2);

  // output
  string tmpfile = file1+".tmp";
  ofstream destfile;
  destfile.open(tmpfile);

  int i1 = fetch(infile1);
  int i2 = fetch(infile2);

  while(true) {
    // fetched all
    if (i1 > MAX_RANGE && i2 > MAX_RANGE) break;

    if (i1 <= i2) {
      destfile << i1 << '\n';
      i1 = fetch(infile1);
      continue;
    }
    if (i1 > i2) {
      destfile << i2 << '\n';
      i2 = fetch(infile2);
      continue;
    }
  }

  infile1.close();
  infile2.close();
  destfile.close();

  remove(file1.c_str());
  remove(file2.c_str());
  rename(tmpfile.c_str(), tmp_filename(pairid).c_str());
}

int merge_chunks(int chunkNum) {
  int pairid=0;
  for(; pairid<chunkNum/2; ++pairid) {
    merge(pairid);
  }
  if (chunkNum % 2 == 1) {
    int orgfileid  = chunkNum-1;
    int destfileid = pairid;
    rename(tmp_filename(orgfileid).c_str(), tmp_filename(destfileid).c_str());
  }

  return (chunkNum / 2) + (chunkNum % 2);
}

int main () {
  vector<int> inputNums = read_nums("input.dat");
  int chunkNum = create_chunks(inputNums);

  while(chunkNum > 1) {
    chunkNum = merge_chunks(chunkNum);
  }

  rename(tmp_filename(chunkNum-1).c_str(), "output.dat");
  
  return 0;
}

