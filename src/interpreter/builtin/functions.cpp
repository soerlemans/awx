#include "functions.hpp"

// STL Includes:
#include <cctype>


using namespace interpreter::builtin;


auto tolower(const Any& t_str) -> std::string
{}

auto toupper(const Any& t_any) -> std::string
{
  std::string str{stringify(t_any)};
  std::transform(str.begin(), str.end(), str.begin(),
                 [](const unsigned char c) {
                   return std::toupper(c);
                 });
  return str;
}
