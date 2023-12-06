#include <iostream>
#include <fstream>

#include "main.h"
#include "aoc.h"
#include "schematic.h"

int main(int argc, char const *argv[]) {
  std::ifstream ifs("input.txt");
  std::string line;
  Schematic sch;

  int sum = 0, sumb = 0;
  if (ifs.is_open()){
    while (ifs) {
      std::getline(ifs, line);
      if (line.length()) {
        sch.parseLine(line);
      }
    }
  } else {
    std::cout << "failed to open input.txt";
    return 1;
  }
  ifs.close();

  // sch.printGrid();
  sum = sch.searchGrid(sumb);

  std::cout << "Day03A\n";
  std::cout << sum << "\n";

  std::cout << "Day03B\n";
  std::cout << sumb << "\n";

  return 0;
}
