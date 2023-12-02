#pragma once

#include <string>

#define CAT(a, b) a##b
#define aoc_debug_proto(t) t CAT(aoc_debug_, t)(t x)
#define aoc_debug_std_proto(t) std::t CAT(aoc_debug_, t)(std::t x)

aoc_debug_proto(int);
aoc_debug_proto(char);
aoc_debug_proto(double);
aoc_debug_std_proto(string);
