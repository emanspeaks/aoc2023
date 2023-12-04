#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string> StrVec;

StrVec tokenize_string(const std::string &s, const char delim = ' ');
const std::string trim_final_char(const std::string &s);
bool is_numeric(const char c);
