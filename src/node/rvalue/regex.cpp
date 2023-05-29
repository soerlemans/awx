#include "regex.hpp"


using namespace node::rvalue;

using namespace visitor;

Regex::Regex(std::string&& t_value)
  : Literal<std::string>{std::forward<std::string>(t_value)}
{}

