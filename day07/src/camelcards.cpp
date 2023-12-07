#include "camelcards.h"

Round& Round::operator=(const Round &other) {
  hand = other.hand;
  bid = other.bid;
  setType();
  return *this;
}

void Round::setType() {
  m_type = getType();
  m_jokertype = getType(true);
}

HandType Round::getType(bool joker) {
  std::unordered_map<char, char> n;
  for (auto c: hand) if (n.contains(c)) n[c]++; else n[c] = 1;
  if (joker) {
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
  }
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

void CamelCards::parseLine(const std::string &s) {
  StrVec svec = tokenize_string(s);
  m_rounds.push_back(Round(svec[0], std::stoi(svec[1])));
}

long long CamelCards::totalWinnings(bool joker) {
  auto cmp = [&](const Round &a, const Round &b) {return compareHands(a, b, joker);};
  std::priority_queue<Round, std::vector<Round>, decltype(cmp)> rankedrounds(cmp);
  for (auto rnd: m_rounds) rankedrounds.push(rnd);

  std::vector<long long> winnings;
  int i = 0;
  long long sum = 0;
  Round tmp;
  while (!rankedrounds.empty()) {
    tmp = rankedrounds.top();
    sum += tmp.bid*++i;
    rankedrounds.pop();
  }

  return sum;
}

bool compareHands(const Round &a, const Round &b, bool joker) {
  // true = a "comes before" b (i.e. a is later in queue because priority queue is descending)
  const char *order = (joker)? "J23456789TQKA" : "23456789TJQKA";
  bool res = true;
  if (a.type(joker) == b.type(joker)) {
    char as, bs;
    for (int i = 0; i < 5; i++) {
      as = 0;
      while (order[as] != a.hand[i]) as++;
      bs = 0;
      while (order[bs] != b.hand[i]) bs++;
      if (as != bs) {res = as > bs; break;};
    }
  } else res = a.type(joker) > b.type(joker);
  aoc_debug(a.hand + ':' + std::to_string(a.type(joker)) + ((res)? " > " : " < " ) + b.hand + ':' + std::to_string(b.type(joker)));
  return res;
}
