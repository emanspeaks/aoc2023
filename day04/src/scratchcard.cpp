#include <cmath>

#include "scratchcard.h"

void ScratchcardPile::parseLine(const std::string &s) {
  // Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
  StrVec svec = tokenize_string(s);
  bool inwinning = true;
  std::string x;
  Scratchcard sc;
  for (int i = 2; i < svec.size(); i++) {
    x = svec[i];
    if (!x.length()) continue;
    if (x == "|") inwinning = false;
    else if (inwinning) sc.winning.insert(std::stoi(x));
    else sc.given.insert(std::stoi(x));
  }
  m_pile.push_back(sc);
}

int ScratchcardPile::scoreWinningCards() {
  int sum = 0;
  for (auto c: m_pile) sum += cardScore(c);
  return sum;
}

int ScratchcardPile::cardWins(Scratchcard &card) {
  int wins = 0;
  for (auto x: card.given) if (card.winning.contains(x)) wins++;
  return wins;
}

int ScratchcardPile::cardScore(Scratchcard &card) {
  int wins = cardWins(card);
  return (!!wins)*pow(2, wins - 1);
}

int ScratchcardPile::countTotalWinningCardsRecursive() {
  int sum = 0;
  int n = m_pile.size();
  for (int i = 0; i < n; i++) sum += countWinningCards(aoc_debug(i)) + 1;
  return sum;
}

int ScratchcardPile::countWinningCards(int i) {
  int wins = cardWins(m_pile[i]);
  int sum = wins;
  for (int j = 0; j < wins; j++) sum += countWinningCards(aoc_debug(i + j + 1));
  return sum;
}

int ScratchcardPile::countTotalWinningCards() {
  int sum = 0;
  int n = m_pile.size();
  std::vector<int> wins, copies;
  for (auto c: m_pile) {
    copies.push_back(1);
    wins.push_back(cardWins(c));
  }
  for (int i = 0; i < n; i++) {
    sum += copies[i];
    for (int j = 0; j < wins[i]; j++) copies[i + j + 1] += copies[i];
  }
  return sum;
}
