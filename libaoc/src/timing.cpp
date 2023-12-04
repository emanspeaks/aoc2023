#include "timing.h"

Epoch tic() {
  return std::chrono::steady_clock::now();
}

double toc(Epoch t0) {
  return std::chrono::duration<double>(tic() - t0).count();
}
