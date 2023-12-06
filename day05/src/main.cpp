#include <iostream>
#include <fstream>

#include "main.h"
#include "aoc.h"
#include "almanac.h"

int main(int argc, char const *argv[]) {
  std::ifstream ifs("input.txt");
  std::string line;
  Almanac alm;

  int sum = 0, sumb = 0;
  if (ifs.is_open()){
    while (ifs) {
      std::getline(ifs, line);
      if (line.length()) {
        alm.parseLine(line);
      }
    }
  } else {
    std::cout << "failed to open input.txt";
    return 1;
  }
  ifs.close();

  std::cout << AOC_DAY << " A\n";
  std::cout << alm.minLoc() << "\n";

  std::cout << AOC_DAY << " B\n";
  std::cout << alm.seedRangesMinLoc() << "\n";

  return 0;
}
