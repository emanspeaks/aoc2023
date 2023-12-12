#include <numeric>
#include <bit>

#include "springrecords.h"

void SpringRecords::parseLine(const std::string &s) {
  StrVec svec = tokenize_string(s), errvec = tokenize_string(svec[1], ',');
  m_rec.push_back(svec[0]);
  std::vector<int> tmp;
  for (auto x: errvec) tmp.push_back(std::stoi(x));
  m_damage.push_back(tmp);
}

unsigned long long SpringRecords::recPermCount() {
  unsigned long long sum = 0;
  for (int i = 0; i < m_rec.size(); i++) {
    // aoc_debug(m_rec[i]);
    // aoc_debug(m_damage[i]);
    sum += aoc_debug(resolveRow(m_rec[i], m_damage[i]));
  }
  aoc_debug("");
  return sum;
}

unsigned long long SpringRecords::foldedRecPermCount() {
  unsigned long long sum = 0;
  // return 0;
  std::string tmp;
  std::vector<int> tmpdamage;
  for (int i = 0; i < m_rec.size(); i++) {
    tmp = m_rec[i];
    tmpdamage = m_damage[i];
    tmpdamage.reserve(5*m_damage[i].size());
    for (int j = 0; j < 4; j++) {
      tmp += UNKNOWN + m_rec[i];
      tmpdamage.insert(tmpdamage.end(), m_damage[i].begin(), m_damage[i].end());
    }
    // aoc_debug(tmp);
    // aoc_debug(tmpdamage);
    sum += aoc_debug(resolveRow(tmp, tmpdamage));
  }
  aoc_debug("");
  return sum;
}

unsigned long long resolveRow(std::string &rec, std::vector<int> &damage, int irec, int idamage, int curdamage RECSTRDEBUGARG) {
  // aoc_debug(debug);
  // aoc_debug(std::to_string(irec) + " " + std::to_string(idamage) + " " + std::to_string(curdamage));
  if (irec < rec.length()) switch (rec[irec]) {
    case UNKNOWN: return tryAddDamage(rec, damage, irec, idamage, curdamage RECSTRDEBUGPASS) + tryAddWorking(rec, damage, irec, idamage, curdamage RECSTRDEBUGPASS);
    case DAMAGED: return tryAddDamage(rec, damage, irec, idamage, curdamage RECSTRDEBUGPASS);
    case WORKING: return tryAddWorking(rec, damage, irec, idamage, curdamage RECSTRDEBUGPASS);
  }
  // if we get here, damage matched except for last character.  Just check final damage.
  int tmp = (idamage == damage.size() - 1)? curdamage == damage[idamage] : idamage == damage.size();
  // if (tmp) aoc_debug(debug + " " + std::to_string(idamage) + " " + std::to_string(curdamage));
  return tmp;
}

unsigned long long tryAddDamage(std::string &rec, std::vector<int> &damage, int irec, int idamage, int curdamage RECSTRDEBUGARG) {
  if (idamage == damage.size()) return 0;
  if (++curdamage > damage[idamage]) return 0;
  return resolveRow(rec, damage, ++irec, idamage, curdamage RECSTRDEBUGADD(DAMAGED));
}

unsigned long long tryAddWorking(std::string &rec, std::vector<int> &damage, int irec, int idamage, int curdamage RECSTRDEBUGARG) {
  if (curdamage) {
    if (curdamage != damage[idamage]) return 0;
    idamage++;
    curdamage = 0;
  }
  if (idamage > damage.size()) return 0;
  return resolveRow(rec, damage, ++irec, idamage, curdamage RECSTRDEBUGADD(WORKING));
}
