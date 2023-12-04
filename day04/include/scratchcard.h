#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include "aoc.h"

typedef std::unordered_set<int> NumSet;

struct Scratchcard {
  NumSet winning;
  NumSet given;
};

class ScratchcardPile {
  public:
    // Thing() {}

    void parseLine(const std::string &s);
    int scoreWinningCards();
    int countTotalWinningCardsRecursive();
    int countTotalWinningCards();

  private:
    std::vector<Scratchcard> m_pile;

    int cardWins(Scratchcard &card);
    int cardScore(Scratchcard &card);
    int countWinningCards(int i);
};
