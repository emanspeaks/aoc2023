#pragma once

#include <string>
#include <vector>
#include <deque>

typedef std::vector<std::string> StrVec;
typedef std::deque<std::string> StrDeq;

StrVec tokenize_string(const std::string &s, const char delim = ' ');
StrDeq tokenize_string_deque(const std::string &s, const char delim = ' ');
const std::string trim_final_char(const std::string &s);
bool is_numeric(const char c);
