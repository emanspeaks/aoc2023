#pragma once

#include <string>

#include "aoc.h"

#define BLANKCHAR '.'
#define ROUNDROCK 'O'
#define SQUAREROCK '#'
#define CYCLES 1000000000

typedef std::vector<bool> RockState;

class DishPlatform {
  public:
    DishPlatform(): m_height(0) {}

    void parseLine(const std::string &s);
    int initNorthBeamLoad();
    int fullSpinCycle();

  private:
    // Grid<char> m_platform;
    int m_width, m_height;
    RockState m_round, m_sq;
    std::vector<RockState> m_roundcycle;

    int xy2idx(int x, int y);
    Coord idx2coord(int idx);
    RockState tiltNorth(const RockState &in);
    RockState tiltWest(const RockState &in);
    RockState tiltSouth(const RockState &in);
    RockState tiltEast(const RockState &in);
    int northBeamLoad(const RockState &in);
    const RockState &debugPlatform(const RockState &round) const;
    RockState spinCycle(const RockState &in);
};
