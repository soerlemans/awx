#include "regex.hpp"


Regex::Regex(std::string&& t_value): Node{std::forward<std::string>(t_value)}
{}

auto Regex::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
