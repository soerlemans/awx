#include "functions.hpp"

// STL Includes:
#include <algorithm>
#include <iostream>
#include <cctype>

// Includes:
#include "../stringify.hpp"


// Using statements:
using namespace interpreter;

namespace interpreter::builtin {
// TODO: tolower and toupper are similar
auto tolower(const Any& t_any) -> std::string
{
  std::string str{stringify(t_any)};

  std::transform(str.begin(), str.end(), str.begin(),
                 [](const unsigned char c) {
                   return std::tolower(c);
                 });
  return str;
}

auto toupper(const Any& t_any) -> std::string
{
  std::string str{stringify(t_any)};

  std::transform(str.begin(), str.end(), str.begin(),
                 [](const unsigned char c) {
                   return std::toupper(c);
                 });

  return str;
}
} // namespace interpreter::builtin
