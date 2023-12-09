#include <iostream>
#include <fstream>

#include "main.h"
#include "aoc.h"
#include "oasis.h"

int main(int argc, char const *argv[]) {
  aoc_debug_open();
  std::ifstream ifs("input.txt");
  std::string line;
  Oasis oas;

  int sum = 0, sumb = 0;
  if (ifs.is_open()){
    while (ifs) {
      std::getline(ifs, line);
      if (line.length()) {
        oas.parseLine(line);
      }
    }
  } else {
    std::cout << "failed to open input.txt";
    return 1;
  }
  ifs.close();

  std::cout << AOC_DAY << " A\n";
  std::cout << oas.extrapolatedSum() << "\n";

  std::cout << AOC_DAY << " B\n";
  std::cout << oas.extrapolatedBackSum() << "\n";

  aoc_debug_close();
  return 0;
}
