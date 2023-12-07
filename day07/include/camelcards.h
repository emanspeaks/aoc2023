#pragma once

#include <string>
#include <unordered_map>

#include "aoc.h"

enum HandType {
  highcard,  // 11111  JOKER:
  onepair,   // 1112   JOKER: 1111(1)
  twopair,   // 122    JOKER: 12(2)
  threekind, // 113    JOKER: 112(1), 111(2)
  fullhouse, // 23     JOKER: 22(1), 13(1)
  fourkind,  // 14     JOKER: 13(1), 12(2), 11(3)
  fivekind   // 5      JOKER: (5), 1(4), 2(3), 3(2), 4(1),
};

struct Round {
  std::string hand;
  int bid;

  Round(): hand(""), bid(0) {}
  Round(std::string newhand, int newbid): hand(newhand), bid(newbid) {setType();}
  Round(const Round &other): Round(other.hand, other.bid) {}
  Round& operator=(const Round &other);

  const HandType type(bool joker = false) const {return (joker)? m_jokertype : m_type;}

  private:
    HandType m_type;
    HandType m_jokertype;

    HandType getType(bool joker = false);
    void setType();
};

class CamelCards {
  public:
    void parseLine(const std::string &s);
    long long totalWinnings(bool joker = false);

  private:
    std::vector<Round> m_rounds;
};

bool compareHands(const Round &a, const Round &b, bool joker = false);
