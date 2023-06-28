#include "stringify.hpp"

// STL Includes:
#include <iomanip>
#include <limits>
#include <sstream>


using namespace interpreter;

auto interpreter::stringify(const Any& t_any) -> std::string
{
  std::stringstream ss;

  std::visit(Overload{[&](auto&& t_number) {
                        const auto precision{
                          std::numeric_limits<decltype(t_number)>::digits10};
                        ss << std::setprecision(precision) << t_number;
                      },
                      [&](const std::string& t_str) {
                        ss << t_str;
                      }},
             t_any);

  return ss.str();
}
