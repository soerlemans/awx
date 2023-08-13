#include "any.hpp"

// STL Includes:
#include <iomanip>
#include <limits>
#include <sstream>

// Local Includes:
#include "overload.hpp"


using namespace interpreter;

auto Any::str() const -> std::string
{

  return std::visit(
    Overload{[](const auto& t_val) {
               std::stringstream ss;

               const auto precision{
                 std::numeric_limits<decltype(t_val)>::digits10};
               ss << std::setprecision(precision) << t_val;

               return ss.str();
             },
             [](const std::string& t_str) {
               return t_str;
             }},
    *this);
}

auto Any::num() const -> double
{
  return std::visit(Overload{[](const double t_num) {
                               return t_num;
                             },
                             [](const std::string& t_str) {
                               if(!t_str.empty()) {
                                 if(std::isdigit(t_str.front())) {
                                   return std::stod(t_str);
                                 }
                               }
                             }},
                    *this);
}
