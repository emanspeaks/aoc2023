#include <deque>

#include "hasher.h"

void Hasher::parseLine(const std::string &s) {
  m_initseq = tokenize_string(s, ',');
}

int Hasher::hashInput() {
  int sum = 0;
  for (auto s: m_initseq) sum += hashString(s);
  return sum;
}

int hashString(std::string s) {
  int tmp = 0;
  for (auto c: s) {
    tmp += c;
    tmp *= CHARSCALAR;
    tmp %= CHARMOD;
  }
  return tmp;
}

long long Hasher::hashMap() {
  std::deque<std::string> label[256];
  std::deque<int> focal[256];
  unsigned char box;
  char mode;
  const char EQUALMODE = 1, DROPMODE = -1;
  std::string lbl, tmpfocal;
  int flen, i;
  for (auto s: m_initseq) {
    lbl = "";
    tmpfocal = "";
    mode = 0;
    for (auto c: s) switch (c) {
      case EQUALCHAR: mode = EQUALMODE; break;
      case DROPCHAR: mode = DROPMODE; break;
      default: if (mode) tmpfocal += c; else lbl += c;
    }
    box = hashString(lbl);
    auto it = std::ranges::find(label[box], lbl);
    i = (it == label[box].end())? -1 : std::distance(label[box].begin(), it);
    if (mode == DROPMODE) {
      if (i >= 0) {
        label[box].erase(it);
        focal[box].erase(focal[box].begin() + i);
      }
    } else {
      flen = std::stoi(tmpfocal);
      if (i < 0) {
        label[box].push_back(lbl);
        focal[box].push_back(flen);
      } else focal[box][i] = flen;
    }
  }

  long long sum = 0;
  for (int j = 0; j < 256; j++) {
    if (!label[j].empty()) {
      aoc_debug(j);
      aoc_debug(label[j]);
      aoc_debug(focal[j]);
    }
    for (int k = 0; k < focal[j].size(); k++) sum += (j + 1)*(k + 1)*focal[j][k];
  }

  return sum;
}
