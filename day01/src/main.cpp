#include <iostream>
#include <fstream>

#include "main.h"
#include "aoc.h"

int main(int argc, char const *argv[]) {
  std::ifstream ifs("input.txt");
  std::string line;

  int sum = 0, sumb = 0, sumc = 0;
  int tmp, tmpb, tmpc, i = 0;
  if (ifs.is_open()){
    while (ifs) {
      std::getline(ifs, line);
      i++;
      if (line.length()) {
        tmp = part1(line);
        tmpb = part2(line);
        tmpc = part2alt(line.c_str());
        if (tmpb != tmpc) std::cout << "line " << i << " " << line << ": " << tmpb << " != " << tmpc << "\n";

        sum += tmp;
        sumb += tmpb;
        sumc += tmpc;
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

  std::cout << "Day01B alternate solution\n";
  std::cout << sumc << "\n";

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
  return aoc_debug(10*first + last);
}

int part2alt(const char *s) {
  bool isfirst = true;
  char first, last, x, *p1 = nullptr, *p2 = nullptr, *p3 = nullptr, *p4 = nullptr;
  for (char *p = (char*)(s); *p; p++) {
    x = -1;
    switch (*p) {
      case 'e': {
        if (!p1) break;
        switch (*p1) {
          case 'e': {
            if (p2 && *p2 == 'r' && p3 && *p3 == 'h' && p4 && *p4 == 't') x = 3;
            break;
          }
          case 'n': {
            if (!p2) break;
            switch (*p2) {
              case 'i':
                if (p3 && *p3 == 'n') x = 9;
                break;

              case 'o':
                x = 1;
                break;
            }
            break;
          }
          case 'v': {
            if (p2 && *p2 == 'i' && p3 && *p3 == 'f') x = 5;
            break;
          }
        }
        break;
      }
      case 'n': {
        if (p1 && *p1 == 'e' && p2 && *p2 == 'v' && p3 && *p3 == 'e' && p4 && *p4 == 's') x = 7;
        break;
      }
      case 'o': {
        if (p1 && *p1 == 'w' && p2 && *p2 == 't') x = 2;
        break;
      }
      case 'r': {
        if (p1 && *p1 == 'u' && p2 && *p2 == 'o' && p3 && *p3 == 'f') x = 4;
        break;
      }
      case 't': {
        if (p1 && *p1 == 'h' && p2 && *p2 == 'g' && p3 && *p3 == 'i' && p4 && *p4 == 'e') x = 8;
        break;
      }
      case 'x': {
        if (p1 && *p1 == 'i' && p2 && *p2 == 's') x = 6;
        break;
      }
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      {
        x = *p - '0';
        break;
      }
    }
    if (x >= 0) {
      last = x;
      if (isfirst) {
        first = x;
        isfirst = false;
      }
    }
    p4 = p3;
    p3 = p2;
    p2 = p1;
    p1 = p;
  }
  return aoc_debug(10*first + last);
}
