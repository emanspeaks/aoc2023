#include <iostream>
#include <fstream>

#include "main.h"
#include "aoc.h"
#include "digplan.h"

int main(int argc, char const *argv[]) {
  ConsoleUTF8 set_console_to_utf8;
  std::ifstream ifs("input.txt");
  std::string line;
  DigPlan dp;

  aoc_debug_open();

  int sum = 0, sumb = 0;
  if (ifs.is_open()){
    while (ifs) {
      std::getline(ifs, line);
      if (line.length()) {
        dp.parseLine(line);
      }
    }
  } else {
    std::cout << "failed to open input.txt";
    return 1;
  }
  ifs.close();

  std::cout << AOC_DAY << " A\n";
  std::cout << dp.simpleLagoonArea() << "\n";

  std::cout << AOC_DAY << " B\n";
  std::cout << sumb << "\n";

  aoc_debug_close();
  return 0;
}
