#ifndef AWX_NODE_RVALUE_REGEX_HPP
#define AWX_NODE_RVALUE_REGEX_HPP

#include "literal.hpp"


namespace node::rvalue {
class Regex : public Literal<std::string> {
  public:
  Regex(std::string&& t_value);

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Regex() override = default;
};
} // namespace node::rvalue

#endif // AWX_NODE_RVALUE_REGEX_HPP
