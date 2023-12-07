#include <iostream>
#include <fstream>

#include "main.h"
#include "aoc.h"
#include "camelcards.h"

int main(int argc, char const *argv[]) {
  std::ifstream ifs("input.txt");
  std::string line;
  CamelCards cc;

  int sum = 0, sumb = 0;
  if (ifs.is_open()){
    while (ifs) {
      std::getline(ifs, line);
      if (line.length()) {
        cc.parseLine(line);
      }
    }
  } else {
    std::cout << "failed to open input.txt";
    return 1;
  }
  ifs.close();

  std::cout << AOC_DAY << " A\n";
  std::cout << cc.totalWinnings() << "\n";

  std::cout << AOC_DAY << " B\n";
  std::cout << cc.totalWinnings(true) << "\n";

  return 0;
}
