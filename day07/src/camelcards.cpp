#include "camelcards.h"

HandType CamelRound::getType(std::string newhand) {
  std::unordered_map<char, char> n;
  for (auto c: newhand) if (n.contains(c)) n[c]++; else n[c] = 1;
  char pairs = 0, triple = 0;
  for (auto& [k, v]: n) {
    switch (v) {
      case 5: {return HandType::fivekind; break;}
      case 4: {return HandType::fourkind; break;}
      case 3: {triple = 1; break;}
      case 2: {pairs++; break;}
    }
  }
  if (triple) return (pairs)? HandType::fullhouse : HandType::threekind;
  else if (pairs == 2) return HandType::twopair;
  else if (pairs) return HandType::onepair;
  return HandType::highcard;
}

HandType JokerCamelRound::getType(std::string newhand) {
  std::unordered_map<char, char> n;
  for (auto c: newhand) if (n.contains(c)) n[c]++; else n[c] = 1;
  char pairs = 0, triple = 0;
  if (n.contains('J')) {
    char maxk, maxv = 0;
    for (auto& [k, v]: n) {
      if (k == 'J') continue;
      if (v > maxv) {
        maxv = v;
        maxk = k;
      }
    }
    n[maxk] += n['J'];
    n['J'] = 0;
  }
  for (auto& [k, v]: n) {
    switch (v) {
      case 5: {return HandType::fivekind; break;}
      case 4: {return HandType::fourkind; break;}
      case 3: {triple = 1; break;}
      case 2: {pairs++; break;}
    }
  }
  if (triple) return (pairs)? HandType::fullhouse : HandType::threekind;
  else if (pairs == 2) return HandType::twopair;
  else if (pairs) return HandType::onepair;
  return HandType::highcard;
}

void CamelCards::parseLine(const std::string &s) {
  StrVec svec = tokenize_string(s);
  CamelRound tmp(svec[0], std::stoi(svec[1]));
  m_rounds.push_back(tmp);

  JokerCamelRound jtmp(svec[0], std::stoi(svec[1]));
  m_jokerrounds.push_back(jtmp);
}

long long CamelCards::totalWinnings() {
  auto cmp = [&](const CamelRound &a, const CamelRound &b) {return compareHands(a, b, STRENGTH);};
  std::priority_queue<CamelRound, std::vector<CamelRound>, decltype(cmp)> rankedrounds(cmp);
  for (auto rnd: m_rounds) rankedrounds.push(rnd);

  std::vector<long long> winnings;
  int i = 0;
  long long sum = 0;
  CamelRound tmp;
  while (!rankedrounds.empty()) {
    tmp = rankedrounds.top();
    sum += tmp.bid*++i;
    rankedrounds.pop();
  }

  return sum;
}

long long CamelCards::totalJokerWinnings() {
  auto cmp = [&](const JokerCamelRound &a, const JokerCamelRound &b) {return compareHands(a, b, JOKERSTRENGTH);};
  std::priority_queue<JokerCamelRound, std::vector<JokerCamelRound>, decltype(cmp)> rankedrounds(cmp);
  for (auto rnd: m_jokerrounds) rankedrounds.push(rnd);

  std::vector<long long> winnings;
  int i = 0;
  long long sum = 0;
  CamelRound tmp;
  while (!rankedrounds.empty()) {
    tmp = rankedrounds.top();
    sum += tmp.bid*++i;
    rankedrounds.pop();
  }

  return sum;
}

bool compareHands(const CamelRound &a, const CamelRound &b, const char order[]) {
  // true = a "comes before" b (i.e. a is later in queue because priority queue is descending)
  bool res = true;
  if (a.type == b.type) {
    char as, bs;
    for (int i = 0; i < 5; i++) {
      as = 0;
      while (order[as] != a.hand[i]) as++;
      bs = 0;
      while (order[bs] != b.hand[i]) bs++;
      if (as != bs) {res = as > bs; break;};
    }
  } else res = a.type > b.type;
  aoc_debug(a.hand + ':' + std::to_string(a.type) + ((res)? " > " : " < " ) + b.hand + ':' + std::to_string(b.type));
  return res;
}
