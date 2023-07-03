#include "stringify.hpp"

// STL Includes:
#include <iomanip>
#include <limits>
#include <sstream>


auto interpreter::stringify(const Any& t_any) -> std::string
{
  return std::visit(
    Overload{[&](auto&& t_number) {
               std::stringstream ss;

               const auto precision{
                 std::numeric_limits<decltype(t_number)>::digits10};
               ss << std::setprecision(precision) << t_number;

               return ss.str();
             },
             [&](const std::string& t_str) {
               return t_str;
             }},
    t_any);
}
