#pragma once

#include <string>
#include <deque>
#include <vector>
#include <unordered_map>

#include "aoc.h"

#define WORKING '.'
#define DAMAGED '#'
#define UNKNOWN '?'

// #define RECSTRDEBUG

#ifdef RECSTRDEBUG
  #define RECSTRDEBUGARG , std::string debug
  #define RECSTRDEBUGARGDEF RECSTRDEBUGARG = ""
  #define RECSTRDEBUGPASS , debug
  #define RECSTRDEBUGADD(x) , debug + x
#else
  #define RECSTRDEBUGARG
  #define RECSTRDEBUGARGDEF
  #define RECSTRDEBUGPASS
  #define RECSTRDEBUGADD(x)
#endif

typedef std::unordered_map<std::string, unsigned long long> MemoMap;

class SpringRecords {
  public:
    void parseLine(const std::string &s);

    unsigned long long recPermCount();
    unsigned long long foldedRecPermCount();

  private:
    StrVec m_rec;
    std::vector<std::vector<int>> m_damage;
};

unsigned long long resolveRow(std::string &rec, std::vector<int> &damage);
unsigned long long resolveRow(std::string &rec, std::vector<int> &damage, MemoMap &memo,
  int irec = 0, int idamage = 0, int curdamage = 0 RECSTRDEBUGARGDEF);
unsigned long long tryAddDamage(std::string &rec, std::vector<int> &damage, MemoMap &memo,
  int irec, int idamage, int curdamage RECSTRDEBUGARG);
unsigned long long tryAddWorking(std::string &rec, std::vector<int> &damage, MemoMap &memo,
  int irec, int idamage, int curdamage RECSTRDEBUGARG);
std::string argHash(int irec, int idamage, int curdamage);
