#include <iostream>
#include <fstream>

#include "main.h"

int main(int argc, char const *argv[]) {
  std::ifstream ifs("input.txt");
  std::string line;

  int sum = 0, sumb = 0;
  if (ifs.is_open()){

    while (ifs) {
      std::getline(ifs, line);
      if (line.length()) {
        sum += part1(line);
        sumb += part2(line);
      }
    }
  } else {
    std::cout << "failed to open input.txt";
    return 1;
  }

  std::cout << "Day01A\n";
  std::cout << sum << "\n";

  std::cout << "Day01B\n";
  std::cout << sumb << "\n";

  return 0;
}

int part1(const std::string &s) {
  bool first = true;
  char a, b, c;
  for (int i = 0; i < s.length(); i++) {
    c = s[i];
    if (c >= '0' && c <= '9') {
      b = c - '0';
      if (first) {
        a = b;
        first = false;
      }
    }
  }
  return 10*a + b;
}

int part2(const std::string &s) {
  bool isfirst = true;
  char first, last, x, c;
  std::string buf;
  for (int i = 0; i < s.length(); i++) {
    x = -1;
    c = s[i];
    if (c >= '0' && c <= '9') {
      x = c - '0';
    } else {
      if (x < 0 && i > 3) {
        buf = s.substr(i - 4, 5);
        if (buf == "three") x = 3;
        else if (buf == "seven") x = 7;
        else if (buf == "eight") x = 8;
      }
      if (x < 0 && i > 2) {
        buf = s.substr(i - 3, 4);
        if (buf == "four") x = 4;
        else if (buf == "five") x = 5;
        else if (buf == "nine") x = 9;
      }
      if (x < 0 && i > 1) {
        buf = s.substr(i - 2, 3);
        if (buf == "one") x = 1;
        else if (buf == "two") x = 2;
        else if (buf == "six") x = 6;
      }
    }
    if (x >= 0) {
      last = x;
      if (isfirst) {
        first = x;
        isfirst = false;
      }
    }
  }
  return 10*first + last;
}
