#include <iostream>
#include <fstream>

#include "main.h"

int main(int argc, char const *argv[]) {
  std::cout << "Day01A\n";

  std::ifstream ifs("input.txt");
  std::string line;

  if (ifs.is_open()){
    while (ifs) {
      std::getline(ifs, line);
      if (line.length()) {
        std::cout << line << "\n";
      }
    }
  } else {
    std::cout << "failed to open input.txt";
    return 1;
  }

  std::cout << "Day01B\n";

  std::cout << 0 << "\n";

  return 0;
}
