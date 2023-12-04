#pragma once

#include <chrono>

typedef std::chrono::steady_clock::time_point Epoch;

Epoch tic();
double toc(Epoch t0);
