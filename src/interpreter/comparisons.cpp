#include "comparisons.hpp"
#include <string>
#include <type_traits>


using namespace interpreter;

auto equal(const std::string& t_lhs, const std::string& t_rhs) -> bool
{
  return t_lhs == t_rhs;
}
