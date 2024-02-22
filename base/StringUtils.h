#pragma once

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace olc {
namespace base {

void str_tolower(std::string &s);

void str_join(std::vector<std::string> &v, std::string &s,
              const std::string &dot);

void str_split(std::vector<std::string> &v, std::string &input,
               const std::string &dot);

bool str_equals(std::string s1, std::string s2, bool case_sensitivity);

} // namespace base
} // namespace olc
