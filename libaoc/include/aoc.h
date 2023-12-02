#pragma once

#include <string>
#include <vector>

#define CAT(a, b) a##b
#define aoc_debug_proto(t) t CAT(aoc_debug_, t)(t x)
#define aoc_debug_std_proto(t) std::t CAT(aoc_debug_, t)(std::t x)

aoc_debug_proto(int);
aoc_debug_proto(char);
aoc_debug_proto(double);
aoc_debug_std_proto(string);

std::vector<std::string> tokenize_string(const std::string &s);
const std::string trim_final_char(const std::string &s);
