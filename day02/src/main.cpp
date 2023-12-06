#include <iostream>
#include <fstream>

#include "main.h"
#include "aoc.h"

#define MAXR 12
#define MAXG 13
#define MAXB 14

int main(int argc, char const *argv[]) {
  std::ifstream ifs("input.txt");
  std::string line;

  int sum = 0, sumb = 0, pwrtmp;
  if (ifs.is_open()){
    while (ifs) {
      std::getline(ifs, line);
      if (line.length()) {
        sum += aoc_debug(parse_game(line, pwrtmp));
        sumb += pwrtmp;
      }
    }
  } else {
    std::cout << "failed to open input.txt";
    return 1;
  }
  ifs.close();

  std::cout << "Day02A\n";
  std::cout << sum << "\n";

  std::cout << "Day02B\n";
  std::cout << sumb << "\n";

  return 0;
}

int parse_game(const std::string &s, int &power) {
  StrVec svec = tokenize_string(s);
  int ntok = svec.size();
  int id = std::stoi(trim_final_char(svec[1]));
  // std::vector<int> rvec, gvec, bvec;
  int n, r, g, b, rmx, gmx, bmx;
  r = g = b = rmx = gmx = bmx = 0;
  bool failed = false;
  for (int i = 2; i < ntok; i += 2) {
    n = std::stoi(svec[i]);
    switch (svec[i + 1][0])
    {
      case 'r': r = n; rmx = std::max(rmx, r); break;
      case 'g': g = n; gmx = std::max(gmx, g); break;
      case 'b': b = n; bmx = std::max(bmx, b); break;
    }
    if (svec[i + 1].back() == ';' || i + 2 == ntok) {
      // if ((rvec.size() && *std::max_element(rvec.begin(), rvec.end()) > MAXR)
      //   || (gvec.size() && *std::max_element(gvec.begin(), gvec.end()) > MAXG)
      //   || (bvec.size() && *std::max_element(bvec.begin(), bvec.end()) > MAXB)) return 0;
      if (r > MAXR || g > MAXG || b > MAXB) failed = true;
      r = g = b = 0;
    }
  }
  power = rmx*gmx*bmx;
  return (failed)? 0 : id;
}
