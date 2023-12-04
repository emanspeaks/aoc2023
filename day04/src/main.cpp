#include <iostream>
#include <fstream>

#include "main.h"
#include "aoc.h"
#include "scratchcard.h"

int main(int argc, char const *argv[]) {
  std::ifstream ifs("input.txt");
  std::string line;
  ScratchcardPile scp;

  int sum = 0, sumb = 0;
  if (ifs.is_open()){
    while (ifs) {
      std::getline(ifs, line);
      if (line.length()) {
        scp.parseLine(line);
      }
    }
  } else {
    std::cout << "failed to open input.txt";
    return 1;
  }

  sum = scp.scoreWinningCards();
  std::cout << AOC_DAY << " A\n";
  std::cout << sum << "\n";

  sumb = scp.countTotalWinningCards();
  std::cout << AOC_DAY << " B\n";
  std::cout << sumb << "\n";

  return 0;
}
