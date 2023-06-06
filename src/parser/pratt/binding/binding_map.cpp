#include "binding_map.hpp"


using namespace parser::pratt::binding;

auto BindingMap::rbp(token::TokenType t_type) const -> int
{
  return this->at(t_type).second;
}

auto BindingMap::lbp(token::TokenType t_type) const -> int
{
  return this->at(t_type).first;
}
