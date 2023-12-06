#include <iostream>
#include <fstream>

#include "main.h"
#include "aoc.h"
#include "boatrace.h"

int main(int argc, char const *argv[]) {
  std::ifstream ifs("input.txt");
  std::string line;
  RaceRecordSet races;

  int sum = 0, sumb = 0;
  if (ifs.is_open()){
    while (ifs) {
      std::getline(ifs, line);
      if (line.length()) {
        races.parseLine(line);
      }
    }
  } else {
    std::cout << "failed to open input.txt";
    return 1;
  }
  ifs.close();

  std::cout << AOC_DAY << " A\n";
  std::cout << races.winProduct() << "\n";

  std::cout << AOC_DAY << " B\n";
  std::cout << races.winBigCount() << "\n";

  return 0;
}
