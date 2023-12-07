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

const char STRENGTH[] = "23456789TJQKA";
const char JOKERSTRENGTH[] = "J23456789TQKA";

struct CamelRound {
  std::string hand;
  int bid;
  HandType type;

  CamelRound(): hand(""), bid(0), type(HandType::highcard) {}
  CamelRound(std::string newhand, int newbid): hand(newhand), bid(newbid), type(getType(newhand)) {}
  CamelRound(std::string newhand, int newbid, HandType newtype): hand(newhand), bid(newbid), type(newtype) {}

  private:
    HandType getType(std::string newhand);
};

struct JokerCamelRound: CamelRound {
  JokerCamelRound(std::string newhand, int newbid): CamelRound(newhand, newbid, getType(newhand)) {}

  private:
    HandType getType(std::string newhand);
};

class CamelCards {
  public:
    void parseLine(const std::string &s);
    long long totalWinnings();
    long long totalJokerWinnings();

  private:
    std::vector<CamelRound> m_rounds;
    std::vector<JokerCamelRound> m_jokerrounds;
};

bool compareHands(const CamelRound &a, const CamelRound &b, const char order[]);
