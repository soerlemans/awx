#include "regex.hpp"

using namespace node::rvalue;


Regex::Regex(std::string&& t_value)
  : Literal<std::string>{std::forward<std::string>(t_value)}
{}

auto Regex::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
