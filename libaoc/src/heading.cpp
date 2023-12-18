#include "heading.h"

Coord getNextCoord(Coord last, char head) {
  Coord next = last;
  switch (head) {
    case Heading::north: next[1]--; break;
    case Heading::south: next[1]++; break;
    case Heading::east:  next[0]++; break;
    case Heading::west:  next[0]--; break;
  }
  return next;
}
