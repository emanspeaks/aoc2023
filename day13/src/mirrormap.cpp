#include "mirrormap.h"

void MirrorMapNotes::parseLine(const std::string &s) {
  static int imap = 0;
  if (s.length()) {
    if (imap == m_mmap.size()) {m_mmap.push_back(std::make_unique<MirrorMap>());}
    m_mmap[imap].get()->parseLine(s);
  } else imap++;
}

int MirrorMapNotes::notesSummary() {
  int sum = 0;
  for (auto &mmap: m_mmap) sum += aoc_debug(patternSummary(*mmap.get()));//, m_iscolmatch, m_matchidx));
  return sum;
}

int MirrorMapNotes::repairedNotesSummary() {
  int sum = 0;
  for (auto &mmap: m_mmap) sum += aoc_debug(repairedPatternSummary(*mmap.get()));
  return sum;
}

bool colsMatch(MirrorMap &mmap, int left, int right) {
  return mmap.getCol(left) == mmap.getCol(right);
}

bool rowsMatch(MirrorMap &mmap, int up, int down) {
  return mmap.getRow(up) == mmap.getRow(down);
}

bool checkOtherCols(MirrorMap &mmap, int right) {
  int left = right - 1;
  while (left > mmap.mx() && right < mmap.px()) if (!colsMatch(mmap, --left, ++right)) return false;
  return true;
}

bool checkOtherRows(MirrorMap &mmap, int down) {
  int up = down - 1;
  while (up > mmap.my() && down < mmap.py()) if (!rowsMatch(mmap, --up, ++down)) return false;
  return true;
}

int patternSummary(MirrorMap &mmap) {//, std::vector<bool> &iscolmatch, std::vector<int> &matchidx) {
  for (int x = mmap.mx() + 1; x <= mmap.px(); x++)
    if (colsMatch(mmap, x - 1, x) && checkOtherCols(mmap, x)) return x*COLSCALAR;
  for (int y = mmap.my() + 1; y <= mmap.py(); y++)
    if (rowsMatch(mmap, y - 1, y) && checkOtherRows(mmap, y)) return y*ROWSCALAR;
  return -1;
}

int repairedPatternSummary(MirrorMap &mmap) { //, bool iscolmatch, int matchidx) {
  for (int x = mmap.mx() + 1; x <= mmap.px(); x++) if (checkColDiffs(mmap, x)) return x*COLSCALAR;
  for (int y = mmap.my() + 1; y <= mmap.py(); y++) if (checkRowDiffs(mmap, y)) return y*ROWSCALAR;
  return -1;
}

int colDiffs(MirrorMap &mmap, int left, int right) {
  return countDiffs(mmap.getCol(left), mmap.getCol(right));
}

int rowDiffs(MirrorMap &mmap, int up, int down) {
  return countDiffs(mmap.getRow(up), mmap.getRow(down));
}

int countDiffs(std::deque<char> first, std::deque<char> second) {
  int sum = 0;
  for (int i = 0; i < first.size(); i++) sum += first[i] != second[i];
  return sum;
}

bool checkColDiffs(MirrorMap &mmap, int right) {
  int left = right - 1;
  int sum = 0;
  while (left >= mmap.mx() && right <= mmap.px()) sum += colDiffs(mmap, left--, right++);
  return sum == 1;
}

bool checkRowDiffs(MirrorMap &mmap, int down) {
  int up = down - 1;
  int sum = 0;
  while (up >= mmap.my() && down <= mmap.py()) sum += rowDiffs(mmap, up--, down++);
  return sum == 1;
}
