#pragma once

#include <string>

#include "aoc.h"

#define ASHCHAR '.'
#define ROCKCHAR '#'
#define COLSCALAR 1
#define ROWSCALAR 100

typedef Grid<char> MirrorMap;
typedef YData<char> MMapCol;
typedef RowData<char> MMapRow;
typedef std::vector<std::unique_ptr<MirrorMap>> MirrorMapVector;

class MirrorMapNotes {
  public:
    void parseLine(const std::string &s);
    int notesSummary();
    int repairedNotesSummary();

  private:
    MirrorMapVector m_mmap;
    // std::vector<bool> m_iscolmatch;
    // std::vector<int> m_matchidx;
};

bool colsMatch(MirrorMap &mmap, int left, int right);
bool rowsMatch(MirrorMap &mmap, int up, int down);
bool checkOtherCols(MirrorMap &mmap, int right);
bool checkOtherRows(MirrorMap &mmap, int down);
int patternSummary(MirrorMap &mmap); //, std::vector<bool> &iscolmatch, std::vector<int> &matchidx);
int repairedPatternSummary(MirrorMap &mmap); //, bool iscolmatch, int matchidx);
int colDiffs(MirrorMap &mmap, int left, int right);
int rowDiffs(MirrorMap &mmap, int up, int down);
int countDiffs(std::deque<char> first, std::deque<char> second);
bool checkColDiffs(MirrorMap &mmap, int right);
bool checkRowDiffs(MirrorMap &mmap, int down);
